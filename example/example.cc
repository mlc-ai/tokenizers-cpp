#include <tokenizers_cpp.h>

#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using tokenizers::Tokenizer;

std::string LoadBytesFromFile(const std::string& path) {
  std::ifstream fs(path, std::ios::in | std::ios::binary);
  if (fs.fail()) {
    std::cerr << "Cannot open " << path << std::endl;
    exit(1);
  }
  std::string data;
  fs.seekg(0, std::ios::end);
  size_t size = static_cast<size_t>(fs.tellg());
  fs.seekg(0, std::ios::beg);
  data.resize(size);
  fs.read(data.data(), size);
  return data;
}

void PrintEncodeResult(const std::vector<int>& ids) {
  std::cout << "tokens=[";
  for (size_t i = 0; i < ids.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << ids[i];
  }
  std::cout << "]" << std::endl;
}

void TestTokenizer(std::unique_ptr<Tokenizer> tok, bool print_vocab = false,
                   bool check_id_back = true) {
  // Check #1. Encode and Decode
  std::string prompt = "What is the  capital of Canada?";
  std::vector<int> ids = tok->Encode(prompt);
  std::string decoded_prompt = tok->Decode(ids);
  PrintEncodeResult(ids);
  std::cout << "decode=\"" << decoded_prompt << "\"" << std::endl;
  assert(decoded_prompt == prompt);

  // Check #2. IdToToken and TokenToId
  std::vector<int32_t> ids_to_test = {0, 1, 2, 3, 32, 33, 34, 130, 131, 1000};
  for (auto id : ids_to_test) {
    auto token = tok->IdToToken(id);
    auto id_new = tok->TokenToId(token);
    std::cout << "id=" << id << ", token=\"" << token << "\", id_new=" << id_new << std::endl;
    if (check_id_back) {
      assert(id == id_new);
    }
  }

  // Check #3. GetVocabSize
  auto vocab_size = tok->GetVocabSize();
  std::cout << "vocab_size=" << vocab_size << std::endl;

  std::cout << std::endl;
}

// Sentencepiece tokenizer
// - dist/tokenizer.model
void SentencePieceTokenizerExample() {
  std::cout << "Tokenizer: SentencePiece" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  // Read blob from file.
  auto blob = LoadBytesFromFile("dist/tokenizer.model");
  // Note: all the current factory APIs takes in-memory blob as input.
  // This gives some flexibility on how these blobs can be read.
  auto tok = Tokenizer::FromBlobSentencePiece(blob);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "Load time: " << duration << " ms" << std::endl;

  TestTokenizer(std::move(tok), false, true);
}

// HF tokenizer
// - dist/tokenizer.json
void HuggingFaceTokenizerExample() {
  std::cout << "Tokenizer: Huggingface" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  // Read blob from file.
  auto blob = LoadBytesFromFile("dist/tokenizer.json");
  // Note: all the current factory APIs takes in-memory blob as input.
  // This gives some flexibility on how these blobs can be read.
  auto tok = Tokenizer::FromBlobJSON(blob);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "Load time: " << duration << " ms" << std::endl;

  TestTokenizer(std::move(tok), false, true);
}

// RWKV world tokenizer
// - dist/tokenizer_model
void RWKVWorldTokenizerExample() {
  std::cout << "Tokenizer: RWKVWorld" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  auto tok = Tokenizer::FromBlobRWKVWorld("dist/tokenizer_model");

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "Load time: " << duration << " ms" << std::endl;

  // We cannot check id back for RWKVWorldTokenizer yet.
  TestTokenizer(std::move(tok), false, false);
}

int main(int argc, char* argv[]) {
  SentencePieceTokenizerExample();
  HuggingFaceTokenizerExample();
  RWKVWorldTokenizerExample();
}
