#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>

// Detectar sistema operacional
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
    #define PAUSE_COMMAND "pause"
    #define SET_TITLE "title Jogo da velha - Prova do Douglas"
    #define SET_COLOR "Color 0A"
#else
    #define CLEAR_SCREEN "clear"
    #define PAUSE_COMMAND "read -p 'Pressione Enter para continuar...'"
    #define SET_TITLE "echo '\033]0;Jogo da velha - Prova do Douglas\007'"
    #define SET_COLOR "echo '\033[32m'" // Verde no terminal
#endif

// Constantes
#define TAMANHO_TABULEIRO 9
#define LINHAS 3
#define COLUNAS 3
#define VAZIO ' '
#define JOGADOR_X 'X'
#define JOGADOR_O 'O'

// Enums para melhor legibilidade
typedef enum {
    MENU_PLAY = 1,
    MENU_INSTRUCOES,
    MENU_CREDITOS,
    MENU_REFERENCIA,
    MENU_SAIR
} MenuPrincipal;

typedef enum {
    MODO_PVP = 1,
    MODO_PVC,
    MODO_VOLTAR
} ModoJogo;

typedef enum {
    DIFICULDADE_FACIL = 1,
    DIFICULDADE_MEDIO
} Dificuldade;

typedef enum {
    CONTINUAR_JOGO = 1,
    VOLTAR_MENU
} ContinuarJogo;

// Estrutura do jogo
typedef struct {
    char tabuleiro[TAMANHO_TABULEIRO];
    int placarX;
    int placarO;
    int empates;
    char jogadorAtual;
    int modoJogo;
    int dificuldade;
} JogoDaVelha;

// Padrões de vitória (linhas, colunas, diagonais)
const int PADROES_VITORIA[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // linhas
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // colunas
    {0, 4, 8}, {2, 4, 6}             // diagonais
};

// Estratégias da IA (posições prioritárias)
const int ESTRATEGIA_IA[] = {4, 0, 2, 6, 8, 1, 3, 5, 7}; // centro, cantos, bordas

// Protótipos das funções
void configurarSistema(void);
void limparTela(void);
void pausar(void);
void inicializarJogo(JogoDaVelha* jogo);
void limparTabuleiro(JogoDaVelha* jogo);
void exibirTabuleiro(const JogoDaVelha* jogo);
void exibirLegenda(void);
char verificarVencedor(const JogoDaVelha* jogo);
bool tabuleiroCheio(const JogoDaVelha* jogo);
bool jogadaValida(const JogoDaVelha* jogo, int posicao);
void fazerJogada(JogoDaVelha* jogo, int posicao);
int obterJogadaHumano(const JogoDaVelha* jogo);
int obterJogadaIA(const JogoDaVelha* jogo);
int encontrarJogadaVencedora(const JogoDaVelha* jogo, char jogador);
int encontrarJogadaBloqueio(const JogoDaVelha* jogo);
int obterJogadaAleatoria(const JogoDaVelha* jogo);
void alternarJogador(JogoDaVelha* jogo);
void executarJogo(JogoDaVelha* jogo);
void exibirResultado(const JogoDaVelha* jogo, char vencedor);
int obterOpcaoMenu(int min, int max);

// Funções de interface
void exibirCapaPrincipal(void);
void exibirCapaJogo(void);
void exibirMenuFimJogo(void);
void exibirMenuDificuldade(void);
void exibirInstrucoes(void);
void exibirCreditos(void);
void exibirReferencias(void);

// Funções de menu
void menuPrincipal(void);
void menuJogo(void);

// Implementações

void configurarSistema(void) {
    setlocale(LC_ALL, "Portuguese");
    system(SET_TITLE);
    system(SET_COLOR);
}

void limparTela(void) {
    system(CLEAR_SCREEN);
}

void pausar(void) {
    system(PAUSE_COMMAND);
}

void inicializarJogo(JogoDaVelha* jogo) {
    limparTabuleiro(jogo);
    jogo->placarX = 0;
    jogo->placarO = 0;
    jogo->empates = 0;
    jogo->jogadorAtual = JOGADOR_X;
    jogo->modoJogo = MODO_PVP;
    jogo->dificuldade = DIFICULDADE_FACIL;
}

