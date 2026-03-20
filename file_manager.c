#include "file_manager.h"
#include "utils.h"
#include "theme.h"
#include "ui.h"

#define SETTINGS_FILE "settings.cfg"

static void applyCrypto(char* data) {
    if (data == NULL) return;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '\n' || data[i] == '\r') continue; // Manter quebras de linha legíveis para fgets mas conteúdo cifrado
        data[i] ^= CRYPTO_KEY;
    }
}

bool criarDiretorioSaves(void) {
    int result = MKDIR(SAVE_DIR);
    if (result == 0 || errno == EEXIST) {
        return true;
    }
    printf("Erro ao criar diretório '%s': %s\n", SAVE_DIR, strerror(errno));
    return false;
}

FILE* abrirArquivo(const char* path, const char* mode) {
    FILE* file = fopen(path, mode);
    if (file == NULL) {
        printf("Erro ao abrir arquivo '%s': %s\n", path, strerror(errno));
    }
    return file;
}

void fecharArquivo(FILE* file) {
    if (file != NULL) {
        fclose(file);
    }
}

bool escreverLinhaFormatada(FILE* file, const char* format, ...) {
    if (file == NULL) return false;
    
    va_list args;
    va_start(args, format);
    int result = vfprintf(file, format, args);
    va_end(args);
    
    return result >= 0;
}

void carregarRanking(void) {
    FILE *file = abrirArquivo(RANKING_FILE, "rb");
    if (file == NULL) {
        return;
    }
    
    num_ranking_entries = 0;
    while (num_ranking_entries < MAX_RANKING_ENTRIES &&
           fread(&ranking[num_ranking_entries], sizeof(RankingEntry), 1, file) == 1) {
        num_ranking_entries++;
    }
    
    fecharArquivo(file);
}

void salvarRanking(void) {
    FILE *file = abrirArquivo(RANKING_FILE, "wb");
    if (file == NULL) {
        return;
    }
    
    fwrite(ranking, sizeof(RankingEntry), num_ranking_entries, file);
    fecharArquivo(file);
}

