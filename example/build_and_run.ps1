$ErrorActionPreference = "Stop"

# --- Build ---
New-Item -ItemType Directory -Force -Path "./build" | Out-Null
Push-Location ./build
cmake ..
cmake --build .
Pop-Location

# --- Download example files ---
New-Item -ItemType Directory -Force -Path "./dist" | Out-Null
Push-Location ./dist

if (-not (Test-Path "tokenizer.model")) {
    Invoke-WebRequest -Uri "https://huggingface.co/lmsys/vicuna-7b-v1.5/resolve/main/tokenizer.model" -OutFile "tokenizer.model"
}

if (-not (Test-Path "tokenizer.json")) {
    Invoke-WebRequest -Uri "https://huggingface.co/togethercomputer/RedPajama-INCITE-Chat-3B-v1/resolve/main/tokenizer.json" -OutFile "tokenizer.json"
}

if (-not (Test-Path "tokenizer_model")) {
    Invoke-WebRequest -Uri "https://github.com/BBuf/run-rwkv-world-4-in-mlc-llm/releases/download/v1.0.0/tokenizer_model.zip" -OutFile "tokenizer_model.zip"
    Expand-Archive -Path "tokenizer_model.zip" -DestinationPath .
    Remove-Item "tokenizer_model.zip"
}

Pop-Location

# --- Run ---
Write-Host "---Running example----"
Start-Process -FilePath ".\build\Debug\example.exe" -Wait