void limparTabuleiro(JogoDaVelha* jogo) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        jogo->tabuleiro[i] = VAZIO;
    }
    jogo->jogadorAtual = JOGADOR_X;
}

void exibirTabuleiro(const JogoDaVelha* jogo) {
    limparTela();
    printf("##############JOGO DA VELHA ####################\n\n");
    printf("JOGADOR 1 = X\nJOGADOR 2 = O\n\n");
    
    printf("\t %c | %c | %c \n", jogo->tabuleiro[0], jogo->tabuleiro[1], jogo->tabuleiro[2]);
    printf("\t --------- \n");
    printf("\t %c | %c | %c \n", jogo->tabuleiro[3], jogo->tabuleiro[4], jogo->tabuleiro[5]);
    printf("\t --------- \n");
    printf("\t %c | %c | %c \n", jogo->tabuleiro[6], jogo->tabuleiro[7], jogo->tabuleiro[8]);
    printf("\n");
}

void exibirLegenda(void) {
    printf("\n\t*-----OBS---* \n");
    printf("\t| 1 | 2 | 3 |\n");
    printf("\t| 4 | 5 | 6 |\n");
    printf("\t| 7 | 8 | 9 |\n");
    printf("\t*-----------*\n\n");
}

char verificarVencedor(const JogoDaVelha* jogo) {
    for (int i = 0; i < 8; i++) {
        char primeiro = jogo->tabuleiro[PADROES_VITORIA[i][0]];
        if (primeiro != VAZIO &&
            primeiro == jogo->tabuleiro[PADROES_VITORIA[i][1]] &&
            primeiro == jogo->tabuleiro[PADROES_VITORIA[i][2]]) {
            return primeiro;
        }
    }
    return VAZIO;
}

bool tabuleiroCheio(const JogoDaVelha* jogo) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (jogo->tabuleiro[i] == VAZIO) {
            return false;
        }
    }
    return true;
}

bool jogadaValida(const JogoDaVelha* jogo, int posicao) {
    return posicao >= 1 && posicao <= 9 && jogo->tabuleiro[posicao - 1] == VAZIO;
}

void fazerJogada(JogoDaVelha* jogo, int posicao) {
    if (jogadaValida(jogo, posicao)) {
        jogo->tabuleiro[posicao - 1] = jogo->jogadorAtual;
    }
}