void atualizarRanking(const char* player_name, int result_type) {
    if (player_name == NULL || strlen(player_name) == 0) return;

    int found_index = -1;
    for (int i = 0; i < num_ranking_entries; i++) {
        if (strcmp(ranking[i].name, player_name) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        if (num_ranking_entries < MAX_RANKING_ENTRIES) {
            found_index = num_ranking_entries++;
            strncpy(ranking[found_index].name, player_name, MAX_NOME_JOGADOR - 1);
            ranking[found_index].name[MAX_NOME_JOGADOR - 1] = '\0';
            ranking[found_index].wins = 0;
            ranking[found_index].losses = 0;
            ranking[found_index].ties = 0;
            ranking[found_index].medals = 0; // INICIALIZAÇÃO IMPORTANTE
        } else {
            return;
        }
    }
    
    switch (result_type) {
        case 1: ranking[found_index].wins++; break;
        case 0: ranking[found_index].ties++; break;
        case -1: ranking[found_index].losses++; break;
    }
}

void salvarConfiguracoes(void) {
    FILE* file = abrirArquivo(SETTINGS_FILE, "w");
    if (file != NULL) {
        fprintf(file, "tema_ativo:%d\n", tema_ativo);
        fecharArquivo(file);
    }
}

void carregarConfiguracoes(void) {
    FILE* file = abrirArquivo(SETTINGS_FILE, "r");
    if (file != NULL) {
        if (fscanf(file, "tema_ativo:%d", &tema_ativo) != 1) {
            tema_ativo = 0;
        }
        fecharArquivo(file);
    }
}

int compararRankingEntries(const void* a, const void* b) {
    const RankingEntry* entryA = (const RankingEntry*)a;
    const RankingEntry* entryB = (const RankingEntry*)b;
    
    if (entryA->wins != entryB->wins) {
        return entryB->wins - entryA->wins;
    }
    
    if (entryA->losses != entryB->losses) {
        return entryA->losses - entryB->losses;
    }
    
    return entryB->ties - entryA->ties;
}

void salvarJogo(GameState* game) {
    if (!criarDiretorioSaves()) {
        esperarEnter();
        return;
    }
    
    char save_name[MAX_NOME_JOGADOR] = "";
    char filename[MAX_LINE_BUFFER] = "";
    bool sobrescrever = false;

    if (strlen(game->loaded_filename) > 0) {
        printf("Você carregou este jogo do arquivo: %s\n", game->loaded_filename);
        printf("Deseja sobrescrever este arquivo? (1 - Sim, 0 - Novo Salvamento): ");
        int op = lerInteiro("", 0, 1);
        if (op == 1) {
            strncpy(filename, game->loaded_filename, MAX_LINE_BUFFER - 1);
            
            // Tenta extrair o nome do salvamento original do caminho
            char *base = strrchr(filename, '/');
            if (!base) base = strrchr(filename, '\\');
            if (base) base++; else base = filename;
            
            char temp_n[MAX_LINE_BUFFER];
            strncpy(temp_n, base, MAX_LINE_BUFFER-1);
            char *underscore = strchr(temp_n, '_');
            if (underscore) *underscore = '\0';
            strncpy(save_name, temp_n, MAX_NOME_JOGADOR - 1);
            
            sobrescrever = true;
        }
    }

    if (!sobrescrever) {
        printf("Deseja escolher um salvamento da lista para sobrescrever? (1 - Sim, 0 - Criar Novo): ");
        int op_list = lerInteiro("", 0, 1);
        if (op_list == 1) {
            SaveInfo available_saves[MAX_SAVES];
            int num_available_saves = listarSaves(available_saves, MAX_SAVES);
            if (num_available_saves > 0) {
                printf("Selecione qual salvamento sobrescrever (ou 0 para cancelar): ");
                int sel = lerInteiro("", 0, num_available_saves);
                if (sel > 0) {
                    strncpy(filename, available_saves[sel-1].filename, MAX_LINE_BUFFER-1);
                    strncpy(save_name, available_saves[sel-1].save_name, MAX_NOME_JOGADOR-1);
                    sobrescrever = true;
                }
            } else {
                printf("Nenhum salvamento disponível na lista.\n");
            }
        }
    }

    if (!sobrescrever) {
        lerString("Digite um nome para o seu novo salvamento: ", save_name, sizeof(save_name));
        if (strlen(save_name) == 0) {
            printf("Nome do salvamento não pode ser vazio. Cancelando salvamento.\n");
            printf("Pressione ENTER para continuar...\n\n");
            esperarEnter();
            return;
        }

        time_t rawtime;
        struct tm *info;
        char timestamp[80];
        time(&rawtime);
        info = localtime(&rawtime);
        strftime(timestamp, 80, "%Y%m%d_%H%M%S", info);
        snprintf(filename, sizeof(filename), "%s/%s_%s.txt", SAVE_DIR, save_name, timestamp);
    }
    
    char data_to_checksum[MAX_CHECKSUM_BUFFER];
    time_t rawtime_now;
    struct tm *info_now;
    char timestamp_now[80];
    time(&rawtime_now);
    info_now = localtime(&rawtime_now);
    strftime(timestamp_now, 80, "%Y%m%d_%H%M%S", info_now);
    
    FILE *file = abrirArquivo(filename, "w");
    if (file == NULL) {
        printf("Pressione ENTER para continuar...\n\n");
        esperarEnter();
        return;
    }
    
    snprintf(data_to_checksum, sizeof(data_to_checksum),
        "--- jogo da veia - Salvo ---\n"
        "Nome do Salvamento: %s\n"
        "Versão do Jogo: %s\n"
        "Data e Hora: %s\n"
        "Modo: %d\n"
        "Dificuldade: %d\n"
        "\n"
        "--- Jogadores ---\n"
        "Jogador X: %s\n"
        "Jogador O: %s\n"
        "\n"
        "--- Placar ---\n"
        "Vitorias X: %d\n"
        "Vitorias O: %d\n"
        "Empates: %d\n"
        "\n"
        "--- Último Vencedor ---\n"
        "Vencedor: %s\n"
        "\n"
        "--- Estado do Jogo ---\n"
        "Hist X: %d %d %d\n"
        "Hist O: %d %d %d\n"
        "Num Jogadas X: %d\n"
        "Num Jogadas O: %d\n"
        "--- Tabuleiro ---\n"
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n"
        "Jogador Atual: %c\n",
        save_name, GAME_VERSION, timestamp_now,
        (int)game->current_mode, game->ai_difficulty,
        game->nomeJogadorX, game->nomeJogadorO,
        game->placarX, game->placarO, game->empates,
        game->ultimoVencedor,
        game->historicoJogadasX[0], game->historicoJogadasX[1], game->historicoJogadasX[2],
        game->historicoJogadasO[0], game->historicoJogadasO[1], game->historicoJogadasO[2],
        game->numJogadasX, game->numJogadasO,
        game->tabuleiro[0][0], game->tabuleiro[0][1], game->tabuleiro[0][2],
        game->tabuleiro[1][0], game->tabuleiro[1][1], game->tabuleiro[1][2],
        game->tabuleiro[2][0], game->tabuleiro[2][1], game->tabuleiro[2][2],
        game->jogadorAtual);
    
    unsigned int checksum = calcularChecksum(data_to_checksum);
    
    // CRIPTOGRAFAR ANTES DE SALVAR
    applyCrypto(data_to_checksum);

    fprintf(file, "%s", data_to_checksum);
    fprintf(file, "\n--- Checksum ---\n%u\n", checksum);
    
    fecharArquivo(file);
    strncpy(game->loaded_filename, filename, MAX_LINE_BUFFER-1);
    
    printf("\a"); // Beep de sucesso
    printf("Jogo salvo com sucesso!\n");
    printf("Pressione ENTER para continuar...\n\n");
    esperarEnter();
}

int listarSaves(SaveInfo* saves_array, int max_saves) {
    int num_saves = 0;
    
    #ifdef _WIN32
    system("dir /b " SAVE_DIR "\\*.txt > saves_list.tmp 2>nul");
    #else
    system("ls " SAVE_DIR "/*.txt > saves_list.tmp 2>/dev/null");
    #endif
    
    FILE *list_file = abrirArquivo("saves_list.tmp", "r");
    if (list_file == NULL) {
        printf("Nenhum arquivo de salvamento encontrado ou erro ao listar.\n");
        return 0;
    }
    
    char line_filename[MAX_LINE_BUFFER];
    while (fgets(line_filename, sizeof(line_filename), list_file) != NULL && num_saves < max_saves) {
        line_filename[strcspn(line_filename, "\n")] = 0;
        
        char full_path[1024];
        #ifdef _WIN32
        snprintf(full_path, sizeof(full_path), "%s\\%s", SAVE_DIR, line_filename);
        #else
        if (strstr(line_filename, SAVE_DIR) == NULL) {
            snprintf(full_path, sizeof(full_path), "%s/%s", SAVE_DIR, line_filename);
        } else {
            strcpy(full_path, line_filename);
        }
        #endif
        
        FILE *save_file = abrirArquivo(full_path, "r");
        if (save_file != NULL) {
            char temp_line[MAX_LINE_BUFFER];
            char temp_save_name[MAX_NOME_JOGADOR] = "Sem Nome";
            char temp_game_version[MAX_NOME_JOGADOR] = "3.0";
            char temp_timestamp[80] = "N/A";
            char temp_playerX[MAX_NOME_JOGADOR] = "N/A";
            char temp_playerO[MAX_NOME_JOGADOR] = "N/A";
            int temp_winsX = 0, temp_winsO = 0, temp_ties = 0;
            char temp_last_winner[MAX_NOME_JOGADOR] = "N/A";
            
            bool has_save_name = false;
            bool has_players = false;
            bool has_stats = false;

            while (fgets(temp_line, sizeof(temp_line), save_file) != NULL) {
                applyCrypto(temp_line); // DECRIPTAR LINHA
                
                if (strstr(temp_line, "Nome do Salvamento:") != NULL) {
                    if (sscanf(temp_line, "Nome do Salvamento: %[^\n]", temp_save_name) == 1) has_save_name = true;
                } else if (strstr(temp_line, "Versão do Jogo:") != NULL) {
                    sscanf(temp_line, "Versão do Jogo: %s", temp_game_version);
                } else if (strstr(temp_line, "Data e Hora:") != NULL) {
                    char *ts_start = strstr(temp_line, "Data e Hora: ");
                    if (ts_start) sscanf(ts_start + strlen("Data e Hora: "), "%s", temp_timestamp);
                } else if (strstr(temp_line, "Jogador X:") != NULL) {
                    sscanf(temp_line, "Jogador X: %[^\n]", temp_playerX);
                } else if (strstr(temp_line, "Jogador O:") != NULL) {
                    if (sscanf(temp_line, "Jogador O: %[^\n]", temp_playerO) == 1) has_players = true;
                } else if (strstr(temp_line, "Vitorias X:") != NULL) {
                    sscanf(temp_line, "Vitorias X: %d", &temp_winsX);
                } else if (strstr(temp_line, "Vitorias O:") != NULL) {
                    sscanf(temp_line, "Vitorias O: %d", &temp_winsO);
                } else if (strstr(temp_line, "Empates:") != NULL) {
                    if (sscanf(temp_line, "Empates: %d", &temp_ties) == 1) has_stats = true;
                } else if (strstr(temp_line, "Vencedor:") != NULL) {
                    sscanf(temp_line, "Vencedor: %[^\n]", temp_last_winner);
                } else if (strstr(temp_line, "--- Checksum ---") != NULL) {
                    break;
                }
            }
            
            bool valid_file = has_save_name && has_players && has_stats;
            
            if (valid_file) {
                strcpy(saves_array[num_saves].filename, full_path);
                strcpy(saves_array[num_saves].save_name, temp_save_name);
                strcpy(saves_array[num_saves].playerX, temp_playerX);
                strcpy(saves_array[num_saves].playerO, temp_playerO);
                saves_array[num_saves].winsX = temp_winsX;
                saves_array[num_saves].winsO = temp_winsO;
                saves_array[num_saves].ties = temp_ties;
                strcpy(saves_array[num_saves].last_winner, temp_last_winner);
                strcpy(saves_array[num_saves].timestamp, temp_timestamp);
                num_saves++;
            }
            
            fecharArquivo(save_file);
        }
    }
    
    fecharArquivo(list_file);
    remove("saves_list.tmp");
    
    return num_saves;
}

bool carregarJogo(GameState* game) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloDados();
    
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                       CARREGAR JOGO SALVO                                            ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    SaveInfo available_saves[MAX_SAVES];
    int num_available_saves = listarSaves(available_saves, MAX_SAVES);
    
    if (num_available_saves == 0) {
        printf("║ Nenhum jogo salvo encontrado.                                                                        ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("Pressione ENTER para continuar...\n\n");
        esperarEnter();
        return false;
    }
    
    printf("║ Saves Disponíveis:                                                                                   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < num_available_saves; i++) {
        printf("║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Venc: %-14s ║\n",
               i + 1,
               available_saves[i].save_name,
               available_saves[i].playerX, available_saves[i].winsX,
               available_saves[i].playerO, available_saves[i].winsO,
               available_saves[i].ties,
               available_saves[i].last_winner);
    }
    
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    int escolha = lerInteiro("Digite o número do jogo para carregar (ou 0 para voltar): ", 0, num_available_saves);
    
    if (escolha == 0) {
        printf("Voltando ao menu de Save/Load...\n");
        return false;
    }
    
    char selected_filename[MAX_LINE_BUFFER];
    strcpy(selected_filename, available_saves[escolha - 1].filename);
    
    FILE *file = abrirArquivo(selected_filename, "r");
    if (file == NULL) {
        printf("Pressione ENTER para continuar...\n\n");
        esperarEnter();
        return false;
    }
    
    char line[MAX_LINE_BUFFER];
    char data_for_checksum[MAX_CHECKSUM_BUFFER] = "";
    unsigned int saved_checksum = 0;
    bool parsing_data_for_checksum = true;
    
    char temp_save_name[MAX_NOME_JOGADOR] = "";
    char temp_game_version[MAX_NOME_JOGADOR] = "";
    char temp_timestamp[80] = "";
    char temp_playerX[MAX_NOME_JOGADOR] = "";
    char temp_playerO[MAX_NOME_JOGADOR] = "";
    int temp_winsX = 0, temp_winsO = 0, temp_ties = 0;
    char temp_last_winner[MAX_NOME_JOGADOR] = "";
    char temp_jogadorAtual = ' ';
    char temp_tabuleiro[3][3];
    
    for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) temp_tabuleiro[i][j] = '?';
    
    int temp_mode = (int)MODE_PLAYER_VS_PLAYER;
    int temp_diff = 0;
    int temp_histX[3] = {-1, -1, -1};
    int temp_histO[3] = {-1, -1, -1};
    int temp_numX = 0, temp_numO = 0;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "--- Checksum ---") != NULL) {
            parsing_data_for_checksum = false;
            if (fgets(line, sizeof(line), file) != NULL) {
                sscanf(line, "%u", &saved_checksum);
            }
            break;
        }

        if (parsing_data_for_checksum) {
            applyCrypto(line); // DECRIPTAR LINHA LIDA
            
            if (strlen(data_for_checksum) + strlen(line) + 1 > MAX_CHECKSUM_BUFFER) {
                fprintf(stderr, "Erro: Buffer de checksum muito pequeno ao carregar jogo.\n");
                fecharArquivo(file);
                return false;
            }
            strcat(data_for_checksum, line);
        }
        
        if (strstr(line, "Nome do Salvamento:") != NULL) {
            sscanf(line, "Nome do Salvamento: %[^\n]", temp_save_name);
        } else if (strstr(line, "Versão do Jogo:") != NULL) {
            sscanf(line, "Versão do Jogo: %s", temp_game_version);
        } else if (strstr(line, "Data e Hora:") != NULL) {
            char *ts_start = strstr(line, "Data e Hora: ");
            if (ts_start) sscanf(ts_start + strlen("Data e Hora: "), "%s", temp_timestamp);
        } else if (strstr(line, "Modo:") != NULL) {
            sscanf(line, "Modo: %d", &temp_mode);
        } else if (strstr(line, "Dificuldade:") != NULL) {
            sscanf(line, "Dificuldade: %d", &temp_diff);
        } else if (strstr(line, "Jogador X:") != NULL) {
            sscanf(line, "Jogador X: %[^\n]", temp_playerX);
        } else if (strstr(line, "Jogador O:") != NULL) {
            sscanf(line, "Jogador O: %[^\n]", temp_playerO);
        } else if (strstr(line, "Vitorias X:") != NULL) {
            sscanf(line, "Vitorias X: %d", &temp_winsX);
        } else if (strstr(line, "Vitorias O:") != NULL) {
            sscanf(line, "Vitorias O: %d", &temp_winsO);
        } else if (strstr(line, "Empates:") != NULL) {
            sscanf(line, "Empates: %d", &temp_ties);
        } else if (strstr(line, "Vencedor:") != NULL) {
            sscanf(line, "Vencedor: %[^\n]", temp_last_winner);
        } else if (strstr(line, "Hist X:") != NULL) {
            sscanf(line, "Hist X: %d %d %d", &temp_histX[0], &temp_histX[1], &temp_histX[2]);
        } else if (strstr(line, "Hist O:") != NULL) {
            sscanf(line, "Hist O: %d %d %d", &temp_histO[0], &temp_histO[1], &temp_histO[2]);
        } else if (strstr(line, "Num Jogadas X:") != NULL) {
            sscanf(line, "Num Jogadas X: %d", &temp_numX);
        } else if (strstr(line, "Num Jogadas O:") != NULL) {
            sscanf(line, "Num Jogadas O: %d", &temp_numO);
        } else if (strstr(line, "--- Tabuleiro ---") != NULL) {
            if (fgets(line, sizeof(line), file) == NULL) break;
            if (parsing_data_for_checksum) strcat(data_for_checksum, line);
            sscanf(line, " %c | %c | %c ", &temp_tabuleiro[0][0], &temp_tabuleiro[0][1], &temp_tabuleiro[0][2]);
            
            if (fgets(line, sizeof(line), file) == NULL) break;
            if (parsing_data_for_checksum) strcat(data_for_checksum, line);
            
            if (fgets(line, sizeof(line), file) == NULL) break;
            if (parsing_data_for_checksum) strcat(data_for_checksum, line);
            sscanf(line, " %c | %c | %c ", &temp_tabuleiro[1][0], &temp_tabuleiro[1][1], &temp_tabuleiro[1][2]);
            
            if (fgets(line, sizeof(line), file) == NULL) break;
            if (parsing_data_for_checksum) strcat(data_for_checksum, line);
            
            if (fgets(line, sizeof(line), file) == NULL) break;
            if (parsing_data_for_checksum) strcat(data_for_checksum, line);
            sscanf(line, " %c | %c | %c ", &temp_tabuleiro[2][0], &temp_tabuleiro[2][1], &temp_tabuleiro[2][2]);
        } else if (strstr(line, "Jogador Atual:") != NULL) {
            sscanf(line, "Jogador Atual: %c", &temp_jogadorAtual);
        }
    }
    fecharArquivo(file);
    
    unsigned int recalculated_checksum = calcularChecksum(data_for_checksum);
    if (saved_checksum != recalculated_checksum) {
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ ! AVISO: ARQUIVO PODE TER SIDO CORROMPIDO OU ALTERADO !                                              ║\n");
        printf("║ Checksum esperado: %-10u │ Checksum atual: %-10u                                          ║\n", saved_checksum, recalculated_checksum);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ Deseja continuar mesmo assim? (1 - Sim, 0 - Não):                                                    ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        int continuar = lerInteiro("Sua escolha: ", 0, 1);
        if (continuar == 0) {
            return false;
        }
    }
    
    if (strlen(temp_playerX) == 0 || strlen(temp_playerO) == 0 || temp_jogadorAtual == ' ' || temp_tabuleiro[0][0] == '?') {
        printf("Erro: Dados essenciais do jogo não foram encontrados ou estão incompletos no arquivo.\n");
        printf("Pressione ENTER para continuar...\n\n");
        esperarEnter();
        return false;
    }

    if (strcmp(temp_game_version, GAME_VERSION) != 0) {
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ ! AVISO: INCOMPATIBILIDADE DE VERSÃO !                                                               ║\n");
        printf("║ Versão do save: %-10s │ Versão do jogo: %-10s                                            ║\n", temp_game_version, GAME_VERSION);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ Deseja tentar carregar mesmo assim? (1 - Sim, 0 - Não):                                              ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        int continuar = lerInteiro("Sua escolha: ", 0, 1);
        if (continuar == 0) {
            return false;
        }
    }
    
    strcpy(game->nomeJogadorX, temp_playerX);
    strcpy(game->nomeJogadorO, temp_playerO);
    game->placarX = temp_winsX;
    game->placarO = temp_winsO;
    game->empates = temp_ties;
    strcpy(game->ultimoVencedor, temp_last_winner);
    game->jogadorAtual = temp_jogadorAtual;
    game->current_mode = (GameMode)temp_mode;
    game->ai_difficulty = temp_diff;
    game->numJogadasX = temp_numX;
    game->numJogadasO = temp_numO;
    for(int i = 0; i < 3; i++) {
        game->historicoJogadasX[i] = temp_histX[i];
        game->historicoJogadasO[i] = temp_histO[i];
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            game->tabuleiro[i][j] = temp_tabuleiro[i][j];
        }
    }
    
    strcpy(game->loaded_filename, selected_filename);
    
    printf("\a"); // Beep de sucesso
    printf("Jogo carregado com sucesso de '%s'!\n", selected_filename);
    printf("Placar carregado: %s (X): %d | %s (O): %d | Empates: %d\n", 
           game->nomeJogadorX, game->placarX, game->nomeJogadorO, game->placarO, game->empates);
    printf("Último Vencedor: %s\n", game->ultimoVencedor);
    esperarEnter();
    
    return true;
}

