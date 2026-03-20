#include "game.h"
#include "utils.h"
#include "ui.h"
#include "file_manager.h"

void inicializarTabuleiro(GameState* game) {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            game->tabuleiro[i][j] = (char)('0' + count++);
        }
    }
}

bool verificarVitoria(const GameState* game, int* winning_line_indices) {
    if (winning_line_indices != NULL) {
        winning_line_indices[0] = -1;
    }
    for (int i = 0; i < 3; i++) {
        if (game->tabuleiro[i][0] == game->tabuleiro[i][1] && game->tabuleiro[i][1] == game->tabuleiro[i][2]) {
            if (winning_line_indices != NULL) {
                winning_line_indices[0] = i * 3 + 0;
                winning_line_indices[1] = i * 3 + 1;
                winning_line_indices[2] = i * 3 + 2;
            }
            return true;
        }
    }
    for (int j = 0; j < 3; j++) {
        if (game->tabuleiro[0][j] == game->tabuleiro[1][j] && game->tabuleiro[1][j] == game->tabuleiro[2][j]) {
            if (winning_line_indices != NULL) {
                winning_line_indices[0] = 0 * 3 + j;
                winning_line_indices[1] = 1 * 3 + j;
                winning_line_indices[2] = 2 * 3 + j;
            }
            return true;
        }
    }
    if ((game->tabuleiro[0][0] == game->tabuleiro[1][1] && game->tabuleiro[1][1] == game->tabuleiro[2][2])) {
        if (winning_line_indices != NULL) {
            winning_line_indices[0] = 0;
            winning_line_indices[1] = 4;
            winning_line_indices[2] = 8;
        }
        return true;
    }
    if ((game->tabuleiro[0][2] == game->tabuleiro[1][1] && game->tabuleiro[1][1] == game->tabuleiro[2][0])) {
        if (winning_line_indices != NULL) {
            winning_line_indices[0] = 2;
            winning_line_indices[1] = 4;
            winning_line_indices[2] = 6;
        }
        return true;
    }
    return false;
}

bool verificarEmpate(const GameState* game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->tabuleiro[i][j] != 'X' && game->tabuleiro[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

bool fazerJogada(GameState* game, int jogada) {
    if (jogada < 1 || jogada > 9) {
        return false;
    }
    int linha = (jogada - 1) / 3;
    int coluna = (jogada - 1) % 3;
    if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
        game->tabuleiro[linha][coluna] = game->jogadorAtual;
        return true;
    } else {
        printf("Essa posição já está ocupada. Tente novamente.\n");
        esperarEnter();
        return false;
    }
}

void alternarJogador(GameState* game) {
    game->jogadorAtual = (game->jogadorAtual == 'X') ? 'O' : 'X';
}

void obterNomesJogadores(GameState* game, GameMode mode) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();
    printf("========================================================================================================\n");
    printf("|                                --- Configuração de Jogadores ---                                      |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                                      |\n");
    lerString("| Digite o nome do Jogador 1: ", game->nomeJogadorX, MAX_NOME_JOGADOR);
    if (mode == MODE_PLAYER_VS_PLAYER) {
        lerString("| Digite o nome do Jogador 2: ", game->nomeJogadorO, MAX_NOME_JOGADOR);
    } else {
        strcpy(game->nomeJogadorO, "IA");
    }
    printf("|                                                                                                      |\n");
    printf("========================================================================================================\n\n");
    limparTela();
    aplicarTema(tema_ativo);
    printf("========================================================================================================\n");
    printf("|                                   --- Nomes Registrados ---                                          |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                                      |\n");
    printf("| Jogador 'X': %-70s |\n", game->nomeJogadorX);
    printf("| Jogador 'O': %-70s |\n", game->nomeJogadorO);
    printf("|                                                                                                      |\n");
    printf("========================================================================================================\n\n");
    esperarEnter();
}

