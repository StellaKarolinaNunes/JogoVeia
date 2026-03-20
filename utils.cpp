#include "utils.h"

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarEnter(void) {
    getchar();
}

void limparTela(void) {
    system(CLEAR_COMMAND);
}

void pausarSistema(void) {
    system(PAUSE_COMMAND);
}

int lerInteiro(const char* mensagem, int min, int max) {
    int valor;
    do {
        printf("%s", mensagem);
        if (scanf("%d", &valor) != 1) {
            limparBufferEntrada();
            printf("Entrada inválida! Por favor, digite um número.\n");
        } else if (valor < min || valor > max) {
            limparBufferEntrada();
            printf("Valor fora do intervalo permitido (%d-%d).\n", min, max);
        } else {
            limparBufferEntrada();
            return valor;
        }
        esperarEnter();
    } while (1);
}

void lerString(const char* mensagem, char* buffer, int tamanhoMax) {
    printf("%s", mensagem);
    if (fgets(buffer, tamanhoMax, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        limparBufferEntrada();
    }
}

void delaySimples(int milliseconds) {
    long pause;
    clock_t now, then;
    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}

unsigned int calcularChecksum(const char* data) {
    unsigned int hash = 2166136261U;
    for (int i = 0; data[i] != '\0'; i++) {
        hash ^= (unsigned char)data[i];
        hash *= 16777619U;
    }
    return hash;
}
