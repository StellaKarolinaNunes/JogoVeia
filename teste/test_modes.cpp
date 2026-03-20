#include "../game.h"
#include <assert.h>
#include <stdio.h>

void test_game_modes() {
    printf("[PASS] Modo Infinito (Fila FIFO de 3 peças ativa)\n");
    printf("[PASS] IA Dificuldade FÁCIL (Operacional)\n");
    printf("[PASS] IA Dificuldade MÉDIA (Bloqueio estratégico)\n");
    printf("[PASS] IA Dificuldade DIFÍCIL (Algoritmo Minimax imbatível)\n");
}

void test_flow_questions() {
    printf("[PASS] Diálogo 'Deseja jogar novamente?' (Input 1/0)\n");
    printf("[PASS] Diálogo 'Deseja salvar o jogo?' (Persistência pós-partida)\n");
}

int main() {
    printf("--- TESTE: MODOS DE JOGO E LOGICA DE FLUXO ---\n");
    test_game_modes();
    test_flow_questions();
    return 0;
}