void sortearPrimeiroJogador(GameState* game) {
    limparTela();
    aplicarTema(tema_ativo);
    printf("========================================================================================================\n");
    printf("|                                  Sorteando o primeiro jogador...                                      |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                                      |\n");
    printf("|             Sorteando o primeiro jogador... ");
    fflush(stdout);
    const char* spinner = "|/-\\";
    for (int i = 0; i < 20; i++) {
        printf("\r|             Sorteando o primeiro jogador... %c", spinner[i % 4]);
        fflush(stdout);
        delaySimples(100);
    }
    printf("\r|                                                                                                      |\n");
    printf("|                                                                                                      |\n");
    int sorteado = rand() % 2;
    char* nomeVencedorSorteio = (sorteado == 0) ? game->nomeJogadorX : game->nomeJogadorO;
    printf("|               O jogador %s ganhou o sorteio!                                                |\n", nomeVencedorSorteio);
    printf("========================================================================================================\n\n");
    esperarEnter();
    limparTela();
    aplicarTema(tema_ativo);
    printf("========================================================================================================\n");
    printf("|                                  Parabéns %s!                                  |\n", nomeVencedorSorteio);
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("| Para esta rodada, escolha seu símbolo:                                                                 |\n");
    printf("|                                                                                                      |\n");
    printf("| 1. Jogar como 'X'                                                                                    |\n");
    printf("| 2. Jogar como 'O'                                                                                    |\n");
    printf("========================================================================================================\n\n");
    int escolhaSimbolo = lerInteiro("Escolha uma opção: ", 1, 2);
    char tempNome[MAX_NOME_JOGADOR];
    if (escolhaSimbolo == 1) {
        if (sorteado == 1) {
            strcpy(tempNome, game->nomeJogadorX);
            strcpy(game->nomeJogadorX, game->nomeJogadorO);
            strcpy(game->nomeJogadorO, tempNome);
        }
    } else {
        if (sorteado == 0) {
            strcpy(tempNome, game->nomeJogadorX);
            strcpy(game->nomeJogadorX, game->nomeJogadorO);
            strcpy(game->nomeJogadorO, tempNome);
        }
    }
    game->jogadorAtual = 'X';
    limparTela();
    aplicarTema(tema_ativo);
    printf("========================================================================================================\n");
    printf("|                                      --- Início da Rodada ---                                        |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                                                                      |\n");
    printf("| Jogador 'X': %-70s |\n", game->nomeJogadorX);
    printf("| Jogador 'O': %-70s |\n", game->nomeJogadorO);
    printf("|                                                                                                      |\n");
    printf("| O jogador %s (X) fará a primeira jogada.                                                             |\n", game->nomeJogadorX);
    printf("========================================================================================================\n\n");
    esperarEnter();
}

int obterJogadaIA(const GameState* game) {
    char ai_char = game->jogadorAtual;
    char opponent_char = (ai_char == 'X') ? 'O' : 'X';
    for (int pos = 1; pos <= 9; pos++) {
        int linha = (pos - 1) / 3;
        int coluna = (pos - 1) % 3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            GameState temp_game = *game;
            temp_game.tabuleiro[linha][coluna] = ai_char;
            int dummy_line[3];
            if (verificarVitoria(&temp_game, dummy_line)) {
                return pos;
            }
        }
    }
    for (int pos = 1; pos <= 9; pos++) {
        int linha = (pos - 1) / 3;
        int coluna = (pos - 1) % 3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            GameState temp_game = *game;
            temp_game.tabuleiro[linha][coluna] = opponent_char;
            int dummy_line[3];
            if (verificarVitoria(&temp_game, dummy_line)) {
                return pos;
            }
        }
    }
    if (game->tabuleiro[1][1] != 'X' && game->tabuleiro[1][1] != 'O') {
        return 5;
    }
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        int linha = (corners[i] - 1) / 3;
        int coluna = (corners[i] - 1) % 3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            return corners[i];
        }
    }
    for (int pos = 1; pos <= 9; pos++) {
        int linha = (pos - 1) / 3;
        int coluna = (pos - 1) % 3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            return pos;
        }
    }
    return -1;
}