void funcaoDeletarJogo(void) {
    limparTela();
    aplicarTema(tema_ativo);
    exibirTituloDeletar();

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                       DELETAR JOGO SALVO                                             ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    SaveInfo available_saves[MAX_SAVES];
    int num_available_saves = listarSaves(available_saves, MAX_SAVES);
    
    if (num_available_saves == 0) {
        printf("║ Nenhum jogo salvo encontrado.                                                                        ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("Pressione ENTER para continuar...\n\n");
        esperarEnter();
        return;
    }
    
    printf("║ Saves Disponíveis:                                                                                   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < num_available_saves; i++) {
        printf("║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Data: %-21s ║\n",
               i + 1,
               available_saves[i].save_name,
               available_saves[i].playerX, available_saves[i].winsX,
               available_saves[i].playerO, available_saves[i].winsO,
               available_saves[i].ties,
               available_saves[i].timestamp);
    }
    
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    int escolha = lerInteiro("Digite o número do jogo para DELETAR (ou 0 para voltar): ", 0, num_available_saves);
    
    if (escolha == 0) {
        printf("Operação de exclusão cancelada.\n");
        return;
    }
    
    char file_to_delete[MAX_LINE_BUFFER];
    strcpy(file_to_delete, available_saves[escolha - 1].filename);
    
    printf("Tem certeza que deseja deletar '%s'? (1 - Sim, 0 - Não): ", available_saves[escolha - 1].save_name);
    int confirm = lerInteiro("", 0, 1);
    
    if (confirm == 1) {
        if (remove(file_to_delete) == 0) {
            printf("Arquivo '%s' deletado com sucesso!\n", file_to_delete);
        } else {
            printf("Erro ao deletar o arquivo '%s': %s\n", file_to_delete, strerror(errno));
        }
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
    printf("Pressione ENTER para continuar...\n\n");
    esperarEnter();
}
