#include "ui.h"
#include "theme.h"
#include "utils.h"

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

    int vlen = visible_strlen(info_string);
    int padding = largura_arte - vlen;
    if (padding > 0) printf("%*s", padding, "");
    printf("%s\n", info_string);
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

void exibirTituloReferencia(void) {
    printf(
        "\n\n"
        "██████╗ ███████╗███████╗███████╗██████╗ ███████╗███╗   ██╗ ██████╗██╗ █████╗ \n"
        "██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝████╗  ██║██╔════╝██║██╔══██╗\n"
        "██████╔╝█████╗  █████╗  █████╗  ██████╔╝█████╗  ██╔██╗ ██║██║     ██║███████║\n"
        "██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██╔════╝██║╚██╗██║██║     ██║██╔══██║\n"
        "██║  ██║███████╗██║     ███████╗██║  ██║███████╗██║ ╚████║╚██████╗██║██║  ██║\n"
        "╚═╝  ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝╚═╝  ╚═╝\n"
        "\n"
    );
}

void exibirTituloModoJogo(void) {
    printf(
        "███╗   ███╗ ██████╗ ██████╗  ██████╗     ██████╗ ███████╗        ██╗ ██████╗  ██████╗  ██████╗\n"
        "████╗ ████║██╔═══██╗██╔══██╗██╔═══██╗    ██╔══██╗██╔════╝        ██║██╔═══██╗██╔════╝ ██╔═══██╗\n"
        "██╔████╔██║██║   ██║██║  ██║██║   ██║    ██║  ██║█████╗          ██║██║   ██║██║  ███╗██║   ██║\n"
        "██║╚██╔╝██║██║   ██║██║  ██║██║   ██║    ██║  ██║██╔══╝     ██   ██║██║   ██║██║   ██║██║   ██║\n"
        "██║ ╚═╝ ██║╚██████╔╝██████╔╝╚██████╔╝    ██████╔╝███████╗   ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝\n"
        "╚═╝     ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝     ╚═════╝ ╚══════╝   ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝ \n"
    );
}

void exibirTituloDados(void) {
    printf(
        " ██████╗ ███████╗██████╗ ███████╗███╗   ██╗ ██████╗██╗ █████╗ \n"
        "██╔════╝ ██╔════╝██╔══██╗██╔════╝████╗  ██║██╔════╝██║██╔══██╗\n"
        "██║  ███╗█████╗  ██████╔╝█████╗  ██╔██╗ ██║██║     ██║███████║\n"
        "██║   ██║██╔════╝██╔══██╗██╔════╝██║╚██╗██║██║     ██║██╔══██║\n"
        "╚██████╔╝███████╗██║  ██║███████╗██║ ╚████║╚██████╗██║██║  ██║\n"
        " ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝╚═╝  ╚═╝\n"
    );
}

void exibirTituloDeletar(void) {
    printf(
        "██████╗ ███████╗██╗     ███████╗████████╗ █████╗ ██████╗         ██╗ ██████╗  ██████╗  ██████╗      ███████╗ █████╗ ██╗     ██╗   ██╗ ██████╗\n"
        "██╔══██╗██╔════╝██║     ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗        ██║██╔═══██╗██╔════╝ ██╔═══██╗     ██╔════╝██╔══██╗██║     ██║   ██║██╔═══██╗\n"
        "██║  ██║█████╗  ██║     █████╗     ██║   ███████║██████╔╝        ██║██║   ██║██║  ███╗██║   ██║     ███████╗███████║██║     ██║   ██║██║   ██║\n"
        "██║  ██║██╔══╝  ██║     ██╔══╝     ██║   ██╔══██║██╔══██╗   ██   ██║██║   ██║██║   ██║██║   ██║     ╚════██║██╔══██║██║     ╚██╗ ██╔╝██║   ██║\n"
        "██████╔╝███████╗███████╗███████╗   ██║   ██║  ██║██║  ██║   ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝     ███████║██║  ██║███████╗ ╚████╔╝ ╚██████╔╝\n"
        "╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝      ╚══════╝╚═╝  ╚═╝╚══════╝  ╚═══╝   ╚═════╝ \n"
    );
}

void exibirTituloRanking(void) {
    printf(
        "\n\n"
        "██████╗  █████╗ ███╗   ██╗██╗  ██╗██╗███╗   ██╗ ██████╗ \n"
        "██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝██║████╗  ██║██╔════╝ \n"
        "██████╔╝███████║██╔██╗ ██║█████╔╝ ██║██╔██╗ ██║██║  ███╗\n"
        "██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ██║██║╚██╗██║██║   ██║\n"
        "██║  ██║██║  ██║██║ ╚████║██║  ██╗██║██║ ╚████║╚██████╔╝\n"
        "╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ \n"
        "\n"
    );
}

