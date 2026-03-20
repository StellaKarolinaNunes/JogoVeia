#ifndef GAME_H
#define GAME_H

#include "config.h"

void inicializarTabuleiro(GameState* game);
bool verificarVitoria(const GameState* game, int* winning_line_indices);
bool verificarEmpate(const GameState* game);
bool fazerJogada(GameState* game, int jogada);
void alternarJogador(GameState* game);
void obterNomesJogadores(GameState* game, GameMode mode);
void sortearPrimeiroJogador(GameState* game);
int obterJogadaIA(const GameState* game);
void funcaoJogar(GameState* game, bool is_resumed_game);

#endif // GAME_H
