#include "theme.h"
#include "utils.h"
#include "ui.h"

void carregarTemas(void) {
    FILE* file = fopen("themes.cfg", "r");
    if (file == NULL) {
        // Fallback robusto se o arquivo não existir
        const char* default_names[] = {"Verde", "Ciano", "Vermelho", "Amarelo", "Azul", "Branco", "Preto no Branco", "Roxo"};
        const char* default_codes[] = {"\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[1;33m", "\033[0;34m", "\033[1;37m", "\033[40;37m", "\033[1;35m"};
        num_temas = 8;
        for (int i = 0; i < num_temas; i++) {
            strcpy(nomes_temas[i], default_names[i]);
            strcpy(temas[i], default_codes[i]);
        }
        return;
    }

    num_temas = 0;
    char line[MAX_LINE_BUFFER];
    while (fgets(line, sizeof(line), file) && num_temas < MAX_TEMAS) {
        char* colon = strchr(line, ':');
        if (colon) {
            *colon = '\0';
            char* code = colon + 1;
            
            // Remover \n do final do código
            size_t len = strlen(code);
            if (len > 0 && code[len-1] == '\n') code[len-1] = '\0';
            if (len > 1 && code[len-2] == '\r') code[len-2] = '\0';

            strncpy(nomes_temas[num_temas], line, MAX_THEME_NAME - 1);
            nomes_temas[num_temas][MAX_THEME_NAME - 1] = '\0';

            // Processar sequências de escape como \033 ou \e
            char processed_code[MAX_THEME_CODE];
            int p = 0;
            for (int i = 0; code[i] != '\0' && p < MAX_THEME_CODE - 1; i++) {
                if (code[i] == '\\' && code[i+1] == '0' && code[i+2] == '3' && code[i+3] == '3') {
                    processed_code[p++] = '\033'; // ESC
                    i += 3;
                } else if (code[i] == '\\' && code[i+1] == 'e') {
                    processed_code[p++] = '\033'; // ESC
                    i += 1;
                } else {
                    processed_code[p++] = code[i];
                }
            }
            processed_code[p] = '\0';
            
            strncpy(temas[num_temas], processed_code, MAX_THEME_CODE - 1);
            temas[num_temas][MAX_THEME_CODE - 1] = '\0';
            num_temas++;
        }
    }
    fclose(file);
}

void aplicarTema(int tema) {
#ifdef _WIN32
    char comando[20];
    sprintf(comando, "color %s", temas[tema]);
    system(comando);
#else
    printf("%s", temas[tema]);
#endif
}

void apresentarTema(int tema) {
    limparTela();
    aplicarTema(tema);
    printf("Prévia do tema: %s\n\n", nomes_temas[tema]);
    exibirTituloPrincipal();
}

void escolherTema(void) {
    int escolha;
    do {
        limparTela();
        aplicarTema(tema_ativo);
        exibirTituloTemas();

        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                          TEMAS DISPONÍVEIS                                           ║\n");
        printf("╠════════════════════════════════╦═════════════════════════════════╦═════════════════════════════════╣\n");

        const int num_cols = 3;
        int num_rows = (TOTAL_TEMAS + num_cols - 1) / num_cols;

        for (int i = 0; i < num_rows; ++i) {
            printf("║");
            for (int j = 0; j < num_cols; ++j) {
                int index = i + j * num_rows;
                int current_col_width = (j == 0) ? 32 : 33; // Colunas 32, 33, 33 para totalizar 100 com 2 separadores
                if (index < TOTAL_TEMAS) {
                    char theme_str[100];
                    snprintf(theme_str, sizeof(theme_str), " %2d - %s", index + 1, nomes_temas[index]);
                    int vlen = visible_strlen(theme_str);
                    if (vlen > current_col_width) {
                        // Se ainda for muito grande (raro), truncar com reticências
                        theme_str[current_col_width - 4] = '.';
                        theme_str[current_col_width - 3] = '.';
                        theme_str[current_col_width - 2] = '.';
                        theme_str[current_col_width - 1] = '\0';
                        vlen = current_col_width;
                    }
                    printf("%s", theme_str);
                    for (int k = 0; k < current_col_width-vlen; k++) putchar(' ');
                } else {
                    for (int k = 0; k < current_col_width; k++) putchar(' ');
                }
                if (j < num_cols - 1) {
                    printf("║");
                }
            }
            printf("║\n");
        }

        printf("╠════════════════════════════════╩═════════════════════════════════╩═════════════════════════════════╣\n");
        printf("║ 0 - Voltar ao menu                                                                                   ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

        escolha = lerInteiro("Escolha o tema para visualizar a prévia (ou 0 para voltar): ", 0, TOTAL_TEMAS);
        
        if (escolha > 0 && escolha <= TOTAL_TEMAS) {
            apresentarTema(escolha - 1);
            int usar = lerInteiro("\nEsse tema lhe agrada? (1 - Usar, 0 - Voltar): ", 0, 1);
            if (usar == 1) {
                tema_ativo = escolha - 1;
                printf("Tema alterado para: %s\n", nomes_temas[tema_ativo]);
                printf("Pressione Enter para continuar...");
                esperarEnter();
                break;
            }
        }
    } while (escolha != 0);
    
    limparTela();
    aplicarTema(tema_ativo);
}
