#include "config.h"
#include "utils.h"
#include "theme.h"
#include "file_manager.h"
#include "menu.h"

void configurarSistema(void) {
    setlocale(LC_ALL, "");
    system(SET_TITLE);
    aplicarTema(tema_ativo);
    srand((unsigned)time(NULL));
}

int main() {
    GameState current_game_state = {0};
    strcpy(current_game_state.ultimoVencedor, "Nenhum");
    
    carregarConfiguracoes();
    configurarSistema();
    carregarTemas();
    carregarRanking();
    
    menuPrincipal(&current_game_state);
    
    salvarRanking();
    salvarConfiguracoes();
    
    puts("");
#ifndef _WIN32
    printf(RESET_COLOR_COMMAND);
#endif
    
    return 0;
}