void exibirMenuCapa(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                                                      ║\n");
    printf("║                                    ESCOLHA O QUE DESEJA FAZER                                        ║\n");
    printf("║                                                                                                      ║\n");
    printf("║         1 - Jogar       |   2 - Instruções   |   3 - Créditos    |   4 - Referência                  ║\n");
    printf("║         5 - Tema        |   6 - Save/Load    |   7 - Ranking     |   8 - Sair                        ║\n");
    printf("║                                                                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
}



void exibirInterfaceJogo(const GameState* game, const int* winning_line_indices, const char* mensagemInfo) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();
    
    // Dimensões unificadas: Placar (71 chars), Tabuleiro (31 chars) incluindo bordas = 102 total
    printf("╔══════════════════════════════════════════════════════════════════════╦═════════════════════════════╗\n");
    printf("║                                PLACAR                                ║          TABULEIRO          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════╬═════════╦═════════╦═════════╣\n");
    
    #define PRINT_PLAYER_LINE(label, name, symbol, score) { \
        printf("║ %s", label); \
        int vlen = visible_strlen(name); \
        printf("%s", name); \
        for (int i = 0; i < 45 - vlen; i++) putchar(' '); \
        printf(" (%c): %3d       ║", symbol, score); \
    }

    #define PRINT_BOARD_CELL(value, row, col) { \
        int pos = row * 3 + col; \
        bool highlight = false; \
        if (winning_line_indices && winning_line_indices[0] != -1) { \
            for (int k = 0; k < 3; k++) if (winning_line_indices[k] == pos) highlight = true; \
        } \
        printf("   "); \
        if (highlight) { \
            printf("%s %c %s", HIGHLIGHT_COLOR, value, NORMAL_COLOR); \
            aplicarTema(tema_ativo); \
        } else { \
            printf(" %c ", value); \
        } \
        printf("   "); \
    }

    // Linha 1
    PRINT_PLAYER_LINE("Jogador ", game->nomeJogadorX, 'X', game->placarX);
    PRINT_BOARD_CELL(game->tabuleiro[0][0], 0, 0);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[0][1], 0, 1);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[0][2], 0, 2);
    printf("║\n");
    
    printf("║                                                                      ║═════════╬═════════╬═════════╣\n");
    
    // Linha 2
    PRINT_PLAYER_LINE("Jogador ", game->nomeJogadorO, 'O', game->placarO);
    PRINT_BOARD_CELL(game->tabuleiro[1][0], 1, 0);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[1][1], 1, 1);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[1][2], 1, 2);
    printf("║\n");
    
    printf("║                                                                      ║═════════╬═════════╬═════════╣\n");
    
    // Linha 3
    printf("║ Empates: %3d                                                         ║", game->empates);
    PRINT_BOARD_CELL(game->tabuleiro[2][0], 2, 0);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[2][1], 2, 1);
    printf("║");
    PRINT_BOARD_CELL(game->tabuleiro[2][2], 2, 2);
    printf("║\n");
    
    printf("╠══════════════════════════════════════════════════════════════════════╩═════════╩═════════╩═════════╣\n");
    printf("║   0. Sair do jogo                                                                                  ║\n");
    
    if (mensagemInfo && strlen(mensagemInfo) > 0) {
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        int vlen = visible_strlen(mensagemInfo);
        int left = (100 - vlen) / 2;
        int right = 100 - vlen - left;
        printf("║");
        for (int i = 0; i < left; i++) putchar(' ');
        printf("%s", mensagemInfo);
        for (int i = 0; i < right; i++) putchar(' ');
        printf("║\n");
    }
    
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    #undef PRINT_PLAYER_LINE
    #undef PRINT_BOARD_CELL
}

void animarSorteio(void) {
    char spinner[] = {'-', '\\', '|', '/'};
    for (int i = 0; i < 20; i++) {
        char spinnerLine[105];
        snprintf(spinnerLine, sizeof(spinnerLine), "             Sorteando o primeiro jogador... %c", spinner[i % 4]);
        int vlenSL = visible_strlen(spinnerLine);
        printf("\r║%s", spinnerLine);
        for (int k = 0; k < 100 - vlenSL; k++) putchar(' ');
        printf("║");
        fflush(stdout);
        delaySimples(100);
    }
    printf("\n"); // Quebra de linha necessária após o loop de \r
}

void animarVitoria(const GameState* game, const int* winning_line_indices) {
    for (int i = 0; i < 6; i++) {
        limparTela();
        if (i % 2 == 0) {
            // Brilha com cor branca/fundo preto (padrão highlight)
            exibirInterfaceJogo(game, winning_line_indices, "VITÓRIA!!!");
        } else {
            // Sem realce momentarily
            exibirInterfaceJogo(game, NULL, "VITÓRIA!!!");
        }
        delaySimples(300);
    }
}

void exibirTrofeu(const char* vencedor) {
    limparTela();
    aplicarTema(tema_ativo);
    printf("\n\n");
    printf("                      ___________   \n");
    printf("                     '._==_==_=_.'  \n");
    printf("                     .-\\:      /-.  \n");
    printf("                    | (|:.     |) | \n");
    printf("                     '-|:.     |-'  \n");
    printf("                       \\::.    /    \n");
    printf("                        '::. .'     \n");
    printf("                          ) (       \n");
    printf("                        _.' '._     \n");
    printf("                       `-------`    \n\n");
    printf("               🏆 CAMPEÃO DO TORNEIO: %s 🏆\n\n", vencedor);
    esperarEnter();
}

void exibirConquista(const char* titulo) {
    printf("\n  ✨ NOVA CONQUISTA DESBLOQUEADA: [ %s ] ✨\n", titulo);
    printf("\a"); // Beep de conquista
    delaySimples(1000);
}
