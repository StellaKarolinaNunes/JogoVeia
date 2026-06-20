#!/bin/bash

# 1. Cria a pasta build se não existir
mkdir -p build

# 2. Compila o jogo jogando o executável para dentro da pasta build
if gcc -Wall -Wextra -std=c11 *.c -o build/jogo_veia -lm; then
    echo "Compilação concluída com sucesso!"
    echo "Jogo compilado com sucesso!"
    
    # 3. Executa o jogo em uma nova janela de terminal, tanto no Windows quanto no Linux
    if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
        
        if [ -f "build/jogo_veia.exe" ]; then
            start build/jogo_veia.exe
        elif [ -f "build/jogo_veia" ]; then
            start build/jogo_veia
        else
            echo "Erro: Executável não encontrado!"
        fi
    else
        # Linux / macOS
        if [ "$TERM_PROGRAM" = "vscode" ] && [ -n "$DISPLAY" ]; then
       
            if command -v gnome-terminal >/dev/null 2>&1; then
                gnome-terminal --geometry=140x48 -- ./build/jogo_veia
            elif command -v x-terminal-emulator >/dev/null 2>&1; then
                x-terminal-emulator --geometry=140x48 -e ./build/jogo_veia
            else
                printf "\033[8;48;140t"
                ./build/jogo_veia
            fi
        else
            # Se for terminal externo normal, redimensiona e executa
            printf "\033[8;48;140t"
            ./build/jogo_veia
        fi
    fi
    
    # 4. Ao fechar o jogo, limpa arquivos temporários e tenta remover arquivos fuse ocultos
    echo "Limpando arquivos temporários..."
    rm -f saves_list.tmp 2>/dev/null
    rm -f .fuse_hidden* 2>/dev/null
    echo "Pronto!"
else
    echo "Erro na compilação!"
fi