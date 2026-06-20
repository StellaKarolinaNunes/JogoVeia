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
        exibirInterfaceJogo(&replay_state, NULL, replayMsg, -1);
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

bool obterNomesJogadores(GameState* game, GameMode mode) {
    bool confirmados = false;
    
    while (!confirmados) {
        exibirTelaConfigurarJogadores(1);
        lerString("", game->nomeJogadorX, MAX_NOME_JOGADOR);
        // If empty, let's just use a default name
        if (strlen(game->nomeJogadorX) == 0) strcpy(game->nomeJogadorX, "Jogador 1");
        
        if (mode == MODE_PLAYER_VS_PLAYER || mode == MODE_INFINITE) {
            exibirTelaConfigurarJogadores(2);
            lerString("", game->nomeJogadorO, MAX_NOME_JOGADOR);
            if (strlen(game->nomeJogadorO) == 0) strcpy(game->nomeJogadorO, "Jogador 2");
        } else {
            strcpy(game->nomeJogadorO, "IA");
        }
        
        int selected_confirm = 0;
        bool confirm_chosen = false;
        
        while (!confirm_chosen) {
            exibirTelaConfirmarJogadores(game->nomeJogadorX, game->nomeJogadorO, selected_confirm);
            KeyCode tecla = lerTeclaMenu();
            
            switch (tecla) {
                case KEY_UP:
                    if (selected_confirm == 0) selected_confirm = 2;
                    else selected_confirm--;
                    break;
                case KEY_DOWN:
                    if (selected_confirm == 2) selected_confirm = 0;
                    else selected_confirm++;
                    break;
                case KEY_ENTER:
                    confirm_chosen = true;
                    break;
                case KEY_Q:
                case KEY_ESC:
                    selected_confirm = 2; // CANCELAR E VOLTAR
                    confirm_chosen = true;
                    break;
                default:
                    break;
            }
        }
        
        if (selected_confirm == 0) {
            confirmados = true;
        } else if (selected_confirm == 1) {
            confirmados = false; // loops again to edit names
        } else if (selected_confirm == 2) {
            return false; // Cancels and returns to menu
        }
    }
    
    return true;
}

