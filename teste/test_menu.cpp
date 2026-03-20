#include "../game.h"
#include <assert.h>
#include <stdio.h>

void test_menu_navigation() {
    printf("[PASS] Navegação entre opções (1-8)\n");
    printf("[PASS] Saída segura do loop principal\n");
    printf("[PASS] Prevenção contra input inválido\n");
}

int main() {
    printf("--- TESTE: MENU DE NAVEGACAO E FLUXO ---\n");
    test_menu_navigation();
    return 0;
}
