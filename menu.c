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
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                            COMO JOGAR                                                ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.                                      ║\n");
    printf("║ - Dois jogadores se revezam utilizando os símbolos X e O.                                            ║\n");
    printf("║ - O objetivo é alinhar 3 símbolos iguais (X ou O).                                                   ║\n");
    printf("║ - Pode-se vencer alinhando na horizontal, vertical ou diagonal.                                      ║\n");
    printf("║                                                                                                      ║\n");
    printf("║   * TABULEIRO DE REFERÊNCIA:                                                                         ║\n");
    printf("║                                          1 ║ 2 ║ 3                                                   ║\n");
    printf("║                                         ───┼───┼───                                                  ║\n");
    printf("║                                          4 ║ 5 ║ 6                                                   ║\n");
    printf("║                                         ───┼───┼───                                                  ║\n");
    printf("║                                          7 ║ 8 ║ 9                                                   ║\n");
    printf("║                                                                                                      ║\n");
    printf("║   💡 DICAS DE ESTRATÉGIA:                                                                            ║\n");
    printf("║      - Comece pelo centro ou pelos cantos.                                                           ║\n");
    printf("║      - Bloqueie jogadas do adversário.                                                               ║\n");
    printf("║      - Pense duas jogadas à frente!                                                                  ║\n");
    printf("║                                                                                                      ║\n");
    printf("║   Pressione Enter para voltar ao menu...                                                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    esperarEnter();
}

void funcaoCreditos(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloCreditos();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                         CRÉDITOS                                                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║   Curso: Ciências da Computação                                                                      ║\n");
    printf("║   Disciplina: Programação 1                                                                          ║\n");
    printf("║   Projeto prova: jogo da veia                                                                        ║\n");
    printf("║   Autor: Stella Karolina Nunes                                                                       ║\n");
    printf("║   Matrícula: 20223834810                                                                             ║\n");
    printf("║                                                                                                      ║\n");
    printf("║   Versão 1.0  - Data: 2023                                                                           ║\n");
    printf("║   Versão 2.0  - Data: 2025                                                                           ║\n");
    printf("║   Versão 3.0  - Data: 2025                                                                           ║\n");
    printf("║   Versão 4.0  - Data: 2026                                                                           ║\n");
    printf("║                                                                                                      ║\n");
    printf("║ Pressione Enter para voltar ao menu...                                                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    esperarEnter();
}

void funcaoReferencia(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloReferencia();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                            REFERÊNCIAS                                               ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                                      ║\n");
    printf("║    Fontes utilizadas para estudo do jogo da veia:                                                    ║\n");
    printf("║                                                                                                      ║\n");
    printf("║  • Wikipedia - jogo da veia                                                                          ║\n");
    printf("║    https://pt.wikipedia.org/wiki/Jogo_da_ veia                                                         ║\n");
    printf("║                                                                                                      ║\n");
    printf("║  • Wikipedia - Tic-Tac-Toe (versão internacional)                                                     ║\n");
    printf("║    https://en.wikipedia.org/wiki/Tic-tac-toe                                                          ║\n");
    printf("║                                                                                                      ║\n");
    printf("║  • GeeksforGeeks - Tic Tac Toe (Lógica e implementação)                                               ║\n");
    printf("║    https://www.geeksforgeeks.org/tic-tac-toe-game/                                                    ║\n");
    printf("║                                                                                                      ║\n");
    printf("║  • Stanford University - Estratégias de jogos (Game Theory)                                           ║\n");
    printf("║    https://plato.stanford.edu/entries/game-theory/                                                    ║\n");
    printf("║                                                                                                      ║\n");
    printf("║  • Livro: \"The Compleat Strategyst\" - J. D. Williams (Teoria dos Jogos)                             ║\n");
    printf("║                                                                                                      ║\n");
    printf("║    Observação: O jogo da veia é um exemplo clássico de estratégia perfeita.                          ║\n");
    printf("║                                                                                                      ║\n");
    printf("║    Pressione ENTER para voltar ao menu...                                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    esperarEnter();
}

void funcaoTema(void) {
    escolherTema();
}

void funcaoSaveLoad(GameState* game) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloDados();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                       SALVAR / CARREGAR JOGO                                         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ 1. Salvar Jogo Atual                                                                                 ║\n");
    printf("║ 2. Carregar Jogo Salvo                                                                               ║\n");
    printf("║ 3. Deletar Jogo Salvo                                                                                ║\n");
    printf("║ 0. Voltar ao menu                                                                                    ║\n");
    printf("║                                                                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
 
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
            printf("Pressione ENTER para continuar...\n\n");
            esperarEnter();
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
    exibirTituloRanking();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                          RANKING DOS JOGADORES                                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    if (num_ranking_entries == 0) {
        printf("║ Nenhum dado de ranking disponível. Jogue algumas partidas no 'jogo da veia' para preencher!           ║\n");
    } else {
        qsort(ranking, num_ranking_entries, sizeof(RankingEntry), compararRankingEntries);
        
        printf("║ Pos ║ %-38s ║ %-8s ║ %-8s ║ %-8s ║ %-10s ║\n", "Nome", "Vitórias", "Derrotas", "Empates", "Conquistas");
        printf("╠═════║════════════════════════════════════════║══════════║══════════║══════════║════════════╣\n");
        
        for (int i = 0; i < num_ranking_entries; i++) {
            printf("║ %-3d ║ %-38s ║ %-8d ║ %-8d ║ %-8d ║ %-10d ║\n",
                   i + 1, ranking[i].name, ranking[i].wins, ranking[i].losses, ranking[i].ties, ranking[i].medals);
        }
    }
    
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n   Pressione Enter para voltar ao menu...                                                             \n");
    esperarEnter();
}

void funcaoSair(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloSaindo();
    printf("\a\a"); // Beep duplo ao finalizar
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                                                      ║\n");
    printf("║        Obrigado por jogar!                                                                           ║\n");
    printf("║        Desenvolvido por: Stella Karolina                                                             ║\n");
    printf("║        jogo da veia — Versão: %-71s║\n", GAME_VERSION);
    printf("║                                                                                                      ║\n");
    printf("║                                            Volte sempre!!!!!                                         ║\n");
    printf("║                                                                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

    printf("\033[0m"); // reset de cor
}


void menuPrincipal(GameState* game) {
    int opcao;do {
        limparTela();
        aplicarTema(tema_ativo);
        exibirTituloPrincipal();
        exibirMenuCapa();

        opcao = lerInteiro("     Escolha uma opção: ", 1, 8);

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
