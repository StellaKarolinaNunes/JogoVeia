
#include "i18n.h"
#include "config.h"
#include "theme.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

typedef struct {
  const char *key;
  const char *pt;
  const char *en;
  const char *es;
} Translation;

static const Translation dict[] = {
    {"[2] JOGAR COM O", "[2] JOGAR COM O", "[2] PLAY WITH O",
     "[2] JUGAR CON O"},
    {"  Escolha o idioma que será utilizado nas telas, menus e mensagens do "
     "jogo.",
     "  Escolha o idioma que será utilizado nas telas, menus e mensagens do "
     "jogo.",
     "  Choose the language to be used in the game screens, menus, and "
     "messages.",
     "  Elige el idioma que se utilizará en las pantallas, menús y mensajes "
     "del juego."},
    {"DIGITE O NOME DO JOGADOR %d: ", "DIGITE O NOME DO JOGADOR %d: ",
     "[EN] DIGITE O NOME DO JOGADOR %d: ",
     "[ES] DIGITE O NOME DO JOGADOR %d: "},
    {"      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ESC para "
     "cancelar",
     "      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ESC para "
     "cancelar",
     "[EN]       • Use ↑ ↓ para navegar     • ENTER para confirmar     • ESC "
     "para cancelar",
     "[ES]       • Use ↑ ↓ para navegar     • ENTER para confirmar     • ESC "
     "para cancelar"},
    {"[1] JOGADOR VS JOGADOR", "[1] JOGADOR VS JOGADOR", "[1] PLAYER VS PLAYER",
     "[1] JUGADOR VS JUGADOR"},
    {"TABULEIRO", "TABULEIRO", "BOARD", "TABLERO"},
    {"CONFIRMAR AÇÃO", "CONFIRMAR AÇÃO", "CONFIRM ACTION", "CONFIRMAR ACCIÓN"},
    {"  Ao colocar a 4ª peça, a mais antiga desaparece automaticamente.",
     "  Ao colocar a 4ª peça, a mais antiga desaparece automaticamente.",
     "  When placing the 4th piece, the oldest one automatically disappears.",
     "  Al colocar la 4ta pieza, la más antigua desaparece automáticamente."},
    {"TIPO DE PARTIDA", "TIPO DE PARTIDA", "MATCH TYPE", "TIPO DE PARTIDA"},
    {"CRÉDITOS DO PROJETO", "CRÉDITOS DO PROJETO", "PROJECT CREDITS",
     "CRÉDITOS DEL PROYECTO"},
    {"  JOGADOR VS IA: enfrente o computador e teste suas melhores "
     "estratégias.",
     "  JOGADOR VS IA: enfrente o computador e teste suas melhores "
     "estratégias.",
     "  PLAYER VS AI: face the computer and test your best strategies.",
     "  JUGADOR VS IA: enfréntate a la computadora y prueba tus mejores "
     "estrategias."},
    {"      • Use ↑ ↓ para navegar     • ENTER para selecionar     • 0, Q ou "
     "ESC para voltar ao Menu Principal",
     "      • Use ↑ ↓ para navegar     • ENTER para selecionar     • 0, Q ou "
     "ESC para voltar ao Menu Principal",
     "      • Use ↑ ↓ to navigate      • ENTER to select           • 0, Q or "
     "ESC to return to Main Menu",
     "      • Usa ↑ ↓ para navegar     • ENTER para seleccionar    • 0, Q o "
     "ESC para volver al Menú Principal"},
    {"  Acompanhe as vitórias, empates, derrotas e medalhas conquistadas por "
     "cada jogador.",
     "  Acompanhe as vitórias, empates, derrotas e medalhas conquistadas por "
     "cada jogador.",
     "  Track the wins, draws, losses, and medals earned by each player.",
     "  Sigue las victorias, empates, derrotas y medallas ganadas por cada "
     "jugador."},
    {"      • Use ↑ ↓ para navegar     • ENTER para aplicar     • 0, Q ou ESC "
     "para voltar ao Menu Principal",
     "      • Use ↑ ↓ para navegar     • ENTER para aplicar     • 0, Q ou ESC "
     "para voltar ao Menu Principal",
     "      • Use ↑ ↓ to navigate      • ENTER to apply         • 0, Q or ESC "
     "to return to Main Menu",
     "      • Usa ↑ ↓ para navegar     • ENTER para aplicar     • 0, Q o ESC "
     "para volver al Menú Principal"},
    {"  MODO INFINITO: cada jogador pode manter apenas 3 peças no tabuleiro.",
     "  MODO INFINITO: cada jogador pode manter apenas 3 peças no tabuleiro.",
     "  INFINITE MODE: each player can only keep 3 pieces on the board.",
     "  MODO INFINITO: cada jugador solo puede mantener 3 piezas en el "
     "tablero."},
    {"RANKING GLOBAL", "RANKING GLOBAL", "GLOBAL RANKING", "RANKING GLOBAL"},
    {"TURNO ATUAL", "TURNO ATUAL", "CURRENT TURN", "TURNO ACTUAL"},
    {"[2] JOGADOR VS IA", "[2] JOGADOR VS IA", "[2] PLAYER VS AI",
     "[2] JUGADOR VS IA"},
    {"             Sorteando o primeiro jogador... %c",
     "             Sorteando o primeiro jogador... %c",
     "[EN]              Sorteando o primeiro jogador... %c",
     "[ES]              Sorteando o primeiro jogador... %c"},
    {"JOGAR", "JOGAR", "PLAY", "JUGAR"},
    {"REFERÊNCIAS TÉCNICAS", "REFERÊNCIAS TÉCNICAS", "TECHNICAL REFERENCES",
     "REFERENCIAS TÉCNICAS"},
    {"MELHORES JOGADORES", "MELHORES JOGADORES", "BEST PLAYERS",
     "MEJORES JUGADORES"},
    {"RESULTADO DO SORTEIO", "RESULTADO DO SORTEIO", "DRAW RESULT",
     "RESULTADO DEL SORTEO"},
    {"  Escolha como deseja jogar. Cada modo possui uma experiência diferente "
     "para desafiar sua estratégia.",
     "  Escolha como deseja jogar. Cada modo possui uma experiência diferente "
     "para desafiar sua estratégia.",
     "  Choose how you want to play. Each mode has a different experience to "
     "challenge your strategy.",
     "  Elige cómo quieres jugar. Cada modo tiene una experiencia diferente "
     "para desafiar tu estrategia."},
    {"  Informe os nomes dos participantes para iniciar a partida.",
     "  Informe os nomes dos participantes para iniciar a partida.",
     "  Enter the names of the participants to start the match.",
     "  Introduce los nombres de los participantes para iniciar la partida."},
    {"[0] VOLTAR AO MENU PRINCIPAL", "[0] VOLTAR AO MENU PRINCIPAL",
     "[0] BACK TO MAIN MENU", "[0] VOLVER AL MENÚ PRINCIPAL"},
    {"SELEÇÃO DE TEMA", "SELEÇÃO DE TEMA", "THEME SELECTION",
     "SELECCIÓN DE TEMA"},
    {"CONFIGURAR JOGADORES", "CONFIGURAR JOGADORES", "CONFIGURE PLAYERS",
     "CONFIGURAR JUGADORES"},
    {"  Escolha como será definida a vitória antes de iniciar o jogo.",
     "  Escolha como será definida a vitória antes de iniciar o jogo.",
     "  Choose how victory will be defined before starting the game.",
     "  Elige cómo se definirá la victoria antes de iniciar el juego."},
    {"[2] EDITAR NOMES DOS JOGADORES", "[2] EDITAR NOMES DOS JOGADORES",
     "[2] EDIT PLAYER NAMES", "[2] EDITAR NOMBRES DE JUGADORES"},
    {"MODO DE JOGO", "MODO DE JOGO", "GAME MODE", "MODO DE JUEGO"},
    {"[1] JOGAR COM X", "[1] JOGAR COM X", "[1] PLAY WITH X",
     "[1] JUGAR CON X"},
    {"SOBRE O MODO SELECIONADO", "SOBRE O MODO SELECIONADO",
     "ABOUT THE SELECTED MODE", "SOBRE EL MODO SELECCIONADO"},
    {"TABULEIRO SELECIONÁVEL", "TABULEIRO SELECIONÁVEL", "SELECTABLE BOARD",
     "TABLERO SELECCIONABLE"},
    {"Casa selecionada: %d", "Casa selecionada: %d",
     "[EN] Casa selecionada: %d", "[ES] Casa selecionada: %d"},
    {"[Q] VOLTAR AO MENU PRINCIPAL", "[Q] VOLTAR AO MENU PRINCIPAL",
     "[Q] BACK TO MAIN MENU", "[Q] VOLVER AL MENÚ PRINCIPAL"},
    {"  JOGADOR VS JOGADOR: desafie outra pessoa no mesmo computador, "
     "alternando entre X e O.",
     "  JOGADOR VS JOGADOR: desafie outra pessoa no mesmo computador, "
     "alternando entre X e O.",
     "  PLAYER VS PLAYER: challenge another person on the same computer, "
     "alternating between X and O.",
     "  JUGADOR VS JUGADOR: desafía a otra persona en la misma computadora, "
     "alternando entre X y O."},
    {"[2] MELHOR DE 5 — TORNEIO", "[2] MELHOR DE 5 — TORNEIO",
     "[2] BEST OF 5 — TOURNAMENT", "[2] MEJOR DE 5 — TORNEO"},
    {"[0] PARTIDA ÚNICA — PADRÃO", "[0] PARTIDA ÚNICA — PADRÃO",
     "[0] SINGLE MATCH — DEFAULT", "[0] PARTIDA ÚNICA — ESTÁNDAR"},
    {"  Após confirmar o nome do Jogador 2, você revisará as informações.",
     "  Após confirmar o nome do Jogador 2, você revisará as informações.",
     "  After confirming Player 2's name, you will review the information.",
     "  Después de confirmar el nombre del Jugador 2, revisarás la "
     "información."},
    {"  Confira os nomes antes de iniciar a partida.",
     "  Confira os nomes antes de iniciar a partida.",
     "  Check the names before starting the match.",
     "  Revisa los nombres antes de iniciar la partida."},
    {"SELEÇÃO DE IDIOMA", "SELEÇÃO DE IDIOMA", "LANGUAGE SELECTION",
     "SELECCIÓN DE IDIOMA"},
    {"      • Digite um nome e pressione ENTER para salvar     • ESC para "
     "cancelar",
     "      • Digite um nome e pressione ENTER para salvar     • ESC para "
     "cancelar",
     "[EN]       • Digite um nome e pressione ENTER para salvar     • ESC para "
     "cancelar",
     "[ES]       • Digite um nome e pressione ENTER para salvar     • ESC para "
     "cancelar"},
    {"PRÓXIMA ETAPA", "PRÓXIMA ETAPA", "NEXT STEP", "PRÓXIMA ETAPA"},
    {"  PARTIDA ÚNICA: uma vitória define o vencedor da partida.",
     "  PARTIDA ÚNICA: uma vitória define o vencedor da partida.",
     "  SINGLE MATCH: one win defines the winner of the match.",
     "  PARTIDA ÚNICA: una victoria define al ganador de la partida."},
    {"[3] MODO INFINITO", "[3] MODO INFINITO", "[3] INFINITE MODE",
     "[3] MODO INFINITO"},
    {"É a vez de: %s [%c]", "É a vez de: %s [%c]", "[EN] É a vez de: %s [%c]",
     "[ES] É a vez de: %s [%c]"},
    {"[0] CANCELAR E VOLTAR", "[0] CANCELAR E VOLTAR", "[0] CANCEL AND RETURN",
     "[0] CANCELAR Y VOLVER"},
    {"NOMES REGISTRADOS", "NOMES REGISTRADOS", "REGISTERED NAMES",
     "NOMBRES REGISTRADOS"},
    {"[1] MELHOR DE 3 — TORNEIO", "[1] MELHOR DE 3 — TORNEIO",
     "[1] BEST OF 3 — TOURNAMENT", "[1] MEJOR DE 3 — TORNEO"},
    {"NUVEM: SAVE / LOAD", "NUVEM: SAVE / LOAD", "CLOUD: SAVE / LOAD",
     "NUBE: SAVE / LOAD"},
    {"  O Jogador 1 utilizará o símbolo X e o Jogador 2 utilizará o símbolo O.",
     "  O Jogador 1 utilizará o símbolo X e o Jogador 2 utilizará o símbolo O.",
     "  Player 1 will use the X symbol and Player 2 will use the O symbol.",
     "  El Jugador 1 usará el símbolo X y el Jugador 2 usará el símbolo O."},
    {"      • Use ↑ ↓ para navegar e ENTER para selecionar",
     "      • Use ↑ ↓ para navegar e ENTER para selecionar",
     "      • Use ↑ ↓ to navigate and ENTER to select",
     "      • Usa ↑ ↓ para navegar y ENTER para seleccionar"},
    {"SAIR DO SISTEMA", "SAIR DO SISTEMA", "EXIT SYSTEM", "SALIR DEL SISTEMA"},
    {"[1] SEGUIR PARA A PARTIDA", "[1] SEGUIR PARA A PARTIDA",
     "[1] PROCEED TO MATCH", "[1] PROCEDER A LA PARTIDA"},
    {"      • Use ↑ ↓ para navegar     • ENTER para selecionar     • Q ou ESC "
     "para voltar ao Menu Principal",
     "      • Use ↑ ↓ para navegar     • ENTER para selecionar     • Q ou ESC "
     "para voltar ao Menu Principal",
     "      • Use ↑ ↓ to navigate      • ENTER to select           • Q or ESC "
     "to return to Main Menu",
     "      • Usa ↑ ↓ para navegar     • ENTER para seleccionar    • Q o ESC "
     "para volver al Menú Principal"},
    {"  Após confirmar o nome do Jogador 1, será solicitado o nome do Jogador "
     "2.",
     "  Após confirmar o nome do Jogador 1, será solicitado o nome do Jogador "
     "2.",
     "  After confirming Player 1's name, Player 2's name will be requested.",
     "  Después de confirmar el nombre del Jugador 1, se solicitará el nombre "
     "del Jugador 2."},
    {"  MELHOR DE 3: vence quem conquistar 2 vitórias primeiro.",
     "  MELHOR DE 3: vence quem conquistar 2 vitórias primeiro.",
     "  BEST OF 3: the first to achieve 2 wins is the winner.",
     "  MEJOR DE 3: el primero en conseguir 2 victorias es el ganador."},
    {"  MELHOR DE 5: vence quem conquistar 3 vitórias primeiro.",
     "  MELHOR DE 5: vence quem conquistar 3 vitórias primeiro.",
     "  BEST OF 5: the first to achieve 3 wins is the winner.",
     "  MEJOR DE 5: el primero en conseguir 3 victorias es el ganador."},
    {"      [ CONTROLES DA TELA ]", "      [ CONTROLES DA TELA ]",
     "[EN]       [ CONTROLES DA TELA ]", "[ES]       [ CONTROLES DA TELA ]"},
    {"ESCOLHA O SEU SÍMBOLO", "ESCOLHA O SEU SÍMBOLO", "CHOOSE YOUR SYMBOL",
     "ELIGE TU SÍMBOLO"},
    {"  CADA JOGADOR LANÇOU UM DADO PARA DEFINIR QUEM COMEÇA.",
     "  CADA JOGADOR LANÇOU UM DADO PARA DEFINIR QUEM COMEÇA.",
     "  EACH PLAYER ROLLED A DICE TO DECIDE WHO STARTS.",
     "  CADA JUGADOR LANZÓ UN DADO PARA DEFINIR QUIÉN EMPIEZA."},
    {"IDIOMA ATUAL", "IDIOMA ATUAL", "CURRENT LANGUAGE", "IDIOMA ACTUAL"},
    {"      • Use ↑ ↓ ← → para navegar     • ENTER para aplicar     • 00, Q ou "
     "ESC para voltar ao menu principal",
     "      • Use ↑ ↓ ← → para navegar     • ENTER para aplicar     • 00, Q ou "
     "ESC para voltar ao menu principal",
     "[EN]       • Use ↑ ↓ ← → para navegar     • ENTER para aplicar     • 00, "
     "Q ou ESC para voltar ao menu principal",
     "[ES]       • Use ↑ ↓ ← → para navegar     • ENTER para aplicar     • 00, "
     "Q ou ESC para voltar ao menu principal"},
    {"INSTRUÇÕES OFICIAIS", "INSTRUÇÕES OFICIAIS", "OFFICIAL INSTRUCTIONS",
     "INSTRUCCIONES OFICIALES"},
    {"IDIOMAS DISPONÍVEIS", "IDIOMAS DISPONÍVEIS", "AVAILABLE LANGUAGES",
     "IDIOMAS DISPONIBLES"},
    {"PERSONALIZAÇÃO DO JOGO", "PERSONALIZAÇÃO DO JOGO", "GAME CUSTOMIZATION",
     "PERSONALIZACIÓN DEL JUEGO"},
    {"║                             1 - Sim                                0 - "
     "Não                            ║\\n",
     "║                             1 - Sim                                0 - "
     "Não                            ║\\n",
     "║                             1 - Sim                                0 - "
     "Não                            ║\\n",
     "║                             1 - Sim                                0 - "
     "Não                            ║\\n"},
    {"║  • Wikipedia - jogo da veia                                            "
     "                              ║\\n",
     "║  • Wikipedia - jogo da veia                                            "
     "                              ║\\n",
     "║  • Wikipedia - jogo da veia                                            "
     "                              ║\\n",
     "║  • Wikipedia - jogo da veia                                            "
     "                              ║\\n"},
    {"Reproduzindo jogada %d/%d (Jogador %c na posição %d)",
     "Reproduzindo jogada %d/%d (Jogador %c na posição %d)",
     "Reproduzindo jogada %d/%d (Jogador %c na posição %d)",
     "Reproduzindo jogada %d/%d (Jogador %c na posição %d)"},
    {"      ║    │  Ao confirmar, o salvamento selecionado será ",
     "      ║    │  Ao confirmar, o salvamento selecionado será ",
     "      ║    │  Ao confirmar, o salvamento selecionado será ",
     "      ║    │  Ao confirmar, o salvamento selecionado será "},
    {"║ Saves Disponíveis:                                                     "
     "                              ║\\n",
     "║ Saves Disponíveis:                                                     "
     "                              ║\\n",
     "║ Saves Disponíveis:                                                     "
     "                              ║\\n",
     "║ Saves Disponíveis:                                                     "
     "                              ║\\n"},
    {"v%s • CARREGAR SALVAMENTO", "v%s • CARREGAR SALVAMENTO",
     "v%s • CARREGAR SALVAMENTO", "v%s • CARREGAR SALVAMENTO"},
    {"      ║      [ CONTROLES DA TELA ]                               ",
     "      ║      [ CONTROLES DA TELA ]                               ",
     "      ║      [ CONTROLES DA TELA ]                               ",
     "      ║      [ CONTROLES DA TELA ]                               "},
    {"Erro ao abrir arquivo '%s': %s\\n", "Erro ao abrir arquivo '%s': %s\\n",
     "Erro ao abrir arquivo '%s': %s\\n", "Erro ao abrir arquivo '%s': %s\\n"},
    {"║                   ✦ Você superou os desafios e conquistou o topo ",
     "║                   ✦ Você superou os desafios e conquistou o topo ",
     "║                   ✦ Você superou os desafios e conquistou o topo ",
     "║                   ✦ Você superou os desafios e conquistou o topo "},
    {"      ║    │                                SALVAMENTOS ",
     "      ║    │                                SALVAMENTOS ",
     "      ║    │                                SALVAMENTOS ",
     "      ║    │                                SALVAMENTOS "},
    {"║ 1. Salvar Jogo Atual                                                   "
     "                              ║\\n",
     "║ 1. Salvar Jogo Atual                                                   "
     "                              ║\\n",
     "║ 1. Salvar Jogo Atual                                                   "
     "                              ║\\n",
     "║ 1. Salvar Jogo Atual                                                   "
     "                              ║\\n"},
    {"      ║    │                         ║\\033[7m          ▶ [1] VER ",
     "      ║    │                         ║\\033[7m          ▶ [1] VER ",
     "      ║    │                         ║\\033[7m          ▶ [1] VER ",
     "      ║    │                         ║\\033[7m          ▶ [1] VER "},
    {"║    https://pt.wikipedia.org/wiki/Jogo_da_ veia                         "
     "                                ║\\n",
     "║    https://pt.wikipedia.org/wiki/Jogo_da_ veia                         "
     "                                ║\\n",
     "║    https://pt.wikipedia.org/wiki/Jogo_da_ veia                         "
     "                                ║\\n",
     "║    https://pt.wikipedia.org/wiki/Jogo_da_ veia                         "
     "                                ║\\n"},
    {"║                                         CRÉDITOS                       "
     "                              ║\\n",
     "║                                         CRÉDITOS                       "
     "                              ║\\n",
     "║                                         CRÉDITOS                       "
     "                              ║\\n",
     "║                                         CRÉDITOS                       "
     "                              ║\\n"},
    {"║ ! AVISO: ARQUIVO PODE TER SIDO CORROMPIDO OU ALTERADO !                "
     "                              ║\\n",
     "║ ! AVISO: ARQUIVO PODE TER SIDO CORROMPIDO OU ALTERADO !                "
     "                              ║\\n",
     "║ ! AVISO: ARQUIVO PODE TER SIDO CORROMPIDO OU ALTERADO !                "
     "                              ║\\n",
     "║ ! AVISO: ARQUIVO PODE TER SIDO CORROMPIDO OU ALTERADO !                "
     "                              ║\\n"},
    {"%s\\n", "%s\\n", "%s\\n", "%s\\n"},
    {"      ║    │                                      INFORMAÇÃO     ",
     "      ║    │                                      INFORMAÇÃO     ",
     "      ║    │                                      INFORMAÇÃO     ",
     "      ║    │                                      INFORMAÇÃO     "},
    {"      ║    │                              ║ JOGADOR: %-39.39s ║  ",
     "      ║    │                              ║ JOGADOR: %-39.39s ║  ",
     "      ║    │                              ║ JOGADOR: %-39.39s ║  ",
     "      ║    │                              ║ JOGADOR: %-39.39s ║  "},
    {"      ║    │  EMPATES: %02d                                         ",
     "      ║    │  EMPATES: %02d                                         ",
     "      ║    │  EMPATES: %02d                                         ",
     "      ║    │  EMPATES: %02d                                         "},
    {"║ - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.        "
     "                              ║\\n",
     "║ - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.        "
     "                              ║\\n",
     "║ - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.        "
     "                              ║\\n",
     "║ - O tabuleiro é uma matriz 3x3 com posições numeradas de 1 a 9.        "
     "                              ║\\n"},
    {"      ║    │  Uma nova rodada será iniciada mantendo os jogadores ",
     "      ║    │  Uma nova rodada será iniciada mantendo os jogadores ",
     "      ║    │  Uma nova rodada será iniciada mantendo os jogadores ",
     "      ║    │  Uma nova rodada será iniciada mantendo os jogadores "},
    {"║ Deseja continuar mesmo assim? (1 - Sim, 0 - Não):                      "
     "                              ║\\n",
     "║ Deseja continuar mesmo assim? (1 - Sim, 0 - Não):                      "
     "                              ║\\n",
     "║ Deseja continuar mesmo assim? (1 - Sim, 0 - Não):                      "
     "                              ║\\n",
     "║ Deseja continuar mesmo assim? (1 - Sim, 0 - Não):                      "
     "                              ║\\n"},
    {"      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar   ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar   ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar   ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar   "},
    {"      ║    │                                     [0] PULAR ",
     "      ║    │                                     [0] PULAR ",
     "      ║    │                                     [0] PULAR ",
     "      ║    │                                     [0] PULAR "},
    {"║ 3. Deletar Jogo Salvo                                                  "
     "                              ║\\n",
     "║ 3. Deletar Jogo Salvo                                                  "
     "                              ║\\n",
     "║ 3. Deletar Jogo Salvo                                                  "
     "                              ║\\n",
     "║ 3. Deletar Jogo Salvo                                                  "
     "                              ║\\n"},
    {"      ║    │%s│    │%s│    ║\\n", "      ║    │%s│    │%s│    ║\\n",
     "      ║    │%s│    │%s│    ║\\n", "      ║    │%s│    │%s│    ║\\n"},
    {"Erro: Dados essenciais do jogo não foram encontrados ou estão "
     "incompletos no arquivo.\\n",
     "Erro: Dados essenciais do jogo não foram encontrados ou estão "
     "incompletos no arquivo.\\n",
     "Erro: Dados essenciais do jogo não foram encontrados ou estão "
     "incompletos no arquivo.\\n",
     "Erro: Dados essenciais do jogo não foram encontrados ou estão "
     "incompletos no arquivo.\\n"},
    {"      ║    │                                  ESCOLHER SALVAMENTO     ",
     "      ║    │                                  ESCOLHER SALVAMENTO     ",
     "      ║    │                                  ESCOLHER SALVAMENTO     ",
     "      ║    │                                  ESCOLHER SALVAMENTO     "},
    {"      ║    │                    ║    [%d] %-15.15s  •  ",
     "      ║    │                    ║    [%d] %-15.15s  •  ",
     "      ║    │                    ║    [%d] %-15.15s  •  ",
     "      ║    │                    ║    [%d] %-15.15s  •  "},
    {"Arquivo criado: %-35.35s", "Arquivo criado: %-35.35s",
     "Arquivo criado: %-35.35s", "Arquivo criado: %-35.35s"},
    {"║   Matrícula: 20223834810                                               "
     "                              ║\\n",
     "║   Matrícula: 20223834810                                               "
     "                              ║\\n",
     "║   Matrícula: 20223834810                                               "
     "                              ║\\n",
     "║   Matrícula: 20223834810                                               "
     "                              ║\\n"},
    {"      ║    │  Partida em andamento.                               │  ",
     "      ║    │  Partida em andamento.                               │  ",
     "      ║    │  Partida em andamento.                               │  ",
     "      ║    │  Partida em andamento.                               │  "},
    {"      ║    │                        PLACAR                        │  ",
     "      ║    │                        PLACAR                        │  ",
     "      ║    │                        PLACAR                        │  ",
     "      ║    │                        PLACAR                        │  "},
    {"      ║    │                                     [1] SIM, JOGAR ",
     "      ║    │                                     [1] SIM, JOGAR ",
     "      ║    │                                     [1] SIM, JOGAR ",
     "      ║    │                                     [1] SIM, JOGAR "},
    {"%s\\033[7m%s\\033[0m%s%s", "%s\\033[7m%s\\033[0m%s%s",
     "%s\\033[7m%s\\033[0m%s%s", "%s\\033[7m%s\\033[0m%s%s"},
    {"║                                            COMO JOGAR                  "
     "                              ║\\n",
     "║                                            COMO JOGAR                  "
     "                              ║\\n",
     "║                                            COMO JOGAR                  "
     "                              ║\\n",
     "║                                            COMO JOGAR                  "
     "                              ║\\n"},
    {"      ║    │                         \\033[7m║          JOGO SALVO ",
     "      ║    │                         \\033[7m║          JOGO SALVO ",
     "      ║    │                         \\033[7m║          JOGO SALVO ",
     "      ║    │                         \\033[7m║          JOGO SALVO "},
    {"\\n   Reproduzindo jogada %d/%d (Jogador %c na posição %d)...\\n",
     "\\n   Reproduzindo jogada %d/%d (Jogador %c na posição %d)...\\n",
     "\\n   Reproduzindo jogada %d/%d (Jogador %c na posição %d)...\\n",
     "\\n   Reproduzindo jogada %d/%d (Jogador %c na posição %d)...\\n"},
    {"║ 2. Carregar Jogo Salvo                                                 "
     "                              ║\\n",
     "║ 2. Carregar Jogo Salvo                                                 "
     "                              ║\\n",
     "║ 2. Carregar Jogo Salvo                                                 "
     "                              ║\\n",
     "║ 2. Carregar Jogo Salvo                                                 "
     "                              ║\\n"},
    {"      ║    │                                      INFORMAÇÃO          ",
     "      ║    │                                      INFORMAÇÃO          ",
     "      ║    │                                      INFORMAÇÃO          ",
     "      ║    │                                      INFORMAÇÃO          "},
    {"      ║    │                                      OPÇÕES DISPONÍVEIS  ",
     "      ║    │                                      OPÇÕES DISPONÍVEIS  ",
     "      ║    │                                      OPÇÕES DISPONÍVEIS  ",
     "      ║    │                                      OPÇÕES DISPONÍVEIS  "},
    {"║                                       DELETAR JOGO SALVO               "
     "                              ║\\n",
     "║                                       DELETAR JOGO SALVO               "
     "                              ║\\n",
     "║                                       DELETAR JOGO SALVO               "
     "                              ║\\n",
     "║                                       DELETAR JOGO SALVO               "
     "                              ║\\n"},
    {"      ║    │  MÉDIO: a IA tenta vencer e bloquear suas jogadas ",
     "      ║    │  MÉDIO: a IA tenta vencer e bloquear suas jogadas ",
     "      ║    │  MÉDIO: a IA tenta vencer e bloquear suas jogadas ",
     "      ║    │  MÉDIO: a IA tenta vencer e bloquear suas jogadas "},
    {"║                             Este jogo já estava vencido por: %-38s! "
     "║\\n",
     "║                             Este jogo já estava vencido por: %-38s! "
     "║\\n",
     "║                             Este jogo já estava vencido por: %-38s! "
     "║\\n",
     "║                             Este jogo já estava vencido por: %-38s! "
     "║\\n"},
    {"      ║    │  Assim você pode pausar e voltar depois sem perder o ",
     "      ║    │  Assim você pode pausar e voltar depois sem perder o ",
     "      ║    │  Assim você pode pausar e voltar depois sem perder o ",
     "      ║    │  Assim você pode pausar e voltar depois sem perder o "},
    {"║   Pressione Enter para voltar ao menu...                               "
     "                              ║\\n",
     "║   Pressione Enter para voltar ao menu...                               "
     "                              ║\\n",
     "║   Pressione Enter para voltar ao menu...                               "
     "                              ║\\n",
     "║   Pressione Enter para voltar ao menu...                               "
     "                              ║\\n"},
    {"║                         ║  CONQUISTA: %-38.38s ║                 ",
     "║                         ║  CONQUISTA: %-38.38s ║                 ",
     "║                         ║  CONQUISTA: %-38.38s ║                 ",
     "║                         ║  CONQUISTA: %-38.38s ║                 "},
    {"v%s • JOGO DA VEIA EM ANDAMENTO", "v%s • JOGO DA VEIA EM ANDAMENTO",
     "v%s • JOGO DA VEIA EM ANDAMENTO", "v%s • JOGO DA VEIA EM ANDAMENTO"},
    {"      ║    │                         \\033[7m║          JOGADOR O: ",
     "      ║    │                         \\033[7m║          JOGADOR O: ",
     "      ║    │                         \\033[7m║          JOGADOR O: ",
     "      ║    │                         \\033[7m║          JOGADOR O: "},
    {"║   * TABULEIRO DE REFERÊNCIA:                                           "
     "                              ║\\n",
     "║   * TABULEIRO DE REFERÊNCIA:                                           "
     "                              ║\\n",
     "║   * TABULEIRO DE REFERÊNCIA:                                           "
     "                              ║\\n",
     "║   * TABULEIRO DE REFERÊNCIA:                                           "
     "                              ║\\n"},
    {"Erro ao criar diretório '%s': %s\\n",
     "Erro ao criar diretório '%s': %s\\n",
     "Erro ao criar diretório '%s': %s\\n",
     "Erro ao criar diretório '%s': %s\\n"},
    {"v%s • SALVAR PARTIDA ATUAL", "v%s • SALVAR PARTIDA ATUAL",
     "v%s • SALVAR PARTIDA ATUAL", "v%s • SALVAR PARTIDA ATUAL"},
    {"v%s • CONFIGURAÇÃO DE JOGADORES", "v%s • CONFIGURAÇÃO DE JOGADORES",
     "v%s • CONFIGURAÇÃO DE JOGADORES", "v%s • CONFIGURAÇÃO DE JOGADORES"},
    {"      ║    │                                ✦ Cada rodada é uma nova ",
     "      ║    │                                ✦ Cada rodada é uma nova ",
     "      ║    │                                ✦ Cada rodada é uma nova ",
     "      ║    │                                ✦ Cada rodada é uma nova "},
    {"      ║    │                         ║\\033[7m      ▶ [1] FÁCIL ",
     "      ║    │                         ║\\033[7m      ▶ [1] FÁCIL ",
     "      ║    │                         ║\\033[7m      ▶ [1] FÁCIL ",
     "      ║    │                         ║\\033[7m      ▶ [1] FÁCIL "},
    {"║  • Wikipedia - Tic-Tac-Toe (versão internacional)                      "
     "                               ║\\n",
     "║  • Wikipedia - Tic-Tac-Toe (versão internacional)                      "
     "                               ║\\n",
     "║  • Wikipedia - Tic-Tac-Toe (versão internacional)                      "
     "                               ║\\n",
     "║  • Wikipedia - Tic-Tac-Toe (versão internacional)                      "
     "                               ║\\n"},
    {"Você carregou este jogo do arquivo: %s\\n",
     "Você carregou este jogo do arquivo: %s\\n",
     "Você carregou este jogo do arquivo: %s\\n",
     "Você carregou este jogo do arquivo: %s\\n"},
    {"║    Fontes utilizadas para estudo do jogo da veia:                      "
     "                              ║\\n",
     "║    Fontes utilizadas para estudo do jogo da veia:                      "
     "                              ║\\n",
     "║    Fontes utilizadas para estudo do jogo da veia:                      "
     "                              ║\\n",
     "║    Fontes utilizadas para estudo do jogo da veia:                      "
     "                              ║\\n"},
    {"      ║    │                                      NÍVEIS ",
     "      ║    │                                      NÍVEIS ",
     "      ║    │                                      NÍVEIS ",
     "      ║    │                                      NÍVEIS "},
    {"      ║    │                                  SALVAMENTOS ",
     "      ║    │                                  SALVAMENTOS ",
     "      ║    │                                  SALVAMENTOS ",
     "      ║    │                                  SALVAMENTOS "},
    {"      ║    │  O salvamento selecionado será substituído e os ",
     "      ║    │  O salvamento selecionado será substituído e os ",
     "      ║    │  O salvamento selecionado será substituído e os ",
     "      ║    │  O salvamento selecionado será substituído e os "},
    {"      ║─────────────────────────────────────────────── v4.0 • FINAL ",
     "      ║─────────────────────────────────────────────── v4.0 • FINAL ",
     "      ║─────────────────────────────────────────────── v4.0 • FINAL ",
     "      ║─────────────────────────────────────────────── v4.0 • FINAL "},
    {"      ║    │  Escolha um nome curto para identificar esta partida ",
     "      ║    │  Escolha um nome curto para identificar esta partida ",
     "      ║    │  Escolha um nome curto para identificar esta partida ",
     "      ║    │  Escolha um nome curto para identificar esta partida "},
    {"║    Pressione ENTER para voltar ao menu...                              "
     "                              ║\\n",
     "║    Pressione ENTER para voltar ao menu...                              "
     "                              ║\\n",
     "║    Pressione ENTER para voltar ao menu...                              "
     "                              ║\\n",
     "║    Pressione ENTER para voltar ao menu...                              "
     "                              ║\\n"},
    {"║ Versão do save: %-10s │ Versão do jogo: %-10s                          "
     "                  ║\\n",
     "║ Versão do save: %-10s │ Versão do jogo: %-10s                          "
     "                  ║\\n",
     "║ Versão do save: %-10s │ Versão do jogo: %-10s                          "
     "                  ║\\n",
     "║ Versão do save: %-10s │ Versão do jogo: %-10s                          "
     "                  ║\\n"},
    {"\\a\\a", "\\a\\a", "\\a\\a", "\\a\\a"},
    {" [%c]  %02d vitórias     │    ", " [%c]  %02d vitórias     │    ",
     " [%c]  %02d vitórias     │    ", " [%c]  %02d vitórias     │    "},
    {"      ║    │  Essa ação não poderá ser desfeita.                      ",
     "      ║    │  Essa ação não poderá ser desfeita.                      ",
     "      ║    │  Essa ação não poderá ser desfeita.                      ",
     "      ║    │  Essa ação não poderá ser desfeita.                      "},
    {"║   Autor: Stella Karolina Nunes                                         "
     "                              ║\\n",
     "║   Autor: Stella Karolina Nunes                                         "
     "                              ║\\n",
     "║   Autor: Stella Karolina Nunes                                         "
     "                              ║\\n",
     "║   Autor: Stella Karolina Nunes                                         "
     "                              ║\\n"},
    {"Pressione ENTER para continuar...\\n\\n",
     "Pressione ENTER para continuar...\\n\\n",
     "Pressione ENTER para continuar...\\n\\n",
     "Pressione ENTER para continuar...\\n\\n"},
    {"\\n   Pressione Enter para voltar ao menu...                             "
     "                                \\n",
     "\\n   Pressione Enter para voltar ao menu...                             "
     "                                \\n",
     "\\n   Pressione Enter para voltar ao menu...                             "
     "                                \\n",
     "\\n   Pressione Enter para voltar ao menu...                             "
     "                                \\n"},
    {"║ Checksum esperado: %-10u │ Checksum atual: %-10u                       "
     "                   ║\\n",
     "║ Checksum esperado: %-10u │ Checksum atual: %-10u                       "
     "                   ║\\n",
     "║ Checksum esperado: %-10u │ Checksum atual: %-10u                       "
     "                   ║\\n",
     "║ Checksum esperado: %-10u │ Checksum atual: %-10u                       "
     "                   ║\\n"},
    {"      ║    │                                  GERENCIAR PROGRESSO     ",
     "      ║    │                                  GERENCIAR PROGRESSO     ",
     "      ║    │                                  GERENCIAR PROGRESSO     ",
     "      ║    │                                  GERENCIAR PROGRESSO     "},
    {"      ║    │                         ║\\033[7m        ▶ [0] PULAR ",
     "      ║    │                         ║\\033[7m        ▶ [0] PULAR ",
     "      ║    │                         ║\\033[7m        ▶ [0] PULAR ",
     "      ║    │                         ║\\033[7m        ▶ [0] PULAR "},
    {"║                              Pressione ENTER para continuar...   ",
     "║                              Pressione ENTER para continuar...   ",
     "║                              Pressione ENTER para continuar...   ",
     "║                              Pressione ENTER para continuar...   "},
    {"Tem certeza que deseja deletar '%s'? (1 - Sim, 0 - Não): ",
     "Tem certeza que deseja deletar '%s'? (1 - Sim, 0 - Não): ",
     "Tem certeza que deseja deletar '%s'? (1 - Sim, 0 - Não): ",
     "Tem certeza que deseja deletar '%s'? (1 - Sim, 0 - Não): "},
    {"║        jogo da veia — Versão: %-71s║\\n",
     "║        jogo da veia — Versão: %-71s║\\n",
     "║        jogo da veia — Versão: %-71s║\\n",
     "║        jogo da veia — Versão: %-71s║\\n"},
    {"      ║      • Acompanhe o resultado da jogada no tabuleiro.          ",
     "      ║      • Acompanhe o resultado da jogada no tabuleiro.          ",
     "      ║      • Acompanhe o resultado da jogada no tabuleiro.          ",
     "      ║      • Acompanhe o resultado da jogada no tabuleiro.          "},
    {"      ║    │                              [3] DIFÍCIL — ",
     "      ║    │                              [3] DIFÍCIL — ",
     "      ║    │                              [3] DIFÍCIL — ",
     "      ║    │                              [3] DIFÍCIL — "},
    {"║──────────────────────────────────────────── v4.0 • NOVA ",
     "║──────────────────────────────────────────── v4.0 • NOVA ",
     "║──────────────────────────────────────────── v4.0 • NOVA ",
     "║──────────────────────────────────────────── v4.0 • NOVA "},
    {"      ║    │                         ║\\033[7m      ▶ [2] MÉDIO ",
     "      ║    │                         ║\\033[7m      ▶ [2] MÉDIO ",
     "      ║    │                         ║\\033[7m      ▶ [2] MÉDIO ",
     "      ║    │                         ║\\033[7m      ▶ [2] MÉDIO "},
    {"Saindo do jogo atual...\\n", "Saindo do jogo atual...\\n",
     "Saindo do jogo atual...\\n", "Saindo do jogo atual...\\n"},
    {"Opção inválida!\\n", "Opção inválida!\\n", "Opção inválida!\\n",
     "Opção inválida!\\n"},
    {"║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Venc: "
     "%-14s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Venc: "
     "%-14s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Venc: "
     "%-14s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Venc: "
     "%-14s ║\\n"},
    {"║   Versão 3.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 3.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 3.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 3.0  - Data: 2025                                             "
     "                              ║\\n"},
    {"É a vez do jogador %s (%c)", "É a vez do jogador %s (%c)",
     "É a vez do jogador %s (%c)", "É a vez do jogador %s (%c)"},
    {"      ║    │  JOGADOR 1                                           │  ",
     "      ║    │  JOGADOR 1                                           │  ",
     "      ║    │  JOGADOR 1                                           │  ",
     "      ║    │  JOGADOR 1                                           │  "},
    {"\\n\\n", "\\n\\n", "\\n\\n", "\\n\\n"},
    {"      ║      [ COMANDOS ]                                             ",
     "      ║      [ COMANDOS ]                                             ",
     "      ║      [ COMANDOS ]                                             ",
     "      ║      [ COMANDOS ]                                             "},
    {"      ║    │                              [1] FÁCIL — ",
     "      ║    │                              [1] FÁCIL — ",
     "      ║    │                              [1] FÁCIL — ",
     "      ║    │                              [1] FÁCIL — "},
    {"║      - Pense duas jogadas à frente!                                    "
     "                              ║\\n",
     "║      - Pense duas jogadas à frente!                                    "
     "                              ║\\n",
     "║      - Pense duas jogadas à frente!                                    "
     "                              ║\\n",
     "║      - Pense duas jogadas à frente!                                    "
     "                              ║\\n"},
    {"      ║    │%s│%s│%s│    ║\\n", "      ║    │%s│%s│%s│    ║\\n",
     "      ║    │%s│%s│%s│    ║\\n", "      ║    │%s│%s│%s│    ║\\n"},
    {"      ║    │                         \\033[7m║          JOGADOR X: ",
     "      ║    │                         \\033[7m║          JOGADOR X: ",
     "      ║    │                         \\033[7m║          JOGADOR X: ",
     "      ║    │                         \\033[7m║          JOGADOR X: "},
    {"    INICIANDO REPLAY DA PARTIDA... \\n",
     "    INICIANDO REPLAY DA PARTIDA... \\n",
     "    INICIANDO REPLAY DA PARTIDA... \\n",
     "    INICIANDO REPLAY DA PARTIDA... \\n"},
    {"Arquivo '%s' deletado com sucesso!\\n",
     "Arquivo '%s' deletado com sucesso!\\n",
     "Arquivo '%s' deletado com sucesso!\\n",
     "Arquivo '%s' deletado com sucesso!\\n"},
    {"      ║    │  Ao carregar uma partida, o jogo continuará ",
     "      ║    │  Ao carregar uma partida, o jogo continuará ",
     "      ║    │  Ao carregar uma partida, o jogo continuará ",
     "      ║    │  Ao carregar uma partida, o jogo continuará "},
    {"Nenhum salvamento disponível na lista.\\n",
     "Nenhum salvamento disponível na lista.\\n",
     "Nenhum salvamento disponível na lista.\\n",
     "Nenhum salvamento disponível na lista.\\n"},
    {"Nenhum arquivo de salvamento encontrado ou erro ao listar.\\n",
     "Nenhum arquivo de salvamento encontrado ou erro ao listar.\\n",
     "Nenhum arquivo de salvamento encontrado ou erro ao listar.\\n",
     "Nenhum arquivo de salvamento encontrado ou erro ao listar.\\n"},
    {"      ║    │  Selecione um salvamento para remover do sistema. ",
     "      ║    │  Selecione um salvamento para remover do sistema. ",
     "      ║    │  Selecione um salvamento para remover do sistema. ",
     "      ║    │  Selecione um salvamento para remover do sistema. "},
    {"║   Versão 1.0  - Data: 2023                                             "
     "                              ║\\n",
     "║   Versão 1.0  - Data: 2023                                             "
     "                              ║\\n",
     "║   Versão 1.0  - Data: 2023                                             "
     "                              ║\\n",
     "║   Versão 1.0  - Data: 2023                                             "
     "                              ║\\n"},
    {"║                                       FIM DE JOGO CARREGADO!           "
     "                              ║\\n",
     "║                                       FIM DE JOGO CARREGADO!           "
     "                              ║\\n",
     "║                                       FIM DE JOGO CARREGADO!           "
     "                              ║\\n",
     "║                                       FIM DE JOGO CARREGADO!           "
     "                              ║\\n"},
    {"║   Disciplina: Programação 1                                            "
     "                              ║\\n",
     "║   Disciplina: Programação 1                                            "
     "                              ║\\n",
     "║   Disciplina: Programação 1                                            "
     "                              ║\\n",
     "║   Disciplina: Programação 1                                            "
     "                              ║\\n"},
    {"║ ! AVISO: INCOMPATIBILIDADE DE VERSÃO !                                 "
     "                              ║\\n",
     "║ ! AVISO: INCOMPATIBILIDADE DE VERSÃO !                                 "
     "                              ║\\n",
     "║ ! AVISO: INCOMPATIBILIDADE DE VERSÃO !                                 "
     "                              ║\\n",
     "║ ! AVISO: INCOMPATIBILIDADE DE VERSÃO !                                 "
     "                              ║\\n"},
    {"      ║    │                                   DIFICULDADE DA IA ",
     "      ║    │                                   DIFICULDADE DA IA ",
     "      ║    │                                   DIFICULDADE DA IA ",
     "      ║    │                                   DIFICULDADE DA IA "},
    {"v%s • CONFIRMAÇÃO DE JOGADORES", "v%s • CONFIRMAÇÃO DE JOGADORES",
     "v%s • CONFIRMAÇÃO DE JOGADORES", "v%s • CONFIRMAÇÃO DE JOGADORES"},
    {"      ║    │                                  SALVAMENTO CONCLUÍDO    ",
     "      ║    │                                  SALVAMENTO CONCLUÍDO    ",
     "      ║    │                                  SALVAMENTO CONCLUÍDO    ",
     "      ║    │                                  SALVAMENTO CONCLUÍDO    "},
    {"      ║    │                             │       JOGADOR 1      │    ",
     "      ║    │                             │       JOGADOR 1      │    ",
     "      ║    │                             │       JOGADOR 1      │    ",
     "      ║    │                             │       JOGADOR 1      │    "},
    {"      ║    │                         ║\\033[7m        ▶ [1] SIM, ",
     "      ║    │                         ║\\033[7m        ▶ [1] SIM, ",
     "      ║    │                         ║\\033[7m        ▶ [1] SIM, ",
     "      ║    │                         ║\\033[7m        ▶ [1] SIM, "},
    {"║   Projeto prova: jogo da veia                                          "
     "                              ║\\n",
     "║   Projeto prova: jogo da veia                                          "
     "                              ║\\n",
     "║   Projeto prova: jogo da veia                                          "
     "                              ║\\n",
     "║   Projeto prova: jogo da veia                                          "
     "                              ║\\n"},
    {"║                                    Este jogo terminou em EMPATE!       "
     "                           ║\\n",
     "║                                    Este jogo terminou em EMPATE!       "
     "                           ║\\n",
     "║                                    Este jogo terminou em EMPATE!       "
     "                           ║\\n",
     "║                                    Este jogo terminou em EMPATE!       "
     "                           ║\\n"},
    {"║ Pos ║ %-38s ║ %-8s ║ %-8s ║ %-8s ║ %-10s ║\\n",
     "║ Pos ║ %-38s ║ %-8s ║ %-8s ║ %-8s ║ %-10s ║\\n",
     "║ Pos ║ %-38s ║ %-8s ║ %-8s ║ %-8s ║ %-10s ║\\n",
     "║ Pos ║ %-38s ║ %-8s ║ %-8s ║ %-8s ║ %-10s ║\\n"},
    {"│ \\033[7m▶ [%d]  %-40.40s \\033[0m%s│",
     "│ \\033[7m▶ [%d]  %-40.40s \\033[0m%s│",
     "│ \\033[7m▶ [%d]  %-40.40s \\033[0m%s│",
     "│ \\033[7m▶ [%d]  %-40.40s \\033[0m%s│"},
    {"      ║    │  JOGADOR 2                                           │  ",
     "      ║    │  JOGADOR 2                                           │  ",
     "      ║    │  JOGADOR 2                                           │  ",
     "      ║    │  JOGADOR 2                                           │  "},
    {" [%c]  %02d vitórias     │    │%s│%s│%s│      ║\\n",
     " [%c]  %02d vitórias     │    │%s│%s│%s│      ║\\n",
     " [%c]  %02d vitórias     │    │%s│%s│%s│      ║\\n",
     " [%c]  %02d vitórias     │    │%s│%s│%s│      ║\\n"},
    {"      ║    │                              ║ SÍMBOLO: [%c] • ",
     "      ║    │                              ║ SÍMBOLO: [%c] • ",
     "      ║    │                              ║ SÍMBOLO: [%c] • ",
     "      ║    │                              ║ SÍMBOLO: [%c] • "},
    {"      ║    │                              [0] VOLTAR AO MENU ",
     "      ║    │                              [0] VOLTAR AO MENU ",
     "      ║    │                              [0] VOLTAR AO MENU ",
     "      ║    │                              [0] VOLTAR AO MENU "},
    {"%s/%s_%s.txt", "%s/%s_%s.txt", "%s/%s_%s.txt", "%s/%s_%s.txt"},
    {"v%s • EXCLUIR SALVAMENTO", "v%s • EXCLUIR SALVAMENTO",
     "v%s • EXCLUIR SALVAMENTO", "v%s • EXCLUIR SALVAMENTO"},
    {"║    https://plato.stanford.edu/entries/game-theory/                     "
     "                               ║\\n",
     "║    https://plato.stanford.edu/entries/game-theory/                     "
     "                               ║\\n",
     "║    https://plato.stanford.edu/entries/game-theory/                     "
     "                               ║\\n",
     "║    https://plato.stanford.edu/entries/game-theory/                     "
     "                               ║\\n"},
    {"      ║      • Use ↑ ↓ ← → para navegar     • ENTER para jogar     • ",
     "      ║      • Use ↑ ↓ ← → para navegar     • ENTER para jogar     • ",
     "      ║      • Use ↑ ↓ ← → para navegar     • ENTER para jogar     • ",
     "      ║      • Use ↑ ↓ ← → para navegar     • ENTER para jogar     • "},
    {"      ║    │                                      SALVAMENTOS ",
     "      ║    │                                      SALVAMENTOS ",
     "      ║    │                                      SALVAMENTOS ",
     "      ║    │                                      SALVAMENTOS "},
    {"\\n   FIM DO REPLAY. Pressione Enter para voltar.\\n",
     "\\n   FIM DO REPLAY. Pressione Enter para voltar.\\n",
     "\\n   FIM DO REPLAY. Pressione Enter para voltar.\\n",
     "\\n   FIM DO REPLAY. Pressione Enter para voltar.\\n"},
    {"      ║    │                                      NOME DO SALVAMENTO  ",
     "      ║    │                                      NOME DO SALVAMENTO  ",
     "      ║    │                                      NOME DO SALVAMENTO  ",
     "      ║    │                                      NOME DO SALVAMENTO  "},
    {"      ║    │                                      AVISO ",
     "      ║    │                                      AVISO ",
     "      ║    │                                      AVISO ",
     "      ║    │                                      AVISO "},
    {"║──────────────────────────────────────────── v4.0 • FINAL DO ",
     "║──────────────────────────────────────────── v4.0 • FINAL DO ",
     "║──────────────────────────────────────────── v4.0 • FINAL DO ",
     "║──────────────────────────────────────────── v4.0 • FINAL DO "},
    {"mensagem", "mensagem", "mensagem", "mensagem"},
    {"      ║    │      EXEMPLO DE JOGO       │    │                        ",
     "      ║    │      EXEMPLO DE JOGO       │    │                        ",
     "      ║    │      EXEMPLO DE JOGO       │    │                        ",
     "      ║    │      EXEMPLO DE JOGO       │    │                        "},
    {"A IA escolheu jogar com %s", "A IA escolheu jogar com %s",
     "A IA escolheu jogar com %s", "A IA escolheu jogar com %s"},
    {"      ║    │  Escolha uma partida salva para continuar de onde ",
     "      ║    │  Escolha uma partida salva para continuar de onde ",
     "      ║    │  Escolha uma partida salva para continuar de onde ",
     "      ║    │  Escolha uma partida salva para continuar de onde "},
    {"║ - Dois jogadores se revezam utilizando os símbolos X e O.              "
     "                              ║\\n",
     "║ - Dois jogadores se revezam utilizando os símbolos X e O.              "
     "                              ║\\n",
     "║ - Dois jogadores se revezam utilizando os símbolos X e O.              "
     "                              ║\\n",
     "║ - Dois jogadores se revezam utilizando os símbolos X e O.              "
     "                              ║\\n"},
    {"      ║    │                                                  REPLAY ",
     "      ║    │                                                  REPLAY ",
     "      ║    │                                                  REPLAY ",
     "      ║    │                                                  REPLAY "},
    {"v%s • NOVO SALVAMENTO", "v%s • NOVO SALVAMENTO", "v%s • NOVO SALVAMENTO",
     "v%s • NOVO SALVAMENTO"},
    {"║    Observação: O jogo da veia é um exemplo clássico de estratégia "
     "perfeita.                          ║\\n",
     "║    Observação: O jogo da veia é um exemplo clássico de estratégia "
     "perfeita.                          ║\\n",
     "║    Observação: O jogo da veia é um exemplo clássico de estratégia "
     "perfeita.                          ║\\n",
     "║    Observação: O jogo da veia é um exemplo clássico de estratégia "
     "perfeita.                          ║\\n"},
    {"║ Nenhum jogo salvo encontrado.                                          "
     "                              ║\\n",
     "║ Nenhum jogo salvo encontrado.                                          "
     "                              ║\\n",
     "║ Nenhum jogo salvo encontrado.                                          "
     "                              ║\\n",
     "║ Nenhum jogo salvo encontrado.                                          "
     "                              ║\\n"},
    {"      ║    │                               SELECIONAR SALVAMENTO ",
     "      ║    │                               SELECIONAR SALVAMENTO ",
     "      ║    │                               SELECIONAR SALVAMENTO ",
     "      ║    │                               SELECIONAR SALVAMENTO "},
    {"Operação de exclusão cancelada.\\n", "Operação de exclusão cancelada.\\n",
     "Operação de exclusão cancelada.\\n",
     "Operação de exclusão cancelada.\\n"},
    {"      ║    │                         \\033[7m║\\033[0m%s",
     "      ║    │                         \\033[7m║\\033[0m%s",
     "      ║    │                         \\033[7m║\\033[0m%s",
     "      ║    │                         \\033[7m║\\033[0m%s"},
    {"      ║    │      [ BASE DO JOGO ]      │    │                        ",
     "      ║    │      [ BASE DO JOGO ]      │    │                        ",
     "      ║    │      [ BASE DO JOGO ]      │    │                        ",
     "      ║    │      [ BASE DO JOGO ]      │    │                        "},
    {"      ║    │                                     [1] VER REPLAY ",
     "      ║    │                                     [1] VER REPLAY ",
     "      ║    │                                     [1] VER REPLAY ",
     "      ║    │                                     [1] VER REPLAY "},
    {"%02d - %s", "%02d - %s", "%02d - %s", "%02d - %s"},
    {"v%s • JOGO SALVO", "v%s • JOGO SALVO", "v%s • JOGO SALVO",
     "v%s • JOGO SALVO"},
    {"║    https://en.wikipedia.org/wiki/Tic-tac-toe                           "
     "                               ║\\n",
     "║    https://en.wikipedia.org/wiki/Tic-tac-toe                           "
     "                               ║\\n",
     "║    https://en.wikipedia.org/wiki/Tic-tac-toe                           "
     "                               ║\\n",
     "║    https://en.wikipedia.org/wiki/Tic-tac-toe                           "
     "                               ║\\n"},
    {"      ║    │                                      ATENÇÃO             ",
     "      ║    │                                      ATENÇÃO             ",
     "      ║    │                                      ATENÇÃO             ",
     "      ║    │                                      ATENÇÃO             "},
    {"\\033[7m%s\\033[0m%s", "\\033[7m%s\\033[0m%s", "\\033[7m%s\\033[0m%s",
     "\\033[7m%s\\033[0m%s"},
    {"║                                          RANKING DOS JOGADORES         "
     "                              ║\\n",
     "║                                          RANKING DOS JOGADORES         "
     "                              ║\\n",
     "║                                          RANKING DOS JOGADORES         "
     "                              ║\\n",
     "║                                          RANKING DOS JOGADORES         "
     "                              ║\\n"},
    {"Jogo carregado com sucesso de '%s'!\\n",
     "Jogo carregado com sucesso de '%s'!\\n",
     "Jogo carregado com sucesso de '%s'!\\n",
     "Jogo carregado com sucesso de '%s'!\\n"},
    {"      ║    │  Você escolheu criar um novo arquivo de progresso.       ",
     "      ║    │  Você escolheu criar um novo arquivo de progresso.       ",
     "      ║    │  Você escolheu criar um novo arquivo de progresso.       ",
     "      ║    │  Você escolheu criar um novo arquivo de progresso.       "},
    {"      ║    │  O salvamento armazenará o estado atual da partida para ",
     "      ║    │  O salvamento armazenará o estado atual da partida para ",
     "      ║    │  O salvamento armazenará o estado atual da partida para ",
     "      ║    │  O salvamento armazenará o estado atual da partida para "},
    {"      ║    │  Os dados da partida não poderão ser recuperados ",
     "      ║    │  Os dados da partida não poderão ser recuperados ",
     "      ║    │  Os dados da partida não poderão ser recuperados ",
     "      ║    │  Os dados da partida não poderão ser recuperados "},
    {"Jogo salvo com sucesso!\\n", "Jogo salvo com sucesso!\\n",
     "Jogo salvo com sucesso!\\n", "Jogo salvo com sucesso!\\n"},
    {"      ║    │  Você deseja substituir um salvamento já existente ou ",
     "      ║    │  Você deseja substituir um salvamento já existente ou ",
     "      ║    │  Você deseja substituir um salvamento já existente ou ",
     "      ║    │  Você deseja substituir um salvamento já existente ou "},
    {"Selecione qual salvamento sobrescrever (ou 0 para cancelar): ",
     "Selecione qual salvamento sobrescrever (ou 0 para cancelar): ",
     "Selecione qual salvamento sobrescrever (ou 0 para cancelar): ",
     "Selecione qual salvamento sobrescrever (ou 0 para cancelar): "},
    {"Erro ao deletar o arquivo '%s': %s\\n",
     "Erro ao deletar o arquivo '%s': %s\\n",
     "Erro ao deletar o arquivo '%s': %s\\n",
     "Erro ao deletar o arquivo '%s': %s\\n"},
    {"      ║    │                         \\033[7m║  %-46.46s  ║\\033[0m%s  ",
     "      ║    │                         \\033[7m║  %-46.46s  ║\\033[0m%s  ",
     "      ║    │                         \\033[7m║  %-46.46s  ║\\033[0m%s  ",
     "      ║    │                         \\033[7m║  %-46.46s  ║\\033[0m%s  "},
    {"║   Curso: Ciências da Computação                                        "
     "                              ║\\n",
     "║   Curso: Ciências da Computação                                        "
     "                              ║\\n",
     "║   Curso: Ciências da Computação                                        "
     "                              ║\\n",
     "║   Curso: Ciências da Computação                                        "
     "                              ║\\n"},
    {"║  • Livro: \\\"The Compleat Strategyst\\\" - J. D. Williams (Teoria dos "
     "Jogos)                             ║\\n",
     "║  • Livro: \\\"The Compleat Strategyst\\\" - J. D. Williams (Teoria dos "
     "Jogos)                             ║\\n",
     "║  • Livro: \\\"The Compleat Strategyst\\\" - J. D. Williams (Teoria dos "
     "Jogos)                             ║\\n",
     "║  • Livro: \\\"The Compleat Strategyst\\\" - J. D. Williams (Teoria dos "
     "Jogos)                             ║\\n"},
    {"║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Data: "
     "%-21s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Data: "
     "%-21s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Data: "
     "%-21s ║\\n",
     "║ %2d. Nome: %-15s │ X: %-10s (%d) │ O: %-10s (%d) │ Emp: %2d │ Data: "
     "%-21s ║\\n"},
    {"║ %-3d ║ %-38s ║ %-8d ║ %-8d ║ %-8d ║ %-10d ║\\n",
     "║ %-3d ║ %-38s ║ %-8d ║ %-8d ║ %-8d ║ %-10d ║\\n",
     "║ %-3d ║ %-38s ║ %-8d ║ %-8d ║ %-8d ║ %-10d ║\\n",
     "║ %-3d ║ %-38s ║ %-8d ║ %-8d ║ %-8d ║ %-10d ║\\n"},
    {"║                                            REFERÊNCIAS                 "
     "                              ║\\n",
     "║                                            REFERÊNCIAS                 "
     "                              ║\\n",
     "║                                            REFERÊNCIAS                 "
     "                              ║\\n",
     "║                                            REFERÊNCIAS                 "
     "                              ║\\n"},
    {"\\r║%s", "\\r║%s", "\\r║%s", "\\r║%s"},
    {"║ - O objetivo é alinhar 3 símbolos iguais (X ou O).                     "
     "                              ║\\n",
     "║ - O objetivo é alinhar 3 símbolos iguais (X ou O).                     "
     "                              ║\\n",
     "║ - O objetivo é alinhar 3 símbolos iguais (X ou O).                     "
     "                              ║\\n",
     "║ - O objetivo é alinhar 3 símbolos iguais (X ou O).                     "
     "                              ║\\n"},
    {"\\033[7m║\\033[0m%s                                           │    ",
     "\\033[7m║\\033[0m%s                                           │    ",
     "\\033[7m║\\033[0m%s                                           │    ",
     "\\033[7m║\\033[0m%s                                           │    "},
    {"║ Deseja tentar carregar mesmo assim? (1 - Sim, 0 - Não):                "
     "                              ║\\n",
     "║ Deseja tentar carregar mesmo assim? (1 - Sim, 0 - Não):                "
     "                              ║\\n",
     "║ Deseja tentar carregar mesmo assim? (1 - Sim, 0 - Não):                "
     "                              ║\\n",
     "║ Deseja tentar carregar mesmo assim? (1 - Sim, 0 - Não):                "
     "                              ║\\n"},
    {"      ║      [ COMANDOS DA PARTIDA ]                                 ",
     "      ║      [ COMANDOS DA PARTIDA ]                                 ",
     "      ║      [ COMANDOS DA PARTIDA ]                                 ",
     "      ║      [ COMANDOS DA PARTIDA ]                                 "},
    {"v%s • RANKING DOS JOGADORES", "v%s • RANKING DOS JOGADORES",
     "v%s • RANKING DOS JOGADORES", "v%s • RANKING DOS JOGADORES"},
    {"║      - Bloqueie jogadas do adversário.                                 "
     "                              ║\\n",
     "║      - Bloqueie jogadas do adversário.                                 "
     "                              ║\\n",
     "║      - Bloqueie jogadas do adversário.                                 "
     "                              ║\\n",
     "║      - Bloqueie jogadas do adversário.                                 "
     "                              ║\\n"},
    {"      ║    │                                     [0] NÃO, VOLTAR ",
     "      ║    │                                     [0] NÃO, VOLTAR ",
     "      ║    │                                     [0] NÃO, VOLTAR ",
     "      ║    │                                     [0] NÃO, VOLTAR "},
    {"\\033[7m║\\033[0m%s                              │    ║\\n",
     "\\033[7m║\\033[0m%s                              │    ║\\n",
     "\\033[7m║\\033[0m%s                              │    ║\\n",
     "\\033[7m║\\033[0m%s                              │    ║\\n"},
    {"║   Versão 4.0  - Data: 2026                                             "
     "                              ║\\n",
     "║   Versão 4.0  - Data: 2026                                             "
     "                              ║\\n",
     "║   Versão 4.0  - Data: 2026                                             "
     "                              ║\\n",
     "║   Versão 4.0  - Data: 2026                                             "
     "                              ║\\n"},
    {"      ║    │  Sua partida foi armazenada. Você poderá continuar ",
     "      ║    │  Sua partida foi armazenada. Você poderá continuar ",
     "      ║    │  Sua partida foi armazenada. Você poderá continuar ",
     "      ║    │  Sua partida foi armazenada. Você poderá continuar "},
    {"      ║    │        MASCOTE v4.0        │    │                        ",
     "      ║    │        MASCOTE v4.0        │    │                        ",
     "      ║    │        MASCOTE v4.0        │    │                        ",
     "      ║    │        MASCOTE v4.0        │    │                        "},
    {"╚════════════════════════════════════════════════════════════════════════"
     "══════════════════════════════╝\\n\\n",
     "╚════════════════════════════════════════════════════════════════════════"
     "══════════════════════════════╝\\n\\n",
     "╚════════════════════════════════════════════════════════════════════════"
     "══════════════════════════════╝\\n\\n",
     "╚════════════════════════════════════════════════════════════════════════"
     "══════════════════════════════╝\\n\\n"},
    {"║  • GeeksforGeeks - Tic Tac Toe (Lógica e implementação)                "
     "                               ║\\n",
     "║  • GeeksforGeeks - Tic Tac Toe (Lógica e implementação)                "
     "                               ║\\n",
     "║  • GeeksforGeeks - Tic Tac Toe (Lógica e implementação)                "
     "                               ║\\n",
     "║  • GeeksforGeeks - Tic Tac Toe (Lógica e implementação)                "
     "                               ║\\n"},
    {"║    https://www.geeksforgeeks.org/tic-tac-toe-game/                     "
     "                               ║\\n",
     "║    https://www.geeksforgeeks.org/tic-tac-toe-game/                     "
     "                               ║\\n",
     "║    https://www.geeksforgeeks.org/tic-tac-toe-game/                     "
     "                               ║\\n",
     "║    https://www.geeksforgeeks.org/tic-tac-toe-game/                     "
     "                               ║\\n"},
    {"Voltando ao menu de Save/Load...\\n",
     "Voltando ao menu de Save/Load...\\n",
     "Voltando ao menu de Save/Load...\\n",
     "Voltando ao menu de Save/Load...\\n"},
    {"Placar carregado: %s (X): %d | %s (O): %d | Empates: %d\\n",
     "Placar carregado: %s (X): %d | %s (O): %d | Empates: %d\\n",
     "Placar carregado: %s (X): %d | %s (O): %d | Empates: %d\\n",
     "Placar carregado: %s (X): %d | %s (O): %d | Empates: %d\\n"},
    {"      ║    │                         [ NENHUM SALVAMENTO ",
     "      ║    │                         [ NENHUM SALVAMENTO ",
     "      ║    │                         [ NENHUM SALVAMENTO ",
     "      ║    │                         [ NENHUM SALVAMENTO "},
    {"      ║    │                              [2] MÉDIO — ",
     "      ║    │                              [2] MÉDIO — ",
     "      ║    │                              [2] MÉDIO — ",
     "      ║    │                              [2] MÉDIO — "},
    {"║        Obrigado por jogar!                                             "
     "                              ║\\n",
     "║        Obrigado por jogar!                                             "
     "                              ║\\n",
     "║        Obrigado por jogar!                                             "
     "                              ║\\n",
     "║        Obrigado por jogar!                                             "
     "                              ║\\n"},
    {"║   Versão 2.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 2.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 2.0  - Data: 2025                                             "
     "                              ║\\n",
     "║   Versão 2.0  - Data: 2025                                             "
     "                              ║\\n"},
    {"║        Desenvolvido por: Stella Karolina                               "
     "                              ║\\n",
     "║        Desenvolvido por: Stella Karolina                               "
     "                              ║\\n",
     "║        Desenvolvido por: Stella Karolina                               "
     "                              ║\\n",
     "║        Desenvolvido por: Stella Karolina                               "
     "                              ║\\n"},
    {"║ Nenhum dado de ranking disponível. Jogue algumas partidas no 'jogo da "
     "veia' para preencher!           ║\\n",
     "║ Nenhum dado de ranking disponível. Jogue algumas partidas no 'jogo da "
     "veia' para preencher!           ║\\n",
     "║ Nenhum dado de ranking disponível. Jogue algumas partidas no 'jogo da "
     "veia' para preencher!           ║\\n",
     "║ Nenhum dado de ranking disponível. Jogue algumas partidas no 'jogo da "
     "veia' para preencher!           ║\\n"},
    {"      ║    │                         ║\\033[7m      ▶ [0] NÃO, ",
     "      ║    │                         ║\\033[7m      ▶ [0] NÃO, ",
     "      ║    │                         ║\\033[7m      ▶ [0] NÃO, ",
     "      ║    │                         ║\\033[7m      ▶ [0] NÃO, "},
    {"Deseja sobrescrever este arquivo? (1 - Sim, 0 - Novo Salvamento): ",
     "Deseja sobrescrever este arquivo? (1 - Sim, 0 - Novo Salvamento): ",
     "Deseja sobrescrever este arquivo? (1 - Sim, 0 - Novo Salvamento): ",
     "Deseja sobrescrever este arquivo? (1 - Sim, 0 - Novo Salvamento): "},
    {"║ - Pode-se vencer alinhando na horizontal, vertical ou diagonal.        "
     "                              ║\\n",
     "║ - Pode-se vencer alinhando na horizontal, vertical ou diagonal.        "
     "                              ║\\n",
     "║ - Pode-se vencer alinhando na horizontal, vertical ou diagonal.        "
     "                              ║\\n",
     "║ - Pode-se vencer alinhando na horizontal, vertical ou diagonal.        "
     "                              ║\\n"},
    {"║                         ║              PARABÉNS, CAMPEÃO!        ",
     "║                         ║              PARABÉNS, CAMPEÃO!        ",
     "║                         ║              PARABÉNS, CAMPEÃO!        ",
     "║                         ║              PARABÉNS, CAMPEÃO!        "},
    {"      ║    │                                      ATENÇÃO        ",
     "      ║    │                                      ATENÇÃO        ",
     "      ║    │                                      ATENÇÃO        ",
     "      ║    │                                      ATENÇÃO        "},
    {"║                                            Volte sempre!!!!!           "
     "                              ║\\n",
     "║                                            Volte sempre!!!!!           "
     "                              ║\\n",
     "║                                            Volte sempre!!!!!           "
     "                              ║\\n",
     "║                                            Volte sempre!!!!!           "
     "                              ║\\n"},
    {"1º LUGAR  •  %s  •  %d VITÓRIAS", "1º LUGAR  •  %s  •  %d VITÓRIAS",
     "1º LUGAR  •  %s  •  %d VITÓRIAS", "1º LUGAR  •  %s  •  %d VITÓRIAS"},
    {"║ 0. Voltar ao menu                                                      "
     "                              ║\\n",
     "║ 0. Voltar ao menu                                                      "
     "                              ║\\n",
     "║ 0. Voltar ao menu                                                      "
     "                              ║\\n",
     "║ 0. Voltar ao menu                                                      "
     "                              ║\\n"},
    {"      ║      [ CONTROLES DA TELA ]                                    ",
     "      ║      [ CONTROLES DA TELA ]                                    ",
     "      ║      [ CONTROLES DA TELA ]                                    ",
     "      ║      [ CONTROLES DA TELA ]                                    "},
    {"      ║    │                                 [0] CRIAR NOVO ",
     "      ║    │                                 [0] CRIAR NOVO ",
     "      ║    │                                 [0] CRIAR NOVO ",
     "      ║    │                                 [0] CRIAR NOVO "},
    {"      ║    │                    \\033[7m%s\\033[0m%s         ",
     "      ║    │                    \\033[7m%s\\033[0m%s         ",
     "      ║    │                    \\033[7m%s\\033[0m%s         ",
     "      ║    │                    \\033[7m%s\\033[0m%s         "},
    {"║    DICAS DE ESTRATÉGIA:                                                "
     "                            ║\\n",
     "║    DICAS DE ESTRATÉGIA:                                                "
     "                            ║\\n",
     "║    DICAS DE ESTRATÉGIA:                                                "
     "                            ║\\n",
     "║    DICAS DE ESTRATÉGIA:                                                "
     "                            ║\\n"},
    {"A IA (%s) jogou na posição %d.", "A IA (%s) jogou na posição %d.",
     "A IA (%s) jogou na posição %d.", "A IA (%s) jogou na posição %d."},
    {"      ║    │  FÁCIL: a IA faz movimentos aleatórios e é ideal ",
     "      ║    │  FÁCIL: a IA faz movimentos aleatórios e é ideal ",
     "      ║    │  FÁCIL: a IA faz movimentos aleatórios e é ideal ",
     "      ║    │  FÁCIL: a IA faz movimentos aleatórios e é ideal "},
    {"Retornando ao menu principal...\\n", "Retornando ao menu principal...\\n",
     "Retornando ao menu principal...\\n",
     "Retornando ao menu principal...\\n"},
    {"\\033[7m║\\033[0m%s                                       │    ║\\n",
     "\\033[7m║\\033[0m%s                                       │    ║\\n",
     "\\033[7m║\\033[0m%s                                       │    ║\\n",
     "\\033[7m║\\033[0m%s                                       │    ║\\n"},
    {"v%s • SALVAR / CARREGAR JOGO", "v%s • SALVAR / CARREGAR JOGO",
     "v%s • SALVAR / CARREGAR JOGO", "v%s • SALVAR / CARREGAR JOGO"},
    {"      ║    │                              ║              O JOGO ",
     "      ║    │                              ║              O JOGO ",
     "      ║    │                              ║              O JOGO ",
     "      ║    │                              ║              O JOGO "},
    {"      ║    │                              \\033[7m║\\033[0m%s",
     "      ║    │                              \\033[7m║\\033[0m%s",
     "      ║    │                              \\033[7m║\\033[0m%s",
     "      ║    │                              \\033[7m║\\033[0m%s"},
    {"      ║    │                                 [1] SOBRESCREVER ",
     "      ║    │                                 [1] SOBRESCREVER ",
     "      ║    │                                 [1] SOBRESCREVER ",
     "      ║    │                                 [1] SOBRESCREVER "},
    {"      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ",
     "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • "},
    {"      ║    │                         │   [%d]  %-40.40s │  ",
     "      ║    │                         │   [%d]  %-40.40s │  ",
     "      ║    │                         │   [%d]  %-40.40s │  ",
     "      ║    │                         │   [%d]  %-40.40s │  "},
    {"      ║    │  DIFÍCIL: a IA usa a melhor estratégia possível e ",
     "      ║    │  DIFÍCIL: a IA usa a melhor estratégia possível e ",
     "      ║    │  DIFÍCIL: a IA usa a melhor estratégia possível e ",
     "      ║    │  DIFÍCIL: a IA usa a melhor estratégia possível e "},
    {"      ║    │  Use esta tela para salvar a partida atual, continuar um ",
     "      ║    │  Use esta tela para salvar a partida atual, continuar um ",
     "      ║    │  Use esta tela para salvar a partida atual, continuar um ",
     "      ║    │  Use esta tela para salvar a partida atual, continuar um "},
    {"Último Vencedor: %s\\n", "Último Vencedor: %s\\n",
     "Último Vencedor: %s\\n", "Último Vencedor: %s\\n"},
    {"      ║    │                         \\033[7m║\\033[0m%s       ",
     "      ║    │                         \\033[7m║\\033[0m%s       ",
     "      ║    │                         \\033[7m║\\033[0m%s       ",
     "      ║    │                         \\033[7m║\\033[0m%s       "},
    {"║                                       SALVAR / CARREGAR JOGO           "
     "                              ║\\n",
     "║                                       SALVAR / CARREGAR JOGO           "
     "                              ║\\n",
     "║                                       SALVAR / CARREGAR JOGO           "
     "                              ║\\n",
     "║                                       SALVAR / CARREGAR JOGO           "
     "                              ║\\n"},
    {"      ║    │                                  SOBRE A ",
     "      ║    │                                  SOBRE A ",
     "      ║    │                                  SOBRE A ",
     "      ║    │                                  SOBRE A "},
    {"║                         ║  CAMPEÃO DO TORNEIO: %-29.29s ║        ",
     "║                         ║  CAMPEÃO DO TORNEIO: %-29.29s ║        ",
     "║                         ║  CAMPEÃO DO TORNEIO: %-29.29s ║        ",
     "║                         ║  CAMPEÃO DO TORNEIO: %-29.29s ║        "},
    {"      ║    │                                      AVISO IMPORTANTE    ",
     "      ║    │                                      AVISO IMPORTANTE    ",
     "      ║    │                                      AVISO IMPORTANTE    ",
     "      ║    │                                      AVISO IMPORTANTE    "},
    {"v%s • ESCOLHA O MODO DE JOGO", "v%s • ESCOLHA O MODO DE JOGO",
     "v%s • ESCOLHA O MODO DE JOGO", "v%s • ESCOLHA O MODO DE JOGO"},
    {"║      - Comece pelo centro ou pelos cantos.                             "
     "                              ║\\n",
     "║      - Comece pelo centro ou pelos cantos.                             "
     "                              ║\\n",
     "║      - Comece pelo centro ou pelos cantos.                             "
     "                              ║\\n",
     "║      - Comece pelo centro ou pelos cantos.                             "
     "                              ║\\n"},
    {"║ Pressione Enter para voltar ao menu...                                 "
     "                              ║\\n",
     "║ Pressione Enter para voltar ao menu...                                 "
     "                              ║\\n",
     "║ Pressione Enter para voltar ao menu...                                 "
     "                              ║\\n",
     "║ Pressione Enter para voltar ao menu...                                 "
     "                              ║\\n"},
    {"Jogo não salvo. Retornando ao menu principal...\\n",
     "Jogo não salvo. Retornando ao menu principal...\\n",
     "Jogo não salvo. Retornando ao menu principal...\\n",
     "Jogo não salvo. Retornando ao menu principal...\\n"},
    {"      ║    │  Escolha o nível de desafio da Inteligência ",
     "      ║    │  Escolha o nível de desafio da Inteligência ",
     "      ║    │  Escolha o nível de desafio da Inteligência ",
     "      ║    │  Escolha o nível de desafio da Inteligência "},
    {"v%s • CONFIGURAR PARTIDA", "v%s • CONFIGURAR PARTIDA",
     "v%s • CONFIGURAR PARTIDA", "v%s • CONFIGURAR PARTIDA"},
    {"║                                       DESEJA SALVAR O JOGO?            "
     "                                ║\\n",
     "║                                       DESEJA SALVAR O JOGO?            "
     "                                ║\\n",
     "║                                       DESEJA SALVAR O JOGO?            "
     "                                ║\\n",
     "║                                       DESEJA SALVAR O JOGO?            "
     "                                ║\\n"},
    {"      ║    │                                              DESEJA ",
     "      ║    │                                              DESEJA ",
     "      ║    │                                              DESEJA ",
     "      ║    │                                              DESEJA "},
    {"      ║    │       [ IDENTIDADE ]       │    │                        ",
     "      ║    │       [ IDENTIDADE ]       │    │                        ",
     "      ║    │       [ IDENTIDADE ]       │    │                        ",
     "      ║    │       [ IDENTIDADE ]       │    │                        "},
    {"      ║    │                         \\033[7m║\\033[0m%s             ",
     "      ║    │                         \\033[7m║\\033[0m%s             ",
     "      ║    │                         \\033[7m║\\033[0m%s             ",
     "      ║    │                         \\033[7m║\\033[0m%s             "},
    {"      ║    │                         %-83s│    ║\\n",
     "      ║    │                         %-83s│    ║\\n",
     "      ║    │                         %-83s│    ║\\n",
     "      ║    │                         %-83s│    ║\\n"},
    {"Deseja escolher um salvamento da lista para sobrescrever? (1 - Sim, 0 - "
     "Criar Novo): ",
     "Deseja escolher um salvamento da lista para sobrescrever? (1 - Sim, 0 - "
     "Criar Novo): ",
     "Deseja escolher um salvamento da lista para sobrescrever? (1 - Sim, 0 - "
     "Criar Novo): ",
     "Deseja escolher um salvamento da lista para sobrescrever? (1 - Sim, 0 - "
     "Criar Novo): "},
    {"      ║    │                         ║          NENHUM JOGADOR ",
     "      ║    │                         ║          NENHUM JOGADOR ",
     "      ║    │                         ║          NENHUM JOGADOR ",
     "      ║    │                         ║          NENHUM JOGADOR "},
    {"Nome do salvamento não pode ser vazio. Cancelando salvamento.\\n",
     "Nome do salvamento não pode ser vazio. Cancelando salvamento.\\n",
     "Nome do salvamento não pode ser vazio. Cancelando salvamento.\\n",
     "Nome do salvamento não pode ser vazio. Cancelando salvamento.\\n"},
    {"      ║    │  Escolha um salvamento da lista para substituir ",
     "      ║    │  Escolha um salvamento da lista para substituir ",
     "      ║    │  Escolha um salvamento da lista para substituir ",
     "      ║    │  Escolha um salvamento da lista para substituir "},
    {"      ║    │                                   CRIAR NOVO SALVAMENTO  ",
     "      ║    │                                   CRIAR NOVO SALVAMENTO  ",
     "      ║    │                                   CRIAR NOVO SALVAMENTO  ",
     "      ║    │                                   CRIAR NOVO SALVAMENTO  "},
    {"║                         Pressione ENTER para continuar...        ",
     "║                         Pressione ENTER para continuar...        ",
     "║                         Pressione ENTER para continuar...        ",
     "║                         Pressione ENTER para continuar...        "},
    {"║                    ✦ Muito bem! Continue jogando para ",
     "║                    ✦ Muito bem! Continue jogando para ",
     "║                    ✦ Muito bem! Continue jogando para ",
     "║                    ✦ Muito bem! Continue jogando para "},
    {"      ║    │  Ao deletar um jogo salvo, o progresso armazenado será ",
     "      ║    │  Ao deletar um jogo salvo, o progresso armazenado será ",
     "      ║    │  Ao deletar um jogo salvo, o progresso armazenado será ",
     "      ║    │  Ao deletar um jogo salvo, o progresso armazenado será "},
    {"║                                       CARREGAR JOGO SALVO              "
     "                              ║\\n",
     "║                                       CARREGAR JOGO SALVO              "
     "                              ║\\n",
     "║                                       CARREGAR JOGO SALVO              "
     "                              ║\\n",
     "║                                       CARREGAR JOGO SALVO              "
     "                              ║\\n"},
    {"      ║    │  Ao sobrescrever um arquivo, os dados antigos daquele ",
     "      ║    │  Ao sobrescrever um arquivo, os dados antigos daquele ",
     "      ║    │  Ao sobrescrever um arquivo, os dados antigos daquele ",
     "      ║    │  Ao sobrescrever um arquivo, os dados antigos daquele "},
    {"      ║    │                    ║      %s (%d)  vs  %s ",
     "      ║    │                    ║      %s (%d)  vs  %s ",
     "      ║    │                    ║      %s (%d)  vs  %s ",
     "      ║    │                    ║      %s (%d)  vs  %s "},
    {"║  • Stanford University - Estratégias de jogos (Game Theory)            "
     "                               ║\\n",
     "║  • Stanford University - Estratégias de jogos (Game Theory)            "
     "                               ║\\n",
     "║  • Stanford University - Estratégias de jogos (Game Theory)            "
     "                               ║\\n",
     "║  • Stanford University - Estratégias de jogos (Game Theory)            "
     "                               ║\\n"},
    {"OBRIGADA POR JOGAR!", "OBRIGADA POR JOGAR!", "THANK YOU FOR PLAYING!", "¡GRACIAS POR JUGAR!"},
    {"ATÉ A PRÓXIMA PARTIDA!", "ATÉ A PRÓXIMA PARTIDA!", "SEE YOU NEXT GAME!", "¡HASTA LA PRÓXIMA PARTIDA!"},
    {"  Obrigada por jogar o Jogo da Veia e fazer parte desta experiência.", "  Obrigada por jogar o Jogo da Veia e fazer parte desta experiência.", "  Thank you for playing Jogo da Veia and being part of this experience.", "  Gracias por jugar al Jogo da Veia y ser parte de esta experiencia."},
    {"  Volte sempre para testar novas estratégias, desafios e jogadas incríveis.", "  Volte sempre para testar novas estratégias, desafios e jogadas incríveis.", "  Come back anytime to test new strategies, challenges, and incredible moves.", "  Vuelve siempre para probar nuevas estrategias, desafíos y jugadas increíbles."},
    {"MENSAGEM FINAL", "MENSAGEM FINAL", "FINAL MESSAGE", "MENSAJE FINAL"},
    {"✦ Toda grande estratégia começa com a primeira jogada. ✦", "✦ Toda grande estratégia começa com a primeira jogada. ✦", "✦ Every great strategy begins with the first move. ✦", "✦ Toda gran estrategia comienza con la primera jugada. ✦"},
    {"DESENVOLVIMENTO", "DESENVOLVIMENTO", "DEVELOPMENT", "DESARROLLO"},
    {"Desenvolvedora: Stella Karolina Nunes Peixoto", "Desenvolvedora: Stella Karolina Nunes Peixoto", "Developer: Stella Karolina Nunes Peixoto", "Desarrolladora: Stella Karolina Nunes Peixoto"},
    {"Projeto acadêmico • Ciência da Computação •", "Projeto acadêmico • Ciência da Computação •", "Academic Project • Computer Science •", "Proyecto académico • Ciencias de la Computación •"},
    {"Pressione ENTER para encerrar o jogo...", "Pressione ENTER para encerrar o jogo...", "Press ENTER to close the game...", "Presiona ENTER para cerrar el juego..."},
    {"✦ Pense bem. Uma jogada pode decidir tudo. Controle o centro e vença. ✦",
     "✦ Pense bem. Uma jogada pode decidir tudo. Controle o centro e vença. ✦",
     "✦ Think well. One move can decide everything. Control the center and win. ✦",
     "✦ Piensa bien. Una jugada puede decidir todo. Controla el centro y gana. ✦"},
    {"MENU PRINCIPAL", "MENU PRINCIPAL", "MAIN MENU", "MENÚ PRINCIPAL"},
    {"MASCOTE v4.0", "MASCOTE v4.0", "MASCOT v4.0", "MASCOTA v4.0"},
    {"CARREGAR SALVAMENTO", "CARREGAR SALVAMENTO", "LOAD SAVE", "CARGAR PARTIDA"},
    {"CONFIGURAR PARTIDA", "CONFIGURAR PARTIDA", "CONFIGURE MATCH", "CONFIGURAR PARTIDA"},
    {"CONFIGURAÇÃO DE JOGADORES", "CONFIGURAÇÃO DE JOGADORES", "PLAYER CONFIGURATION", "CONFIGURACIÓN DE JUGADORES"},
    {"CONFIRMAÇÃO DE JOGADORES", "CONFIRMAÇÃO DE JOGADORES", "PLAYER CONFIRMATION", "CONFIRMACIÓN DE JUGADORES"},
    {"ESCOLHA O MODO DE JOGO", "ESCOLHA O MODO DE JOGO", "CHOOSE GAME MODE", "ELIGE EL MODO DE JUEGO"},
    {"EXCLUIR SALVAMENTO", "EXCLUIR SALVAMENTO", "DELETE SAVE", "ELIMINAR PARTIDA"},
    {"IDIOMA", "IDIOMA", "LANGUAGE", "IDIOMA"},
    {"JOGO DA VEIA EM ANDAMENTO", "JOGO DA VEIA EM ANDAMENTO", "TIC TAC TOE IN PROGRESS", "TRES EN RAYA EN CURSO"},
    {"JOGO SALVO", "JOGO SALVO", "GAME SAVED", "JUEGO GUARDADO"},
    {"NOVO SALVAMENTO", "NOVO SALVAMENTO", "NEW SAVE", "NUEVA PARTIDA"},
    {"RANKING DOS JOGADORES", "RANKING DOS JOGADORES", "PLAYER RANKING", "RANKING DE JUGADORES"},
    {"SALVAR / CARREGAR JOGO", "SALVAR / CARREGAR JOGO", "SAVE / LOAD GAME", "GUARDAR / CARGAR JUEGO"},
    {"SALVAR PARTIDA ATUAL", "SALVAR PARTIDA ATUAL", "SAVE CURRENT MATCH", "GUARDAR PARTIDA ACTUAL"},
    {"alternando entre X e O.", "alternando entre X e O.", "alternating between X and O.", "alternando entre X y O."},
    {"                              Pressione ENTER para continuar...", "                              Pressione ENTER para continuar...", "                              Press ENTER to continue...", "                              Presiona ENTER para continuar..."},
    {"   JOGADOR VS JOGADOR: desafie outra pessoa no mesmo computador, ", "   JOGADOR VS JOGADOR: desafie outra pessoa no mesmo computador, ", "   PLAYER VS PLAYER: challenge another person on the same computer, ", "   JUGADOR VS JUGADOR: desafía a otra persona en la misma computadora, "},
    {"  Continue jogando para subir de posição e conquistar mais medalhas.", "  Continue jogando para subir de posição e conquistar mais medalhas.", "  Keep playing to climb the ranks and earn more medals.", "  Sigue jugando para subir de posición y ganar más medallas."},
    {"SORTEIO DO PRIMEIRO JOGADOR", "SORTEIO DO PRIMEIRO JOGADOR", "FIRST PLAYER DRAW", "SORTEO DEL PRIMER JUGADOR"},
    {"      [ SELEÇÃO DE TEMA ]", "      [ SELEÇÃO DE TEMA ]", "      [ THEME SELECTION ]", "      [ SELECCIÓN DE TEMA ]"},
    {"      • Pressione ENTER, ESC ou Q para retornar ao Menu Principal", "      • Pressione ENTER, ESC ou Q para retornar ao Menu Principal", "      • Press ENTER, ESC or Q to return to Main Menu", "      • Presiona ENTER, ESC o Q para volver al Menú Principal"},
    {"      [ CONTROLES DO MENU ]", "      [ CONTROLES DO MENU ]", "      [ MENU CONTROLS ]", "      [ CONTROLES DEL MENÚ ]"},
    {"SOBRESCREVER SALVAMENTO", "SOBRESCREVER SALVAMENTO", "OVERWRITE SAVE", "SOBREESCRIBIR GUARDADO"},
    {"DESTAQUE DO RANKING", "DESTAQUE DO RANKING", "RANKING HIGHLIGHT", "DESTACADO DEL RANKING"},
    {"Use ↑ ↓ ← → para navegar entre os temas. Pressione ENTER para aplicar.", "Use ↑ ↓ ← → para navegar entre os temas. Pressione ENTER para aplicar.", "Use ↑ ↓ ← → to navigate between themes. Press ENTER to apply.", "Usa ↑ ↓ ← → para navegar entre los temas. Presiona ENTER para aplicar."}
};

