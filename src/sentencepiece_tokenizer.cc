/*!
 *  Copyright (c) 2023 by Contributors
 * \file sentencepiece_tokenizer.cc
 * \brief Sentencepice tokenizer
 */
#include <tokenizers_cpp.h>

#include "sentencepiece_processor.h"

namespace tokenizers {

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

 private:
  // the tokenizer
  sentencepiece::SentencePieceProcessor sentence_piece_;
};

std::unique_ptr<Tokenizer> Tokenizer::FromBlobSentencePiece(const std::string& model_blob) {
  return std::make_unique<SentencePieceTokenizer>(model_blob);
}
}  // namespace tokenizers
