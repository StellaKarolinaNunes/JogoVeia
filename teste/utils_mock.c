#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils.h"

// Mocks para evitar travamento em testes automatizados
void limparBufferEntrada(void) {}
void esperarEnter(void) {}
void limparTela(void) {}
void pausarSistema(void) {}

int visible_strlen(const char* s) {
    if (s == NULL) return 0;
    int len = 0;
    const char* p = s;
    while (*p) {
        if (*p == '\033') {
            p++;
            if (*p == '[') {
                p++;
                while (*p && (*p < 'A' || *p > 'Z') && (*p < 'a' || *p > 'z')) p++;
                if (*p) p++;
                continue;
            }
        }
        if ((*p & 0xc0) != 0x80) len++;
        p++;
    }
    return len;
}

int lerInteiro(const char* mensagem, int min, int max) {
    // Retorna o valor mínimo em testes automáticos para evitar loop
    return min; 
}

void lerString(const char* mensagem, char* buffer, int tamanhoMax) {
    strncpy(buffer, "MockedInput", tamanhoMax-1);
}

void delaySimples(int milliseconds) {}

unsigned int calcularChecksum(const char* data) {
    unsigned int hash = 2166136261U;
    for (int i = 0; data[i] != '\0'; i++) {
        hash ^= (unsigned char)data[i];
        hash *= 16777619U;
    }
    return hash;
}
