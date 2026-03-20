#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "config.h"

bool criarDiretorioSaves(void);
void salvarJogo(const GameState* game);
bool carregarJogo(GameState* game);
int listarSaves(SaveInfo* saves_array, int max_saves);
void funcaoDeletarJogo(void);

FILE* abrirArquivo(const char* path, const char* mode);
void fecharArquivo(FILE* file);
bool escreverLinhaFormatada(FILE* file, const char* format, ...);

void carregarRanking(void);
void salvarRanking(void);
void atualizarRanking(const char* player_name, int result_type);
int compararRankingEntries(const void* a, const void* b);

#endif // FILE_MANAGER_H
