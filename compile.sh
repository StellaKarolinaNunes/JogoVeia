#!/bin/bash

# 1. Cria a pasta build se não existir
mkdir -p build

# 2. Compila o jogo jogando o executável para dentro da pasta build
gcc main.c globals.c game.c maintenance.c utils.c theme.c ui.c file_manager.c menu.c -o build/jogo_velha -lm

if [ $? -eq 0 ]; then
    echo "Jogo compilado com sucesso!"
    
    # 3. Executa o jogo a partir da pasta raiz para manter os caminhos (saves, config)
    ./build/jogo_velha
    
    # 4. Ao fechar o jogo, limpa arquivos temporários e tenta remover arquivos fuse ocultos
    echo "Limpando arquivos temporários..."
    rm -f saves_list.tmp 2>/dev/null
    rm -f .fuse_hidden* 2>/dev/null
    echo "Pronto!"
else
    echo "Erro na compilação!"
fi