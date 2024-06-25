/*!
 *  Copyright (c) 2023 by Contributors
 * \file sentencepiece_tokenizer.cc
 * \brief Sentencepice tokenizer
 */
#include <sentencepiece_processor.h>
#include <tokenizers_cpp.h>

#include <cassert>

namespace tokenizers {

#ifdef MLC_ENABLE_SENTENCEPIECE_TOKENIZER
class SentencePieceTokenizer : public Tokenizer {
 public:
  explicit SentencePieceTokenizer(const std::string& model_blob) {
    sentence_piece_.LoadFromSerializedProto(model_blob);
  }

  std::vector<int32_t> Encode(const std::string& text) final {
    std::vector<int32_t> tokens;
    sentence_piece_.Encode(text, &tokens).IgnoreError();
    return tokens;
  }

  std::string Decode(const std::vector<int32_t>& ids) final {
    std::string text;
    sentence_piece_.Decode(ids, &text).IgnoreError();
    return text;
  }

  size_t GetVocabSize() final {
    auto size = sentence_piece_.GetPieceSize();
    assert(size > 0);
    return size;
  }

  std::string IdToToken(int32_t id) final { return sentence_piece_.IdToPiece(id); }

  int32_t TokenToId(const std::string& token) final { return sentence_piece_.PieceToId(token); }

 private:
  // the tokenizer
  sentencepiece::SentencePieceProcessor sentence_piece_;
};

std::unique_ptr<Tokenizer> Tokenizer::FromBlobSentencePiece(const std::string& model_blob) {
  return std::make_unique<SentencePieceTokenizer>(model_blob);
}
#else
std::unique_ptr<Tokenizer> Tokenizer::FromBlobSentencePiece(const std::string& model_blob) {
  assert(false);
  throw;
}
#endif  // MLC_ENABLE_SENTENCEPIECE_TOKENIZER

}  // namespace tokenizers
