#include <stdio.h>
#include <assert.h>
#include "tests.h"
#include "../game.h"

void test_minimax_bloqueio() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.ai_difficulty = DIFFICULTY_HARD;
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[0][1] = 'X';
    game.jogadorAtual = 'O';
    
    int jogada = obterJogadaIA(&game);
    assert(jogada == 3);
}
