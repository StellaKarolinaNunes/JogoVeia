#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <errno.h>
#include <stdarg.h>

// Para criar diretórios (OS-specific)
#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#define SET_TITLE "title Jogo da Velha"
#define PAUSE_COMMAND "pause"
#define CLEAR_COMMAND "cls"
#define RESET_COLOR_COMMAND ""
#else
#include <sys/stat.h>
#define MKDIR(dir) mkdir(dir, 0777)
#define SET_TITLE "echo -ne \"\\033]0;Jogo da Velha\\007\""
#define PAUSE_COMMAND "read -p 'Pressione Enter para continuar...'"
#define CLEAR_COMMAND "clear"
#define RESET_COLOR_COMMAND "\033[0m"
#endif

// =============================================================================
// CONSTANTES E DEFINIÇÕES
// =============================================================================
#define GAME_VERSION "2.2" // Versão atualizada
#define MAX_NOME_JOGADOR 50
#define SAVE_DIR "saves"
#define RANKING_FILE "ranking.dat"
#define MAX_RANKING_ENTRIES 100
#define MAX_LINE_BUFFER 256
#define MAX_CHECKSUM_BUFFER 4096

// Temas de cores
#ifdef _WIN32
extern const char* temas[];
#else
extern const char* temas[];
extern const char* nomes_temas[];
#endif

#define TOTAL_TEMAS (sizeof(nomes_temas)/sizeof(nomes_temas[0]))

// Cores para destaque da linha vencedora (ANSI)
#define HIGHLIGHT_COLOR "\033[47;30m" // Fundo branco, texto preto
#define NORMAL_COLOR "\033[0m"        // Resetar cor

// =============================================================================
// ESTRUTURAS DE DADOS
// =============================================================================
typedef struct {
    char tabuleiro[3][3];
    char jogadorAtual;
    char nomeJogadorX[MAX_NOME_JOGADOR];
    char nomeJogadorO[MAX_NOME_JOGADOR];
    int placarX;
    int placarO;
    int empates;
    char ultimoVencedor[MAX_NOME_JOGADOR];
} GameState;

typedef struct {
    char name[MAX_NOME_JOGADOR];
    int wins;
    int losses;
    int ties;
} RankingEntry;

typedef struct {
    char filename[MAX_LINE_BUFFER];
    char save_name[MAX_NOME_JOGADOR];
    char playerX[MAX_NOME_JOGADOR];
    char playerO[MAX_NOME_JOGADOR];
    int winsX, winsO, ties;
    char last_winner[MAX_NOME_JOGADOR];
    char timestamp[80];
} SaveInfo;

typedef enum {
    MODE_PLAYER_VS_PLAYER,
    MODE_PLAYER_VS_AI
} GameMode;

extern RankingEntry ranking[MAX_RANKING_ENTRIES];
extern int num_ranking_entries;
extern int tema_ativo;

#endif // CONFIG_H
