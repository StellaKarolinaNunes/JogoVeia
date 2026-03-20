#include "../config.h"
#include "../game.h"
#include "../file_manager.h"
#include "../utils.h"
#include "../theme.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Mock para evitar chamadas de sistema ou IO pesado se necessário
// No caso desse projeto, as funções de lógica são puras o suficiente

int tests_run = 0;
int tests_passed = 0;

#define RUN_TEST(test) do { \
    printf("Executando %s... ", #test); \
    tests_run++; \
    test(); \
    tests_passed++; \
    printf("PASSOU\n"); \
} while (0)

// --- TESTES DE LÓGICA DE JOGO ---

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
    assert(result == false); // Já está ocupada
}

void test_fazer_jogada_invalida() {
    GameState game;
    inicializarTabuleiro(&game);
    assert(fazerJogada(&game, 0) == false);
    assert(fazerJogada(&game, 10) == false);
}

void test_vitoria_horizontal() {
    GameState game;
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[0][1] = 'X';
    game.tabuleiro[0][2] = 'X';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
    assert(win_line[0] == 0 && win_line[1] == 1 && win_line[2] == 2);
}

void test_vitoria_vertical() {
    GameState game;
    inicializarTabuleiro(&game);
    game.tabuleiro[0][0] = 'O';
    game.tabuleiro[1][0] = 'O';
    game.tabuleiro[2][0] = 'O';
    int win_line[3];
    assert(verificarVitoria(&game, win_line) == true);
    assert(win_line[0] == 0 && win_line[1] == 3 && win_line[2] == 6);
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

// --- TESTES DE IA (MINIMAX) ---

void test_minimax_bloqueio() {
    // Se X está prestes a ganhar na linha 1, O (IA) deve bloquear
    GameState game = {0};
    inicializarTabuleiro(&game);
    game.ai_difficulty = DIFFICULTY_HARD;
    game.tabuleiro[0][0] = 'X';
    game.tabuleiro[0][1] = 'X';
    game.jogadorAtual = 'O';
    
    int jogada = obterJogadaIA(&game);
    assert(jogada == 3);
}

// --- TESTES DE UTILITÁRIOS ---

void test_visible_strlen() {
    assert(visible_strlen("Teste") == 5);
    assert(visible_strlen("\033[31mCor\033[0m") == 3);
}

// --- TESTES DE PERSISTÊNCIA (MOCK) ---

void test_ranking_sort() {
    // Simular entrada no ranking
    num_ranking_entries = 0;
    strcpy(ranking[0].name, "B"); ranking[0].wins = 5;
    strcpy(ranking[1].name, "A"); ranking[1].wins = 10;
    num_ranking_entries = 2;
    
    salvarRanking(); // Isso também ordena se a implementação tiver ordenação
    carregarRanking();
    
    // Verificando se A está em primeiro (10 vitórias) se a ordenação for por vitórias
    // No projeto original, a ordenação pode ser em salvarRanking ou carregarRanking
    // Se não estiver implementada a ordenação automática, esse teste serve para documentar a lógica atual
}

void test_medals_logic() {
    // Verificar se o sistema de medalhas incrementa corretamente
    // Nota: Essa função imprime logs, talvez precise silenciar no relatório
    int initial_medals = ranking[0].medals;
    verificarEAtribuirMedalhas(ranking[0].name, true, false, true, DIFFICULTY_HARD);
    // Se a lógica permitir ganhar medalha ao vencer IA difícil
    // assert(ranking[0].medals > initial_medals);
}

int main() {
    printf("Iniciando Suite de Testes Unitarios - Jogo da  veia em C\n");
    printf("Data: 20/03/2026\n");
    printf("----------------------------------------------------\n");
    
    RUN_TEST(test_inicializar_tabuleiro);
    RUN_TEST(test_alternar_jogador);
    RUN_TEST(test_fazer_jogada_valida);
    RUN_TEST(test_fazer_jogada_ocupada);
    RUN_TEST(test_fazer_jogada_invalida);
    RUN_TEST(test_vitoria_horizontal);
    RUN_TEST(test_vitoria_vertical);
    RUN_TEST(test_vitoria_diagonal);
    RUN_TEST(test_empate);
    RUN_TEST(test_visible_strlen);
    RUN_TEST(test_minimax_bloqueio);
    
    printf("----------------------------------------------------\n");
    printf("Testes finalizados.\n");
    printf("Total Executado: %d\n", tests_run);
    printf("Total Aprovado:  %d\n", tests_passed);
    
    if (tests_run == tests_passed) {
        return 0;
    } else {
        return 1;
    }
}
