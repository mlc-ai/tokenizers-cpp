/*!
 *  Copyright (c) 2023 by Contributors
 * \file rwkv_world_tokenizer.cpp
 * \brief Implementation of llm chat.
 */
#include <tokenizers_cpp.h>
#include "rwkv_world_tokenizer.h"

#include <iostream>
#include <fstream>
#include <string_view>
#include <msgpack.hpp>

namespace tokenizers {

RWKVWorldToolTokenizer::RWKVWorldToolTokenizer(const std::string &path) {
  std::ifstream infile;
  infile.open(path, std::ios::binary | std::ios::in);
  infile.seekg(0, std::ios::end);
  int64_t length = infile.tellg();
  infile.seekg(0, std::ios::beg);
  char *data = new char[length];
  infile.read(data, length);
  infile.close();

  auto unpacker = msgpack::unpack(data, length);
  auto obj = unpacker.get();
  _idx2word = obj.as<std::unordered_map<int, std::string>>();
  for (auto &pair : _idx2word) {
    _word2idx[pair.second] = pair.first;
  }
}

std::vector<int> RWKVWorldToolTokenizer::encode(std::string_view str) const {
  std::vector<int> ids;
  int str_idx = 0;
  int word_len = 1;
  int id = 0;
  while (str_idx < str.size()) {
    if (str_idx + word_len > str.size()) {
      ids.push_back(id);
      break;
    }
    auto substr = str.substr(str_idx, word_len);
    auto it = _word2idx.find(std::string(substr));
    if (it == _word2idx.end()) {
      ids.push_back(id);
      str_idx += (word_len - 1);
      word_len = 1;
    } else {
      id = it->second;
      word_len++;
    }
  }
  return ids;
}

std::string RWKVWorldToolTokenizer::decode(int id) const {
  auto it = _idx2word.find(id);
  if (it == _idx2word.end()) {
    return "<unk>";
  } else {
    return it->second;
  }
}

std::string RWKVWorldToolTokenizer::decode(const std::vector<int> &ids) const {
  std::string str;
  for (auto id : ids) {
    str += decode(id);
  }
  return str;
}

RWKVWorldToolTokenizer createRWKVWorldToolTokenizer(const std::string &path) {
    return RWKVWorldToolTokenizer(path);
}

class RWKVWorldTokenizer : public Tokenizer {
 public:
  explicit RWKVWorldTokenizer(const std::string& model_blob) : rwkv_world_tokenizer_(model_blob) {
  }

  std::vector<int32_t> Encode(const std::string& text) final {
    return rwkv_world_tokenizer_.encode(text);
  }

  std::string Decode(const std::vector<int32_t>& ids) final {
    return rwkv_world_tokenizer_.decode(ids);
  }

 private:
  // the tokenizer
  RWKVWorldToolTokenizer rwkv_world_tokenizer_;
};

std::unique_ptr<Tokenizer> Tokenizer::FromBlobRWKVWorld(const std::string& model_blob) {
  return std::make_unique<RWKVWorldTokenizer>(model_blob);
}

} // namespace tokenizers
