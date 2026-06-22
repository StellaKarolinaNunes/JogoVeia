#include "config.h"
#include "theme.h"
#include "file_manager.h"
#include "i18n.h"
#include "menu.h"

void configurarSistema(void) {
    setlocale(LC_ALL, "");
#ifdef _WIN32
    system(SET_TITLE);
    system("mode con cols=140 lines=48");
#else
    // No Linux/macOS, define o título e redimensiona o terminal usando sequências ANSI
    printf("\033]0;jogo da veia\007");
    printf("\033[8;48;140t");
    fflush(stdout);
#endif
    aplicarTema(tema_ativo);
    srand((unsigned)time(NULL));
}

int main() {
    GameState current_game_state = {0};
    strcpy(current_game_state.ultimoVencedor, "Nenhum");
    
    carregarConfiguracoes();
    init_i18n();
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
