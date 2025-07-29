#/bin/bash
echo "Usage: $0 (ENABLE_SENTENCEPIECE_TOKENIZER default value 1=ON)"
# build
mkdir -p build
cd build
echo
echo "cmake ..."
echo "CXX=$CXX"
g++ --version

ENABLESP=${1:-ON}

cmake .. -DMLC_ENABLE_SENTENCEPIECE_TOKENIZER=$ENABLESP || exit 1
echo
echo "make..."
make -j8 || exit 1
cd ..
# get example files

mkdir -p dist
cd dist
if [ ! -f "tokenizer.model" ]; then
    wget https://huggingface.co/lmsys/vicuna-7b-v1.5/resolve/main/tokenizer.model
fi
if [ ! -f "tokenizer.json" ]; then
    wget https://huggingface.co/togethercomputer/RedPajama-INCITE-Chat-3B-v1/resolve/main/tokenizer.json
fi
if [ ! -f "tokenizer_model" ]; then
    wget https://github.com/BBuf/run-rwkv-world-4-in-mlc-llm/releases/download/v1.0.0/tokenizer_model.zip
    unzip tokenizer_model.zip
fi
if [ ! -f "vocab.json" ]; then
    wget https://huggingface.co/Qwen/Qwen2.5-3B-Instruct/resolve/main/vocab.json
fi
if [ ! -f "merges.txt" ]; then
    wget https://huggingface.co/Qwen/Qwen2.5-3B-Instruct/resolve/main/merges.txt
fi

cd ..

# run
echo "---Running example----"
./build/example || exit 1
