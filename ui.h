#ifndef UI_H
#define UI_H

#include "config.h"

void exibirTituloPrincipal(void);
void exibirTituloInstrucoes(void);
void exibirTituloCreditos(void);
void exibirTituloTemas(void);
void exibirTituloSaindo(void);
void exibirTituloReferencia(void);
void exibirTituloDados(void);
void exibirTituloModoJogo(void);
void exibirTituloDeletar(void);
void exibirTituloRanking(void);
void exibirMenuCapa(void);

void exibirInterfaceJogo(const GameState* game, const int* winning_line_indices, const char* mensagemInfo);
void animarVitoria(const GameState* game, const int* winning_line_indices); // NOVO
void exibirTrofeu(const char* vencedor); // NOVO
void exibirConquista(const char* titulo); // NOVO

#endif
