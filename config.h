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

#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#define SET_TITLE "title jogo da veia"
#define PAUSE_COMMAND "pause"
#define CLEAR_COMMAND "cls"
#define RESET_COLOR_COMMAND ""
#else
#include <sys/stat.h>
#define MKDIR(dir) mkdir(dir, 0777)
#define SET_TITLE "echo -ne \"\\033]0;jogo da veia\\007\""
#define PAUSE_COMMAND "read -p 'Pressione Enter para continuar...'"
#define CLEAR_COMMAND "clear"
#define RESET_COLOR_COMMAND "\033[0m"
#endif
#define GAME_VERSION "4.0"
#define MAX_NOME_JOGADOR 50
#define SAVE_DIR "saves"
#define RANKING_FILE "ranking.dat"
#define MAX_RANKING_ENTRIES 100
#define MAX_SAVES 100
#define MAX_LINE_BUFFER 256
#define MAX_CHECKSUM_BUFFER 4096

// Temas de cores dinâmicos
#define MAX_TEMAS 50
#define MAX_THEME_NAME 50
#define MAX_THEME_CODE 64

extern char temas[MAX_TEMAS][MAX_THEME_CODE];
extern char nomes_temas[MAX_TEMAS][MAX_THEME_NAME];
extern int num_temas;

#define TOTAL_TEMAS num_temas

#define HIGHLIGHT_COLOR "\033[47;30m"
#define NORMAL_COLOR "\033[0m"

typedef enum {
    MODE_PLAYER_VS_PLAYER,
    MODE_PLAYER_VS_AI,
    MODE_INFINITE
} GameMode;

typedef enum {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
} DifficultyLevel;

#define CRYPTO_KEY 0xAA // Chave simples para criptografia XOR dos saves

typedef struct {
    char tabuleiro[3][3];
    char jogadorAtual;
    char nomeJogadorX[MAX_NOME_JOGADOR];
    char nomeJogadorO[MAX_NOME_JOGADOR];
    int placarX;
    int placarO;
    int empates;
    char ultimoVencedor[MAX_NOME_JOGADOR];
    int historicoJogadasX[3]; // Armazena as 3 últimas posições de X (Modo Infinito)
    int historicoJogadasO[3]; // Armazena as 3 últimas posições de O (Modo Infinito)
    int numJogadasX;
    int numJogadasO;
    int ai_difficulty; // 0: Fácil, 1: Médio, 2: Difícil
    GameMode current_mode;
    char loaded_filename[MAX_LINE_BUFFER];
    
    // Suporte para Replay e Torneio (NOVO)
    int full_move_history[9]; 
    int total_moves_count;
    int tournament_target_wins; // 0, 3 ou 5
} GameState;

typedef struct {
    char name[MAX_NOME_JOGADOR];
    int wins;
    int losses;
    int ties;
    int medals; // Contador de conquistas/medalhas
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

extern RankingEntry ranking[MAX_RANKING_ENTRIES];
extern int num_ranking_entries;
extern int tema_ativo;

void carregarTemas(void);

#endif
