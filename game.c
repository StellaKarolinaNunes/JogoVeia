#include "game.h"
#include "utils.h"
#include "ui.h"
#include "file_manager.h"
#include "theme.h"

void inicializarTabuleiro(GameState* game) {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            game->tabuleiro[i][j] = (char)('0' + count++);
        }
    }
    game->numJogadasX = 0;
    game->numJogadasO = 0;
    game->total_moves_count = 0; // REPLAY
    for (int i = 0; i < 3; i++) {
        game->historicoJogadasX[i] = -1;
        game->historicoJogadasO[i] = -1;
    }
}

void executarReplay(const GameState* game) {
    limparTela();
    printf("   🎬 INICIANDO REPLAY DA PARTIDA... 🎬\n");
    delaySimples(1000);
    
    GameState replay_state = *game;
    // Reiniciar tabuleiro para o replay
    int count = 1;
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) replay_state.tabuleiro[i][j] = (char)('0' + count++);
    
    char curr_p = 'X'; // Assume X começou (ou pode ser dinâmico, mas simplificando)
    // Na verdade, precisamos saber quem começou. Vamos assumir que o histórico registra a ordem exata.

    for (int i = 0; i < game->total_moves_count; i++) {
        int pos = game->full_move_history[i];
        int r = (pos-1)/3, c = (pos-1)%3;
        
        replay_state.tabuleiro[r][c] = curr_p;
        char replayMsg[100];
        snprintf(replayMsg, sizeof(replayMsg), "Reproduzindo jogada %d/%d (Jogador %c na posição %d)", i+1, game->total_moves_count, curr_p, pos);
        exibirInterfaceJogo(&replay_state, NULL, replayMsg);
        printf("\n   Reproduzindo jogada %d/%d (Jogador %c na posição %d)...\n", i+1, game->total_moves_count, curr_p, pos);
        delaySimples(1200);
        curr_p = (curr_p == 'X') ? 'O' : 'X';
    }
    printf("\n   FIM DO REPLAY. Pressione Enter para voltar.\n");
    esperarEnter();
}

