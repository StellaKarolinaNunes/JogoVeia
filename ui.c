#include "ui.h"
#include "file_manager.h"
#include "i18n.h"
#include "theme.h"
#include "utils.h"

void exibirTelaEscolherModoJogo(int selected) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      "__  __  ___  ___   ___     ___  ___       _  ___   ___  ___   ",
      "|  \\/  |/ _ \\|   \\ / _ \\   |   \\| __|     | |/ _ \\ / __|/ _ \\ ",
      "| |\\/| | (_) | |) | (_) |  | |) | _|   _  | | (_) | (_ | (_) |",
      "|_|  |_|\\___/|___/ \\___/   |___/|___| (_)|_|\\___/ \\___|\\___/ "};

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

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("ESCOLHA O MODO DE JOGO"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("MODO DE JOGO");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 = "  Escolha como deseja jogar. Cada modo possui uma "
                      "experiência diferente para desafiar sua estratégia.";
  printf("      ║    │%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *opts[] = {"[1] JOGADOR VS JOGADOR", "[2] JOGADOR VS IA",
                        "[3] MODO INFINITO", "[0] VOLTAR AO MENU PRINCIPAL"};

  for (int i = 0; i < 4; i++) {
    if (selected == i) {
      char formatado[100];
      int p_opt =
          9; // align all selected items so their `[` starts at column 11

      // Box is 52 chars wide (╔ + 50═ + ╗).
      // We want 25 spaces before, and 39 spaces after. 25 + 52 + 39 = 116.
      printf("      ║    │                         "
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
      printf("\033[7m║\033[0m%s                                       │    ║\n",
             temas[tema_ativo]);

      printf("      ║    │                         "
             "\033[7m╚══════════════════════════════════════════════════╝\033["
             "0m%s                                       │    ║\n",
             temas[tema_ativo]);
    } else {
      int p_opt = 11; // fix the `[` to column 11
      printf("      ║    │                         "); // 25 spaces
      printf(" ");                                     // border space (1)
      for (int j = 0; j < p_opt; j++)
        printf(" ");
      printf("%s", _(opts[i]));
      for (int j = 0; j < 50 - visible_strlen(_(opts[i])) - p_opt; j++)
        printf(" ");
      printf(" "); // border space (1)
      printf("                                       │    ║\n"); // 39 spaces
    }

    if (i < 3) {
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *t2 = _("SOBRE O MODO SELECIONADO");
  int p_t2 = (116 - visible_strlen(t2)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t2; i++)
    printf(" ");
  printf("%s", t2);
  for (int i = 0; i < 116 - visible_strlen(t2) - p_t2; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc_lines[] = {
      "  JOGADOR VS JOGADOR: desafie outra pessoa no mesmo computador, "
      "alternando entre X e O.",
      "",
      "  JOGADOR VS IA: enfrente o computador e teste suas melhores "
      "estratégias.",
      "",
      "  MODO INFINITO: cada jogador pode manter apenas 3 peças no tabuleiro.",
      "  Ao colocar a 4ª peça, a mais antiga desaparece automaticamente."};

  for (int i = 0; i < 6; i++) {
    printf("      ║    │%s", _(desc_lines[i]));
    for (int j = 0; j < 116 - visible_strlen(_(desc_lines[i])); j++)
      printf(" ");
    printf("│    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 =
      "      • Use ↑ ↓ para navegar     • ENTER para selecionar     • 0, Q ou "
      "ESC para voltar ao Menu Principal";
  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaEscolherTipoPartida(int selected) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      " _____ ___ ___   ___    ___ ___   ___ _____ ___ ___   _     ",
      "|_   _|_ _| _ \\ / _ \\  |   \\ __| | _ \\ _  _|_ _|   \\ /_\\    ",
      "  | |  | ||  _/| (_) | | |) | _|  |  _/  ||  | || | | / _ \\ ",
      "  |_| |___|_|   \\___/  |___/___| |_|   |_|___|___/_/ \\_\\    "};

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

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("CONFIGURAR PARTIDA"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("TIPO DE PARTIDA");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 =
      _("  Escolha como será definida a vitória antes de iniciar o jogo.");
  printf("      ║    │%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *opts[] = {
      "[0] PARTIDA ÚNICA — PADRÃO", "[1] MELHOR DE 3 — TORNEIO",
      "[2] MELHOR DE 5 — TORNEIO", "[Q] VOLTAR AO MENU PRINCIPAL"};

  for (int i = 0; i < 4; i++) {
    if (selected == i) {
      char formatado[100];
      snprintf(formatado, sizeof(formatado), "▶ %s ◀", _(opts[i]));
      int p_opt = 9; // Fix string offset for '[' to be at col 11

      printf("      ║    │                         "
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
      printf("\033[7m║\033[0m%s                                       │    ║\n",
             temas[tema_ativo]);

      printf("      ║    │                         "
             "\033[7m╚══════════════════════════════════════════════════╝\033["
             "0m%s                                       │    ║\n",
             temas[tema_ativo]);
    } else {
      int p_opt = 11;
      printf("      ║    │                         "); // 25 spaces
      printf(" ");                                     // border space (1)
      for (int j = 0; j < p_opt; j++)
        printf(" ");
      printf("%s", _(opts[i]));
      for (int j = 0; j < 50 - visible_strlen(_(opts[i])) - p_opt; j++)
        printf(" ");
      printf(" "); // border space (1)
      printf("                                       │    ║\n"); // 39 spaces
    }

    if (i < 3) {
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *t2 = _("SOBRE O MODO SELECIONADO");
  int p_t2 = (116 - visible_strlen(t2)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t2; i++)
    printf(" ");
  printf("%s", t2);
  for (int i = 0; i < 116 - visible_strlen(t2) - p_t2; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc_lines[] = {
      "  PARTIDA ÚNICA: uma vitória define o vencedor da partida.", "",
      "  MELHOR DE 3: vence quem conquistar 2 vitórias primeiro.",  "",
      "  MELHOR DE 5: vence quem conquistar 3 vitórias primeiro.",  ""};

  for (int i = 0; i < 6; i++) {
    printf("      ║    │%s", _(desc_lines[i]));
    for (int j = 0; j < 116 - visible_strlen(_(desc_lines[i])); j++)
      printf(" ");
    printf("│    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 = "      • Use ↑ ↓ para navegar     • ENTER para "
                      "selecionar     • Q ou ESC para voltar ao Menu Principal";
  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaConfigurarJogadores(int jogadorNum) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      " ___ ___  _  _ ___ ___ ___ _   ___   ___ ___  ___ ___ ",
      "/ __/ _ \\| \\| | |_ _/ __| | | | _ \\ / _ \\ _ \\| __/ __|",
      "| (_| (_) | .` |  | | (_ | |_| |   /|  __/   /| _|\\__ \\",
      " \\___\\___/|_|\\_| |___\\___|\\___/|_|_\\ \\___|_|_\\|___|___/"};

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

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("CONFIGURAÇÃO DE JOGADORES"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("CONFIGURAR JOGADORES");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 =
      _("  Informe os nomes dos participantes para iniciar a partida.");
  const char *desc2 = "  O Jogador 1 utilizará o símbolo X e o Jogador 2 "
                      "utilizará o símbolo O.";
  printf("      ║    │%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1); i++)
    printf(" ");
  printf("│    ║\n");
  printf("      ║    │%s", desc2);
  for (int i = 0; i < 116 - visible_strlen(desc2); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  char sub_title[100];
  if (jogadorNum == 1)
    strcpy(sub_title, "JOGADOR 1 — SÍMBOLO X");
  else
    strcpy(sub_title, "JOGADOR 2 — SÍMBOLO O");

  int p_st = (116 - visible_strlen(sub_title)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_st; i++)
    printf(" ");
  printf("%s", sub_title);
  for (int i = 0; i < 116 - visible_strlen(sub_title) - p_st; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    │                         "
         "\033[7m╔══════════════════════════════════════════════════╗\033[0m%s "
         "                                      │    ║\n",
         temas[tema_ativo]);
  char prompt[100];
  snprintf(prompt, sizeof(prompt), "DIGITE O NOME DO JOGADOR %d: ", jogadorNum);
  printf("      ║    │                         \033[7m║  %-46.46s  ║\033[0m%s  "
         "                                     │    ║\n",
         prompt, temas[tema_ativo]);
  printf("      ║    │                         \033[7m║                        "
         "                          ║\033[0m%s                                 "
         "      │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                         "
         "\033[7m╚══════════════════════════════════════════════════╝\033[0m%s "
         "                                      │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *next_t = _("PRÓXIMA ETAPA");
  int p_nt = (116 - visible_strlen(next_t)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_nt; i++)
    printf(" ");
  printf("%s", next_t);
  for (int i = 0; i < 116 - visible_strlen(next_t) - p_nt; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *next_d = (jogadorNum == 1)
                           ? "  Após confirmar o nome do Jogador 1, será "
                             "solicitado o nome do Jogador 2."
                           : "  Após confirmar o nome do Jogador 2, você "
                             "revisará as informações.";
  printf("      ║    │%s", next_d);
  for (int i = 0; i < 116 - visible_strlen(next_d); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 = "      • Digite o nome e pressione ENTER para confirmar  "
                      "   • ESC para cancelar";
  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");

  // Positioning the cursor right after "DIGITE O NOME DO JOGADOR X: "
  // The prompt is on the line which is 17 lines up from the bottom (excluding
  // bottom box borders, text, spacing). The safest way is to print the UI, move
  // cursor up. Total lines printed after the prompt line: 1 (empty), 1
  // (border), 1 (border), 1 (title), 1 (border), 1 (desc), 1 (empty), 1
  // (border), 1 (empty), 1 (border), 1 (ctrl title), 1 (ctrl desc), 1 (border)
  // = 13 lines. Let's use ANSI escape sequence to move the cursor UP and RIGHT.
  // Actually, `game.c` will use `lerString` which uses its own prompt.
  // But `lerString` simply uses `printf("mensagem"); fgets(...)`. So we can't
  // easily jump to a middle of the screen unless `lerString` understands ANSI.
  // Wait, the original code uses:
  // `lerString("║ Digite o nome do Jogador 1: ", game->nomeJogadorX,
  // MAX_NOME_JOGADOR);` If I want the input to happen inside the box,
  // `lerString` has to clear the line and print the prompt there. Since
  // `lerString` just prints the prompt at the current cursor position, it will
  // print it at the bottom of the screen! I need a special macro or I need to
  // rewrite the prompt. For now, I will just move the cursor up by 15 lines and
  // right by 65 columns, but that's very fragile! Let's modify
  // `obterNomesJogadores` instead to use ANSI! We'll just leave the cursor at
  // the bottom. The user will type at the bottom! Wait, no, the mockup puts the
  // input box in the middle. Let's reposition cursor with ANSI! 13 lines up, 35
  // columns right.
  printf("\033[13A\033[64C\033[7m");
}

void exibirTelaConfirmarJogadores(const char *jogadorX, const char *jogadorO,
                                  int selected) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      " ___ ___  _  _ ___ ___ ___ _   ___   ___ ___  ___ ___ ",
      "/ __/ _ \\| \\| | |_ _/ __| | | | _ \\ / _ \\ _ \\| __/ __|",
      "| (_| (_) | .` |  | | (_ | |_| |   /|  __/   /| _|\\__ \\",
      " \\___\\___/|_|\\_| |___\\___|\\___/|_|_\\ \\___|_|_\\|___|___/"};

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

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("CONFIRMAÇÃO DE JOGADORES"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("NOMES REGISTRADOS");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    │                         "
         "\033[7m╔══════════════════════════════════════════════════╗\033[0m%s "
         "                                      │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                         \033[7m║          JOGADOR X: "
         "%-24.24s ║\033[0m%s                                       │    ║\n",
         jogadorX, temas[tema_ativo]);
  printf("      ║    │                         \033[7m║          JOGADOR O: "
         "%-24.24s ║\033[0m%s                                       │    ║\n",
         jogadorO, temas[tema_ativo]);
  printf("      ║    │                         "
         "\033[7m╚══════════════════════════════════════════════════╝\033[0m%s "
         "                                      │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 = _("  Confira os nomes antes de iniciar a partida.");
  printf("      ║    │%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *title2 = _("CONFIRMAR AÇÃO");
  int p_t2 = (116 - visible_strlen(title2)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t2; i++)
    printf(" ");
  printf("%s", title2);
  for (int i = 0; i < 116 - visible_strlen(title2) - p_t2; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *opts[] = {"[1] SEGUIR PARA A PARTIDA",
                        "[2] EDITAR NOMES DOS JOGADORES",
                        "[0] CANCELAR E VOLTAR"};

  for (int i = 0; i < 3; i++) {
    if (selected == i) {
      char formatado[100];

      int p_opt =
          9; // align all selected items so their `[` starts at column 11

      printf("      ║    │                         "
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
      printf("\033[7m║\033[0m%s                                       │    ║\n",
             temas[tema_ativo]);

      printf("      ║    │                         "
             "\033[7m╚══════════════════════════════════════════════════╝\033["
             "0m%s                                       │    ║\n",
             temas[tema_ativo]);
    } else {
      int p_opt = 11; // fix the `[` to column 11
      printf("      ║    │                         "); // 25 spaces
      printf(" ");                                     // border space (1)
      for (int j = 0; j < p_opt; j++)
        printf(" ");
      printf("%s", _(opts[i]));
      for (int j = 0; j < 50 - visible_strlen(_(opts[i])) - p_opt; j++)
        printf(" ");
      printf(" "); // border space (1)
      printf("                                       │    ║\n"); // 39 spaces
    }

    if (i < 2) {
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 = "      • Use ↑ ↓ para navegar     • ENTER para confirmar "
                      "    • 0, Q ou ESC para voltar ao Menu Principal";
  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaSorteio(int dadoJogador1, int dadoJogador2, const char *jogador1,
                       const char *jogador2, const char *vencedor,
                       int selected) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ _____ ___ ___ ___ ",
                       "/ __|/ _ \\| _ \\_ _| __|_ _/ _ \\",
                       "\\__ \\ (_) | / | | | _| | | (_) |",
                       "|___/\\___/|_|_\\ |_| |___|___\\___/"};

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

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("SORTEIO DO PRIMEIRO JOGADOR"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("RESULTADO DO SORTEIO");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 =
      _("  CADA JOGADOR LANÇOU UM DADO PARA DEFINIR QUEM COMEÇA.");
  int p_d1 = (116 - visible_strlen(desc1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_d1; i++)
    printf(" ");
  printf("%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1) - p_d1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  // Draw the dice side by side! Total width = 116.
  // Box for player 1: 24 wide
  // Box for player 2: 24 wide
  // Space between them: 10
  // Total: 58. (116-58)/2 = 29 spaces on left.
  printf("      ║    │                             ┌──────────────────────┐    "
         "      ┌──────────────────────┐                             │    ║\n");
  printf("      ║    │                             │       JOGADOR 1      │    "
         "      │       JOGADOR 2      │                             │    ║\n");
  printf("      ║    │                             ├──────────────────────┤    "
         "      ├──────────────────────┤                             │    ║\n");
  printf("      ║    │                             │        ┌─────┐       │    "
         "      │        ┌─────┐       │                             │    ║\n");
  printf(
      "      ║    │                             │        │  %d  │       │      "
      "    │        │  %d  │       │                             │    ║\n",
      dadoJogador1, dadoJogador2);
  printf("      ║    │                             │        └─────┘       │    "
         "      │        └─────┘       │                             │    ║\n");
  printf("      ║    │                             │ %-20.20s │          │ "
         "%-20.20s │                             │    ║\n",
         jogador1, jogador2);
  printf("      ║    │                             └──────────────────────┘    "
         "      └──────────────────────┘                             │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    │                              "
         "\033[7m╔════════════════════════════════════════════════════╗\033[0m%"
         "s                              │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                              \033[7m║             "
         "PRIMEIRO JOGADOR DEFINIDO!             ║\033[0m%s                    "
         "          │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                              "
         "\033[7m╠════════════════════════════════════════════════════╣\033[0m%"
         "s                              │    ║\n",
         temas[tema_ativo]);
  char win1[100];
  snprintf(win1, sizeof(win1), "%s", vencedor);
  int pw1 = (52 - visible_strlen(win1)) / 2;
  printf("      ║    │                              \033[7m║\033[0m%s",
         temas[tema_ativo]);
  for (int j = 0; j < pw1 - 1; j++)
    printf(" ");
  printf("\033[7m%s\033[0m%s", win1, temas[tema_ativo]);
  for (int j = 0; j < 52 - visible_strlen(win1) - pw1 - 1; j++)
    printf(" ");
  printf("\033[7m║\033[0m%s                              │    ║\n",
         temas[tema_ativo]);

  char win2[] = "venceu o sorteio e começa a partida!";
  int pw2 = (52 - visible_strlen(win2)) / 2;
  printf("      ║    │                              \033[7m║\033[0m%s",
         temas[tema_ativo]);
  for (int j = 0; j < pw2 - 1; j++)
    printf(" ");
  printf("\033[7m%s\033[0m%s", win2, temas[tema_ativo]);
  for (int j = 0; j < 52 - visible_strlen(win2) - pw2 - 1; j++)
    printf(" ");
  printf("\033[7m║\033[0m%s                              │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                              "
         "\033[7m╚════════════════════════════════════════════════════╝\033[0m%"
         "s                              │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *t_sym = _("ESCOLHA O SEU SÍMBOLO");
  int p_sym = (116 - visible_strlen(t_sym)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_sym; i++)
    printf(" ");
  printf("%s", t_sym);
  for (int i = 0; i < 116 - visible_strlen(t_sym) - p_sym; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *opts[] = {"[1] JOGAR COM X", "[2] JOGAR COM O"};

  if (selected == -1) {
    // AI mode, just show standard box centered or don't show selection
    int p_opt = (50 - visible_strlen(opts[0])) / 2;
    printf("      ║    │                         "); // 25 spaces
    printf(" ");                                     // border space (1)
    for (int j = 0; j < p_opt; j++)
      printf(" ");
    printf("A IA escolheu jogar com %s",
           (dadoJogador2 > dadoJogador1) ? "O" : "X");
    for (int j = 0;
         j < 50 - visible_strlen("A IA escolheu jogar com X") - p_opt; j++)
      printf(" ");
    printf(" "); // border space (1)
    printf("                                       │    ║\n"); // 39 spaces
  } else {
    for (int i = 0; i < 2; i++) {
      if (selected == i) {
        char formatado[100];

        int p_opt = 16;

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
        int p_opt = 18;
        printf("      ║    │                         "); // 25 spaces
        printf(" ");                                     // border space (1)
        for (int j = 0; j < p_opt; j++)
          printf(" ");
        printf("%s", _(opts[i]));
        for (int j = 0; j < 50 - visible_strlen(_(opts[i])) - p_opt; j++)
          printf(" ");
        printf(" "); // border space (1)
        printf("                                       │    ║\n"); // 39 spaces
      }

      if (i < 1) {
        printf("      ║    │                                                   "
               "                                                               "
               "  │    ║\n");
      }
    }
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 = _("      • Use ↑ ↓ para navegar e ENTER para selecionar");
  if (selected == -1)
    ctrl2 = "      • Pressione ENTER para continuar";

  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirInterfaceJogo(const GameState *game, const int *winning_line_indices,
                         const char *mensagemInfo, int selected_cell) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 3; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf(
      "      ║                                      ___  _   ___ _____ ___ ___ "
      "  _                                                          ║\n");
  printf(
      "      ║                                     | _ \\/_\\ | _ \\_   _|_ _| "
      "  \\ /_\\                                                         ║\n");
  printf(
      "      ║                                     |  _/ _ \\|   / | |  | || "
      "|) / _ \\                                                        ║\n");
  printf("      ║                                     |_|/_/ \\_\\_|_\\ |_| "
         "|___|___/_/ \\_\\                                                    "
         "   ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("JOGO DA VEIA EM ANDAMENTO"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    ┌──────────────────────────────────────────────────────┐  "
         "  ┌──────────────────────────────────────────────────────┐      ║\n");

  const char *tab_title =
      (selected_cell >= 0) ? "TABULEIRO SELECIONÁVEL" : "TABULEIRO";
  int p_tab = (54 - visible_strlen(tab_title)) / 2;
  int p_tab_r = 54 - visible_strlen(tab_title) - p_tab;
  printf("      ║    │                        PLACAR                        │  "
         "  │");
  for (int k = 0; k < p_tab; k++)
    printf(" ");
  printf("%s", tab_title);
  for (int k = 0; k < p_tab_r; k++)
    printf(" ");
  printf("│      ║\n");

  printf("      ║    ├──────────────────────────────────────────────────────┤  "
         "  ├─────────────────┬──────────────────┬─────────────────┤      ║\n");

  char board[9][256];
  for (int i = 0; i < 9; i++) {
    char val = game->tabuleiro[i / 3][i % 3];
    bool is_winning = false;
    if (winning_line_indices && winning_line_indices[0] != -1) {
      for (int k = 0; k < 3; k++)
        if (winning_line_indices[k] == i)
          is_winning = true;
    }

    int cell_width = (i % 3 == 1) ? 18 : 17;
    char content[50];
    int content_len;
    if (i == selected_cell) {
      snprintf(content, sizeof(content), "▶ %c ◀", val);
      content_len = 5;
    } else {
      snprintf(content, sizeof(content), " %c ", val);
      content_len = 3;
    }

    int p_left = (cell_width - content_len) / 2;
    int p_right = cell_width - content_len - p_left;

    char left_pad_str[20] = "";
    char right_pad_str[20] = "";
    for (int p = 0; p < p_left; p++)
      strcat(left_pad_str, " ");
    for (int p = 0; p < p_right; p++)
      strcat(right_pad_str, " ");

    if (is_winning) {
      snprintf(board[i], sizeof(board[i]), "%s\033[7m%s\033[0m%s%s",
               left_pad_str, content, temas[tema_ativo], right_pad_str);
    } else if (i == selected_cell) {
      snprintf(board[i], sizeof(board[i]), "%s\033[7m%s\033[0m%s%s",
               left_pad_str, content, temas[tema_ativo], right_pad_str);
    } else {
      snprintf(board[i], sizeof(board[i]), "%s%s%s", left_pad_str, content,
               right_pad_str);
    }
  }

  printf("      ║    │                                                      │  "
         "  │                 │                  │                 │      ║\n");
  printf("      ║    │  JOGADOR 1                                           │  "
         "  │%s│%s│%s│      ║\n",
         board[0], board[1], board[2]);

  printf("      ║    │  ");
  int vlen1 = visible_strlen(game->nomeJogadorX);
  printf("%s", game->nomeJogadorX);
  for (int i = 0; i < 30 - vlen1; i++)
    putchar(' ');
  printf(" [%c]  %02d vitórias     │    "
         "├─────────────────┼──────────────────┼─────────────────┤      ║\n",
         'X', game->placarX);

  printf("      ║    │                                                      │  "
         "  │                 │                  │                 │      ║\n");
  printf("      ║    │──────────────────────────────────────────────────────│  "
         "  │%s│%s│%s│      ║\n",
         board[3], board[4], board[5]);
  printf("      ║    │                                                      │  "
         "  ├─────────────────┼──────────────────┼─────────────────┤      ║\n");

  printf("      ║    │  JOGADOR 2                                           │  "
         "  │                 │                  │                 │      ║\n");
  printf("      ║    │  ");
  int vlen2 = visible_strlen(game->nomeJogadorO);
  printf("%s", game->nomeJogadorO);
  for (int i = 0; i < 30 - vlen2; i++)
    putchar(' ');
  printf(" [%c]  %02d vitórias     │    │%s│%s│%s│      ║\n", 'O',
         game->placarO, board[6], board[7], board[8]);

  printf("      ║    │                                                      │  "
         "  └─────────────────┴──────────────────┴─────────────────┘      ║\n");
  printf("      ║    │──────────────────────────────────────────────────────│  "
         "                                                                ║\n");
  printf("      ║    │                                                      │  "
         "  ┌──────────────────────────────────────────────────────┐      ║\n");

  const char *jogadorAtualNome =
      (game->jogadorAtual == 'X') ? game->nomeJogadorX : game->nomeJogadorO;
  char text_turno[100];
  char text_turno_2[100] = "";
  const char *titulo_turno = _("TURNO ATUAL");
  if (mensagemInfo && strlen(mensagemInfo) > 0) {
    snprintf(text_turno, sizeof(text_turno), "%s", mensagemInfo);
    titulo_turno = "RESULTADO";
  } else {
    snprintf(text_turno, sizeof(text_turno), "É a vez de: %s [%c]",
             jogadorAtualNome, game->jogadorAtual);
    if (selected_cell >= 0) {
      snprintf(text_turno_2, sizeof(text_turno_2), "Casa selecionada: %d",
               selected_cell + 1);
    }
  }
  int p_titulo = (54 - visible_strlen(titulo_turno)) / 2;
  int p_titulo_r = 54 - visible_strlen(titulo_turno) - p_titulo;

  printf("      ║    │  EMPATES: %02d                                         "
         "│    │",
         game->empates);
  for (int k = 0; k < p_titulo; k++)
    printf(" ");
  printf("%s", titulo_turno);
  for (int k = 0; k < p_titulo_r; k++)
    printf(" ");
  printf("│      ║\n");

  printf("      ║    │                                                      │  "
         "  ├──────────────────────────────────────────────────────┤      ║\n");

  int p_texto = (54 - visible_strlen(text_turno)) / 2;
  int p_texto_r = 54 - visible_strlen(text_turno) - p_texto;
  printf("      ║    │  Partida em andamento.                               │  "
         "  │");
  for (int k = 0; k < p_texto; k++)
    printf(" ");
  printf("%s", text_turno);
  for (int k = 0; k < p_texto_r; k++)
    printf(" ");
  printf("│      ║\n");

  if (strlen(text_turno_2) > 0) {
    int p_texto2 = (54 - visible_strlen(text_turno_2)) / 2;
    int p_texto2_r = 54 - visible_strlen(text_turno_2) - p_texto2;
    printf("      ║    │                                                      "
           "│    │");
    for (int k = 0; k < p_texto2; k++)
      printf(" ");
    printf("%s", text_turno_2);
    for (int k = 0; k < p_texto2_r; k++)
      printf(" ");
    printf("│      ║\n");
  } else {
    printf(
        "      ║    │                                                      │   "
        " │                                                      │      ║\n");
  }

  printf("      ║    └──────────────────────────────────────────────────────┘  "
         "  └──────────────────────────────────────────────────────┘      ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║      [ COMANDOS DA PARTIDA ]                                 "
         "                                                                ║\n");
  if (selected_cell >= 0) {
    printf(
        "      ║      • Use ↑ ↓ ← → para navegar     • ENTER para jogar     • "
        "0, Q ou ESC para salvar ou sair da partida                      ║\n");
  } else {
    printf(
        "      ║      • Acompanhe o resultado da jogada no tabuleiro.          "
        "                                                               ║\n");
  }
  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");

  printf("\n");
}

void animarVitoria(const GameState *game, const int *winning_line_indices) {
  for (int i = 0; i < 6; i++) {
    limparTela();
    if (i % 2 == 0) {
      // Brilha com cor branca/fundo preto (padrão highlight)
      exibirInterfaceJogo(game, winning_line_indices, "VITÓRIA!!!", -1);
    } else {
      // Sem realce momentarily
      exibirInterfaceJogo(game, NULL, "VITÓRIA!!!", -1);
    }
    delaySimples(300);
  }
}

bool perguntarReplayResultado(const char *vencedor, char simboloVencedor,
                              bool is_empate) {
  int selected = 1; // 1 = YES, 0 = NO

  while (true) {
    limparTela();
    aplicarTema(tema_ativo);

    for (int i = 0; i < 3; i++)
      printf("\n");

    printf("      "
           "╔══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╗\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf(
        "      ║                                      ___  _   ___ _____ ___ "
        "___   _                                                          ║\n");
    printf("      ║                                     | _ \\/_\\ | _ \\_   "
           "_|_ _|   \\ /_\\                                                   "
           "      ║\n");
    printf(
        "      ║                                     |  _/ _ \\|   / | |  | || "
        "|) / _ \\                                                        ║\n");
    printf("      ║                                     |_|/_/ \\_\\_|_\\ |_| "
           "|___|___/_/ \\_\\                                                  "
           "     ║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║─────────────────────────────────────────────── v4.0 • "
           "RESULTADO DA PARTIDA "
           "──────────────────────────────────────────────────║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║    "
           "┌──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┐    ║\n");

    if (is_empate) {
      printf("      ║    │                                                 "
             "PARTIDA EMPATADA!                                                "
             "  │    ║\n");
    } else {
      printf("      ║    │                                                 "
             "VITÓRIA DETECTADA!                                               "
             "  │    ║\n");
    }

    printf("      ║    "
           "├──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┤    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │                              "
           "╔════════════════════════════════════════════════════╗             "
           "                   │    ║\n");

    if (is_empate) {
      printf("      ║    │                              ║              O JOGO "
             "TERMINOU SEM VENCEDOR!         ║                                "
             "│    ║\n");
    } else {
      printf("      ║    │                              ║               "
             "PARABÉNS AO VENCEDOR!                ║                           "
             "     │    ║\n");
    }

    printf("      ║    │                              "
           "╚════════════════════════════════════════════════════╝             "
           "                   │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    if (!is_empate) {
      printf("      ║    │                                       .-=========-. "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                       "
             "\\'-=======-'/                                                   "
             "             │    ║\n");
      printf("      ║    │                                       _|   .=.   |_ "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                      ((|  {o}  |))  "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                       \\|   /|\\   "
             "|/                                                               "
             " │    ║\n");
      printf("      ║    │                                        \\__ '`' __/ "
             "                                                                "
             "│    ║\n");
      printf("      ║    │                                          _`) (`_    "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                        _/_______\\_ "
             "                                                                "
             "│    ║\n");
      printf("      ║    │                                       "
             "/___________\\                                                   "
             "             │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                              "
             "╔════════════════════════════════════════════════════╗           "
             "                     │    ║\n");
      printf("      ║    │                              ║ JOGADOR: %-39.39s ║  "
             "                              │    ║\n",
             vencedor);
      printf("      ║    │                              ║ SÍMBOLO: [%c] • "
             "VENCEU A PARTIDA!                   ║                            "
             "    │    ║\n",
             simboloVencedor);
      printf("      ║    │                              "
             "╚════════════════════════════════════════════════════╝           "
             "                     │    ║\n");
    } else {
      printf("      ║    │                                            ⚖️  O "
             "tabuleiro lotou! ⚖️                                               "
             " │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                              "
             "╔════════════════════════════════════════════════════╗           "
             "                     │    ║\n");
      printf("      ║    │                              ║                    "
             "RESULTADO                       ║                                "
             "│    ║\n");
      printf("      ║    │                              ║                      "
             "EMPATE!                       ║                                │ "
             "   ║\n");
      printf("      ║    │                              "
             "╚════════════════════════════════════════════════════╝           "
             "                     │    ║\n");
    }

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                  REPLAY "
        "DA RODADA                                                  │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    if (selected == 1) {
      printf("      ║    │                         "
             "╔══════════════════════════════════════════════╗                 "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m          ▶ [1] VER "
             "REPLAY DA RODADA ◀      \033[0m%s║                               "
             "            │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚══════════════════════════════════════════════╝                 "
             "                          │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                     [0] PULAR "
             "REPLAY E CONTINUAR                                               "
             "    │    ║\n");
    } else {
      printf("      ║    │                                     [1] VER REPLAY "
             "DA RODADA                                                       "
             "│    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                         "
             "╔══════════════════════════════════════════════╗                 "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m        ▶ [0] PULAR "
             "REPLAY E CONTINUAR ◀    \033[0m%s║                               "
             "            │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚══════════════════════════════════════════════╝                 "
             "                          │    ║\n");
    }

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
    printf(
        "      ║      [ COMANDOS ]                                             "
        "                                                               ║\n");
    printf(
        "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • "
        "0 para pular o replay                                           ║\n");
    printf("      "
           "╚══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╝\n");

    KeyCode tecla = lerTeclaMenu();
    if (tecla == KEY_UP || tecla == KEY_DOWN) {
      selected = (selected == 1) ? 0 : 1;
    } else if (tecla == KEY_ENTER) {
      return (selected == 1);
    } else if (tecla == KEY_0 || tecla == KEY_Q || tecla == KEY_ESC) {
      return false;
    } else if (tecla == KEY_OTHER) {
      // Check if they pressed '1'
      int raw_key = obterTecla();
      if (raw_key == '1')
        return true;
    }
  }
}

bool perguntarJogarNovamente(void) {
  int selected = 1; // 1 = YES, 0 = NO

  while (true) {
    limparTela();
    aplicarTema(tema_ativo);

    for (int i = 0; i < 3; i++)
      printf("\n");

    printf("      "
           "╔══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╗\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf(
        "      ║                                 _  _  _____  _   _  ___   ___ "
        "  _   ___  _____  ___  ___   _                                 ║\n");
    printf("      ║                                | \\| |/ _ \\ \\| | /_\\ | "
           "\\ | _ \\ /_\\ | _ \\_ _|_ _| \\ /_\\                              "
           "  ║\n");
    printf(
        "      ║                                | .` | (_) | .` |/ _ \\| |) | "
        "| _// _ \\| / | | | || |) / _ \\                               ║\n");
    printf("      ║                                |_|\\_|\\___/|_|\\_/_/ "
           "\\_\\___/ |_| /_/ \\_\\_|_\\ |_| |___|___/_/ \\_\\                 "
           "              ║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf(
        "      ║─────────────────────────────────────────────── v4.0 • FINAL "
        "DA RODADA ───────────────────────────────────────────────────────║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║    "
           "┌──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┐    ║\n");
    printf("      ║    │                                              DESEJA "
           "JOGAR NOVAMENTE?                                               │   "
           " ║\n");
    printf("      ║    "
           "├──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┤    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │  Uma nova rodada será iniciada mantendo os jogadores "
           "atuais.                                                       │    "
           "║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    if (selected == 1) {
      printf("      ║    │                         "
             "╔══════════════════════════════════════════════╗                 "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m        ▶ [1] SIM, "
             "JOGAR NOVAMENTE ◀        \033[0m%s║                              "
             "             │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚══════════════════════════════════════════════╝                 "
             "                          │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                     [0] NÃO, VOLTAR "
             "AO MENU PRINCIPAL                                              │ "
             "   ║\n");
    } else {
      printf("      ║    │                                     [1] SIM, JOGAR "
             "NOVAMENTE                                                       "
             "│    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                         "
             "╔══════════════════════════════════════════════╗                 "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m      ▶ [0] NÃO, "
             "VOLTAR AO MENU PRINCIPAL ◀ \033[0m%s║                            "
             "               │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚══════════════════════════════════════════════╝                 "
             "                          │    ║\n");
    }

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf("      ║    │                                                   "
           "MENSAGEM FINAL                                                   │ "
           "   ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │                                ✦ Cada rodada é uma nova "
        "chance de vencer. ✦                                        │    ║\n");
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
    printf(
        "      ║      [ CONTROLES DA TELA ]                                    "
        "                                                               ║\n");
    printf(
        "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • "
        "0, Q ou ESC para voltar ao Menu Principal                       ║\n");
    printf("      "
           "╚══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╝\n");

    KeyCode tecla = lerTeclaMenu();
    if (tecla == KEY_UP || tecla == KEY_DOWN) {
      selected = (selected == 1) ? 0 : 1;
    } else if (tecla == KEY_ENTER) {
      return (selected == 1);
    } else if (tecla == KEY_0 || tecla == KEY_Q || tecla == KEY_ESC) {
      return false;
    } else if (tecla == KEY_OTHER) {
      int raw_key = obterTecla();
      if (raw_key == '1')
        return true;
    }
  }
}
int perguntarDificuldadeIA(void) {
  int selected = 1; // 1=Fácil, 2=Médio, 3=Difícil, 0=Voltar

  while (true) {
    limparTela();
    aplicarTema(tema_ativo);

    for (int i = 0; i < 3; i++)
      printf("\n");

    printf("      "
           "╔══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╗\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf(
        "      ║                         ___ ___ ___ ___ ___ _   _ _   _____ _ "
        "  ___ ___                                               ║\n");
    printf("      ║                        |   \\_ _| __|_ _/ __| | | | | |_   "
           "_/_\\ |   \\_ _|                                              ║\n");
    printf("      ║                        | |) | || _| | | (__| |_| | |__ | "
           "|/ _ \\| |) | |                                               ║\n");
    printf("      ║                        |___/___|_| "
           "|___\\___|\\___/|____|_|/_/ \\_\\___/___|                          "
           "                    ║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║────────────────────────────────────────────── v4.0 • "
           "CONFIGURAR ADVERSÁRIO IA "
           "─────────────────────────────────────────────║\n");
    printf(
        "      ║                                                               "
        "                                                               ║\n");
    printf("      ║    "
           "┌──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┐    ║\n");
    printf(
        "      ║    │                                   DIFICULDADE DA IA      "
        "                                                          │    ║\n");
    printf("      ║    "
           "├──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────┤    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │  Escolha o nível de desafio da Inteligência Artificial "
        "antes de iniciar a partida.                                 │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                      NÍVEIS DISPONÍVEIS  "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");

    if (selected == 1) {
      printf("      ║    │                         "
             "╔════════════════════════════════════════════════╗               "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m      ▶ [1] FÁCIL — "
             "MOVIMENTOS ALEATÓRIOS ◀     \033[0m%s║                           "
             "              │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚════════════════════════════════════════════════╝               "
             "                          │    ║\n");
    } else {
      printf("      ║    │                              [1] FÁCIL — MOVIMENTOS "
             "ALEATÓRIOS                                                     │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }

    if (selected == 2) {
      printf("      ║    │                         "
             "╔════════════════════════════════════════════════╗               "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m      ▶ [2] MÉDIO — "
             "ESTRATÉGICO           ◀     \033[0m%s║                           "
             "              │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚════════════════════════════════════════════════╝               "
             "                          │    ║\n");
    } else {
      printf("      ║    │                              [2] MÉDIO — "
             "ESTRATÉGICO                                                      "
             "         │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }

    if (selected == 3) {
      printf("      ║    │                         "
             "╔════════════════════════════════════════════════╗               "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m      ▶ [3] DIFÍCIL "
             "— IMBATÍVEL           ◀     \033[0m%s║                           "
             "              │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚════════════════════════════════════════════════╝               "
             "                          │    ║\n");
    } else {
      printf("      ║    │                              [3] DIFÍCIL — "
             "IMBATÍVEL                                                        "
             "       │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }

    if (selected == 0) {
      printf("      ║    │                         "
             "╔════════════════════════════════════════════════╗               "
             "                          │    ║\n");
      printf("      ║    │                         ║\033[7m      ▶ [0] VOLTAR "
             "AO MENU PRINCIPAL      ◀     \033[0m%s║                          "
             "               │    ║\n",
             temas[tema_ativo]);
      printf("      ║    │                         "
             "╚════════════════════════════════════════════════╝               "
             "                          │    ║\n");
    } else {
      printf("      ║    │                              [0] VOLTAR AO MENU "
             "PRINCIPAL                                                        "
             "  │    ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }

    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                  SOBRE A DIFICULDADE     "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │  FÁCIL: a IA faz movimentos aleatórios e é ideal para "
           "aprender as regras.                                          │    "
           "║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │  MÉDIO: a IA tenta vencer e bloquear suas jogadas sempre "
        "que possível.                                             │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │  DIFÍCIL: a IA usa a melhor estratégia possível e não "
           "pode ser derrotada.                                          │    "
           "║\n");
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
    printf(
        "      ║      [ CONTROLES DA TELA ]                                    "
        "                                                               ║\n");
    printf(
        "      ║      • Use ↑ ↓ para navegar     • ENTER para confirmar     • "
        "0, Q ou ESC para voltar ao Menu Principal                       ║\n");
    printf("      "
           "╚══════════════════════════════════════════════════════════════════"
           "════════════════════════════════════════════════════════════╝\n");

    KeyCode tecla = lerTeclaMenu();
    if (tecla == KEY_UP) {
      if (selected == 0)
        selected = 3;
      else if (selected == 1)
        selected = 0;
      else
        selected--;
    } else if (tecla == KEY_DOWN) {
      if (selected == 3)
        selected = 0;
      else if (selected == 0)
        selected = 1;
      else
        selected++;
    } else if (tecla == KEY_ENTER) {
      if (selected == 0)
        return -1;
      return selected - 1; // 0, 1, 2 para dificuldade, -1 para voltar
    } else if (tecla == KEY_0 || tecla == KEY_Q || tecla == KEY_ESC) {
      return -1;
    } else if (tecla == KEY_OTHER) {
      int raw_key = obterTecla();
      if (raw_key == '1')
        return 0;
      if (raw_key == '2')
        return 1;
      if (raw_key == '3')
        return 2;
      if (raw_key == '0')
        return -1;
    }
  }
}

void exibirTrofeu(const char *vencedor) {
  printf("\a"); // Alerta sonoro de troféu
  printf("\n");

  printf("╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════╗\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                     ___   _   __  __ ___ ___ ___    ___  ___       "
         "                                 ║\n");
  printf("║                    / __| /_\\ |  \\/  | _ \\ __/ _ \\  |   \\| _ "
         "\\                                       ║\n");
  printf("║                   | (__ / _ \\| |\\/| |  _/ _| (_) | | |) |   /    "
         "                                   ║\n");
  printf("║                    \\___/_/ \\_\\_|  |_|_| |___\\___/  |___/|_|_\\ "
         "                                      ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║──────────────────────────────────────────── v4.0 • FINAL DO "
         "TORNEIO ────────────────────────────────║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                         "
         "╔════════════════════════════════════════════╗                       "
         "      ║\n");
  printf("║                         ║              PARABÉNS, CAMPEÃO!          "
         "  ║                             ║\n");
  printf("║                         "
         "╚════════════════════════════════════════════╝                       "
         "      ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                                      .-=========-.                 "
         "                                  ║\n");
  printf("║                                      \\'-=======-'/                "
         "                                   ║\n");
  printf("║                                      _|   .=.   |_                 "
         "                                   ║\n");
  printf("║                                     ((|  {o}  |))                  "
         "                                   ║\n");
  printf("║                                      \\|   /|\\   |/               "
         "                                    ║\n");
  printf("║                                       \\__ '`' __/                 "
         "                                   ║\n");
  printf("║                                         _`) (`_                    "
         "                                   ║\n");
  printf("║                                       _/_______\\_                 "
         "                                    ║\n");
  printf("║                                      /___________\\                "
         "                                    ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                         "
         "╔════════════════════════════════════════════════════╗               "
         "      ║\n");
  printf("║                         ║  CAMPEÃO DO TORNEIO: %-29.29s ║          "
         "           ║\n",
         vencedor);
  printf("║                         "
         "╚════════════════════════════════════════════════════╝               "
         "      ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                   ✦ Você superou os desafios e conquistou o topo "
         "do ranking! ✦                    ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                              Pressione ENTER para continuar...     "
         "                                 ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════╝\n\n");

  esperarEnter();
}

void exibirConquista(const char *titulo) {

  printf("\a"); // Alerta sonoro de conquista

  printf("╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════╗\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                    ___ ___  _  _  ___ _   _ ___ ___ _____ _        "
         "                           ║\n");
  printf("║                   / __/ _ \\| \\| |/ _ \\ | | |_ _/ __|_   _/_\\   "
         "                               ║\n");
  printf("║                  | (_| (_) | .` | (_) | |_| || |\\__ \\ | |/ _ \\  "
         "                               ║\n");
  printf("║                   \\___\\___/|_|\\_|\\_  / \\___/|___|___/ |_/_/ "
         "\\_\\                                ║\n");
  printf("║                                   /_/                              "
         "                                  ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║──────────────────────────────────────────── v4.0 • NOVA CONQUISTA "
         "──────────────────────────────────║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                                      .-=========-.                 "
         "                                  ║\n");
  printf("║                                      \\'-=======-'/                "
         "                                   ║\n");
  printf("║                                      _|   .=.   |_                 "
         "                                   ║\n");
  printf("║                                     ((|  {o}  |))                  "
         "                                   ║\n");
  printf("║                                      \\|   /|\\   |/               "
         "                                    ║\n");
  printf("║                                       \\__ '`' __/                 "
         "                                   ║\n");
  printf("║                                         _`) (`_                    "
         "                                   ║\n");
  printf("║                                       _/_______\\_                 "
         "                                    ║\n");
  printf("║                                      /___________\\                "
         "                                    ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                         "
         "╔════════════════════════════════════════════════════╗               "
         "      ║\n");
  printf("║                         ║  CONQUISTA: %-38.38s ║                   "
         "  ║\n",
         titulo);
  printf("║                         "
         "╚════════════════════════════════════════════════════╝               "
         "      ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                    ✦ Muito bem! Continue jogando para desbloquear "
         "mais conquistas. ✦              ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("║                         Pressione ENTER para continuar...          "
         "                                  ║\n");
  printf("║                                                                    "
         "                                  ║\n");
  printf("╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════╝\n\n");

  esperarEnter();
}

void exibirTelaRanking(void) {
  limparTela();
  aplicarTema(tema_ativo);

  carregarRanking();
  if (num_ranking_entries > 1) {
    qsort(ranking, num_ranking_entries, sizeof(RankingEntry),
          compararRankingEntries);
  }

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___   _   _  _ _  _____ _  _  ___ ",
                       "| _ \\ /_\\ | \\| | |/ /_ _| \\| |/ __|",
                       "|   / / _ \\| .` | ' < | || .` | (_ |",
                       "|_|_\\/_/ \\_\\_|\\_|_|\\_\\___|_|\\_|\\___|"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("RANKING DOS JOGADORES"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  const char *title1 = _("MELHORES JOGADORES");
  int p_t1 = (116 - visible_strlen(title1)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t1; i++)
    printf(" ");
  printf("%s", title1);
  for (int i = 0; i < 116 - visible_strlen(title1) - p_t1; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc1 = "  Acompanhe as vitórias, empates, derrotas e medalhas "
                      "conquistadas por cada jogador.";
  printf("      ║    │%s", desc1);
  for (int i = 0; i < 116 - visible_strlen(desc1); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *col_headers = "   POS    JOGADOR                         "
                            "VITÓRIAS     EMPATES     DERROTAS     MEDALHAS";
  printf("      ║    │%s", col_headers);
  for (int i = 0; i < 116 - visible_strlen(col_headers); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  for (int i = 0; i < 3; i++) {
    if (i < num_ranking_entries) {
      char line_buf[200];
      snprintf(line_buf, sizeof(line_buf),
               "   %02d     %-32.32s%-13d%-12d%-13d%d", i + 1, ranking[i].name,
               ranking[i].wins, ranking[i].ties, ranking[i].losses,
               ranking[i].medals);
      int len = visible_strlen(line_buf);
      printf("      ║    │%s", line_buf);
      for (int p = 0; p < 116 - len; p++)
        printf(" ");
      printf("│    ║\n");
    } else {
      if (i == 0 && num_ranking_entries == 0) {
        const char *empty_msg = "   --     Nenhum jogador registrado          "
                                "0            0            0             0";
        printf("      ║    │%s", empty_msg);
        for (int p = 0; p < 116 - visible_strlen(empty_msg); p++)
          printf(" ");
        printf("│    ║\n");
      } else {
        printf("      ║    │                                                   "
               "                                                               "
               "  │    ║\n");
      }
    }

    if (i < 2) {
      printf("      ║    │                                                     "
             "                                                               │ "
             "   ║\n");
    }
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  const char *title2 = _("DESTAQUE DO RANKING");
  int p_t2 = (116 - visible_strlen(title2)) / 2;
  printf("      ║    │");
  for (int i = 0; i < p_t2; i++)
    printf(" ");
  printf("%s", title2);
  for (int i = 0; i < 116 - visible_strlen(title2) - p_t2; i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  if (num_ranking_entries > 0) {
    char dest_buf[100];
    snprintf(dest_buf, sizeof(dest_buf), "1º LUGAR  •  %s  •  %d VITÓRIAS",
             ranking[0].name, ranking[0].wins);
    int dest_len = visible_strlen(dest_buf);
    int pad_l = (46 - dest_len) / 2;
    int pad_r = 46 - dest_len - pad_l;

    printf("      ║    │                         "
           "\033[7m╔══════════════════════════════════════════════╗\033[0m%s   "
           "                                        │    ║\n",
           temas[tema_ativo]);

    printf("      ║    │                         \033[7m║\033[0m%s",
           temas[tema_ativo]);
    for (int p = 0; p < pad_l; p++)
      printf(" ");
    printf("\033[7m%s\033[0m%s", dest_buf, temas[tema_ativo]);
    for (int p = 0; p < pad_r; p++)
      printf(" ");
    printf(
        "\033[7m║\033[0m%s                                           │    ║\n",
        temas[tema_ativo]);

    printf("      ║    │                         "
           "\033[7m╚══════════════════════════════════════════════╝\033[0m%s   "
           "                                        │    ║\n",
           temas[tema_ativo]);
  } else {
    printf("      ║    │                         "
           "╔══════════════════════════════════════════════╗                   "
           "                        │    ║\n");
    printf("      ║    │                         ║          NENHUM JOGADOR "
           "REGISTRADO           ║                                           │ "
           "   ║\n");
    printf("      ║    │                         "
           "╚══════════════════════════════════════════════╝                   "
           "                        │    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *desc2 =
      _("  Continue jogando para subir de posição e conquistar mais medalhas.");
  printf("      ║    │%s", desc2);
  for (int i = 0; i < 116 - visible_strlen(desc2); i++)
    printf(" ");
  printf("│    ║\n");

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int p = 0; p < 126 - visible_strlen(ctrl1); p++)
    printf(" ");
  printf("║\n");

  const char *ctrl2 =
      _("      • Pressione ENTER, ESC ou Q para retornar ao Menu Principal");
  printf("      ║%s", ctrl2);
  for (int p = 0; p < 126 - visible_strlen(ctrl2); p++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirMenuInterativo(int selected, const GameState *game) {
  (void)game; // Evita warning de variavel nao utilizada
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf(
      "      ║                      _   ___   ___   ___             __   ___   "
      " __          __   _   _  ___   ___   __                      ║\n");
  printf("      ║                     | | / _ \\ / __| / _ \\   ____    / /  | "
         "  \\  /  \\   ____  \\ \\ | | | || __| |_ _| /  \\                   "
         "  ║\n");
  printf("      ║                  _  | || (_) | (_ || (_) | |____|  / /   | "
         "|) |/ () \\ |____|  \\ \\ \\ V / | _|   | | / () \\                  "
         "  ║\n");
  printf("      ║                  | |_| | \\___/ \\___| \\___/          \\ \\ "
         "  |___/ \\__/           / /  \\_/  |___| |___|\\__/                  "
         "   ║\n");
  printf(
      "      ║                   \\___/                              \\_\\     "
      "                 /_/                                            ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info),
           "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦",
           nomes_temas[tema_ativo], GAME_VERSION);
  int info_len = visible_strlen(header_info);
  int pad_left = (126 - info_len) / 2;
  int pad_right = 126 - info_len - pad_left;
  printf("      ║");
  for (int i = 0; i < pad_left; i++)
    printf(" ");
  printf("%s", header_info);
  for (int i = 0; i < pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║    ┌────────────────────────────┐    "
         "┌────────────────────────────────────────────────────────────────────"
         "──────────────┐    ║\n");
  printf("      ║    │        MASCOTE v4.0        │    │                       "
         "           MENU PRINCIPAL                                  │    ║\n");
  printf("      ║    ├────────────────────────────┤    "
         "├────────────────────────────────────────────────────────────────────"
         "──────────────┤    ║\n");
  const char *options[] = {"JOGAR",
                           "INSTRUÇÕES OFICIAIS",
                           "CRÉDITOS DO PROJETO",
                           "REFERÊNCIAS TÉCNICAS",
                           "SELEÇÃO DE TEMA",
                           "NUVEM: SAVE / LOAD",
                           "RANKING GLOBAL",
                           "SAIR DO SISTEMA",
                           "IDIOMA"};

  const char *left_col[21] = {
      "                            ",    "          /)  (\\            ",
      "      )\\.:::::::::./(       ",   "      \\( o       o )/       ",
      "        '-./ / _.-'`-.      ",    "         ( oo  ) / _  \\     ",
      "         |'--'/\\/ ( \\  \\    ", "          \\''/  \\| \\ \\  \\   ",
      "           ww   |  '  )  \\  ",   "                |.' .'   |  ",
      "               .' .'==|==|  ",    "              / .\\    [_]   ",
      "           .-(/\\) |     /   ",   "          /.-\"\"\"'/|    |    ",
      "          ||    / |    |    ",    "          //   |  |    |    ",
      "          ||   |__|___/     ",    "          \\\\   [__[___]     ",
      "          // .-'.-'  (      ",    "          ||(__(__.-._)     ",
      "                            "};

  char right_col[21][300];
  for (int r = 0; r < 21; r++) {
    strcpy(right_col[r], "                                                     "
                         "                             "); // 82 spaces
  }

  int current_line = 3;
  for (int i = 1; i <= 9; i++) {
    if (i == selected) {
      char padding[50] = "";
      int len = visible_strlen(options[i - 1]);
      int pad_len = 26 - len;
      for (int p = 0; p < pad_len; p++)
        padding[p] = ' ';
      padding[pad_len] = '\0';

      char formatted_option[200];
      // Reseta a formatação (\033[0m) para evitar que o fundo vaze pela tela
      // inteira, e reaplica a cor do tema
      sprintf(formatted_option, "\033[7m >> [%d] %s%s << \033[0m%s", i,
              options[i - 1], padding, temas[tema_ativo]);

      sprintf(right_col[current_line],
              "                      %s                      ",
              formatted_option); // 22 padding
      current_line += 2;
    } else {
      char padding[100] = "";
      int len = visible_strlen(options[i - 1]);
      int text_len = 4 + len; // "[x] " + text
      int left_pad_size = 26;
      int right_pad_size = 82 - left_pad_size - text_len;
      for (int p = 0; p < right_pad_size; p++)
        padding[p] = ' ';
      padding[right_pad_size] = '\0';

      sprintf(right_col[current_line], "                          [%d] %s%s", i,
              options[i - 1], padding); // 26 padding
      current_line += 2;
    }
  }

  for (int r = 0; r < 21; r++) {
    printf("      ║    │%s│    │%s│    ║\n", left_col[r], right_col[r]);
  }

  printf("      ║    └────────────────────────────┘    "
         "└────────────────────────────────────────────────────────────────────"
         "──────────────┘    ║\n");

  char footer_msg[] =
      "✦ Pense bem. Uma jogada pode decidir tudo. Controle o centro e vença. ✦";
  int flen = visible_strlen(footer_msg);
  int fpad_left = (126 - flen) / 2;
  int fpad_right = 126 - flen - fpad_left;
  printf("      ║");
  for (int i = 0; i < fpad_left; i++)
    printf(" ");
  printf("%s", footer_msg);
  for (int i = 0; i < fpad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DO MENU ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[500];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Use as setas \033[7m ↑ ↓ \033[0m%s para navegar     • "
           "Pressione \033[7m ENTER \033[0m%s para selecionar     • Pressione "
           "\033[7m Q \033[0m%s para sair rapidamente",
           temas[tema_ativo], temas[tema_ativo], temas[tema_ativo]);
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m"); // Restaura a cor para que prompt ou saídas seguintes não
                     // vazem o tema
}

void exibirTelaInstrucoes(void) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf(
      "      ║                                  ___ _  _ _____ ___   ___  ___  "
      "_   _  ___   _   ___   ___                                    ║\n");
  printf("      ║                                 |_ _| \\| |_   _| _ \\ / _ "
         "\\|   \\| | | |/ __| /_\\ / _ \\ | _ \\                              "
         "     ║\n");
  printf(
      "      ║                                  | || .` | | | |   /| (_) | |) "
      "| |_| | (__ / _ \\ (_) ||   /                                   ║\n");
  printf("      ║                                 |___|_|\\_| |_| |_|_\\ "
         "\\___/|___/ \\___/ \\___/_/ \\_\\___/ |_|_\\                         "
         "         ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info),
           "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦",
           nomes_temas[tema_ativo], GAME_VERSION);
  int info_len = visible_strlen(header_info);
  int pad_left = (126 - info_len) / 2;
  int pad_right = 126 - info_len - pad_left;
  printf("      ║");
  for (int i = 0; i < pad_left; i++)
    printf(" ");
  printf("%s", header_info);
  for (int i = 0; i < pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║    ┌────────────────────────────┐    "
         "┌────────────────────────────────────────────────────────────────────"
         "──────────────┐    ║\n");
  printf("      ║    │      EXEMPLO DE JOGO       │    │                       "
         "  APRENDA COMO FUNCIONA CADA MODO                          │    ║\n");
  printf("      ║    ├────────────────────────────┤    "
         "├────────────────────────────────────────────────────────────────────"
         "──────────────┤    ║\n");

  const char *left_col[21] = {
      "                            ", "        COMO JOGAR:         ",
      "                            ", "         1 │ 2 │ 3          ",
      "        ───┼───┼───         ", "         4 │ 5 │ 6          ",
      "        ───┼───┼───         ", "         7 │ 8 │ 9          ",
      "                            ", "       ALINHE 3 PEÇAS:      ",
      "                            ", "         X │ O │            ",
      "        ───┼───┼───         ", "         O │ X │            ",
      "        ───┼───┼───         ", "           │   │ X          ",
      "                            ", "      ✦ VOCÊ VENCEU! ✦      ",
      "                            ", "                            ",
      "                            "};

  const char *instr[21] = {
      "",
      "   \033[7m REGRAS BÁSICAS DO JOGO \033[0m",
      "   Dois jogadores (X e O) se revezam colocando peças no tabuleiro. O",
      "   primeiro a formar uma linha de 3 peças iguais vence a partida.",
      "",
      "   \033[7m MODO JOGADOR VS JOGADOR (1 VS 1 LOCAL) \033[0m",
      "   O modo clássico. Jogue com um amigo no mesmo teclado alternando",
      "   turnos até que um jogador vença ou o tabuleiro fique cheio (empate).",
      "",
      "   \033[7m MODO JOGADOR VS IA (CONTRA O COMPUTADOR) \033[0m",
      "   Jogue contra a máquina. Teste suas habilidades enfrentando nossa",
      "   Inteligência Artificial que tentará bloquear suas jogadas ao máximo.",
      "",
      "   \033[7m MODO INFINITO (O MODO ESTRATÉGICO) \033[0m",
      "   A verdadeira revolução! Neste modo dinâmico, cada jogador só pode",
      "   ter NO MÁXIMO 3 peças simultâneas no tabuleiro.",
      "   Ao colocar sua 4ª peça, a sua 1ª peça (a mais antiga) desaparecerá!",
      "",
      "",
      "",
      ""};

  char right_col[21][300];
  for (int r = 0; r < 21; r++) {
    char padding[100] = "";
    int len = visible_strlen(instr[r]);
    int pad_size = 82 - len;
    if (pad_size < 0)
      pad_size = 0;
    for (int p = 0; p < pad_size; p++)
      padding[p] = ' ';
    padding[pad_size] = '\0';

    if (r == 1 || r == 5 || r == 9 || r == 13) {
      sprintf(right_col[r], "%s\033[0m%s%s", instr[r], temas[tema_ativo],
              padding);
    } else {
      sprintf(right_col[r], "%s%s", instr[r], padding);
    }
  }

  for (int r = 0; r < 21; r++) {
    printf("      ║    │%s│    │%s│    ║\n", left_col[r], right_col[r]);
  }

  printf("      ║    └────────────────────────────┘    "
         "└────────────────────────────────────────────────────────────────────"
         "──────────────┘    ║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[500];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Pressione \033[7m ENTER \033[0m%s, \033[7m ESC \033[0m%s "
           "ou \033[7m Q \033[0m%s para retornar ao menu principal",
           temas[tema_ativo], temas[tema_ativo], temas[tema_ativo]);
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaCreditos(void) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ ___ ___ ___ _____ ___  ___ ",
                       "/ __| _ \\ __|   \\_ _|_   _/ _ \\| __|",
                       "| (__|   / _|| |) | |  | || (_) | _|",
                       " \\___|_|_\\___|___/___| |_| \\___/|___|"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info),
           "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦",
           nomes_temas[tema_ativo], GAME_VERSION);
  int info_len = visible_strlen(header_info);
  int pad_left = (126 - info_len) / 2;
  int pad_right = 126 - info_len - pad_left;
  printf("      ║");
  for (int i = 0; i < pad_left; i++)
    printf(" ");
  printf("%s", header_info);
  for (int i = 0; i < pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║    ┌────────────────────────────┐    "
         "┌────────────────────────────────────────────────────────────────────"
         "──────────────┐    ║\n");
  printf("      ║    │       [ IDENTIDADE ]       │    │                       "
         "        CRÉDITOS DO PROJETO                                │    ║\n");
  printf("      ║    ├────────────────────────────┤    "
         "├────────────────────────────────────────────────────────────────────"
         "──────────────┤    ║\n");

  const char *left_col[21] = {
      "                            ", "        ┌───┬───┬───┐       ",
      "        │ X │ O │ X │       ", "        ├───┼───┼───┤       ",
      "        │ O │ X │ O │       ", "        ├───┼───┼───┤       ",
      "        │ X │ O │ X │       ", "        └───┴───┴───┘       ",
      "                            ", "       JOGO DA  Veia        ",
      "                            ", "      Projeto acadêmico     ",
      "      desenvolvido para     ", "      praticar lógica,      ",
      "      estratégia e menus.   ", "                            ",
      "        ┌──────────┐        ", "        │   v4.0   │        ",
      "        └──────────┘        ", "                            ",
      "                            "};

  const char *right_col_raw[21] = {
      "",
      "  Curso:        Ciência da Computação",
      "  Disciplina:   Programação I",
      "  Projeto:      Jogo da  Veia",
      "  Autora:       Stella Karolina Nunes Peixoto",
      "  Matrícula:    20223834810",
      "",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "                               \033[7m HISTÓRICO DE VERSÕES \033[0m",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "  Versão 1.0   │  2023  │  Primeira versão do jogo",
      "  Versão 2.0   │  2025  │  Melhorias de jogabilidade e interface",
      "  Versão 3.0   │  2025  │  Novas telas e refinamento do sistema",
      "  Versão 4.0   │  2026  │  Temas, ranking, save/load e interface ASCII",
      "",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "                                  \033[7m AGRADECIMENTOS \033[0m",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "  Aos professores, colegas e todos que contribuíram para a evolução "
      "deste projeto.",
      "",
      ""};

  char right_col[21][300];
  for (int r = 0; r < 21; r++) {
    char padding[100] = "";
    int len = visible_strlen(right_col_raw[r]);
    int pad_size = 82 - len;
    if (pad_size < 0)
      pad_size = 0;
    for (int p = 0; p < pad_size; p++)
      padding[p] = ' ';
    padding[pad_size] = '\0';

    if (r == 8 || r == 16) {
      sprintf(right_col[r], "%s\033[0m%s%s", right_col_raw[r],
              temas[tema_ativo], padding);
    } else {
      sprintf(right_col[r], "%s%s", right_col_raw[r], padding);
    }
  }

  for (int r = 0; r < 21; r++) {
    printf("      ║    │%s│    │%s│    ║\n", left_col[r], right_col[r]);
  }

  printf("      ║    └────────────────────────────┘    "
         "└────────────────────────────────────────────────────────────────────"
         "──────────────┘    ║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Pressione \033[7m ENTER \033[0m%s, \033[7m ESC \033[0m%s "
           "ou \033[7m Q \033[0m%s para retornar ao menu principal",
           temas[tema_ativo], temas[tema_ativo], temas[tema_ativo]);
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaReferencia(void) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      " ___ ___ ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
      "| _ \\ __| __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
      "|   / _|| _|| _||   / _|| .` | (__ | | / _ \\\\__ \\",
      "|_|_\\___|_| |___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info),
           "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦",
           nomes_temas[tema_ativo], GAME_VERSION);
  int info_len = visible_strlen(header_info);
  int pad_left = (126 - info_len) / 2;
  int pad_right = 126 - info_len - pad_left;
  printf("      ║");
  for (int i = 0; i < pad_left; i++)
    printf(" ");
  printf("%s", header_info);
  for (int i = 0; i < pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║    ┌────────────────────────────┐    "
         "┌────────────────────────────────────────────────────────────────────"
         "──────────────┐    ║\n");
  printf("      ║    │      [ BASE DO JOGO ]      │    │                       "
         "       REFERÊNCIAS UTILIZADAS                              │    ║\n");
  printf("      ║    ├────────────────────────────┤    "
         "├────────────────────────────────────────────────────────────────────"
         "──────────────┤    ║\n");

  const char *left_col[21] = {
      "                            ", "        ┌───┬───┬───┐       ",
      "        │ X │ O │ X │       ", "        ├───┼───┼───┤       ",
      "        │ O │ X │ O │       ", "        ├───┼───┼───┤       ",
      "        │ X │   │ O │       ", "        └───┴───┴───┘       ",
      "                            ", "    Estratégia, lógica      ",
      "    e tomada de decisão.    ", "                            ",
      "       [ OBSERVAÇÃO ]       ", "                            ",
      "  O Jogo da  Veia é um      ", "  exemplo clássico de       ",
      "  estratégia perfeita.      ", "                            ",
      "  Com as jogadas certas,    ", "  é possível evitar a       ",
      "  derrota.                  "};

  const char *right_col_raw[21] = {
      "  As fontes abaixo foram utilizadas como apoio para compreender as "
      "regras,",
      "  a lógica do jogo, estratégias básicas e conceitos de implementação.",
      "",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "                               \033[7m FONTES PRINCIPAIS \033[0m",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "  [1] Wikipedia — pt.wikipedia.org/wiki/Jogo_da_ Veia",
      "  [2] Wikipedia — en.wikipedia.org/wiki/Tic-tac-toe",
      "  [3] GeeksforGeeks — geeksforgeeks.org/tic-tac-toe-game/",
      "  [4] Stanford Encyclopedia — plato.stanford.edu/entries/game-theory/",
      "  [5] Livro — The Compleat Strategyst (Autor: J. D. Williams)",
      "",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "                                \033[7m NOTA DO PROJETO \033[0m",
      "────────────────────────────────────────────────────────────────────────"
      "──────────",
      "  Este projeto usa o Jogo da  Veia como prática acadêmica para "
      "exercitar lógica,",
      "  estruturas condicionais, repetição, menus, organização de código e",
      "  interação com o usuário.",
      "",
      "",
      ""};

  char right_col[21][300];
  for (int r = 0; r < 21; r++) {
    char padding[100] = "";
    int len = visible_strlen(right_col_raw[r]);
    int pad_size = 82 - len;
    if (pad_size < 0)
      pad_size = 0;
    for (int p = 0; p < pad_size; p++)
      padding[p] = ' ';
    padding[pad_size] = '\0';

    if (r == 4 || r == 13) {
      sprintf(right_col[r], "%s\033[0m%s%s", right_col_raw[r],
              temas[tema_ativo], padding);
    } else {
      sprintf(right_col[r], "%s%s", right_col_raw[r], padding);
    }
  }

  for (int r = 0; r < 21; r++) {
    char left_colored[300];
    if (r == 12) {
      sprintf(left_colored, "\033[7m       [ OBSERVAÇÃO ]       \033[0m%s",
              temas[tema_ativo]);
      printf("      ║    │%s│    │%s│    ║\n", left_colored, right_col[r]);
    } else {
      printf("      ║    │%s│    │%s│    ║\n", left_col[r], right_col[r]);
    }
  }

  printf("      ║    └────────────────────────────┘    "
         "└────────────────────────────────────────────────────────────────────"
         "──────────────┘    ║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Pressione \033[7m ENTER \033[0m%s, \033[7m ESC \033[0m%s "
           "ou \033[7m Q \033[0m%s para retornar ao menu principal",
           temas[tema_ativo], temas[tema_ativo], temas[tema_ativo]);
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaTemas(int preview_tema) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {
      " _____ ___ __  __   _   ___ ", "|_   _| __|  \\/  | /_\\ / __|",
      "  | | | _|| |\\/| |/ _ \\\\__ \\", "  |_| |___|_|  |_/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info),
           "✦  TEMA ATIVO: %s  │  VERSÃO DO JOGO: %s  ✦",
           nomes_temas[tema_ativo], GAME_VERSION);
  int info_len = visible_strlen(header_info);
  int pad_left = (126 - info_len) / 2;
  int pad_right = 126 - info_len - pad_left;
  printf("      ║");
  for (int i = 0; i < pad_left; i++)
    printf(" ");
  printf("%s", header_info);
  for (int i = 0; i < pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *instr = _(
      "Use ↑ ↓ ← → para navegar entre os temas. Pressione ENTER para aplicar.");
  int instr_len = visible_strlen(instr);
  int instr_pad_left = (126 - instr_len) / 2;
  int instr_pad_right = 126 - instr_len - instr_pad_left;
  printf("      ║");
  for (int i = 0; i < instr_pad_left; i++)
    printf(" ");
  printf("%s", instr);
  for (int i = 0; i < instr_pad_right; i++)
    printf(" ");
  printf("║\n");

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────┬───────────────────────────────"
         "─────┬────────────────────────────────────────────┐    ║\n");

  char grid[19][3][300];
  for (int r = 0; r < 19; r++) {
    for (int c = 0; c < 3; c++) {
      int width = (c == 2) ? 42 : 36;
      char padding[100] = "";
      for (int p = 0; p < width; p++)
        padding[p] = ' ';
      padding[width] = '\0';
      strcpy(grid[r][c], padding);
    }
  }

  for (int c = 0; c < 3; c++) {
    int start_idx, end_idx;
    if (c == 0) {
      start_idx = 0;
      end_idx = 16;
    } else if (c == 1) {
      start_idx = 17;
      end_idx = 33;
    } else {
      start_idx = 34;
      end_idx = 49;
    }

    int current_row = 0;
    for (int i = start_idx; i <= end_idx; i++) {
      int width = (c == 2) ? 42 : 36;
      if (i == preview_tema) {
        int pad_left = (width - 34) / 2;
        int pad_right = width - 34 - pad_left;
        char p_l[20] = "", p_r[20] = "";
        for (int p = 0; p < pad_left; p++) {
          p_l[p] = ' ';
        }
        p_l[pad_left] = '\0';
        for (int p = 0; p < pad_right; p++) {
          p_r[p] = ' ';
        }
        p_r[pad_right] = '\0';

        sprintf(grid[current_row++][c],
                "%s\033[7m╔════════════════════════════════╗\033[0m%s%s", p_l,
                temas[tema_ativo], p_r);

        char name_buf[50];
        snprintf(name_buf, sizeof(name_buf), "%-21.21s", nomes_temas[i]);
        sprintf(grid[current_row++][c], "%s\033[7m║ ▶ %02d - %s ◀ ║\033[0m%s%s",
                p_l, i + 1, name_buf, temas[tema_ativo], p_r);

        sprintf(grid[current_row++][c],
                "%s\033[7m╚════════════════════════════════╝\033[0m%s%s", p_l,
                temas[tema_ativo], p_r);
      } else {
        if (i < num_temas) {
          char temp[100];
          snprintf(temp, sizeof(temp), "%02d - %s", i + 1, nomes_temas[i]);
          sprintf(grid[current_row++][c], "  %-*.*s  ", width - 4, width - 4,
                  temp);
        } else {
          current_row++;
        }
      }
    }
  }

  for (int r = 0; r < 19; r++) {
    printf("      ║    │%s│%s│%s│    ║\n", grid[r][0], grid[r][1], grid[r][2]);
  }

  printf("      ║    "
         "└────────────────────────────────────┴───────────────────────────────"
         "─────┴────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ SELEÇÃO DE TEMA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Use ↑ ↓ ← → para navegar     • ENTER para aplicar     • "
           "00, Q ou ESC para voltar ao menu principal");
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaSaveLoad(int selected_option) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {"  ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
                       " / __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
                       "| (_ | _||   / _|| .` | (__ | | / _ \\__ \\",
                       " \\___|___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};

  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }
  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("SALVAR / CARREGAR JOGO"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");
  printf("      ║    │                                  GERENCIAR PROGRESSO    "
         "                                                           │    ║\n");
  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf(
      "      ║    │  Use esta tela para salvar a partida atual, continuar um "
      "jogo salvo ou apagar dados antigos do sistema.            │    ║\n");
  printf(
      "      ║    │  Assim você pode pausar e voltar depois sem perder o "
      "progresso.                                                    │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                      OPÇÕES DISPONÍVEIS "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  const char *options[] = {"JOGAR",
                           "INSTRUÇÕES OFICIAIS",
                           "CRÉDITOS DO PROJETO",
                           "REFERÊNCIAS TÉCNICAS",
                           "SELEÇÃO DE TEMA",
                           "NUVEM: SAVE / LOAD",
                           "RANKING GLOBAL",
                           "SAIR DO SISTEMA",
                           "IDIOMA"};

  for (int i = 0; i < 3; i++) {
    if (selected_option == i + 1) {
      printf("      ║    │                                   "
             "\033[7m╔════════════════════════════════════════════╗\033[0m%s   "
             "                                │    ║\n",
             temas[tema_ativo]);

      char line_buf[100];
      snprintf(line_buf, sizeof(line_buf), "║        ▶  %-26.26s  ◀        ║",
               options[i]);
      printf("      ║    │                                   "
             "\033[7m%s\033[0m%s                                   │    ║\n",
             line_buf, temas[tema_ativo]);

      printf("      ║    │                                   "
             "\033[7m╚════════════════════════════════════════════╝\033[0m%s   "
             "                                │    ║\n",
             temas[tema_ativo]);
    } else {
      int len = visible_strlen(options[i]);
      int p = (116 - len) / 2;
      printf("      ║    │");
      for (int j = 0; j < p; j++)
        printf(" ");
      printf("%s", options[i]);
      for (int j = 0; j < 116 - len - p; j++)
        printf(" ");
      printf("│    ║\n");
    }
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
  }

  // Add two blank lines to maintain the same total layout height as when there
  // were 4 options
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                      AVISO IMPORTANTE   "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf(
      "      ║    │  Ao deletar um jogo salvo, o progresso armazenado será "
      "removido permanentemente.                                   │    ║\n");
  printf("      ║    │  Essa ação não poderá ser desfeita.                     "
         "                                                           │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Use ↑ ↓ para navegar     • ENTER para selecionar     • 0, "
           "Q ou ESC para voltar ao Menu Principal");
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaEscolherSalvamento(int selected) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
                       "/ __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
                       "| (_ | _||   / _|| .` | (__ | | / _ \\__ \\",
                       " \\___|___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("SALVAR PARTIDA ATUAL"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");
  printf("      ║    │                                  ESCOLHER SALVAMENTO    "
         "                                                           │    ║\n");
  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf(
      "      ║    │  Você deseja substituir um salvamento já existente ou "
      "criar um novo arquivo?                                       │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  if (selected == 1) {
    printf("      ║    │                         "
           "\033[7m╔════════════════════════════════════════════════╗\033[0m%s "
           "                                        │    ║\n",
           temas[tema_ativo]);
    printf("      ║    │                         \033[7m║       ▶  [1] "
           "SOBRESCREVER SALVAMENTO  ◀       ║\033[0m%s                        "
           "                 │    ║\n",
           temas[tema_ativo]);
    printf("      ║    │                         "
           "\033[7m╚════════════════════════════════════════════════╝\033[0m%s "
           "                                        │    ║\n",
           temas[tema_ativo]);
  } else {
    printf("      ║    │                                 [1] SOBRESCREVER "
           "SALVAMENTO                                                        "
           "│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  if (selected == 2) {
    printf("      ║    │                         "
           "\033[7m╔════════════════════════════════════════════════╗\033[0m%s "
           "                                        │    ║\n",
           temas[tema_ativo]);
    printf("      ║    │                         \033[7m║         ▶  [0] CRIAR "
           "NOVO SALVAMENTO  ◀        ║\033[0m%s                               "
           "          │    ║\n",
           temas[tema_ativo]);
    printf("      ║    │                         "
           "\033[7m╚════════════════════════════════════════════════╝\033[0m%s "
           "                                        │    ║\n",
           temas[tema_ativo]);
  } else {
    printf("      ║    │                                 [0] CRIAR NOVO "
           "SALVAMENTO                                                         "
           " │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                      ATENÇÃO            "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf(
      "      ║    │  Ao sobrescrever um arquivo, os dados antigos daquele "
      "salvamento serão substituídos pela partida atual.            │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Use ↑ ↓ para navegar     • ENTER para confirmar     • ESC "
           "para cancelar");
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirSucessoSalvamento(const char *nomeSalvamento) {
  limparTela();
  aplicarTema(tema_ativo);
  printf("\a");

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
                       "/ __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
                       "| (_ | _||   / _|| .` | (__ | | / _ \\__ \\",
                       " \\___|___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("JOGO SALVO"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    │                                  SALVAMENTO CONCLUÍDO   "
         "                                                           │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    │                         "
         "\033[7m╔════════════════════════════════════════════════╗\033[0m%s   "
         "                                      │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                         \033[7m║          JOGO SALVO "
         "COM SUCESSO!               ║\033[0m%s                                "
         "         │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                         "
         "\033[7m╚════════════════════════════════════════════════╝\033[0m%s   "
         "                                      │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  char name_buf[100];
  snprintf(name_buf, sizeof(name_buf), "Arquivo criado: %-35.35s",
           nomeSalvamento);
  printf("      ║    │                         %-83s│    ║\n", name_buf);
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    │  Sua partida foi armazenada. Você poderá continuar "
         "exatamente de onde parou.                                       │    "
         "║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 =
      _("                              Pressione ENTER para continuar...");
  int p = (126 - visible_strlen(ctrl1)) / 2;
  printf("      ║");
  for (int i = 0; i < p; i++)
    printf(" ");
  printf("%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1) - p; i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}

void exibirTelaNovoSalvamento(void) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
                       "/ __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
                       "| (_ | _||   / _|| .` | (__ | | / _ \\__ \\",
                       " \\___|___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
           _("NOVO SALVAMENTO"));
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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");
  printf("      ║    │                                   CRIAR NOVO SALVAMENTO "
         "                                                           │    ║\n");
  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    │  Você escolheu criar um novo arquivo de progresso.      "
         "                                                           │    ║\n");
  printf(
      "      ║    │  Escolha um nome curto para identificar esta partida "
      "depois.                                                       │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                      NOME DO SALVAMENTO "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  printf("      ║    │                         "
         "\033[7m╔════════════════════════════════════════════════╗\033[0m%s   "
         "                                      │    ║\n",
         temas[tema_ativo]);
  printf("      ║    │                         \033[7m║\033[0m%s               "
         "                                 \033[7m║\033[0m%s                   "
         "                      │    ║\n",
         temas[tema_ativo], temas[tema_ativo]);
  printf("      ║    │                         \033[7m║\033[0m%s       Digite "
         "o nome da nova partida:           \033[7m║\033[0m%s                  "
         "                       │    ║\n",
         temas[tema_ativo], temas[tema_ativo]);
  printf("      ║    │                         \033[7m║\033[0m%s               "
         "                                 \033[7m║\033[0m%s                   "
         "                      │    ║\n",
         temas[tema_ativo], temas[tema_ativo]);
  printf("      ║    │                         "
         "\033[7m╚════════════════════════════════════════════════╝\033[0m%s   "
         "                                      │    ║\n",
         temas[tema_ativo]);

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │                                      INFORMAÇÃO         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");
  printf("      ║    │  O salvamento armazenará o estado atual da partida para "
         "que você possa continuar mais tarde.                       │    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  snprintf(ctrl2, sizeof(ctrl2),
           "      • Digite um nome e pressione ENTER para salvar     • ESC "
           "para cancelar");
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");

  // Move cursor up 14 lines to inside the input box, right after "Digite o nome
  // da nova partida: "
  printf("\033[14A\033[76G");
}

void exibirTelaSavesList(SaveInfo *saves, int num_saves, int selected_idx,
                         int mode) {
  limparTela();
  aplicarTema(tema_ativo);

  for (int i = 0; i < 5; i++)
    printf("\n");

  printf("      "
         "╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╗\n");
  printf("      ║                                                              "
         "                                                                ║\n");

  const char *art[] = {" ___ ___ ___ ___ _  _  ___ ___   _   ___ ",
                       "/ __| __| _ \\ __| \\| |/ __|_ _| /_\\ / __|",
                       "| (_ | _||   / _|| .` | (__ | | / _ \\__ \\",
                       " \\___|___|_|_\\___|_|\\_|\\___|___/_/ \\_\\___/"};
  for (int i = 0; i < 4; i++) {
    int len = visible_strlen(art[i]);
    int p = (126 - len) / 2;
    printf("      ║");
    for (int j = 0; j < p; j++)
      printf(" ");
    printf("%s", art[i]);
    for (int j = 0; j < 126 - len - p; j++)
      printf(" ");
    printf("║\n");
  }

  printf("      ║                                                              "
         "                                                                ║\n");

  char header_info[200];
  if (mode == 0) {
    snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
             _("SOBRESCREVER SALVAMENTO"));
  } else if (mode == 1) {
    snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
             _("CARREGAR SALVAMENTO"));
  } else {
    snprintf(header_info, sizeof(header_info), "v%s • %s", GAME_VERSION,
             _("EXCLUIR SALVAMENTO"));
  }

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

  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      ║    "
         "┌────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┐    ║\n");

  if (mode == 0) {
    printf("      ║    │                               SELECIONAR SALVAMENTO "
           "EXISTENTE                                                      │   "
           " ║\n");
  } else if (mode == 1) {
    printf(
        "      ║    │                                  SALVAMENTOS DISPONÍVEIS "
        "                                                          │    ║\n");
  } else {
    printf(
        "      ║    │                                SALVAMENTOS DISPONÍVEIS "
        "PARA EXCLUSÃO                                               │    ║\n");
  }

  printf("      ║    "
         "├────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┤    ║\n");
  printf("      ║    │                                                         "
         "                                                           │    ║\n");

  if (mode == 0) {
    printf("      ║    │  Escolha um salvamento da lista para substituir pelos "
           "dados da partida atual.                                      │    "
           "║\n");
  } else if (mode == 1) {
    printf(
        "      ║    │  Escolha uma partida salva para continuar de onde você "
        "parou.                                                      │    ║\n");
  } else {
    printf(
        "      ║    │  Selecione um salvamento para remover do sistema. Essa "
        "ação apagará o progresso escolhido.                         │    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  if (mode == 0) {
    printf("      ║    │                                      SALVAMENTOS "
           "DISPONÍVEIS                                                       "
           "│    ║\n");
  } else {
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
  }

  if (mode == 0) {
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │                         "
           "┌──────────────────────────────────────────────────────┐           "
           "                        │    ║\n");
  }

  if (num_saves == 0) {
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf(
        "      ║    │                         [ NENHUM SALVAMENTO ENCONTRADO ] "
        "                                                          │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    if (mode == 0)
      printf("      ║    │                         "
             "└──────────────────────────────────────────────────────┘         "
             "                          │    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
  } else {
    int start_i = 0;
    if (selected_idx >= 3) {
      start_i = selected_idx - 1;
      if (start_i + 3 >= num_saves) {
        start_i = num_saves - 3;
      }
    }
    if (start_i < 0)
      start_i = 0;
    int end_i = start_i + 3;
    if (end_i > num_saves)
      end_i = num_saves;

    for (int i = start_i; i < end_i; i++) {
      if (mode == 0) {
        if (i == selected_idx) {
          char l[200];
          snprintf(l, sizeof(l), "│ \033[7m▶ [%d]  %-40.40s \033[0m%s│", i + 1,
                   saves[i].save_name, temas[tema_ativo]);
          printf("      ║    │                         %s                      "
                 "             │    ║\n",
                 l);
        } else {
          printf("      ║    │                         │   [%d]  %-40.40s │    "
                 "                               │    ║\n",
                 i + 1, saves[i].save_name);
        }
        if (i < end_i - 1) {
          printf("      ║    │                         "
                 "├──────────────────────────────────────────────────────┤     "
                 "                              │    ║\n");
        } else {
          printf("      ║    │                         "
                 "└──────────────────────────────────────────────────────┘     "
                 "                              │    ║\n");
        }
      } else {
        if (i == selected_idx) {
          printf("      ║    │                    "
                 "\033["
                 "7m╔══════════════════════════════════════════════════════════"
                 "══════════╗\033[0m%s                        │    ║\n",
                 temas[tema_ativo]);
          char l1[200], l2[200];
          snprintf(l1, sizeof(l1), "║  ▶ [%d] %-15.15s  •  DATA: %-25.25s ◀  ║",
                   i + 1, saves[i].save_name, saves[i].timestamp);
          snprintf(l2, sizeof(l2),
                   "║      %s (%d)  vs  %s (%d)  │  Empates: %-15d ║",
                   saves[i].playerX, saves[i].winsX, saves[i].playerO,
                   saves[i].winsO, saves[i].ties);
          printf("      ║    │                    \033[7m%s\033[0m%s           "
                 "             │    ║\n",
                 l1, temas[tema_ativo]);
          printf("      ║    │                    \033[7m%s\033[0m%s           "
                 "             │    ║\n",
                 l2, temas[tema_ativo]);
          printf("      ║    │                    "
                 "\033["
                 "7m╚══════════════════════════════════════════════════════════"
                 "══════════╝\033[0m%s                        │    ║\n",
                 temas[tema_ativo]);
        } else {
          printf("      ║    │                    "
                 "╔════════════════════════════════════════════════════════════"
                 "════════╗                        │    ║\n");
          printf("      ║    │                    ║    [%d] %-15.15s  •  DATA: "
                 "%-25.25s    ║                        │    ║\n",
                 i + 1, saves[i].save_name, saves[i].timestamp);
          printf("      ║    │                    ║      %s (%d)  vs  %s (%d)  "
                 "│  Empates: %-15d ║                        │    ║\n",
                 saves[i].playerX, saves[i].winsX, saves[i].playerO,
                 saves[i].winsO, saves[i].ties);
          printf("      ║    │                    "
                 "╚════════════════════════════════════════════════════════════"
                 "════════╝                        │    ║\n");
        }
        printf("      ║    │                                                   "
               "                                                               "
               "  │    ║\n");
      }
    }
  }

  printf("      ║    "
         "│────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────│    ║\n");

  if (mode == 0) {
    printf(
        "      ║    │                                      ATENÇÃO             "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf("      ║    │  O salvamento selecionado será substituído e os dados "
           "antigos não poderão ser recuperados.                         │    "
           "║\n");
  } else if (mode == 1) {
    printf(
        "      ║    │                                      INFORMAÇÃO          "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │  Ao carregar uma partida, o jogo continuará exatamente "
        "com o tabuleiro e os jogadores salvos.                      │    ║\n");
  } else {
    printf(
        "      ║    │                                      AVISO IMPORTANTE    "
        "                                                          │    ║\n");
    printf("      ║    "
           "│──────────────────────────────────────────────────────────────────"
           "──────────────────────────────────────────────────│    ║\n");
    printf(
        "      ║    │                                                          "
        "                                                          │    ║\n");
    printf("      ║    │  Ao confirmar, o salvamento selecionado será excluído "
           "permanentemente.                                             │    "
           "║\n");
    printf(
        "      ║    │  Os dados da partida não poderão ser recuperados depois "
        "da exclusão.                                               │    ║\n");
  }

  printf("      ║    │                                                         "
         "                                                           │    ║\n");
  printf("      ║    "
         "└────────────────────────────────────────────────────────────────────"
         "────────────────────────────────────────────────┘    ║\n");
  printf("      ║                                                              "
         "                                                                ║\n");
  printf("      "
         "╠════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╣\n");

  const char *ctrl1 = _("      [ CONTROLES DA TELA ]");
  printf("      ║%s", ctrl1);
  for (int i = 0; i < 126 - visible_strlen(ctrl1); i++)
    printf(" ");
  printf("║\n");

  char ctrl2[400];
  if (mode == 0) {
    snprintf(ctrl2, sizeof(ctrl2),
             "      • Use ↑ ↓ para navegar     • ENTER para escolher um "
             "salvamento     • ESC para cancelar");
  } else if (mode == 1) {
    snprintf(ctrl2, sizeof(ctrl2),
             "      • Use ↑ ↓ para navegar     • ENTER para carregar     • 0, "
             "Q ou ESC para voltar ao Menu Principal");
  } else {
    snprintf(ctrl2, sizeof(ctrl2),
             "      • Use ↑ ↓ para navegar     • ENTER para selecionar     • "
             "0, Q ou ESC para voltar ao Menu Principal");
  }
  printf("      ║%s", ctrl2);
  for (int i = 0; i < 126 - visible_strlen(ctrl2); i++)
    printf(" ");
  printf("║\n");

  printf("      "
         "╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════════════════════════════════╝\n");
  printf("\033[0m");
}
