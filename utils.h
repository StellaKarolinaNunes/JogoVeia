#ifndef UTILS_H
#define UTILS_H

#include "config.h"

void limparBufferEntrada(void);
void esperarEnter(void);
void limparTela(void);
void pausarSistema(void);
int lerInteiro(const char* mensagem, int min, int max);
void lerString(const char* mensagem, char* buffer, int tamanhoMax);
void delaySimples(int milliseconds);
unsigned int calcularChecksum(const char* data);

#endif // UTILS_H
