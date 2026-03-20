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
int obterJogadaIA(GameState* game);
void funcaoJogar(GameState* game, bool is_resumed_game);
void executarReplay(const GameState* game); // NOVO
void verificarEAtribuirMedalhas(const char* nome, bool venceu, bool empate, bool contra_ia, int dificuldade); // NOVO

#endif // GAME_H
