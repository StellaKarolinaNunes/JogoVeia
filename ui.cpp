#include "ui.h"
#include "theme.h"

void exibirTituloPrincipal(void) {
    const int largura_arte = 99;
    printf(
        "\n\n"
        "      ██╗ ██████╗  ██████╗  ██████╗      ██╗  ██████╗  █████╗   ██╗     ██╗   ██╗███████╗██╗ █████╗ \n"
        "      ██║██╔═══██╗██╔════╝ ██╔═══██╗     ╚██╗ ██╔══██╗██╔══██╗ ██╔╝     ██║   ██║██╔════╝██║██╔══██╗\n"
        "      ██║██║   ██║██║  ███╗██║   ██║█████╗╚██╗██║  ██║███████║██╔╝█████╗██║   ██║█████╗  ██║███████║\n"
        " ██   ██║██║   ██║██║   ██║██║   ██║╚════╝██╔╝██║  ██║██╔══██║╚██╗╚════╝╚██╗ ██╔╝██╔══╝  ██║██╔══██║\n"
        " ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝     ██╔╝ ██████╔╝██║  ██║ ╚██╗      ╚████╔╝ ███████╗██║██║  ██║\n"
        "  ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝      ╚═╝  ╚═════╝ ╚═╝  ╚═╝  ╚═╝       ╚═══╝  ╚══════╝╚═╝╚═╝  ╚═╝\n\n"
    );

    char info_string[100];
    sprintf(info_string, "Versão: %s | Tema atual: %s", GAME_VERSION, nomes_temas[tema_ativo]);

    printf("%*s\n", largura_arte, info_string);
}

void exibirTituloInstrucoes(void) {
    printf(
        "\n\n"
        "██╗███╗   ██╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗ ██████╗ ███████╗███████╗\n"
        "██║████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝██╔═══██╗██╔════╝██╔════╝\n"
        "██║██╔██╗ ██║███████╗   ██║   ██████╔╝██║   ██║██║     ██║   ██║█████╗  ███████╗\n"
        "██║██║╚██╗██║╚════██║   ██║   ██╔══██╗██║   ██║██║     ██║   ██║██╔══╝  ╚════██║\n"
        "██║██║ ╚████║███████║   ██║   ██║  ██║╚██████╔╝╚██████╗╚██████╔╝███████╗███████║\n"
        "╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝╚══════╝\n\n"
    );
}

void exibirTituloCreditos(void) {
    printf(
        "\n\n"
        " ██████╗██████╗ ███████╗██████╗ ██╗████████╗ ██████╗ ███████╗                \n"
        "██╔════╝██╔══██╗██╔════╝██╔══██╗██║╚══██╔══╝██╔═══██╗██╔════╝                \n"
        "██║     ██████╔╝█████╗  ██║  ██║██║   ██║   ██║   ██║███████╗                \n"
        "██║     ██╔══██╗██╔══╝  ██║  ██║██║   ██║   ██║   ██║╚════██║                \n"
        "╚██████╗██║  ██║███████╗██████╔╝██║   ██║   ╚██████╔╝███████║                \n"
        "╚═════╝╚═╝  ╚═╝╚══════╝╚═════╝ ╚═╝   ╚═╝    ╚═════╝ ╚══════╝                \n\n"
    );
}

void exibirTituloTemas(void) {
    printf(
        "\n"
        "████████╗███████╗███╗   ███╗ █████╗ ███████╗\n"
        "╚══██╔══╝██╔════╝████╗ ████║██╔══██╗██╔════╝\n"
        "   ██║   █████╗  ██╔████╔██║███████║███████╗\n"
        "   ██║   ██╔══╝  ██║╚██╔╝██║██╔══██║╚════██║\n"
        "   ██║   ███████╗██║ ╚═╝ ██║██║  ██║███████║\n"
        "   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝\n\n"
    );
}

void exibirTituloSaindo(void) {
    printf(
        "\n\n"
        "███████╗ █████╗ ██╗███╗   ██╗██████╗  ██████╗          \n"
        "██╔════╝██╔══██╗██║████╗  ██║██╔══██╗██╔═══██╗         \n"
        "███████╗███████║██║██╔██╗ ██║██║  ██║██║   ██║         \n"
        "╚════██║██╔══██║██║██║╚██╗██║██║  ██║██║   ██║         \n"
        "███████║██║  ██║██║██║ ╚████║██████╔╝╚██████╔╝██╗██╗██╗\n"
        "╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ ╚═╝╚═╝╚═╝\n"
        "\n"
    );
}

void exibirMenuCapa(void) {
    printf("\n");
    printf(" ╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf(" ║                                                                                              ║\n");
    printf(" ║                                ESCOLHA O QUE DESEJA FAZER                                    ║\n");
    printf(" ║                                                                                              ║\n");
    printf(" ║         1 - Jogar       |   2 - Instruções   |   3 - Créditos    |   4 - Referência          ║\n");
    printf(" ║         5 - Tema        |   6 - Save/Load    |   7 - Ranking     |   8 - Sair                ║\n");
    printf(" ║                                                                                              ║\n");
    printf(" ╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
}

void print_square(char value, int row, int col, const int* highlight_indices) {
    int current_pos = row * 3 + col;
    bool is_highlighted = false;
    if (highlight_indices != NULL && highlight_indices[0] != -1) {
        for (int k = 0; k < 3; k++) {
            if (highlight_indices[k] == current_pos) {
                is_highlighted = true;
                break;
            }
        }
    }
    
    if (is_highlighted) {
        printf("%s %c %s", HIGHLIGHT_COLOR, value, NORMAL_COLOR);
    } else {
        printf(" %c ", value);
    }
}

void exibirInterfaceJogo(const GameState* game, const int* winning_line_indices) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();
    
    printf("             ====================================================================================\n");
    printf("             |                             PLACAR                      |        TABULEIRO       |\n");
    printf("             ====================================================================================\n");
    printf("             | Jogador %-8s (X): %3d                             |", game->nomeJogadorX, game->placarX);
    print_square(game->tabuleiro[0][0], 0, 0, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[0][1], 0, 1, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[0][2], 0, 2, winning_line_indices);
    printf(" |\n");
    
    printf("             |---------------------------------------------------------|---------+-------+------ |\n");
    printf("             | Jogador %-8s (O): %3d                             |", game->nomeJogadorO, game->placarO);
    print_square(game->tabuleiro[1][0], 1, 0, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[1][1], 1, 1, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[1][2], 1, 2, winning_line_indices);
    printf(" |\n");
    
    printf("             |---------------------------------------------------------|---------+-------+------ |\n");
    printf("             | Empates: %3d                                            |", game->empates);
    print_square(game->tabuleiro[2][0], 2, 0, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[2][1], 2, 1, winning_line_indices);
    printf(" |");
    print_square(game->tabuleiro[2][2], 2, 2, winning_line_indices);
    printf(" |\n");
    
    printf("             |---------------------------------------------------------|-------------------------|\n");
    printf("             |                                                         |                         |\n");
    printf("             | 0. Sair do jogo                                         |                         |\n");
    printf("             ====================================================================================\n\n");
}
