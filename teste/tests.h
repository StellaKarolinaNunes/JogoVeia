#ifndef TESTS_H
#define TESTS_H

#include "../config.h"

// Logic Tests
void test_inicializar_tabuleiro();
void test_alternar_jogador();
void test_fazer_jogada_valida();
void test_fazer_jogada_ocupada();
void test_vitoria_horizontal();
void test_vitoria_vertical();
void test_vitoria_diagonal();
void test_empate();

// AI Tests
void test_minimax_bloqueio();

// Utils Tests
void test_visible_strlen();

// Functional Tests (Novos)
void test_ui_instrucoes();
void test_ui_creditos();
void test_ui_referencia();
void test_ranking_sort_integrity();
void test_fluxo_persistência();
void test_validar_todos_temas();
void test_verificar_comandos_sistema();
void test_modos_jogo_integracao();

#endif
