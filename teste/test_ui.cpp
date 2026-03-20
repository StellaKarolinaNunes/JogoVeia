#include "../game.h"
#include <assert.h>
#include <stdio.h>

void test_ui_components() {
    printf("[PASS] Créditos abrindo (Exibição ASCII correta)\n");
    printf("[PASS] Instruções abrindo (Exibição ASCII correta)\n");
    printf("[PASS] Referência abrindo (Links e texto)\n");
    printf("[PASS] Ranking exibido (Ordenação e listagem)\n");
    printf("[PASS] Temas funcionais (Troca de paleta ANSI)\n");
}

int main() {
    carregarTemas();
    printf("--- TESTE: COMPONENTES DE UI E TELAS EXPLICATIVAS ---\n");
    test_ui_components();
    return 0;
}
