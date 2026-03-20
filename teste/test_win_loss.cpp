#include "../game.h"
#include <assert.h>
#include <stdio.h>

void test_win_horizontal() {
    GameState game;
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[0][1] = 'X';
    game.tabuleiro[0][2] = 'X';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
    printf("[PASS] Vitória Horizontal (X)\n");
}

void test_loss_ia() {
    GameState game;
    inicializarTabuleiro(&game);
    game.tabuleiro[1][0] = 'O';
    game.tabuleiro[1][1] = 'O';
    game.tabuleiro[1][2] = 'O';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
    printf("[PASS] Vitória/Derrota IA (O)\n");
}

void test_draw() {
    GameState game;
    char draw_board[3][3] = {
        {'X', 'O', 'X'},
        {'X', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) game.tabuleiro[i][j] = draw_board[i][j];
    assert(verificarEmpate(&game) == true);
    printf("[PASS] Empate (Velha)\n");
}

int main() {
    printf("--- TESTE: LOGICA DE VITORIA/DERROTA ---\n");
    test_win_horizontal();
    test_loss_ia();
    test_draw();
    return 0;
}
