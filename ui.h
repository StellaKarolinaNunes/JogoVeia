#ifndef UI_H
#define UI_H

#include "config.h"

void exibirTituloPrincipal(void);
void exibirTituloInstrucoes(void);
void exibirTituloCreditos(void);
void exibirTituloTemas(void);
void exibirTituloSaindo(void);
void exibirMenuCapa(void);
void print_square(char value, int row, int col, const int* highlight_indices);
void exibirInterfaceJogo(const GameState* game, const int* winning_line_indices);

#endif // UI_H
