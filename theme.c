#include "theme.h"
#include "utils.h"
#include "ui.h"
#include "file_manager.h"

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


void escolherTema(void) {
    int original_tema = tema_ativo;
    int preview_tema = tema_ativo;
    KeyCode tecla;
    
    do {
        // Define tema_ativo temporariamente como preview_tema para renderizar os elementos da tela nas cores certas!
        tema_ativo = preview_tema;
        exibirTelaTemas(preview_tema);
        
        tecla = lerTeclaMenu();
        
        switch (tecla) {
            case KEY_UP:
                preview_tema--;
                if (preview_tema < 0) preview_tema = num_temas - 1;
                break;
                
            case KEY_DOWN:
                preview_tema++;
                if (preview_tema >= num_temas) preview_tema = 0;
                break;
                
            case KEY_LEFT:
                if (preview_tema >= 17) {
                    preview_tema -= 17;
                } else {
                    preview_tema += 34;
                    if (preview_tema >= num_temas) preview_tema = num_temas - 1;
                }
                break;
                
            case KEY_RIGHT:
                if (preview_tema < 34) {
                    preview_tema += 17;
                    if (preview_tema >= num_temas) preview_tema = num_temas - 1;
                } else {
                    preview_tema -= 34;
                }
                break;
                
            case KEY_ENTER:
                // Seleção confirmada!
                tema_ativo = preview_tema;
                aplicarTema(tema_ativo);
                salvarConfiguracoes();
                return;
                
            case KEY_ESC:
            case KEY_Q:
            case KEY_0:
                // Cancelado! Restaurar tema original.
                tema_ativo = original_tema;
                aplicarTema(tema_ativo);
                return;
                
            default:
                break;
        }
    } while (1);
}
