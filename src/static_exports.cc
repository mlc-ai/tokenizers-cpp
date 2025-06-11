#include "tokenizers_cpp.h"

// export LoadBlobJsonAndEncode(const std::string &, const std::string &, std::vector<int32_t> &)
extern "C" __declspec(dllexport) void LoadBlobJsonAndEncode(const std::string& json_blob, const std::string& text, std::vector<int32_t>& token_ids)
{
  auto tokenizer = tokenizers::Tokenizer::FromBlobJSON(json_blob);
  token_ids = tokenizer->Encode(text);
  return;
}

// export LoadBlobJsonAndEncodeBatch(const std::string &, const std::vector<std::string> &, std::vector<std::vector<int32_t>> &)
extern "C" __declspec(dllexport) void LoadBlobJsonAndEncodeBatch(const std::string& json_blob, const std::vector<std::string>& texts, std::vector<std::vector<int32_t>>& token_ids_batch)
{
  auto tokenizer = tokenizers::Tokenizer::FromBlobJSON(json_blob);
  token_ids_batch = tokenizer->EncodeBatch(texts);
  return;
}

// export LoadBlobSentencePieceAndEncode(const std::string &, const std::string &, std::vector<int32_t> &)
extern "C" __declspec(dllexport) void LoadBlobSentencePieceAndEncode(const std::string& model_blob, const std::string& text, std::vector<int32_t>& token_ids)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobSentencePiece(model_blob);
    token_ids = tokenizer->Encode(text);
    return;
}

// export LoadBlobSentencePieceAndEncodeBatch(const std::string &, const std::vector<std::string> &, std::vector<std::vector<int32_t>> &)
extern "C" __declspec(dllexport) void LoadBlobSentencePieceAndEncodeBatch(const std::string& model_blob, const std::vector<std::string>& texts, std::vector<std::vector<int32_t>>& token_ids_batch)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobSentencePiece(model_blob);
    token_ids_batch = tokenizer->EncodeBatch(texts);
    return;
}

// export LoadBlobRWKVWorldAndEncode(const std::string &, const std::string &, std::vector<int32_t> &)
extern "C" __declspec(dllexport) void LoadBlobRWKVWorldAndEncode(const std::string& model_blob, const std::string& text, std::vector<int32_t>& token_ids)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobRWKVWorld(model_blob);
    token_ids = tokenizer->Encode(text);
    return;
}

// export LoadBlobRWKVWorldAndEncodeBatch(const std::string &, const std::vector<std::string> &, std::vector<std::vector<int32_t>> &)
extern "C" __declspec(dllexport) void LoadBlobRWKVWorldAndEncodeBatch(const std::string& model_blob, const std::vector<std::string>& texts, std::vector<std::vector<int32_t>>& token_ids_batch)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobRWKVWorld(model_blob);
    token_ids_batch = tokenizer->EncodeBatch(texts);
    return;
}

// export LoadBlobByteLevelBPEAndEncode(const std::string &, const std::string &, const std::string &, const std::string &, std::vector<int32_t> &)
extern "C" __declspec(dllexport) void LoadBlobByteLevelBPEAndEncode(const std::string& vocab_blob, const std::string& merges_blob, const std::string& added_tokens, const std::string& text, std::vector<int32_t>& token_ids)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobByteLevelBPE(vocab_blob, merges_blob, added_tokens);
    token_ids = tokenizer->Encode(text);
    return;
}

// export LoadBlobByteLevelBPEAndEncodeBatch(const std::string &, const std::string &, const std::string &, const std::vector<std::string> &, std::vector<std::vector<int32_t>> &)
extern "C" __declspec(dllexport) void LoadBlobByteLevelBPEAndEncodeBatch(const std::string& vocab_blob, const std::string& merges_blob, const std::string& added_tokens, const std::vector<std::string>& texts, std::vector<std::vector<int32_t>>& token_ids_batch)
{
    auto tokenizer = tokenizers::Tokenizer::FromBlobByteLevelBPE(vocab_blob, merges_blob, added_tokens);
    token_ids_batch = tokenizer->EncodeBatch(texts);
    return;
}