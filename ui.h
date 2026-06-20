#ifndef UI_H
#define UI_H

#include "config.h"


void exibirTelaEscolherModoJogo(int selected);
void exibirTelaEscolherTipoPartida(int selected);
void exibirTelaConfigurarJogadores(int jogadorNum);
void exibirTelaConfirmarJogadores(const char* jogadorX, const char* jogadorO, int selected);
void exibirTelaSorteio(int dadoJogador1, int dadoJogador2, const char* jogador1, const char* jogador2, const char* vencedor, int selected);
void exibirTelaRanking(void);
void exibirMenuCapa(void);
void exibirMenuInterativo(int selected, const GameState* game);
void exibirTelaInstrucoes(void);
void exibirTelaCreditos(void);
void exibirTelaReferencia(void);
void exibirTelaTemas(int preview_tema);
void exibirTelaSaveLoad(int selected_option);
void exibirTelaSaveLoadEx(int selected_option, 
                           const char* pergunta, 
                           const char* opcoes, 
                           const char* input_label, const char* input_val, 
                           const char* input_label2, const char* input_val2, 
                           const char* status_msg);
void exibirTelaEscolherSalvamento(int selected);
void exibirTelaNovoSalvamento(void);
void exibirSucessoSalvamento(const char* nomeSalvamento);
void exibirTelaSavesList(SaveInfo* saves, int num_saves, int selected_idx, int mode);

void exibirInterfaceJogo(const GameState* game, const int* winning_line_indices, const char* mensagemInfo, int selected_cell);
void animarVitoria(const GameState* game, const int* winning_line_indices); // NOVO
void exibirTrofeu(const char* vencedor); // NOVO
bool perguntarReplayResultado(const char* vencedor, char simboloVencedor, bool is_empate);
bool perguntarJogarNovamente(void);
int perguntarDificuldadeIA(void);
void exibirConquista(const char* titulo); // NOVO

#endif
