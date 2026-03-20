#include "file_manager.h"
#include "utils.h"
#include "theme.h"

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
            strcpy(ranking[found_index].name, player_name);
            ranking[found_index].wins = 0;
            ranking[found_index].losses = 0;
            ranking[found_index].ties = 0;
        } else {
            printf("Aviso: Limite máximo de jogadores no ranking atingido. Não foi possível adicionar %s.\n", player_name);
            return;
        }
    }
    
    switch (result_type) {
        case 1: ranking[found_index].wins++; break;
        case 0: ranking[found_index].ties++; break;
        case -1: ranking[found_index].losses++; break;
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

void salvarJogo(const GameState* game) {
    if (!criarDiretorioSaves()) {
        esperarEnter();
        return;
    }
    
    char save_name[MAX_NOME_JOGADOR];
    lerString("Digite um nome para o seu salvamento: ", save_name, sizeof(save_name));
    
    if (strlen(save_name) == 0) {
        printf("Nome do salvamento não pode ser vazio. Cancelando salvamento.\n");
        esperarEnter();
        return;
    }
    
    time_t rawtime;
    struct tm *info;
    char timestamp[80];
    char filename[MAX_LINE_BUFFER];
    char data_to_checksum[MAX_CHECKSUM_BUFFER];
    
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, 80, "%Y%m%d_%H%M%S", info);
    
    snprintf(filename, sizeof(filename), "%s/%s_%s.txt", SAVE_DIR, save_name, timestamp);
    
    FILE *file = abrirArquivo(filename, "w");
    if (file == NULL) {
        esperarEnter();
        return;
    }
    
    int len = snprintf(data_to_checksum, sizeof(data_to_checksum),
        "--- Jogo da Velha - Salvo ---\n"
        "Nome do Salvamento: %s\n"
        "Versão do Jogo: %s\n"
        "Data e Hora: %s\n"
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
        "--- Tabuleiro ---\n"
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n"
        "---+---+---\n"
        " %c | %c | %c \n"
        "Jogador Atual: %c\n",
        save_name, GAME_VERSION, timestamp,
        game->nomeJogadorX, game->nomeJogadorO,
        game->placarX, game->placarO, game->empates,
        game->ultimoVencedor,
        game->tabuleiro[0][0], game->tabuleiro[0][1], game->tabuleiro[0][2],
        game->tabuleiro[1][0], game->tabuleiro[1][1], game->tabuleiro[1][2],
        game->tabuleiro[2][0], game->tabuleiro[2][1], game->tabuleiro[2][2],
        game->jogadorAtual
    );
    
    if (len < 0 || len >= sizeof(data_to_checksum)) {
        printf("Erro: Dados de salvamento muito grandes para o buffer. Salvamento cancelado.\n");
        fecharArquivo(file);
        esperarEnter();
        return;
    }
    
    if (!escreverLinhaFormatada(file, "%s", data_to_checksum)) {
        printf("Erro ao escrever dados do jogo. Salvamento cancelado.\n");
        fecharArquivo(file);
        esperarEnter();
        return;
    }
    
    unsigned int checksum = calcularChecksum(data_to_checksum);
    if (!escreverLinhaFormatada(file, "\n--- Checksum ---\n%u\n", checksum)) {
        printf("Erro ao escrever checksum. Salvamento cancelado.\n");
        fecharArquivo(file);
        esperarEnter();
        return;
    }
    
    fecharArquivo(file);
    printf("Jogo salvo com sucesso em '%s'!\n", filename);
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
            char temp_save_name[MAX_NOME_JOGADOR];
            char temp_game_version[MAX_NOME_JOGADOR];
            char temp_timestamp[80];
            char temp_playerX[MAX_NOME_JOGADOR];
            char temp_playerO[MAX_NOME_JOGADOR];
            int temp_winsX, temp_winsO, temp_ties;
            char temp_last_winner[MAX_NOME_JOGADOR];
            
            bool valid_file = true;
            
            if (fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                fgets(temp_line, sizeof(temp_line), save_file) == NULL || 
                sscanf(temp_line, "Nome do Salvamento: %[^\n]", temp_save_name) != 1 ||
                fgets(temp_line, sizeof(temp_line), save_file) == NULL || 
                sscanf(temp_line, "Versão do Jogo: %s", temp_game_version) != 1 ||
                fgets(temp_line, sizeof(temp_line), save_file) == NULL || 
                strstr(temp_line, "Data e Hora: ") == NULL) {
                valid_file = false;
            }
            
            if (valid_file) {
                char *ts_start = strstr(temp_line, "Data e Hora: ");
                if (ts_start) {
                    ts_start += strlen("Data e Hora: ");
                    sscanf(ts_start, "%s", temp_timestamp);
                } else {
                    strcpy(temp_timestamp, "N/A");
                }
                
                if (fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                    fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                    fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                    sscanf(temp_line, "Jogador X: %[^\n]", temp_playerX) != 1 ||
                    fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                    sscanf(temp_line, "Jogador O: %[^\n]", temp_playerO) != 1) {
                    valid_file = false;
                }
                
                if (valid_file) {
                    fgets(temp_line, sizeof(temp_line), save_file);
                    fgets(temp_line, sizeof(temp_line), save_file);
                    
                    if (fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                        sscanf(temp_line, "Vitorias X: %d", &temp_winsX) != 1 ||
                        fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                        sscanf(temp_line, "Vitorias O: %d", &temp_winsO) != 1 ||
                        fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                        sscanf(temp_line, "Empates: %d", &temp_ties) != 1) {
                        valid_file = false;
                    }
                }
                
                if (valid_file) {
                    fgets(temp_line, sizeof(temp_line), save_file);
                    fgets(temp_line, sizeof(temp_line), save_file);
                    if (fgets(temp_line, sizeof(temp_line), save_file) == NULL ||
                        sscanf(temp_line, "Vencedor: %[^\n]", temp_last_winner) != 1) {
                        strcpy(temp_last_winner, "N/A");
                    }
                }
            }
            
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
    
    printf("========================================================================================================\n");
    printf("|                                       CARREGAR JOGO SALVO                                           |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    SaveInfo available_saves[MAX_RANKING_ENTRIES];
    int num_available_saves = listarSaves(available_saves, MAX_RANKING_ENTRIES);
    
    if (num_available_saves == 0) {
        printf("| Nenhum jogo salvo encontrado.                                                                        |\n");
        printf("========================================================================================================\n\n");
        esperarEnter();
        return false;
    }
    
    printf("| Saves Disponíveis:                                                                                   |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    for (int i = 0; i < num_available_saves; i++) {
        printf("| %2d. Nome: %-15s | X: %-10s (%d) | O: %-10s (%d) | Empates: %d | Vencedor: %-10s |\n",
               i + 1,
               available_saves[i].save_name,
               available_saves[i].playerX, available_saves[i].winsX,
               available_saves[i].playerO, available_saves[i].winsO,
               available_saves[i].ties,
               available_saves[i].last_winner);
    }
    
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    int escolha = lerInteiro("Digite o número do jogo para carregar (ou 0 para voltar): ", 0, num_available_saves);
    
    if (escolha == 0) {
        printf("Voltando ao menu de Save/Load...\n");
        return false;
    }
    
    char selected_filename[MAX_LINE_BUFFER];
    strcpy(selected_filename, available_saves[escolha - 1].filename);
    
    FILE *file = abrirArquivo(selected_filename, "r");
    if (file == NULL) {
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
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (parsing_data_for_checksum) {
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
        } else if (strstr(line, "--- Checksum ---") != NULL) {
            parsing_data_for_checksum = false;
            if (fgets(line, sizeof(line), file) != NULL) {
                sscanf(line, "%u", &saved_checksum);
            }
            break;
        }
    }
    fecharArquivo(file);
    
    unsigned int recalculated_checksum = calcularChecksum(data_for_checksum);
    if (saved_checksum != recalculated_checksum) {
        printf("AVISO: O arquivo de salvamento pode ter sido alterado externamente! Checksum inválido.\n");
        printf("Checksum esperado: %u, Checksum calculado: %u\n", saved_checksum, recalculated_checksum);
        printf("Deseja continuar mesmo assim? (1 - Sim, 0 - Não): ");
        int continuar = lerInteiro("", 0, 1);
        if (continuar == 0) {
            return false;
        }
    }
    
    if (strlen(temp_playerX) == 0 || strlen(temp_playerO) == 0 || temp_jogadorAtual == ' ' || temp_tabuleiro[0][0] == '?') {
        printf("Erro: Dados essenciais do jogo não foram encontrados ou estão incompletos no arquivo.\n");
        esperarEnter();
        return false;
    }

    if (strcmp(temp_game_version, GAME_VERSION) != 0) {
        printf("Aviso: A versão do jogo salvo (%s) é diferente da versão atual (%s).\n", temp_game_version, GAME_VERSION);
        printf("Pode haver incompatibilidades. Deseja continuar mesmo assim? (1 - Sim, 0 - Não): ");
        int continuar = lerInteiro("", 0, 1);
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
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            game->tabuleiro[i][j] = temp_tabuleiro[i][j];
        }
    }
    
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
    
    printf("========================================================================================================\n");
    printf("|                                       DELETAR JOGO SALVO                                             |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    SaveInfo available_saves[MAX_RANKING_ENTRIES];
    int num_available_saves = listarSaves(available_saves, MAX_RANKING_ENTRIES);
    
    if (num_available_saves == 0) {
        printf("| Nenhum jogo salvo encontrado.                                                                        |\n");
        printf("========================================================================================================\n\n");
        esperarEnter();
        return;
    }
    
    printf("| Saves Disponíveis:                                                                                   |\n");
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
    for (int i = 0; i < num_available_saves; i++) {
        printf("| %2d. Nome: %-15s | X: %-10s (%d) | O: %-10s (%d) | Empates: %d | Data: %s |\n",
               i + 1,
               available_saves[i].save_name,
               available_saves[i].playerX, available_saves[i].winsX,
               available_saves[i].playerO, available_saves[i].winsO,
               available_saves[i].ties,
               available_saves[i].timestamp);
    }
    
    printf("|------------------------------------------------------------------------------------------------------|\n");
    
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
    
    esperarEnter();
}