void init_i18n(void) {
  // Ensure current language is within valid range; default to Portuguese if not
  // set correctly
  if (current_language < LANG_PT || current_language > LANG_ES) {
    current_language = LANG_PT;
  }
  // Configurações podem ser salvas, mas o padrão é PT
}

// stray init block removed

const char *_(const char *text) {
  int num_translations = sizeof(dict) / sizeof(dict[0]);
  for (int i = 0; i < num_translations; i++) {
    if (strcmp(dict[i].key, text) == 0) {
      switch (current_language) {
      case LANG_PT:
        return dict[i].pt;
      case LANG_EN:
        return dict[i].en;
      case LANG_ES:
        return dict[i].es;
      default:
        return dict[i].pt;
      }
    }
  }
  return text; // Fallback
}

void change_language(void) {
  int preview_lang = current_language;
  KeyCode tecla;

  do {
    limparTela();
    aplicarTema(tema_ativo);

    for (int i = 0; i < 5; i++)
      printf("\n");

    printf("      "
           "╔══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╗\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");

    const char *art[] = {" ___ ___ _    ___ ___  _   ___       ___ ___   ___ "
                         "___  __  __   _   ___ ",
                         "/ __| __| |  | __/ __| /_\\ / _ \\     |   \\_ _| |  "
                         " \\_ _|/ _ \\|  \\/  | /_\\ / __|",
                         "\\__ \\ _|| |__| _| (__ / _ \\ (_) |    | |) | |  | "
                         "|) | || (_) | |\\/| |/ _ \\\\__ \\",
                         "|___/___|____|___\\___/_/ \\_\\___/     |___/___| "
                         "|___/___|\\___/|_|  |_/_/ \\_\\___/"};

    for (int i = 0; i < 4; i++) {
      int len = visible_strlen(art[i]);
      int p_left = (126 - len) / 2;
      int p_right = 126 - len - p_left;
      printf("      ║");
      for (int j = 0; j < p_left; j++)
        printf(" ");
      printf("%s", art[i]);
      for (int j = 0; j < p_right; j++)
        printf(" ");
      printf("║\n");
    }

    printf(
        "      ║                                                               "
        "                                                               ║\n");

    char header_info[200];
    snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
             _("PERSONALIZAÇÃO DO JOGO"));
    int info_len = visible_strlen(header_info);
    int pad_left = (126 - info_len - 2) / 2;
    int pad_right = 126 - info_len - 2 - pad_left;
    printf("      ║");
    for (int i = 0; i < pad_left; i++)
      printf("─");
    printf(" %s ", header_info);
    for (int i = 0; i < pad_right; i++)
      printf("─");
    printf("║\n");

    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║    "
           "┌──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┐    ║\n");

    const char *title1 = _("SELEÇÃO DE IDIOMA");
    int p_t1 = (116 - visible_strlen(title1)) / 2;
    printf("      ║    │");
    for (int i = 0; i < p_t1; i++)
      printf(" ");
    printf("%s", title1);
    for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
      printf(" ");
    printf("│    ║\n");

    printf("      ║    "
           "├──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┤    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    const char *desc1 = _("  Escolha o idioma que será utilizado nas telas, "
                          "menus e mensagens do jogo.");
    printf("      ║    │%s", desc1);
    for (int i = 0; i < 116 - visible_strlen(desc1); i++)
      printf(" ");
    printf("│    ║\n");

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");

    const char *t2 = _("IDIOMAS DISPONÍVEIS");
    int p_t2 = (116 - visible_strlen(t2)) / 2;
    printf("      ║    │");
    for (int i = 0; i < p_t2; i++)
      printf(" ");
    printf("%s", t2);
    for (int i = 0; i < 116 - visible_strlen(t2) - p_t2; i++)
      printf(" ");
    printf("│    ║\n");

    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    const char *opts[] = {"[1] PORTUGUÊS", "[2] ENGLISH", "[3] ESPAÑOL",
                          "[0] VOLTAR AO MENU PRINCIPAL"};

    for (int i = 0; i < 4; i++) {
      if (preview_lang == i || (i == 3 && preview_lang == 3)) {
        char formatado[100];
        snprintf(formatado, sizeof(formatado), "▶ %s ◀", _(opts[i]));
        int p_opt = 9;

        printf(
            "      ║    │                         "
            "\033[7m╔══════════════════════════════════════════════════╗\033["
            "0m%s                                       │    ║\n",
            temas[tema_ativo]);

        printf("      ║    │                         \033[7m║\033[0m%s",
               temas[tema_ativo]);
        for (int j = 0; j < p_opt; j++)
          printf(" ");
        printf("\033[7m%s\033[0m%s", formatado, temas[tema_ativo]);
        for (int j = 0; j < 50 - visible_strlen(formatado) - p_opt; j++)
          printf(" ");
        printf(
            "\033[7m║\033[0m%s                                       │    ║\n",
            temas[tema_ativo]);

        printf(
            "      ║    │                         "
            "\033[7m╚══════════════════════════════════════════════════╝\033["
            "0m%s                                       │    ║\n",
            temas[tema_ativo]);
      } else {
        int p_opt = 11;
        printf("      ║    │                         ");
        printf(" ");
        for (int j = 0; j < p_opt; j++)
          printf(" ");
        printf("%s", _(opts[i]));
        for (int j = 0; j < 50 - visible_strlen(_(opts[i])) - p_opt; j++)
          printf(" ");
        printf(" ");
        printf("                                       │    ║\n");
      }

      if (i < 3) {
        printf("      ║    │                                                   "
               "                                                               "
               "  │    ║\n");
      }
    }

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");

    const char *t3 = _("IDIOMA ATUAL");
    int p_t3 = (116 - visible_strlen(t3)) / 2;
    printf("      ║    │");
    for (int i = 0; i < p_t3; i++)
      printf(" ");
    printf("%s", t3);
    for (int i = 0; i < 116 - visible_strlen(t3) - p_t3; i++)
      printf(" ");
    printf("│    ║\n");

    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    const char *cur_lang_str = "";
    if (current_language == LANG_PT)
      cur_lang_str = "Português — Brasil";
    else if (current_language == LANG_EN)
      cur_lang_str = "English — US";
    else if (current_language == LANG_ES)
      cur_lang_str = "Español — España";

    int p_cur = (116 - visible_strlen(cur_lang_str)) / 2;
    printf("      ║    │");
    for (int i = 0; i < p_cur; i++)
      printf(" ");
    printf("%s", cur_lang_str);
    for (int i = 0; i < 116 - visible_strlen(cur_lang_str) - p_cur; i++)
      printf(" ");
    printf("│    ║\n");

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "└──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┘    ║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      "
           "╠══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╣\n");

    const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
    printf("      ║%s", ctrl1);
    for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
      printf(" ");
    printf("║\n");

    const char *ctrl2 =
        _("      • Use ↑ ↓ para navegar     • ENTER para aplicar     • 0, Q ou "
          "ESC para voltar ao Menu Principal");
    printf("      ║%s", ctrl2);
    for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
      printf(" ");
    printf("║\n");

    printf("      "
           "╚══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╝\n");

    tecla = lerTeclaMenu();

    switch (tecla) {
    case KEY_UP:
      preview_lang--;
      if (preview_lang < 0)
        preview_lang = 3;
      break;
    case KEY_DOWN:
      preview_lang++;
      if (preview_lang > 3)
        preview_lang = 0;
      break;
    case KEY_ENTER:
      if (preview_lang == 3)
        return;
      current_language = preview_lang;
      return;
    case KEY_ESC:
    case KEY_Q:
    case KEY_0:
      return;
    default:
      break;
    }
  } while (1);
}
int current_language = 0;
