#include "menu.h"
#include "utils.h"
#include "ui.h"
#include "game.h"
#include "file_manager.h"
#include "theme.h"

void funcaoInstrucoes(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloInstrucoes();
    
    printf("========================================================================================================\n");
    printf("|                                            COMO JOGAR                                                |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("| - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.                                     |\n");
    printf("| - Dois jogadores se revezam utilizando os símbolos X e O.                                           |\n");
    printf("| - O objetivo é alinhar 3 símbolos iguais (X ou O).                                                  |\n");
    printf("| - Pode-se vencer alinhando na horizontal, vertical ou diagonal.                                     |\n");
    printf("========================================================================================================\n\n");
    
    printf("TABULEIRO:\n\n");
    printf("     1 | 2 | 3\n");
    printf("    ---+---+---\n");
    printf("     4 | 5 | 6\n");
    printf("    ---+---+---\n");
    printf("     7 | 8 | 9\n\n");
    
    printf("💡 DICAS DE ESTRATÉGIA:\n");
    printf("- Comece pelo centro ou pelos cantos.\n");
    printf("- Bloqueie jogadas do adversário.\n");
    printf("- Pense duas jogadas à frente!\n");
    
    printf("\n════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("│ Pressione Enter para voltar ao menu...                                                                │\n");
    printf("════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    
    esperarEnter();
}

void funcaoCreditos(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloCreditos();
    
    printf("========================================================================================================\n");
    printf("|                                         CRÉDITOS                                                      |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("| Curso: Ciências da Computação                                                                         |\n");
    printf("| Disciplina: Programação 1                                                                            |\n");
    printf("| Projeto prova: Jogo da Velha                                                                         |\n");
    printf("| Autor: Stella Karolina Nunes                                                                         |\n");
    printf("| Matrícula: 20223834810                                                                               |\n");
    printf("|                                                                                                       |\n");
    printf("| Versão 1.0  - Data: 2023                                                                            |\n");
    printf("| Versão 2.0  - Data: 2025                                                                            |\n");
    printf("========================================================================================================\n\n");
    
    printf("\n════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("│ Pressione Enter para voltar ao menu...                                                                │\n");
    printf("════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    
    esperarEnter();
}

void funcaoReferencia(void) {
    limparTela();
    aplicarTema(tema_ativo);
    printf("========================================================================================================\n");
    printf("|                                           REFERÊNCIAS                                                |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("| Fonte de consulta principal para as regras e história do jogo:                                       |\n");
    printf("|                                                                                                      |\n");
    printf("| Wikipedia - Jogo da Velha: https://pt.wikipedia.org/wiki/Jogo_da_velha                               |\n");
    printf("|                                                                                                      |\n");
    printf("========================================================================================================\n\n");

    printf("\n════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("│ Pressione Enter para voltar ao menu...                                                                │\n");
    printf("════════════════════════════════════════════════════════════════════════════════════════════════════════\n");

    esperarEnter();
}

void funcaoTema(void) {
    escolherTema();
}

void funcaoSaveLoad(GameState* game) {
    limparTela();
    aplicarTema(tema_ativo);
    
    printf("========================================================================================================\n");
    printf("|                                       SALVAR / CARREGAR JOGO                                         |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("| 1. Salvar Jogo Atual                                                                                 |\n");
    printf("| 2. Carregar Jogo Salvo                                                                               |\n");
    printf("| 3. Deletar Jogo Salvo                                                                                |\n");
    printf("| 0. Voltar ao menu                                                                          |\n");
    printf("========================================================================================================\n\n");
    
    int escolha = lerInteiro("Escolha uma opção: ", 0, 3);
    
    switch (escolha) {
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
        case 0:
            printf("Retornando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida!\n");
            esperarEnter();
            break;
    }
}

void funcaoRanking(void) {
    limparTela();
    aplicarTema(tema_ativo);
    
    printf("========================================================================================================\n");
    printf("|                                          RANKING DOS JOGADORES                                       |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    if (num_ranking_entries == 0) {
        printf("| Nenhum dado de ranking disponível. Jogue algumas partidas para preencher o ranking!                  |\n");
    } else {
        qsort(ranking, num_ranking_entries, sizeof(RankingEntry), compararRankingEntries);
        
        printf("| Pos | %-20s | %-8s | %-8s | %-8s |\n", "Nome", "Vitórias", "Derrotas", "Empates");
        printf("|------------------------------------------------------------------------------------------------------|\n");
        
        for (int i = 0; i < num_ranking_entries; i++) {
            printf("| %-3d | %-20s | %-8d | %-8d | %-8d |\n",
                   i + 1, ranking[i].name, ranking[i].wins, ranking[i].losses, ranking[i].ties);
        }
    }
    
    printf("========================================================================================================\n\n");
    
    esperarEnter();
}

void funcaoSair(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloSaindo();
    
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf(" 1. Desenvolvido... Stella Karolina\n\n");
    printf(" 2. Jogo da Velha versão..: %s\n\n", GAME_VERSION);
    printf("\n");
    printf("                          Volte sempre!\n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
}

void menuPrincipal(GameState* game) {
    int opcao;do {
        limparTela();
        aplicarTema(tema_ativo);
        exibirTituloPrincipal();
        exibirMenuCapa();

        opcao = lerInteiro("Escolha uma opção: ", 1, 8);

        switch (opcao) {
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
            default:
                printf("Opção inválida!\n");
                esperarEnter();
        }
    } while (opcao != 8);
}