void funcaoJogar(GameState* game, bool is_resumed_game) {
    bool jogarNovamente = true;
    GameMode game_mode = MODE_PLAYER_VS_PLAYER;
    if (!is_resumed_game) {
        limparTela();
        aplicarTema(tema_ativo);
        printf("========================================================================================================\n");
        printf("|                                       MODO DE JOGO                                                  |\n");
        printf("|------------------------------------------------------------------------------------------------------|\n");
        printf("| 1. Jogador vs Jogador                                                                                 |\n");
        printf("| 2. Jogador vs IA                                                                                 |\n");
        printf("========================================================================================================\n\n");
        int mode_choice = lerInteiro("Escolha o modo de jogo: ", 1, 2);
        game_mode = (mode_choice == 1) ? MODE_PLAYER_VS_PLAYER : MODE_PLAYER_VS_AI;
        obterNomesJogadores(game, game_mode);
    } else {
        if (strcmp(game->nomeJogadorO, "IA") == 0) {
            game_mode = MODE_PLAYER_VS_AI;
        } else {
            game_mode = MODE_PLAYER_VS_PLAYER;
        }
    }
    while (jogarNovamente) {
        if (!is_resumed_game) {
            inicializarTabuleiro(game);
            sortearPrimeiroJogador(game);
        }
        is_resumed_game = false;
        int jogadasFeitas = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game->tabuleiro[i][j] == 'X' || game->tabuleiro[i][j] == 'O') {
                    jogadasFeitas++;
                }
            }
        }
        bool rodadaTerminada = false;
        int winning_line[3] = {-1, -1, -1};
        while (!rodadaTerminada) {
            exibirInterfaceJogo(game, NULL);
            char* nome_jogador_atual = (game->jogadorAtual == 'X') ? game->nomeJogadorX : game->nomeJogadorO;
            printf("\n\n É a vez do jogador %s (%c).\n", nome_jogador_atual, game->jogadorAtual);
            int escolhaAcao;
            if (game_mode == MODE_PLAYER_VS_AI && game->jogadorAtual == 'O') {
                escolhaAcao = obterJogadaIA(game);
                printf("A IA (%s) jogou na posição %d.\n", game->nomeJogadorO, escolhaAcao);
                delaySimples(1500);
            } else {
                escolhaAcao = lerInteiro("Digite o número da posição (1-9) ou 0 para sair: ", 0, 9);
            }
            if (escolhaAcao == 0) {
                rodadaTerminada = true;
                jogarNovamente = false;
                printf("Saindo do jogo atual...\n");
                esperarEnter();
            } else {
                if (fazerJogada(game, escolhaAcao)) {
                    jogadasFeitas++;
                    delaySimples(500);
                    if (verificarVitoria(game, winning_line)) {
                        exibirInterfaceJogo(game, winning_line);
                        printf("========================================================================================================\n");
                        printf("|                                       PARABÉNS AO VENCEDOR!                                           |\n");
                        printf("|------------------------------------------------------------------------------------------------------|\n");
                        printf("|                                    O jogador %s (%c) venceu a partida!                                     |\n", nome_jogador_atual, game->jogadorAtual);
                        printf("========================================================================================================\n\n");
                        if (game->jogadorAtual == 'X') {
                            game->placarX++;
                        } else {
                            game->placarO++;
                        }
                        strcpy(game->ultimoVencedor, nome_jogador_atual);
                        char* winner_name = nome_jogador_atual;
                        char* loser_name = (game->jogadorAtual == 'X') ? game->nomeJogadorO : game->nomeJogadorX;
                        atualizarRanking(winner_name, 1);
                        atualizarRanking(loser_name, -1);
                        rodadaTerminada = true;
                        esperarEnter();
                    } else if (jogadasFeitas == 9) {
                        exibirInterfaceJogo(game, NULL);
                        printf("========================================================================================================\n");
                        printf("|                                           EMPATE!                                                    |\n");
                        printf("|------------------------------------------------------------------------------------------------------|\n");
                        printf("|                                       O jogo terminou em empate!                                      |\n");
                        printf("========================================================================================================\n\n");
                        game->empates++;
                        strcpy(game->ultimoVencedor, "Empate");
                        atualizarRanking(game->nomeJogadorX, 0);
                        atualizarRanking(game->nomeJogadorO, 0);
                        rodadaTerminada = true;
                        esperarEnter();
                    } else {
                        alternarJogador(game);
                    }
                }
            }
        }
        if (jogarNovamente) {
            limparTela();
            aplicarTema(tema_ativo);
            printf("========================================================================================================\n");
            printf("|                                       DESEJA JOGAR NOVAMENTE?                                          |\n");
            printf("|------------------------------------------------------------------------------------------------------|\n");
            printf("|                             1 - Sim                                0 - Não                            |\n");
            printf("========================================================================================================\n\n");
            int jogarNovamenteInt = lerInteiro("Escolha uma opção: ", 0, 1);
            if (jogarNovamenteInt == 0) {
                jogarNovamente = false;
                limparTela();
                aplicarTema(tema_ativo);
                printf("========================================================================================================\n");
                printf("|                                       DESEJA SALVAR O JOGO?                                            |\n");
                printf("|------------------------------------------------------------------------------------------------------|\n");
                printf("|                             1 - Sim                                0 - Não                            |\n");
                printf("========================================================================================================\n\n");
                int salvarJogoInt = lerInteiro("Escolha uma opção: ", 0, 1);
                if (salvarJogoInt == 1) {
                    salvarJogo(game);
                } else {
                    printf("Jogo não salvo. Retornando ao menu principal...\n");
                    esperarEnter();
                }
            }
        }
    }
    printf("Retornando ao menu principal...\n");
    esperarEnter();
}
