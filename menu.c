#include "menu.h"
#include "utils.h"
#include "ui.h"
#include "game.h"
#include "file_manager.h"
#include "theme.h"
#include "i18n.h"
#include <stdlib.h>

void funcaoInstrucoes(void) {
    exibirTelaInstrucoes();
    while (1) {
        KeyCode tecla = lerTeclaMenu();
        if (tecla == KEY_ENTER || tecla == KEY_Q || tecla == KEY_ESC) {
            break;
        }
    }
}

void funcaoCreditos(void) {
    exibirTelaCreditos();
    while (1) {
        KeyCode tecla = lerTeclaMenu();
        if (tecla == KEY_ENTER || tecla == KEY_Q || tecla == KEY_ESC) {
            break;
        }
    }
}

void funcaoReferencia(void) {
    exibirTelaReferencia();
    while (1) {
        KeyCode tecla = lerTeclaMenu();
        if (tecla == KEY_ENTER || tecla == KEY_Q || tecla == KEY_ESC) {
            break;
        }
    }
}

void funcaoTema(void) {
    escolherTema();
}

void funcaoIdioma(void) {
    // Display language selection UI and update current language
    change_language();
    // Persist the new language setting
    salvarConfiguracoes();
    // Optionally provide visual feedback (brief pause)
    limparTela();
    aplicarTema(tema_ativo);
    printf("\n");
    // Return to main menu after language change
}

void funcaoSaveLoad(GameState* game) {
    int selected = 1;
    KeyCode tecla;
    
    do {
        exibirTelaSaveLoad(selected);
        tecla = lerTeclaMenu();
        
        switch (tecla) {
            case KEY_UP:
                selected--;
                if (selected < 1) selected = 3;
                break;
                
            case KEY_DOWN:
                selected++;
                if (selected > 3) selected = 1;
                break;
                
            case KEY_ENTER:
                switch (selected) {
                    case 1:
                        salvarJogo(game);
                        break;
                    case 2:
                        if (carregarJogo(game)) {
                            funcaoJogar(game, true);
                        }
                        break;
                    case 3:
                        funcaoDeletarJogo();
                        break;
                }
                break;
                
            case KEY_ESC:
            case KEY_Q:
            case KEY_0:
                return;
                
            default:
                break;
        }
    } while (1);
}

void funcaoRanking(void) {
    while (1) {
        exibirTelaRanking();
        KeyCode tecla = lerTeclaMenu();
        if (tecla == KEY_ENTER || tecla == KEY_Q || tecla == KEY_ESC) {
            break;
        }
    }
}