void verificarEAtribuirMedalhas(const char* nome, bool venceu, bool empate, bool contra_ia, int dificuldade) {
    if (strcmp(nome, "IA") == 0 || strcmp(nome, "Nenhum") == 0) return;
    
    int idx = -1;
    for (int i = 0; i < num_ranking_entries; i++) {
        if (strcmp(ranking[i].name, nome) == 0) { idx = i; break; }
    }
    if (idx == -1) return;

    if (venceu) {
        if (contra_ia && dificuldade == DIFFICULTY_HARD) {
            ranking[idx].medals++;
            exibirConquista("Mestre da IA (Venceu IA no Difícil)");
        } else if (ranking[idx].wins == 1) {
            ranking[idx].medals++;
            exibirConquista("Primeira Vitória!");
        }
    } else if (empate) {
        if (ranking[idx].ties >= 10) {
            ranking[idx].medals++;
            exibirConquista("Empatador Profissional (10+ empates)");
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

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  --- Configuração de Jogadores ---                                   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                                      ║\n");
    lerString("║ Digite o nome do Jogador 1: ", game->nomeJogadorX, MAX_NOME_JOGADOR);
    if (mode == MODE_PLAYER_VS_PLAYER || mode == MODE_INFINITE) {
        lerString("║ Digite o nome do Jogador 2: ", game->nomeJogadorO, MAX_NOME_JOGADOR);
    } else {
        strcpy(game->nomeJogadorO, "IA");
    }
    printf("║                                                                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                     --- Nomes Registrados ---                                        ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                                      ║\n");
    printf("║  Jogador X: %-85s║\n", game->nomeJogadorX);
    printf("║  Jogador O: %-85s║\n", game->nomeJogadorO);
    printf("║                                                                                                      ║\n");
    printf("║   Pressione Enter para continuar...                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    esperarEnter();
}

void sortearPrimeiroJogador(GameState* game) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    char sorteioTitle[] = "Sorteando o primeiro jogador...";
    int vlenST = visible_strlen(sorteioTitle);
    int leftST = (100 - vlenST) / 2;
    int rightST = 100 - vlenST - leftST;
    printf("║");
    for (int k = 0; k < leftST; k++) putchar(' ');
    printf("%s", sorteioTitle);
    for (int k = 0; k < rightST; k++) putchar(' ');
    printf("║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                                      ║\n");
    const char* spinner = "|/-\\";
    for (int i = 0; i < 20; i++) {
        char spinnerLine[100];
        snprintf(spinnerLine, sizeof(spinnerLine), "             Sorteando o primeiro jogador... %c", spinner[i % 4]);
        int vlenSL = visible_strlen(spinnerLine);
        printf("\r║%-100s║", spinnerLine);
        fflush(stdout);
        delaySimples(100);
    }
    printf("\r║                                                                                                      ║\n");
    printf("║                                                                                                      ║\n");
    int sorteado = rand() % 2;
    char* nomeVencedorSorteio = (sorteado == 0) ? game->nomeJogadorX : game->nomeJogadorO;
    char sorteioMsg[100];
    snprintf(sorteioMsg, sizeof(sorteioMsg), "O jogador %s ganhou o sorteio!", nomeVencedorSorteio);
    int vlenS = visible_strlen(sorteioMsg);
    int leftS = (100 - vlenS) / 2;
    int rightS = 100 - vlenS - leftS;
    printf("║");
    for (int k = 0; k < leftS; k++) putchar(' ');
    printf("%s", sorteioMsg);
    for (int k = 0; k < rightS; k++) putchar(' ');
    printf("║\n");
    printf("║                                                                                                      ║\n");
    printf("║   Pressione Enter para continuar...                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    esperarEnter();
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    char vmsg[100];
    snprintf(vmsg, sizeof(vmsg), "O jogador %s ganhou o sorteio!", nomeVencedorSorteio);
    int vlenV = visible_strlen(vmsg);
    int leftV = (100 - vlenV) / 2;
    int rightV = 100 - vlenV - leftV;
    printf("║");
    for(int k=0; k<leftV; k++) putchar(' ');
    printf("%s", vmsg);
    for(int k=0; k<rightV; k++) putchar(' ');
    printf("║\n");
    printf("║                                                                                                      ║\n");
    printf("║   Pressione Enter para continuar...                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    esperarEnter();
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloPrincipal();

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    char parabensM[100];
    snprintf(parabensM, sizeof(parabensM), "Parabéns %s!", nomeVencedorSorteio);
    int vlenP = visible_strlen(parabensM);
    int leftP = (100 - vlenP) / 2;
    int rightP = 100 - vlenP - leftP;
    printf("║");
    for(int k=0; k<leftP; k++) putchar(' '); printf("%s", parabensM); for(int k=0; k<rightP; k++) putchar(' ');
    printf("║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Para esta rodada, escolha seu símbolo:                                                               ║\n");
    printf("║                                                                                                      ║\n");
    printf("║ 1. Jogar como 'X'                                                                                    ║\n");
    printf("║ 2. Jogar como 'O'                                                                                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    int escolhaSimbolo;
    if (sorteado == 1 && strcmp(game->nomeJogadorO, "IA") == 0) {
        escolhaSimbolo = (rand() % 2) + 1;
        printf("║ A IA escolheu jogar como '%s'.                                                                      ║\n", (escolhaSimbolo == 1) ? "X" : "O");
        delaySimples(1500);
    } else {
        escolhaSimbolo = lerInteiro("Escolha uma opção: ", 1, 2);
    }
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
    exibirTituloPrincipal();

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    char titleStartRound[] = "--- Início da Rodada ---";
    int vlenTSR = visible_strlen(titleStartRound);
    int leftTSR = (100 - vlenTSR) / 2;
    int rightTSR = 100 - vlenTSR - leftTSR;
    printf("║");
    for (int k = 0; k < leftTSR; k++) putchar(' ');
    printf("%s", titleStartRound);
    for (int k = 0; k < rightTSR; k++) putchar(' ');
    printf("║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                                      ║\n");
    printf("║  Jogador X: %-85s║\n", game->nomeJogadorX);
    printf("║  Jogador O: %-85s║\n", game->nomeJogadorO);
    printf("║                                                                                                      ║\n");
    printf("║ O jogador %s (X) fará a primeira jogada.                                                             ║\n", game->nomeJogadorX);
    printf("║                                                                                                      ║\n");
    printf("║   Pressione Enter para continuar...                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    esperarEnter();
}

int minimax(GameState* game, int depth, bool isMaximizing, char ai_char, char opponent_char, int alpha, int beta) {
    int winning_line[3];
    if (verificarVitoria(game, winning_line)) {
        // Se venceu e era a vez do oponente maximizar (isMaximizing=true), 
        // significa que quem jogou por último (IA) ganhou.
        return isMaximizing ? (-20 + depth) : (20 - depth);
    }
    if (verificarEmpate(game)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int pos = 1; pos <= 9; pos++) {
            int r = (pos-1)/3, c = (pos-1)%3;
            if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') {
                char original = game->tabuleiro[r][c];
                game->tabuleiro[r][c] = ai_char;
                int score = minimax(game, depth + 1, false, ai_char, opponent_char, alpha, beta);
                game->tabuleiro[r][c] = original;
                if (score > bestScore) bestScore = score;
                if (score > alpha) alpha = score;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int pos = 1; pos <= 9; pos++) {
            int r = (pos-1)/3, c = (pos-1)%3;
            if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') {
                char original = game->tabuleiro[r][c];
                game->tabuleiro[r][c] = opponent_char;
                int score = minimax(game, depth + 1, true, ai_char, opponent_char, alpha, beta);
                game->tabuleiro[r][c] = original;
                if (score < bestScore) bestScore = score;
                if (score < beta) beta = score;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
}

int obterJogadaIA(GameState* game) {
    if (game->ai_difficulty == DIFFICULTY_EASY) {
        int disponiveis[9];
        int num_disponiveis = 0;
        for (int pos = 1; pos <= 9; pos++) {
            int r = (pos-1)/3, c = (pos-1)%3;
            if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') {
                disponiveis[num_disponiveis++] = pos;
            }
        }
        if (num_disponiveis > 0) {
            return disponiveis[rand() % num_disponiveis];
        }
    }

    if (game->ai_difficulty == DIFFICULTY_HARD) {
        char ai_char = game->jogadorAtual;
        char opponent_char = (ai_char == 'X') ? 'O' : 'X';
        int bestScore = -1000;
        int move = -1;
        for (int pos = 1; pos <= 9; pos++) {
            int r = (pos-1)/3, c = (pos-1)%3;
            if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') {
                char original = game->tabuleiro[r][c];
                game->tabuleiro[r][c] = ai_char;
                int score = minimax(game, 0, false, ai_char, opponent_char, -1000, 1000);
                game->tabuleiro[r][c] = original;
                if (score > bestScore) {
                    bestScore = score;
                    move = pos;
                }
            }
        }
        return move;
    }

    // Médio (comportamento original)
    char ai_char = game->jogadorAtual;
    char opponent_char = (ai_char == 'X') ? 'O' : 'X';
    for (int pos = 1; pos <= 9; pos++) {
        int linha = (pos-1)/3, coluna = (pos-1)%3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            GameState temp = *game;
            temp.tabuleiro[linha][coluna] = ai_char;
            int dummy[3];
            if (verificarVitoria(&temp, dummy)) return pos;
        }
    }
    for (int pos = 1; pos <= 9; pos++) {
        int linha = (pos-1)/3, coluna = (pos-1)%3;
        if (game->tabuleiro[linha][coluna] != 'X' && game->tabuleiro[linha][coluna] != 'O') {
            GameState temp = *game;
            temp.tabuleiro[linha][coluna] = opponent_char;
            int dummy[3];
            if (verificarVitoria(&temp, dummy)) return pos;
        }
    }
    if (game->tabuleiro[1][1] != 'X' && game->tabuleiro[1][1] != 'O') return 5;
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        int r = (corners[i]-1)/3, c = (corners[i]-1)%3;
        if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') return corners[i];
    }
    for (int pos = 1; pos <= 9; pos++) {
        int r = (pos-1)/3, c = (pos-1)%3;
        if (game->tabuleiro[r][c] != 'X' && game->tabuleiro[r][c] != 'O') return pos;
    }
    return -1;
}

void funcaoJogar(GameState* game, bool is_resumed_game) {
    bool jogarNovamente = true;
    if (!is_resumed_game) {
        limparTela();
        aplicarTema(tema_ativo);
        exibirTituloModoJogo();
              printf("\n");
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                       MODO DE JOGO                                                   ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ 1. Jogador vs Jogador                                                                                ║\n");
        printf("║ 2. Jogador vs IA                                                                                     ║\n");
        printf("║ 3. Modo Infinito (Apenas 3 peças no tabuleiro)                                                       ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        int mode_choice = lerInteiro("Escolha o modo de jogo: ", 1, 3);
        if (mode_choice == 1) game->current_mode = MODE_PLAYER_VS_PLAYER;
        else if (mode_choice == 2) {
            game->current_mode = MODE_PLAYER_VS_AI;
            limparTela();
            aplicarTema(tema_ativo);
            printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                      --- DIFICULDADE IA ---                                          ║\n");
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║ 1. Fácil (Movimentos Aleatórios)                                                                     ║\n");
            printf("║ 2. Médio (Estratégico)                                                                               ║\n");
            printf("║ 3. Difícil (Imbatível)                                                                               ║\n");
            printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
            int diff_choice = lerInteiro("Escolha a dificuldade (1-3): ", 1, 3);
            game->ai_difficulty = diff_choice - 1;
        }
        else game->current_mode = MODE_INFINITE;
        
        // NOVO: Seleção de Torneio
        limparTela();
        aplicarTema(tema_ativo);
        exibirTituloPrincipal();
        printf("\n");
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                       TIPO DE PARTIDA                                                ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ 0. Partida Única (Padrão)                                                                            ║\n");
        printf("║ 1. Melhor de 3 (Torneio)                                                                             ║\n");
        printf("║ 2. Melhor de 5 (Torneio)                                                                             ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        int tourney_choice = lerInteiro("Escolha o tipo: ", 0, 2);
        if (tourney_choice == 1) game->tournament_target_wins = 3;
        else if (tourney_choice == 2) game->tournament_target_wins = 5;
        else game->tournament_target_wins = 0;

        obterNomesJogadores(game, game->current_mode);
    }
    if (is_resumed_game) {
        // Correção: Se o modo carregado for PVP mas o Jogador O for a IA, mudar para modo IA
        if (game->current_mode == MODE_PLAYER_VS_PLAYER && strcmp(game->nomeJogadorO, "IA") == 0) {
            game->current_mode = MODE_PLAYER_VS_AI;
        }
    }

    while (jogarNovamente) {
        if (!is_resumed_game) {
            inicializarTabuleiro(game);
            sortearPrimeiroJogador(game);
        }
        
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

        if (is_resumed_game) {
            if (!(verificarVitoria(game, winning_line) || (game->current_mode != MODE_INFINITE && jogadasFeitas == 9))) {
                is_resumed_game = false;
            }
            // Note: Se for terminal, is_resumed_game continua true para pular o sorteio/inicialização 
            // no início da rodada, mas a rodada terminada resetará tudo.
        }

        while (!rodadaTerminada) {
            // Se já estiver em estado terminal quando carregar
            if (verificarVitoria(game, winning_line)) {
                exibirInterfaceJogo(game, winning_line, "PARTIDA CONCLUÍDA!");
                printf("\a");
                printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                printf("║                                       FIM DE JOGO CARREGADO!                                         ║\n");
                printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
                char* vencedor = (game->tabuleiro[winning_line[0] / 3][winning_line[0] % 3] == 'X') ? game->nomeJogadorX : game->nomeJogadorO;
                printf("║                            🏆 Este jogo já estava vencido por: %-38s! ║\n", vencedor);
                printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                rodadaTerminada = true;
                is_resumed_game = false; // Reset imediato após detecção
                esperarEnter();
                break;
            } else if (game->current_mode != MODE_INFINITE && jogadasFeitas == 9) {
                exibirInterfaceJogo(game, NULL, "PARTIDA CONCLUÍDA!");
                printf("\a"); // Beep de empate
                printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                printf("║                                       FIM DE JOGO CARREGADO!                                         ║\n");
                printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
                printf("║                                  ⚖️  Este jogo terminou em EMPATE! ⚖️                                 ║\n");
                printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                rodadaTerminada = true;
                is_resumed_game = false; // Reset imediato após detecção
                esperarEnter();
                break;
            }

            char* nome_jogador_atual = (game->jogadorAtual == 'X') ? game->nomeJogadorX : game->nomeJogadorO;
            int escolhaAcao = -1;
            
            if (game->current_mode == MODE_PLAYER_VS_AI && strcmp(nome_jogador_atual, "IA") == 0) {
                exibirInterfaceJogo(game, NULL, "A IA está pensando...");
                escolhaAcao = obterJogadaIA(game);
                char iaMsg[100];
                snprintf(iaMsg, sizeof(iaMsg), "A IA (%s) jogou na posição %d.", nome_jogador_atual, escolhaAcao);
                exibirInterfaceJogo(game, NULL, iaMsg);
                delaySimples(1500);
            } else {
                while (true) {
                    char turnMsg[100];
                    snprintf(turnMsg, sizeof(turnMsg), "É a vez do jogador %s (%c)", nome_jogador_atual, game->jogadorAtual);
                    exibirInterfaceJogo(game, NULL, turnMsg);
                    
                    printf("\n Digite o número da posição (1-9) ou 0 para sair: ");
                    if (scanf("%d", &escolhaAcao) == 1) {
                        limparBufferEntrada();
                        if (escolhaAcao >= 0 && escolhaAcao <= 9) {
                            break;
                        }
                        exibirInterfaceJogo(game, NULL, "Valor fora do intervalo permitido (0-9). tente novamente.");
                    } else {
                        limparBufferEntrada();
                        exibirInterfaceJogo(game, NULL, "Entrada inválida! Digite um número de 0 a 9.");
                    }
                    delaySimples(1500);
                }
            }
            if (escolhaAcao == 0) {
                rodadaTerminada = true;
                jogarNovamente = false;
                printf("Saindo do jogo atual...\n");
                esperarEnter();
            } else {
                if (fazerJogada(game, escolhaAcao)) {
                    // REGISTRAR NO REPLAY
                    if (game->total_moves_count < 9) {
                        game->full_move_history[game->total_moves_count++] = escolhaAcao;
                    }

                    jogadasFeitas++;
                    delaySimples(500);
                    if (verificarVitoria(game, winning_line)) {
                        animarVitoria(game, winning_line); // ANIMAÇÃO
                        
                        exibirInterfaceJogo(game, winning_line, "VITÓRIA DETECTADA!");
                        printf("\a"); // Beep de vitória
                        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                        printf("║                                       PARABÉNS AO VENCEDOR!                                          ║\n");
                        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
                        printf("║                            🏆 Jogador: %-38s Símbolo: (%c) venceu a partida! ║\n", nome_jogador_atual, game->jogadorAtual);
                        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                        
                        if (game->jogadorAtual == 'X') game->placarX++;
                        else game->placarO++;

                        strcpy(game->ultimoVencedor, nome_jogador_atual);
                        
                        // ACHIEVEMENTS
                        bool contra_ia = (game->current_mode == MODE_PLAYER_VS_AI);
                        verificarEAtribuirMedalhas(nome_jogador_atual, true, false, contra_ia, game->ai_difficulty);

                        char* winner_name = nome_jogador_atual;
                        char* loser_name = (game->jogadorAtual == 'X') ? game->nomeJogadorO : game->nomeJogadorX;
                        atualizarRanking(winner_name, 1);
                        atualizarRanking(loser_name, -1);
                        
                        rodadaTerminada = true;
                        
                        // REPLAY PROMPT
                        printf("Deseja ver o REPLAY desta rodada? (1-Sim, 0-Pular): ");
                        if (lerInteiro("", 0, 1) == 1) executarReplay(game);

                        esperarEnter();
                    } else if (game->current_mode != MODE_INFINITE && jogadasFeitas == 9) {
                        exibirInterfaceJogo(game, NULL, "EMPATE!");
                        printf("\a"); // Beep de empate
                        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                        printf("║                                           EMPATE!                                                    ║\n");
                        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
                        printf("║                                  ⚖️  O jogo terminou sem vencedor! ⚖️                                 ║\n");
                        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                        game->empates++;
                        strcpy(game->ultimoVencedor, "Empate");
                        atualizarRanking(game->nomeJogadorX, 0);
                        atualizarRanking(game->nomeJogadorO, 0);
                        rodadaTerminada = true;
                        esperarEnter();
                    } else {
                        if (game->current_mode == MODE_INFINITE) {
                            if (game->jogadorAtual == 'X') {
                                if (game->numJogadasX == 3) {
                                    int pos_remover = game->historicoJogadasX[0];
                                    int r = (pos_remover - 1) / 3;
                                    int c = (pos_remover - 1) % 3;
                                    game->tabuleiro[r][c] = (char)('0' + pos_remover);
                                    game->historicoJogadasX[0] = game->historicoJogadasX[1];
                                    game->historicoJogadasX[1] = game->historicoJogadasX[2];
                                    game->historicoJogadasX[2] = escolhaAcao;
                                } else {
                                    game->historicoJogadasX[game->numJogadasX++] = escolhaAcao;
                                }
                            } else {
                                if (game->numJogadasO == 3) {
                                    int pos_remover = game->historicoJogadasO[0];
                                    int r = (pos_remover - 1) / 3;
                                    int c = (pos_remover - 1) % 3;
                                    game->tabuleiro[r][c] = (char)('0' + pos_remover);
                                    game->historicoJogadasO[0] = game->historicoJogadasO[1];
                                    game->historicoJogadasO[1] = game->historicoJogadasO[2];
                                    game->historicoJogadasO[2] = escolhaAcao;
                                } else {
                                    game->historicoJogadasO[game->numJogadasO++] = escolhaAcao;
                                }
                            }
                        }
                        alternarJogador(game);
                    }
                } else if (escolhaAcao != 0) {
                    printf("Essa posição já está ocupada. Tente novamente.\n");
                    esperarEnter();
                }
            }
        }
        
        // NOVO: Verificar Fim do Torneio
        if (game->tournament_target_wins > 0) {
            if (game->placarX >= game->tournament_target_wins) {
                exibirTrofeu(game->nomeJogadorX);
                jogarNovamente = false;
            } else if (game->placarO >= game->tournament_target_wins) {
                exibirTrofeu(game->nomeJogadorO);
                jogarNovamente = false;
            }
        }

        if (jogarNovamente) {
            limparTela();
            aplicarTema(tema_ativo);
            exibirTituloDados();

            printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                                       DESEJA JOGAR NOVAMENTE?                                          ║\n");
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║                             1 - Sim                                0 - Não                            ║\n");
            printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
            int jogarNovamenteInt = lerInteiro("Escolha uma opção: ", 0, 1);
            if (jogarNovamenteInt == 0) {
                jogarNovamente = false;
                limparTela();
                aplicarTema(tema_ativo);
                exibirTituloPrincipal();

                printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                printf("║                                       DESEJA SALVAR O JOGO?                                            ║\n");
                printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
                printf("║                             1 - Sim                                0 - Não                            ║\n");
                printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
                int salvarJogoInt = lerInteiro("Escolha uma opção: ", 0, 1);
                if (salvarJogoInt == 1) {
                    salvarJogo(game);
                } else {
                    printf("Jogo não salvo. Retornando ao menu principal...\n");
                    printf("Pressione ENTER para continuar...\n\n");
                    esperarEnter();
                }
            }
        }
    }
    printf("Retornando ao menu principal...\n");
    esperarEnter();
}
