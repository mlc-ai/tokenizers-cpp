import { Tokenizer } from "@mlc-ai/web-tokenizers";

async function testJSONTokenizer() {
  console.log("JSON Tokenizer");
  const jsonBuffer = await (await
    fetch("https://huggingface.co/openai/clip-vit-large-patch14/raw/main/tokenizer.json")
  ).arrayBuffer();

  const tok = await Tokenizer.fromJSON(jsonBuffer);
  const text = "What is the capital of Canada?";
  const ids = tok.encode(text);
  console.log("ids=" + ids)
  const decodedText = tok.decode(ids);
  console.log("decoded=" + decodedText);

  const vocabSize = tok.getVocabSize();
  console.log("vocabSize=" + vocabSize);

  const tok0 = tok.idToToken(0);
  console.log("tok0=" + tok0);
  if (tok0 !== "!") {
    throw Error("Expect token 0 to be !");
  }

  const tok49407 = tok.idToToken(49407);
  console.log("tok49407=" + tok49407);
  if (tok49407 !== "<|endoftext|>") {
    throw Error("Expect token 49407 to be <|endoftext|>");
  }
}

async function testLlamaTokenizer() {
  console.log("Llama Tokenizer");
  const modelBuffer = await (await
    fetch("https://huggingface.co/hongyij/web-llm-test-model/resolve/main/tokenizer.model")
  ).arrayBuffer();
  const tok = await Tokenizer.fromSentencePiece(modelBuffer);
  const text = "What is the capital of Canada?";
  const ids = tok.encode(text);
  console.log("ids=" + ids)
  const decodedText = tok.decode(ids);
  console.log("decoded=" + decodedText);

  const vocabSize = tok.getVocabSize();
  console.log("vocabSize=" + vocabSize);
  if (vocabSize !== 32000) {
    throw Error("Expect Llama to have vocab size 32000");
  }
}

// Without COMPILE_WASM_RUNTIME, this triggers parallel processing, leading to error
async function testBertTokenizer() {
  console.log("Bert Tokenizer");
  const modelBuffer = await (await
    fetch("https://huggingface.co/Snowflake/snowflake-arctic-embed-l/raw/main/tokenizer.json")
  ).arrayBuffer();
  const tok = await Tokenizer.fromJSON(modelBuffer);
  const text = "What is the capital of Canada?";
  const ids = tok.encode(text);
  console.log(ids);
}

async function main() {
  await testJSONTokenizer()
  await testBertTokenizer();
  await testLlamaTokenizer()
}

main()