void funcaoSair(void) {
    limparTela();
    aplicarTema(tema_ativo);
    
    for(int i=0; i<5; i++) printf("\n");
    
    printf("      ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("      ║                                                                                                                              ║\n");
    printf("      ║                             ___  ___ ___ ___ ___   _   ___   ___                                                             ║\n");
    printf("      ║                            / _ \\| _ ) _ \\_ _/ __| /_\\ |   \\ / _ \\                                                            ║\n");
    printf("      ║                           | (_) | _ \\   /| | (_ |/ _ \\| |) | (_) |                                                           ║\n");
    printf("      ║                            \\___/|___/_|_\\___\\___/_/ \\_\\___/ \\___/                                                            ║\n");
    printf("      ║                                                                                                                              ║\n");
    
    char header_info[200];
    snprintf(header_info, sizeof(header_info), "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦", nomes_temas[tema_ativo], GAME_VERSION);
    int info_len = visible_strlen(header_info);
    int pad_left = (126 - info_len) / 2;
    int pad_right = 126 - info_len - pad_left;
    printf("      ║");
    for(int i=0; i<pad_left; i++) printf(" ");
    printf("%s", header_info);
    for(int i=0; i<pad_right; i++) printf(" ");
    printf("║\n");
    
    printf("      ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("      ║                                                                                                                              ║\n");
    printf("      ║    ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐    ║\n");
    
    const char* title1 = "OBRIGADA POR JOGAR!";
    int p_t1 = (116 - visible_strlen(title1)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_t1; i++) printf(" ");
    printf("%s", title1);
    for(int i=0; i<116 - visible_strlen(title1) - p_t1; i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    ├────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤    ║\n");
    printf("      ║    │                                                                                                                    │    ║\n");
    
    const char* destaque_txt = "ATÉ A PRÓXIMA PARTIDA!";
    int p_dest = (46 - visible_strlen(destaque_txt)) / 2;
    printf("      ║    │                         \033[7m╔══════════════════════════════════════════════╗\033[0m%s                                           │    ║\n", temas[tema_ativo]);
    
    printf("      ║    │                         \033[7m║\033[0m%s", temas[tema_ativo]);
    for(int i=0; i<p_dest; i++) printf(" ");
    printf("\033[7m%s\033[0m%s", destaque_txt, temas[tema_ativo]);
    for(int i=0; i<46 - visible_strlen(destaque_txt) - p_dest; i++) printf(" ");
    printf("\033[7m║\033[0m%s                                           │    ║\n", temas[tema_ativo]);
    
    printf("      ║    │                         \033[7m╚══════════════════════════════════════════════╝\033[0m%s                                           │    ║\n", temas[tema_ativo]);
    
    printf("      ║    │                                                                                                                    │    ║\n");
    
    const char* p1 = "  Obrigada por jogar o Jogo da Veia e fazer parte desta experiência.";
    printf("      ║    │%s", p1);
    for(int i=0; i<116 - visible_strlen(p1); i++) printf(" ");
    printf("│    ║\n");
    
    const char* p2 = "  Volte sempre para testar novas estratégias, desafios e jogadas incríveis.";
    printf("      ║    │%s", p2);
    for(int i=0; i<116 - visible_strlen(p2); i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    │                                                                                                                    │    ║\n");
    printf("      ║    │────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│    ║\n");
    
    const char* t2 = "MENSAGEM FINAL";
    int p_t2 = (116 - visible_strlen(t2)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_t2; i++) printf(" ");
    printf("%s", t2);
    for(int i=0; i<116 - visible_strlen(t2) - p_t2; i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    │────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│    ║\n");
    printf("      ║    │                                                                                                                    │    ║\n");
    
    const char* quote = "✦ Toda grande estratégia começa com a primeira jogada. ✦";
    int p_q = (116 - visible_strlen(quote)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_q; i++) printf(" ");
    printf("%s", quote);
    for(int i=0; i<116 - visible_strlen(quote) - p_q; i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    │                                                                                                                    │    ║\n");
    printf("      ║    │────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│    ║\n");
    
    const char* t3 = "DESENVOLVIMENTO";
    int p_t3 = (116 - visible_strlen(t3)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_t3; i++) printf(" ");
    printf("%s", t3);
    for(int i=0; i<116 - visible_strlen(t3) - p_t3; i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    │────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│    ║\n");
    printf("      ║    │                                                                                                                    │    ║\n");
    
    const char* d1 = "Desenvolvedora: Stella Karolina Nunes Peixoto";
    int p_d1 = (116 - visible_strlen(d1)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_d1; i++) printf(" ");
    printf("%s", d1);
    for(int i=0; i<116 - visible_strlen(d1) - p_d1; i++) printf(" ");
    printf("│    ║\n");
    
    char d2[200];
    snprintf(d2, sizeof(d2), "Projeto acadêmico • Ciência da Computação • v%s", GAME_VERSION);
    int p_d2 = (116 - visible_strlen(d2)) / 2;
    printf("      ║    │");
    for(int i=0; i<p_d2; i++) printf(" ");
    printf("%s", d2);
    for(int i=0; i<116 - visible_strlen(d2) - p_d2; i++) printf(" ");
    printf("│    ║\n");
    
    printf("      ║    │                                                                                                                    │    ║\n");
    printf("      ║    └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘    ║\n");
    printf("      ║                                                                                                                              ║\n");
    printf("      ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    const char* enter_msg = "Pressione ENTER para encerrar o jogo...";
    int p_enter = (126 - visible_strlen(enter_msg)) / 2;
    printf("      ║");
    for(int i=0; i<p_enter; i++) printf(" ");
    printf("%s", enter_msg);
    for(int i=0; i<126 - visible_strlen(enter_msg) - p_enter; i++) printf(" ");
    printf("║\n");
    
    printf("      ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    printf("\033[0m"); // reset de cor
    esperarEnter();
    exit(0);
}


void menuPrincipal(GameState* game) {
    int opcaoSelecionada = 1;
    KeyCode tecla;
    
    do {
        limparTela();
        aplicarTema(tema_ativo);
        exibirMenuInterativo(opcaoSelecionada, game);
        
        tecla = lerTeclaMenu();
        
        switch (tecla) {
            case KEY_UP:
                if (opcaoSelecionada == 1) opcaoSelecionada = 9;
                else opcaoSelecionada--;
                break;
                
            case KEY_DOWN:
                if (opcaoSelecionada == 9) opcaoSelecionada = 1;
                else opcaoSelecionada++;
                break;
                
            case KEY_ENTER:
                switch (opcaoSelecionada) {
                    case 1:
                        funcaoJogar(game, false);
                        break;
                    case 2:
                        funcaoInstrucoes();
                        break;
                    case 3:
                        funcaoCreditos();
                        break;
                    case 4:
                        funcaoReferencia();
                        break;
                    case 5:
                        funcaoTema();
                        break;
                    case 6:
                        funcaoSaveLoad(game);
                        break;
                    case 7:
                        funcaoRanking();
                        break;
                    case 8:
                        funcaoSair();
                        break;
                    case 9:
                        funcaoIdioma();
                        break;
                }
                break;
                
            case KEY_Q:
            case KEY_ESC:
                opcaoSelecionada = 8; // Destaca a opção Sair
                break;
                
            default:
                break;
        }
    } while (1);
}
