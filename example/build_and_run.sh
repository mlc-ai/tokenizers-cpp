#/bin/bash

# build
mkdir -p build
cd build
cmake ..
make -j8
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
cd ..

# run
echo "---Running example----"
./build/example
