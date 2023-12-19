/*!
 *  Copyright (c) 2023 by Contributors
 * \file rwkv_world_tokenizer.cpp
 * \brief Implementation of llm chat.
 */
#include "rwkv_world_tokenizer.h"

#include <tokenizers_cpp.h>

#include <fstream>
#include <msgpack.hpp>

namespace tokenizers {

struct TrieTree {
  std::unordered_map<int, std::unique_ptr<TrieTree>> children;
  std::string word;
  std::optional<int> token_id;

  TrieTree(const std::unordered_map<std::string, int>& word2id) {
    for (auto& pair : word2id) {
      add_word(pair.first, pair.second);
    }
  }

  std::pair<std::string, int> find_longest_prefix(const std::string& str) const {
    std::string prefix;
    int token_id = -1;
    const TrieTree* node = this;
    for (int i = 0; i < str.size(); ++i) {
      auto it = node->children.find(str[i]);
      if (it == node->children.end()) {
        break;
      }
      node = it->second.get();
      RV_CHECK(node != nullptr);
      if (node->token_id.has_value()) {
        prefix = node->word;
        token_id = node->token_id.value();
      }
    }
    RV_CHECK(!prefix.empty());
    RV_CHECK(token_id != -1);
    return {prefix, token_id};
  }

 private:
  TrieTree() = default;
  void add_word(const std::string& word, int token_id) { return _add_word(word, token_id, 0); }
  void _add_word(const std::string& word, int token_id, int idx) {
    if (idx == word.size()) {
      this->word = word;
      this->token_id = token_id;
      return;
    }
    auto& child = children[word[idx]];
    if (!child) {
      child = std::unique_ptr<TrieTree>(new TrieTree());
    }
    child->_add_word(word, token_id, idx + 1);
  }
};

class RWKVWorldTokenizer : public Tokenizer {
 public:
  explicit RWKVWorldTokenizer(const std::string& path) {
    std::ifstream infile;
    infile.open(path, std::ios::binary | std::ios::in);
    infile.seekg(0, std::ios::end);
    int64_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);
    char* data = new char[length];
    infile.read(data, length);
    infile.close();

    auto unpacker = msgpack::unpack(data, length);
    auto obj = unpacker.get();
    delete[] data;
    _idx2word = obj.as<std::unordered_map<int, std::string>>();
    for (auto& pair : _idx2word) {
      _word2idx[pair.second] = pair.first;
    }
    _tree = std::make_unique<TrieTree>(_word2idx);
  }

  std::vector<int32_t> Encode(const std::string& str) final {
    std::vector<int> ids;
    int str_idx = 0;

    while (str_idx < str.size()) {
      auto [prefix, token_id] = _tree->find_longest_prefix(str.substr(str_idx));
      ids.push_back(token_id);
      str_idx += prefix.size();
    }
    return ids;
  }

  std::string Decode(const std::vector<int32_t>& ids) final {
    std::string str;
    for (auto id : ids) {
      str += IdToToken(id);
    }
    return str;
  }

  size_t GetVocabSize() final {
    auto size = _idx2word.size();
    RV_CHECK(size > 0);
    return size;
  }

  virtual std::string IdToToken(int32_t token_id) final {
    RV_CHECK(_idx2word.size() > 0);
    auto it = _idx2word.find(token_id);
    if (it == _idx2word.end()) {
      return "<unk>";
    } else {
      return it->second;
    }
  }

  int32_t TokenToId(const std::string& token) final {
    RV_CHECK(_word2idx.size() > 0);
    auto it = _word2idx.find(token);
    if (it == _word2idx.end()) {
      return -1;
    } else {
      return it->second;
    }
  }

 private:
  // the tokenizer
  std::unordered_map<std::string, int> _word2idx;
  std::unordered_map<int, std::string> _idx2word;
  std::unique_ptr<TrieTree> _tree;
};

std::unique_ptr<Tokenizer> Tokenizer::FromBlobRWKVWorld(const std::string& model_blob) {
  return std::make_unique<RWKVWorldTokenizer>(model_blob);
}

}  // namespace tokenizers
