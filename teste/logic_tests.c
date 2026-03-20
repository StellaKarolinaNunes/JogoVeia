#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tests.h"
#include "../game.h"

void test_inicializar_tabuleiro() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(game.tabuleiro[i][j] == (char)('0' + count++));
        }
    }
    assert(game.numJogadasX == 0);
    assert(game.numJogadasO == 0);
}

void test_alternar_jogador() {
    GameState game = {0};
    game.jogadorAtual = 'X';
    alternarJogador(&game);
    assert(game.jogadorAtual == 'O');
    alternarJogador(&game);
    assert(game.jogadorAtual == 'X');
}

void test_fazer_jogada_valida() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.jogadorAtual = 'X';
    bool result = fazerJogada(&game, 5);
    assert(result == true);
    assert(game.tabuleiro[1][1] == 'X');
}

void test_fazer_jogada_ocupada() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.jogadorAtual = 'X';
    fazerJogada(&game, 5);
    bool result = fazerJogada(&game, 5);
    assert(result == false);
}

void test_vitoria_horizontal() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[0][1] = 'X';
    game.tabuleiro[0][2] = 'X';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
}

void test_vitoria_vertical() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'O';
    game.tabuleiro[1][0] = 'O';
    game.tabuleiro[2][0] = 'O';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
}

void test_vitoria_diagonal() {
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[1][1] = 'X';
    game.tabuleiro[2][2] = 'X';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
}

void test_empate() {
    GameState game = {0};
    char mock[3][3] = {
        {'X', 'O', 'X'},
        {'X', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    memcpy(game.tabuleiro, mock, 9);
    assert(verificarEmpate(&game) == true);
}