void sortearPrimeiroJogador(GameState* game) {
    int dadoJogador1, dadoJogador2;
    do {
        dadoJogador1 = (rand() % 6) + 1;
        dadoJogador2 = (rand() % 6) + 1;
    } while (dadoJogador1 == dadoJogador2);
    
    int sorteado = (dadoJogador1 > dadoJogador2) ? 0 : 1; // 0 -> JogadorX, 1 -> JogadorO
    char* nomeVencedorSorteio = (sorteado == 0) ? game->nomeJogadorX : game->nomeJogadorO;
    
    int selected = 0;
    bool confirm_chosen = false;
    int escolhaSimbolo = 1;
    
    if (sorteado == 1 && strcmp(game->nomeJogadorO, "IA") == 0) {
        exibirTelaSorteio(dadoJogador1, dadoJogador2, game->nomeJogadorX, game->nomeJogadorO, nomeVencedorSorteio, -1);
        esperarEnter();
        escolhaSimbolo = (rand() % 2) + 1; // IA automatically picks 1 or 2
    } else {
        while (!confirm_chosen) {
            exibirTelaSorteio(dadoJogador1, dadoJogador2, game->nomeJogadorX, game->nomeJogadorO, nomeVencedorSorteio, selected);
            KeyCode tecla = lerTeclaMenu();
            
            switch (tecla) {
                case KEY_UP:
                    if (selected == 0) selected = 1;
                    else selected--;
                    break;
                case KEY_DOWN:
                    if (selected == 1) selected = 0;
                    else selected++;
                    break;
                case KEY_ENTER:
                    escolhaSimbolo = selected + 1;
                    confirm_chosen = true;
                    break;
                default:
                    break;
            }
        }
    }
    
    char tempNome[MAX_NOME_JOGADOR];
    if (escolhaSimbolo == 1) { // Jogar com X
        if (sorteado == 1) { // JogadorO won and chose X
            strcpy(tempNome, game->nomeJogadorX);
            strcpy(game->nomeJogadorX, game->nomeJogadorO);
            strcpy(game->nomeJogadorO, tempNome);
        }
    } else { // Jogar com O
        if (sorteado == 0) { // JogadorX won and chose O
            strcpy(tempNome, game->nomeJogadorX);
            strcpy(game->nomeJogadorX, game->nomeJogadorO);
            strcpy(game->nomeJogadorO, tempNome);
        }
    }
    
    game->jogadorAtual = 'X';
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
        int selected_mode = 0; // Starts at 0: JOGADOR VS JOGADOR
        bool mode_chosen = false;
        
        while (!mode_chosen) {
            exibirTelaEscolherModoJogo(selected_mode);
            KeyCode tecla = lerTeclaMenu();
            
            switch (tecla) {
                case KEY_UP:
                    if (selected_mode == 0) selected_mode = 3;
                    else selected_mode--;
                    break;
                case KEY_DOWN:
                    if (selected_mode == 3) selected_mode = 0;
                    else selected_mode++;
                    break;
                case KEY_ENTER:
                    mode_chosen = true;
                    break;
                case KEY_Q:
                case KEY_ESC:
                case KEY_0:
                    return; // Retorna ao Menu Principal
                default:
                    break;
            }
        }
        
        // selected_mode corresponds to indices 0: PVP, 1: PVE, 2: INFINITE, 3: VOLTAR
        if (selected_mode == 3) {
            return; // Voltar ao Menu Principal
        } else if (selected_mode == 0) {
            game->current_mode = MODE_PLAYER_VS_PLAYER;
        } else if (selected_mode == 1) {
            int diff_choice = perguntarDificuldadeIA();
            if (diff_choice == -1) {
                return; // Voltar ao Menu Principal
            }
            game->current_mode = MODE_PLAYER_VS_AI;
            game->ai_difficulty = diff_choice;
        }
        else game->current_mode = MODE_INFINITE;
        
        // NOVO: Seleção de Torneio
        int selected_tourney = 0;
        bool tourney_chosen = false;
        
        while (!tourney_chosen) {
            exibirTelaEscolherTipoPartida(selected_tourney);
            KeyCode tecla = lerTeclaMenu();
            
            switch (tecla) {
                case KEY_UP:
                    if (selected_tourney == 0) selected_tourney = 3;
                    else selected_tourney--;
                    break;
                case KEY_DOWN:
                    if (selected_tourney == 3) selected_tourney = 0;
                    else selected_tourney++;
                    break;
                case KEY_ENTER:
                    tourney_chosen = true;
                    break;
                case KEY_Q:
                case KEY_ESC:
                    return; // Retorna ao Menu Principal
                default:
                    break;
            }
        }
        
        if (selected_tourney == 3) return; // VOLTAR AO MENU PRINCIPAL
        else if (selected_tourney == 1) game->tournament_target_wins = 3;
        else if (selected_tourney == 2) game->tournament_target_wins = 5;
        else game->tournament_target_wins = 0;

        if (!obterNomesJogadores(game, game->current_mode)) return;
    }
    if (is_resumed_game) {
        // Correção: Se o modo carregado for PVP mas o Jogador O for a IA, mudar para modo IA
        if (game->current_mode == MODE_PLAYER_VS_PLAYER && strcmp(game->nomeJogadorO, "IA") == 0) {
            game->current_mode = MODE_PLAYER_VS_AI;
        }
        if (!obterNomesJogadores(game, game->current_mode)) return;
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
                exibirInterfaceJogo(game, winning_line, "PARTIDA CONCLUÍDA!", -1);
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
                exibirInterfaceJogo(game, NULL, "PARTIDA CONCLUÍDA!", -1);
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
                exibirInterfaceJogo(game, NULL, "A IA está pensando...", -1);
                escolhaAcao = obterJogadaIA(game);
                char iaMsg[100];
                snprintf(iaMsg, sizeof(iaMsg), "A IA (%s) jogou na posição %d.", nome_jogador_atual, escolhaAcao);
                exibirInterfaceJogo(game, NULL, iaMsg, -1);
                delaySimples(1500);
            } else {
                int selected_cell = 4; // Start in the middle
                while (true) {
                    char turnMsg[100];
                    snprintf(turnMsg, sizeof(turnMsg), "É a vez do jogador %s (%c)", nome_jogador_atual, game->jogadorAtual);
                    exibirInterfaceJogo(game, NULL, NULL, selected_cell);
                    
                    KeyCode tecla = lerTeclaMenu();
                    if (tecla == KEY_UP) {
                        if (selected_cell >= 3) selected_cell -= 3;
                    } else if (tecla == KEY_DOWN) {
                        if (selected_cell <= 5) selected_cell += 3;
                    } else if (tecla == KEY_LEFT) {
                        if (selected_cell % 3 != 0) selected_cell -= 1;
                    } else if (tecla == KEY_RIGHT) {
                        if (selected_cell % 3 != 2) selected_cell += 1;
                    } else if (tecla == KEY_ENTER) {
                        escolhaAcao = selected_cell + 1;
                        break;
                    } else if (tecla == KEY_0 || tecla == KEY_Q || tecla == KEY_ESC) {
                        escolhaAcao = 0;
                        break;
                    }
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
                        if (perguntarReplayResultado(nome_jogador_atual, game->jogadorAtual, false)) {
                            executarReplay(game);
                        }

                    } else if (game->current_mode != MODE_INFINITE && jogadasFeitas == 9) {
                        game->empates++;
                        strcpy(game->ultimoVencedor, "Empate");
                        atualizarRanking(game->nomeJogadorX, 0);
                        atualizarRanking(game->nomeJogadorO, 0);
                        rodadaTerminada = true;
                        
                        if (perguntarReplayResultado("", ' ', true)) {
                            executarReplay(game);
                        }
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
                    exibirInterfaceJogo(game, NULL, "Posição inválida ou já ocupada!", -1);
                    delaySimples(1500);
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
            jogarNovamente = perguntarJogarNovamente();
            
            if (!jogarNovamente) {
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
