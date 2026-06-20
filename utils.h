#ifndef UTILS_H
#define UTILS_H

#include "config.h"

void limparBufferEntrada(void);
void esperarEnter(void);
void limparTela(void);
int visible_strlen(const char* s);
int lerInteiro(const char* mensagem, int min, int max);
void lerString(const char* mensagem, char* buffer, int tamanhoMax);
void delaySimples(int milliseconds);
unsigned int calcularChecksum(const char* data);
typedef enum {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_ESC,
    KEY_Q,
    KEY_0,
    KEY_OTHER
} KeyCode;

int obterTecla(void);
KeyCode lerTeclaMenu(void);

#endif
