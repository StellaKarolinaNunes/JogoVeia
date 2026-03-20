#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tests.h"

int tests_run = 0;
int tests_passed = 0;

#define RUN_TEST(test) do { \
    printf("Executando %s... ", #test); \
    tests_run++; \
    test(); \
    tests_passed++; \
    printf("PASSOU\n"); \
} while (0)

int main() {
    printf("====================================================\n");
    printf("Suíte de Testes ABRANGENTE - Jogo da Velha (v4.0)\n");
    printf("====================================================\n");

    srand((unsigned)time(NULL));

    // Logic Tests
    RUN_TEST(test_inicializar_tabuleiro);
    RUN_TEST(test_alternar_jogador);
    RUN_TEST(test_fazer_jogada_valida);
    RUN_TEST(test_fazer_jogada_ocupada);
    RUN_TEST(test_vitoria_horizontal);
    RUN_TEST(test_vitoria_vertical);
    RUN_TEST(test_vitoria_diagonal);
    RUN_TEST(test_empate);

    // AI Tests
    RUN_TEST(test_minimax_bloqueio);

    // Utils Tests
    RUN_TEST(test_visible_strlen);

    // Functional & UI Tests (Novos)
    RUN_TEST(test_ui_instrucoes);
    RUN_TEST(test_ui_creditos);
    RUN_TEST(test_ui_referencia);
    RUN_TEST(test_ranking_sort_integrity);
    RUN_TEST(test_fluxo_persistência);
    RUN_TEST(test_validar_todos_temas);
    RUN_TEST(test_verificar_comandos_sistema);
    RUN_TEST(test_modos_jogo_integracao);

    printf("====================================================\n");
    printf("Testes finalizados.\n");
    printf("Total Executado: %d\n", tests_run);
    printf("Total Aprovado:  %d\n", tests_passed);
    printf("====================================================\n");

    return (tests_run == tests_passed) ? 0 : 1;
}
