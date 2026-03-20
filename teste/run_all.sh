#!/bin/bash

# Cores para saída
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "===================================================="
echo "    INICIANDO SUÍTE DE TESTES MODULARES (V3.0)      "
echo "===================================================="

# Função para executar um teste individual
run_test() {
    local test_name=$1
    local test_file=$2
    local extra_files=$3

    echo -n "Testando $test_name... "
    g++ "$test_file" $extra_files -o "executar_$test_name" 2>/dev/null
    
    if [ $? -eq 0 ]; then
        ./"executar_$test_name" > "logs_$test_name.log" 2>&1
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}[OK]${NC}"
        else
            echo -e "${RED}[FALHOU]${NC} (Verifique logs_$test_name.log)"
        fi
    else
        echo -e "${RED}[ERRO DE COMPILAÇÃO]${NC}"
    fi
    # Limpar executáveis temporários
    rm -f "executar_$test_name"
}

# Lista de arquivos necessários para a lógica do jogo
GAME_LOGIC="globals.cpp game.cpp maintenance.cpp utils.cpp theme.cpp ui.cpp file_manager.cpp menu.cpp"

# Executar cada teste a partir da pasta 'game'
cd ..
run_test "WinLoss" "teste/test_win_loss.cpp" "$GAME_LOGIC"
run_test "SaveLoad" "teste/test_save_load.cpp" "$GAME_LOGIC"
run_test "Menu" "teste/test_menu.cpp" "$GAME_LOGIC"
run_test "UI" "teste/test_ui.cpp" "$GAME_LOGIC"
run_test "Modes" "teste/test_modes.cpp" "$GAME_LOGIC"
run_test "Game" "teste/test_game.cpp" "$GAME_LOGIC"

echo "===================================================="
echo "    TESTES FINALIZADOS - VERIFIQUE OS LOGS          "
echo "===================================================="