int obterJogadaHumano(const JogoDaVelha* jogo) {
    int jogada;
    do {
        printf("VEZ: %c\n", jogo->jogadorAtual);
        printf("Deseja jogar em qual casa? ");
        
        if (scanf("%d", &jogada) != 1) {
            // Limpar buffer em caso de entrada inválida
            while (getchar() != '\n');
            printf("Entrada invalida! Digite um numero de 1 a 9.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        }
        
        // Limpar buffer
        while (getchar() != '\n');
        
        if (!jogadaValida(jogo, jogada)) {
            if (jogada < 1 || jogada > 9) {
                printf("Jogada %d invalida. Voce so pode marcar de 1 a 9\n", jogada);
            } else {
                printf("Casa ocupada. Jogada invalida\n");
            }
            printf("Pressione Enter para continuar...");
            getchar();
        }
    } while (!jogadaValida(jogo, jogada));
    
    return jogada;
}

int encontrarJogadaVencedora(const JogoDaVelha* jogo, char jogador) {
    for (int i = 0; i < 8; i++) {
        int count = 0, posicaoVazia = -1;
        
        for (int j = 0; j < 3; j++) {
            int pos = PADROES_VITORIA[i][j];
            if (jogo->tabuleiro[pos] == jogador) {
                count++;
            } else if (jogo->tabuleiro[pos] == VAZIO) {
                posicaoVazia = pos;
            }
        }
        
        if (count == 2 && posicaoVazia != -1) {
            return posicaoVazia + 1;
        }
    }
    return -1;
}

int encontrarJogadaBloqueio(const JogoDaVelha* jogo) {
    char oponente = (jogo->jogadorAtual == JOGADOR_X) ? JOGADOR_O : JOGADOR_X;
    return encontrarJogadaVencedora(jogo, oponente);
}

int obterJogadaAleatoria(const JogoDaVelha* jogo) {
    int jogada;
    do {
        srand((unsigned)time(NULL));
        jogada = (rand() % 9) + 1;
    } while (!jogadaValida(jogo, jogada));
    return jogada;
}

int obterJogadaIA(const JogoDaVelha* jogo) {
    printf("VEZ: %c (Computador pensando...)\n", jogo->jogadorAtual);
    
    // Pequena pausa para simular "pensamento"
    #ifdef _WIN32
        system("timeout /t 1 >nul");
    #else
        system("sleep 1");
    #endif
    
    if (jogo->dificuldade == DIFICULDADE_FACIL) {
        return obterJogadaAleatoria(jogo);
    }
    
    // Dificuldade média: estratégia mais inteligente
    
    // 1. Tentar vencer
    int jogadaVencedora = encontrarJogadaVencedora(jogo, jogo->jogadorAtual);
    if (jogadaVencedora != -1) {
        printf("Computador jogou na casa %d\n", jogadaVencedora);
        return jogadaVencedora;
    }
    
    // 2. Bloquear oponente
    int jogadaBloqueio = encontrarJogadaBloqueio(jogo);
    if (jogadaBloqueio != -1) {
        printf("Computador jogou na casa %d\n", jogadaBloqueio);
        return jogadaBloqueio;
    }
    
    // 3. Seguir estratégia (centro, cantos, bordas)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        int posicao = ESTRATEGIA_IA[i] + 1;
        if (jogadaValida(jogo, posicao)) {
            printf("Computador jogou na casa %d\n", posicao);
            return posicao;
        }
    }
    
    int jogadaAleatoria = obterJogadaAleatoria(jogo);
    printf("Computador jogou na casa %d\n", jogadaAleatoria);
    return jogadaAleatoria;
}

void alternarJogador(JogoDaVelha* jogo) {
    jogo->jogadorAtual = (jogo->jogadorAtual == JOGADOR_X) ? JOGADOR_O : JOGADOR_X;
}

void executarJogo(JogoDaVelha* jogo) {
    char vencedor = VAZIO;
    
    while (vencedor == VAZIO && !tabuleiroCheio(jogo)) {
        exibirTabuleiro(jogo);
        exibirLegenda();
        printf("PLACAR X: %d\n", jogo->placarX);
        printf("PLACAR O: %d\n", jogo->placarO);
        printf("EMPATES: %d\n\n", jogo->empates);
        
        int jogada;
        
        if (jogo->modoJogo == MODO_PVP || jogo->jogadorAtual == JOGADOR_X) {
            jogada = obterJogadaHumano(jogo);
        } else {
            jogada = obterJogadaIA(jogo);
        }
        
        fazerJogada(jogo, jogada);
        vencedor = verificarVencedor(jogo);
        
        if (vencedor == VAZIO) {
            alternarJogador(jogo);
        }
    }
    
    // Atualizar placar
    if (vencedor == JOGADOR_X) {
        jogo->placarX++;
    } else if (vencedor == JOGADOR_O) {
        jogo->placarO++;
    } else {
        jogo->empates++;
    }
    
    exibirTabuleiro(jogo);
    exibirLegenda();
    printf("PLACAR X: %d\n", jogo->placarX);
    printf("PLACAR O: %d\n", jogo->placarO);
    printf("EMPATES: %d\n\n", jogo->empates);
    exibirResultado(jogo, vencedor);
}

void exibirResultado(const JogoDaVelha* jogo, char vencedor) {
    if (vencedor == JOGADOR_X) {
        printf("\t========================\n");
        printf("\t    JOGADOR X VENCEU!   \n");
        printf("\t========================\n\n");
    } else if (vencedor == JOGADOR_O) {
        printf("\t========================\n");
        printf("\t    JOGADOR O VENCEU!   \n");
        printf("\t========================\n\n");
    } else {
        printf("\t========================\n");
        printf("\t       EMPATE!          \n");
        printf("\t========================\n\n");
    }
}

int obterOpcaoMenu(int min, int max) {
    int opcao;
    do {
        if (scanf("%d", &opcao) != 1) {
            // Limpar buffer em caso de entrada inválida
            while (getchar() != '\n');
            printf("Entrada invalida! Digite um numero entre %d e %d: ", min, max);
            continue;
        }
        
        // Limpar buffer
        while (getchar() != '\n');
        
        if (opcao < min || opcao > max) {
            printf("Opcao invalida! Digite um numero entre %d e %d: ", min, max);
        }
    } while (opcao < min || opcao > max);
    return opcao;
}

void menuJogo(void) {
    JogoDaVelha jogo;
    inicializarJogo(&jogo);
    
    // Selecionar modo de jogo
    exibirCapaJogo();
    printf("Escolha uma opcao: ");
    int modo = obterOpcaoMenu(1, 3);
    
    if (modo == MODO_VOLTAR) {
        menuPrincipal();
        return;
    }
    
    jogo.modoJogo = modo;
    
    // Se for contra computador, selecionar dificuldade
    if (modo == MODO_PVC) {
        limparTela();
        exibirMenuDificuldade();
        printf("Escolha uma opcao: ");
        jogo.dificuldade = obterOpcaoMenu(1, 2);
    }
    
    // Loop principal do jogo
    int continuar;
    do {
        limparTabuleiro(&jogo);
        executarJogo(&jogo);
        
        exibirMenuFimJogo();
        printf("Digite sua opcao desejada: ");
        continuar = obterOpcaoMenu(1, 2);
        
        if (continuar == VOLTAR_MENU) {
            limparTela();
            menuPrincipal();
            return;
        }
        
        limparTela();
    } while (continuar == CONTINUAR_JOGO);
}

void menuPrincipal(void) {
    int opcao;
    
    do {
        exibirCapaPrincipal();
        printf("Digite a sua opcao: ");
        opcao = obterOpcaoMenu(1, 5);
        limparTela();
        
        switch (opcao) {
            case MENU_PLAY:
                menuJogo();
                break;
            case MENU_INSTRUCOES:
                exibirInstrucoes();
                break;
            case MENU_CREDITOS:
                exibirCreditos();
                break;
            case MENU_REFERENCIA:
                exibirReferencias();
                break;
            case MENU_SAIR:
                printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
                return;
        }
    } while (opcao != MENU_SAIR);
}

// Funções de interface
void exibirCapaPrincipal(void) {
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                                            JOGO DA VELHA                                                        |\n");
    printf("|                                                                                                                  |\n");
    printf("|     *-------*   *----*    *-----*   *----*                      *--* *--*  *------*  *---*      *             |\n");
    printf("|      |__. .__|  |      |  |  .__.|  |      |                    |  | |  |  |  ____|  |   |     / \\            |\n");
    printf("|         | |     | *--* |  | |       | *--* |       -> DA <-     *  * *  *  | |__.    |   |    /   \\           |\n");
    printf("|         | |     | |  | |  | |  *-*  | |  | |         *-*         \\  *  /   |  __|    |   |   /  *  \\          |\n");
    printf("|      *--* |     | *--* |  | |  | |  | *--* |         / /          \\   /    | |____.  |   |  *  * *  *         |\n");
    printf("|      |    |     |      |  | *--* |  |      |         *-*           \\ /     |      |  |   |  |  | |  |         |\n");
    printf("|      *----*     *----*    *----*    *----*                          *      *--**--*  *---*  *-------*         |\n");
    printf("|                                                                                                                  |\n");
    printf("|                                                                                 by Stella Karolina              |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                Menu: 1 - Play | 2 - Instrucoes | 3 - Creditos | 4 - Referencia | 5 - Sair                     |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n\n");
}

void exibirCapaJogo(void) {
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                                            JOGO DA VELHA                                                        |\n");
    printf("|                                                                                                                  |\n");
    printf("|                                        SELECIONE O MODO DE JOGO                                                 |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                           Menu: 1 - Player vs Player | 2 - vs Computador | 3 - Voltar                          |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n\n");
}

void exibirMenuFimJogo(void) {
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                                          PARTIDA FINALIZADA!                                                    |\n");
    printf("|                                                                                                                  |\n");
    printf("|                                     Menu: 1 - Jogar Novamente | 2 - Menu Principal                              |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n\n");
}

void exibirMenuDificuldade(void) {
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|                                        SELECIONE A DIFICULDADE                                                  |\n");
    printf("|                                                                                                                  |\n");
    printf("|                                      1 - Facil (IA Aleatoria)                                                   |\n");
    printf("|                                      2 - Medio (IA Inteligente)                                                 |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n\n");
}

void exibirInstrucoes(void) {
    printf("====================================================================================================================\n");
    printf("|                                              INSTRUCOES                                                         |\n");
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|   COMO JOGAR:                                                                                                   |\n");
    printf("|   - O tabuleiro e uma matriz de 3x3 posicoes                                                                   |\n");
    printf("|   - Dois jogadores alternam jogadas: X e O                                                                     |\n");
    printf("|   - O objetivo e formar uma linha de 3 simbolos iguais                                                         |\n");
    printf("|   - Pode ser na horizontal, vertical ou diagonal                                                                |\n");
    printf("|                                                                                                                  |\n");
    printf("|   LEGENDA DO TABULEIRO:                                                                                         |\n");
    printf("|                                                                                                                  |\n");
    printf("|        | 1 | 2 | 3 |                                                                                           |\n");
    printf("|        | 4 | 5 | 6 |                                                                                           |\n");
    printf("|        | 7 | 8 | 9 |                                                                                           |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n");
    printf("|                           Menu: 1 - Jogar | 2 - Voltar | 3 - Sair                                              |\n");
    printf("====================================================================================================================\n\n");
    printf("Opcao: ");
    
    int opcao = obterOpcaoMenu(1, 3);
    limparTela();
    
    switch (opcao) {
        case 1: menuJogo(); break;
        case 2: return;
        case 3: 
            printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
            exit(0);
    }
}

void exibirCreditos(void) {
    printf("====================================================================================================================\n");
    printf("|                                               CREDITOS                                                          |\n");
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|             Curso: Ciencias da Computacao                                                                       |\n");
    printf("|             Disciplina: Programacao - Prova do Douglas                                                          |\n");
    printf("|             Projeto: Jogo da Velha                                                                              |\n");
    printf("|             Nome: Stella Karolina Nunes                                                                         |\n");
    printf("|             Matricula: 20223834810                                                                              |\n");
    printf("|                                                                                                                  |\n");
    printf("|             Versao: 2.0 - Multiplataforma                                                                       |\n");
    printf("|             Data: 2024                                                                                          |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n");
    printf("|                           Menu: 1 - Jogar | 2 - Voltar | 3 - Sair                                              |\n");
    printf("====================================================================================================================\n\n");
    printf("Opcao: ");
    
    int opcao = obterOpcaoMenu(1, 3);
    limparTela();
    
    switch (opcao) {
        case 1: menuJogo(); break;
        case 2: return;
        case 3: 
            printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
            exit(0);
    }
}

void exibirReferencias(void) {
    printf("====================================================================================================================\n");
    printf("|                                             REFERENCIAS                                                         |\n");
    printf("====================================================================================================================\n");
    printf("|                                                                                                                  |\n");
    printf("|   Regras do Jogo:                                                                                               |\n");
    printf("|   https://www.bigmae.com/regras-jogo-da-velha                                                                   |\n");
    printf("|                                                                                                                  |\n");
    printf("|   Inspiracao de Design:                                                                                         |\n");
    printf("|   https://github.com/samuelCupertino                                                                            |\n");
    printf("|                                                                                                                  |\n");
    printf("|   Documentacao C:                                                                                               |\n");
    printf("|   https://en.cppreference.com/w/c                                                                               |\n");
    printf("|                                                                                                                  |\n");
    printf("====================================================================================================================\n");
    printf("|                           Menu: 1 - Jogar | 2 - Voltar | 3 - Sair                                              |\n");
    printf("====================================================================================================================\n\n");
    printf("Opcao: ");
    
    int opcao = obterOpcaoMenu(1, 3);
    limparTela();
    
    switch (opcao) {
        case 1: menuJogo(); break;
        case 2: return;
        case 3: 
            printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
            exit(0);
    }
}

int main() {
    configurarSistema();
    menuPrincipal();
    
    printf("\n\n");
    pausar();
    return 0;
}