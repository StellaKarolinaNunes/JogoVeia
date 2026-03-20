#include "theme.h"
#include "utils.h"
#include "ui.h"

#ifdef _WIN32
const char* temas[] = {
    "0A", "0B", "0C", "0E", "09", "0F", "70", "5E"
};
const char* nomes_temas[] = {
    "Verde", "Ciano", "Vermelho", "Amarelo",
    "Azul", "Branco", "Preto no Branco", "Roxo"
};
#else
const char* temas[] = {
    "\033[0;32m", "\033[0;36m", "\033[0;31m", "\033[1;33m",
    "\033[0;34m", "\033[1;37m", "\033[40;37m", "\033[1;35m",
    "\033[1;32m", "\033[1;36m", "\033[1;31m", "\033[0;33m",
    "\033[0;95m", "\033[0;90m", "\033[1;90m", "\033[45;37m",
    "\033[44;33m", "\033[42;30m", "\033[41;33m", "\033[46;30m"
};
const char* nomes_temas[] = {
    "Verde", "Ciano", "Vermelho", "Amarelo",
    "Azul", "Branco", "Preto no Branco", "Roxo",
    "Verde Claro", "Ciano Claro", "Vermelho Claro", "Laranja",
    "Magenta Neon", "Cinza", "Cinza Claro", "Roxo com Branco",
    "Azul com Amarelo", "Verde com Preto", "Vermelho com Amarelo", "Ciano com Preto"
};
#endif

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
        
        printf("=========================================================================================\n");
        printf("|                                TEMAS DISPONÍVEIS                                      |\n");
        printf("|---------------------------------------------------------------------------------------|\n");
        
        for (int i = 0; i < TOTAL_TEMAS; i++) {
            printf("|  %-2d - %-80s|\n", i + 1, nomes_temas[i]);
        }
        
        printf("|                                                                                       |\n");
        printf("|  0 - Voltar ao menu                                                                   |\n");
        printf("=========================================================================================\n\n");
        
        escolha = lerInteiro("Escolha o tema desejado para visualizar a prévia (ou 0 para voltar): ", 0, TOTAL_TEMAS);
        
        if (escolha > 0 && escolha <= TOTAL_TEMAS) {
            apresentarTema(escolha - 1);
            int usar = lerInteiro("\nEsse tema lhe agrada? (1 - Usar, 0 - Voltar): ", 0, 1);
            if (usar == 1) {
                tema_ativo = escolha - 1;
                printf("Tema alterado para: %s\n", nomes_temas[tema_ativo]);
                esperarEnter();
                break;
            }
        }
    } while (escolha != 0);
    
    limparTela();
    aplicarTema(tema_ativo);
}
