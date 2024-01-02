// Inclua os headers necessários
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

// limpar jogadas
void limpar(char casas[9])
{
   int i;
   for (i = 0; i < 9; i++)
   {
      casas[i] = ' ';
   }
}
// montando jogo da veia
void tabuleiro(char casas[9])
{
   int capa2();
   setlocale(LC_ALL, "Portuguese");
   system("cls");
   capa2();
   printf("\n");
   printf("\t %c | %c | %c \n", casas[0], casas[1], casas[2]);
   printf("\t --------- \n");
   printf("\t %c | %c | %c \n", casas[3], casas[4], casas[5]);
   printf("\t --------- \n");
   printf("\t %c | %c | %c \n", casas[6], casas[7], casas[8]);
   printf("\n");
}

// corpo do jogo da velha........................................................
void play()
{
   char casas[9];
   int capaplay(), veiacomputador();
   char opcao = 's', vez, vencedor, legenda(void), inicio(void);
   int countJogadas, jogada, xPlacar = 0, oPlacar = 0, jogador = 0, dificuldade = 0, empates = 0;
   while (jogador < 1 || jogador > 2)
   {
      vencedor = ' ';
      capaplay();
      printf("\n\n");
      printf("\t\t\tEscolha uma opcao: ");
      scanf("%i", &jogador);
      getchar();
      system("cls");

      if (jogador == 3)
      {
         system("cls");
         inicio();
      }
      if (jogador == 5)
      {
         system("cls");
         printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
      }
      if (jogador >= 6)
      {
         system("cls");
         printf("\nopção invalida!\n");
         system("pause");
         system("cls");
         play();
      }

      if (jogador == 2)
      {
         while (dificuldade < 1 || dificuldade > 2)
         {
            printf("\n");
            veiacomputador();
            printf("\tEscolha uma opcao: ");
            scanf("%i", &dificuldade);
            getchar();
            system("cls");
         }
      }
   }

   while (opcao == 's' || opcao == 'S')
   {
      countJogadas = 1;
      limpar(casas);
      tabuleiro(casas);
      legenda();
      printf("");
      printf("\nPLACAR X: %d\n", xPlacar);
      printf("PLACAR O: %d\n", oPlacar);
      while (countJogadas <= 9)
      {
         if (countJogadas % 2 != 0)
         {
            vez = 'X';
         }
         else
         {
            vez = 'O';
         }
         printf("\nVEZ: %c\n", vez);
         switch (jogador)
         {
         case 1: // amigo
            printf("Deseja jogar em qual casa? ");
            scanf("%d", &jogada);
            getchar();
            switch (vez)
            {
            case 'X':
               if (jogada < 1 || jogada > 9)
               {
                  printf("Jogada %d invalida. Voce so pode marcar de 1 a 9\n", jogada);
                  getchar();
                  jogada = 0;
               }
               else if (casas[jogada - 1] == 'O' || casas[jogada - 1] == 'X')
               {
                  printf("Casa ocupada. Jogada invalida\n");
                  getchar();
                  jogada = 0;
               }
               else
               {
                  casas[jogada - 1] = 'X';
                  countJogadas++;
               }
               break;

            case 'O':
               if (jogada < 1 || jogada > 9)
               {
                  printf("Jogada %d invalida. Voce so pode marcar de 1 a 9\n", jogada);
                  getchar();
                  jogada = 0;
               }
               else if (casas[jogada - 1] == 'O' || casas[jogada - 1] == 'X')
               {
                  printf("Casa ocupada. Jogada invalida\n");
                  getchar();
                  jogada = 0;
               }
               else
               {
                  casas[jogada - 1] = 'O';
                  countJogadas++;
               }
               break;
            }
            break;

         case 2: // computador
            switch (dificuldade)
            {
            case 1:
               if (vez == 'O')
               {
                  while (casas[jogada - 1] != ' ')
                  {
                     srand((unsigned)time(NULL));
                     jogada = rand() % 10;
                  }
                  casas[jogada - 1] = 'O';
                  countJogadas++;
               }
               else
               {
                  printf("Deseja jogar em qual casa? ");
                  scanf("%d", &jogada);
                  getchar();

                  if (jogada < 1 || jogada > 9)
                  {
                     printf("Jogada %d invalida. Voce so pode marcar de 1 a 9\n", jogada);
                     getchar();
                     jogada = 0;
                  }
                  else if (casas[jogada - 1] == 'O' || casas[jogada - 1] == 'X')
                  {
                     printf("Casa ocupada. Jogada invalida\n");
                     getchar();
                     jogada = 0;
                  }
                  else
                  {
                     casas[jogada - 1] = 'X';
                     countJogadas++;
                  }
               }
               break;

            case 2:
               if (vez == 'X')
               {
                  printf("Deseja jogar em qual casa? \n");
                  scanf("%d", &jogada);
                  getchar();

                  if (jogada < 1 || jogada > 9)
                  {
                     printf("Jogada %d invalida. Voce so pode marcar de 1 a 9\n", jogada);
                     getchar();
                     jogada = 0;
                  }
                  else if (casas[jogada - 1] == 'O' || casas[jogada - 1] == 'X')
                  {
                     printf("Casa ocupada. Jogada invalida\n");
                     getchar();
                     jogada = 0;
                  }
                  else
                  {
                     casas[jogada - 1] = 'X';
                     countJogadas++;
                  }
               }
               else
               {
                  if (casas[0] == 'X' && casas[1] == ' ' && casas[2] == 'X')
                  {
                     jogada = 2;
                  }
                  else if (casas[3] == 'X' && casas[4] == ' ' && casas[5] == 'X')
                  {
                     jogada = 5;
                  }
                  else if (casas[6] == 'X' && casas[7] == ' ' && casas[8] == 'X')
                  {
                     jogada = 9;
                  }

                  else if (casas[0] == 'X' && casas[1] == 'X' && casas[2] == ' ')
                  {
                     jogada = 3;
                  }
                  else if (casas[3] == 'X' && casas[4] == 'X' && casas[5] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[6] == 'X' && casas[7] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }

                  else if (casas[2] == 'X' && casas[4] == 'X' && casas[6] == ' ')
                  {
                     jogada = 7;
                  }
                  else if (casas[2] == ' ' && casas[4] == 'X' && casas[6] == 'X')
                  {
                     jogada = 3;
                  }
                  else if (casas[2] == 'X' && casas[4] == ' ' && casas[6] == ' ')
                  {
                     jogada = 5;
                  }

                  else if (casas[0] == ' ' && casas[4] == 'X' && casas[8] == 'X')
                  {
                     jogada = 1;
                  }
                  else if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }
                  else if (casas[0] == 'X' && casas[4] == ' ' && casas[8] == 'X')
                  {
                     jogada = 5;
                  }

                  else if (casas[0] == 'X' && casas[1] == ' ' && casas[2] == ' ')
                  {
                     jogada = 2;
                  }
                  else if (casas[3] == ' ' && casas[4] == 'X' && casas[5] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[6] == ' ' && casas[7] == ' ' && casas[8] == 'X')
                  {
                     jogada = 8;
                  }

                  else if (casas[3] == 'X' && casas[4] == 'X' && casas[5] == ' ')
                  {
                     jogada = 6;
                  }
                  else if (casas[6] == 'X' && casas[7] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }

                  else if (casas[0] == 'X' && casas[3] == 'X' && casas[6] == ' ')
                  {
                     jogada = 7;
                  }
                  else if (casas[1] == 'X' && casas[4] == 'X' && casas[7] == ' ')
                  {
                     jogada = 8;
                  }
                  else if (casas[2] == 'X' && casas[5] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }

                  else if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }
                  else if (casas[2] == 'X' && casas[4] == 'X' && casas[7] == ' ')
                  {
                     jogada = 7;
                  }

                  else if (casas[0] == ' ' && casas[3] == 'X' && casas[6] == 'X')
                  {
                     jogada = 1;
                  }
                  else if (casas[1] == ' ' && casas[4] == 'X' && casas[7] == 'X')
                  {
                     jogada = 2;
                  }
                  else if (casas[2] == ' ' && casas[5] == 'X' && casas[8] == 'X')
                  {
                     jogada = 3;
                  }

                  else if (casas[2] == ' ' && casas[4] == 'X' && casas[6] == 'X')
                  {
                     jogada = 1;
                  }
                  else if (casas[2] == 'X' && casas[4] == ' ' && casas[7] == 'X')
                  {
                     jogada = 5;
                  }
                  else if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }

                  else if (casas[2] == ' ' && casas[4] == ' ' && casas[6] == 'X')
                  {
                     jogada = 1;
                  }
                  else if (casas[2] == 'X' && casas[4] == ' ' && casas[7] == ' ')
                  {
                     jogada = 4;
                  }
                  else if (casas[0] == ' ' && casas[4] == 'X' && casas[8] == ' ')
                  {
                     jogada = 7;
                  }

                  else if (casas[0] == ' ' && casas[3] == ' ' && casas[6] == 'X')
                  {
                     jogada = 1;
                  }
                  else if (casas[1] == ' ' && casas[4] == 'X' && casas[7] == ' ')
                  {
                     jogada = 2;
                  }
                  else if (casas[2] == ' ' && casas[5] == ' ' && casas[8] == 'X')
                  {
                     jogada = 5;
                  }
                  else if (casas[0] == 'X' && casas[1] == ' ' && casas[2] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[0] == ' ' && casas[1] == 'X' && casas[2] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[0] == ' ' && casas[1] == ' ' && casas[2] == 'X')
                  {
                     jogada = 5;
                  }

                  else if (casas[3] == 'X' && casas[4] == ' ' && casas[5] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[3] == ' ' && casas[4] == 'X' && casas[5] == ' ')
                  {
                     jogada = 1;
                  }
                  else if (casas[3] == ' ' && casas[4] == ' ' && casas[5] == 'X')
                  {
                     jogada = 7;
                  }

                  else if (casas[6] == 'X' && casas[7] == ' ' && casas[8] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[6] == ' ' && casas[7] == 'X' && casas[8] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[6] == ' ' && casas[7] == ' ' && casas[8] == 'X')
                  {
                     jogada = 5;
                  }

                  else if (casas[0] == 'X' && casas[3] == ' ' && casas[6] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[0] == ' ' && casas[3] == 'X' && casas[6] == ' ')
                  {
                     jogada = 1;
                  }
                  else if (casas[0] == ' ' && casas[3] == ' ' && casas[6] == 'X')
                  {
                     jogada = 5;
                  }

                  else if (casas[1] == 'X' && casas[4] == ' ' && casas[7] == ' ')
                  {
                     jogada = 5;
                  }
                  else if (casas[1] == ' ' && casas[4] == 'X' && casas[7] == ' ')
                  {
                     jogada = 1;
                  }
                  else if (casas[1] == ' ' && casas[4] == ' ' && casas[7] == 'X')
                  {
                     jogada = 5;
                  }

                  else if (casas[2] == 'X' && casas[5] == ' ' && casas[8] == ' ')
                  {
                     jogada = 6;
                  }
                  else if (casas[2] == ' ' && casas[5] == 'X' && casas[8] == ' ')
                  {
                     jogada = 9;
                  }
                  else if (casas[2] == ' ' && casas[5] == ' ' && casas[8] == 'X')
                  {
                     jogada = 5;
                  }

                  /////               ??????????? /////////////////

                  while (casas[jogada - 1] != ' ')
                  {
                     srand((unsigned)time(NULL));
                     jogada = rand() % 10;
                  }

                  casas[jogada - 1] = 'O';
                  countJogadas++;
               }
               break;
            }

            break;
         }

         // --------------------------------- XXXXXX ---------------------------
         if (casas[0] == 'X' && casas[1] == 'X' && casas[2] == 'X')
         { // X LINHA 1
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[3] == 'X' && casas[4] == 'X' && casas[5] == 'X')
         { // X LINHA 2
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[6] == 'X' && casas[7] == 'X' && casas[8] == 'X')
         { // X LINHA 3
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[0] == 'X' && casas[3] == 'X' && casas[6] == 'X')
         { // X COLUNA 1
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[1] == 'X' && casas[4] == 'X' && casas[7] == 'X')
         { // X COLUNA 2
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[2] == 'X' && casas[5] == 'X' && casas[8] == 'X')
         { // X COLUNA 3
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[0] == 'X' && casas[4] == 'X' && casas[8] == 'X')
         { // X DIAGONAL 1
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         else if (casas[2] == 'X' && casas[4] == 'X' && casas[6] == 'X')
         { // X DIAGONAL 2
            vencedor = 'X';
            xPlacar++;
            countJogadas = 10;
         }
         // ----------------------------------- OOOOOO -------------------------------------------
         else if (casas[0] == 'O' && casas[1] == 'O' && casas[2] == 'O')
         { // O LINHA 1
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[3] == 'O' && casas[4] == 'O' && casas[5] == 'O')
         { // O LINHA 2
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[6] == 'O' && casas[7] == 'O' && casas[8] == 'O')
         { // O LINHA 3
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[0] == 'O' && casas[3] == 'O' && casas[6] == 'O')
         { // O COLUNA 1
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[1] == 'O' && casas[4] == 'O' && casas[7] == 'O')
         { // O COLUNA 2
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[2] == 'O' && casas[5] == 'O' && casas[8] == 'O')
         { // O COLUNA 3
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[0] == 'O' && casas[4] == 'O' && casas[8] == 'O')
         { // O DIAGONAL 1
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         else if (casas[2] == 'O' && casas[4] == 'O' && casas[6] == 'O')
         { // O DIAGONAL 2
            vencedor = 'O';
            oPlacar++;
            countJogadas = 10;
         }
         tabuleiro(casas);
         legenda();
         printf("");
         printf("\nPLACAR X: %d\n", xPlacar);
         printf("PLACAR O: %d\n", oPlacar);
      }
      if (vencedor == 'X')
      {
         printf("\t------------------------\n\tJOGADOR X VENCEU\n\t-----------------------\n");
      }
      else if (vencedor == 'O')
      {
         printf("\t----------------------\n\tJOGADOR O VENCEU\n\t------------------------\n");
      }
      else
      {
         printf("\t------------------------\n\tNENHUM JOGADOR VENCEU\n\t------------------------\n");
      }
      int jogar, inicio(void), menuplayfim();
      menuplayfim();
      printf("/n");
      printf("\t\t\t\t\tDigite sua opção desejada: ");
      scanf("%d", &jogar);
      if (jogar == 1)
      {
         system("cls");
         play();
      }
      if (jogar == 2)
      {
         system("cls");
         inicio();
      }
      if (jogar >= 3)
      {
         system("cls");
         printf("\nopção invalida!\n");
         system("pause");
         system("cls");
         menuplayfim();
      }
   }
}

// instrucoes....................................................................
void instrucoes(void)
{
   int jogar, inicio(void);
   setlocale(LC_ALL, "Portuguese");
   printf("_______________________________________________________________________________________________________ \n");
   printf("|                                                                                                      |\n");
   printf("|   LEGENDA  |                        INSTRU�OES                                                       |\n");
   printf("|    7|8|9   |   O tabuleiro  é uma matriz  de três linhas por trêss colunas                            |\n");
   printf("|    4|5|6   |   O tabuleiro  ês uma matriz  de trêss linhas por trêss colunas                            |\n");
   printf("|    3|2|1   |   Dois jogadores escolhem uma marcação cada um, geralmente um circulo (O) e um xis (X)  | \n");
   printf("|                                                                                                      |\n");
   printf("|______________________________________________________________________________________________________|\n");
   printf("|                                                                                                      |\n");
   printf("|                                                                                                      |\n");
   printf("|                                 MENU : 1 - Play | 2 - Voltar | 3 - Sair                              |\n");
   printf("|                                                                                                      |\n");
   printf("|______________________________________________________________________________________________________|\n");
   printf("\n\n");
   printf("\t\t\t\tOpção: ");
   scanf("%d", &jogar);
   if (jogar == 1)
   {
      system("cls");
      play();
   }
   if (jogar == 2)
   {
      system("cls");
      inicio();
   }
   if (jogar == 3)
   {
      system("cls");
      printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
   }
   if (jogar >= 4)
   {
      system("cls");
      printf("\nopção invalida!\n");
      system("pause");
      system("cls");
      instrucoes();
   }
}

// creditos......................................................................
void creditos(void)
{
   int jogar, inicio(void);
   setlocale(LC_ALL, "Portuguese");
   printf("\t\t\t\t____________________________________________________\n");
   printf("\t\t\t\t|                                                   |\n");
   printf("\t\t\t\t|                                                   |\n ");
   printf("\t\t\t\t|             Curso:ciencias da computação          |\n");
   printf("\t\t\t\t|             Prova do Douglas - jogo veia          |\n");
   printf("\t\t\t\t|             Nome: Stella Karolina Nunes           |\n");
   printf("\t\t\t\t|             Matricula: 20223834810                |\n");
   printf("\t\t\t\t|                                                   |\n");
   printf("\t\t\t\t|___________________________________________________|\n");
   printf("\t\t\t\t|                                                   |\n");
   printf("\t\t\t\t|                          MENU                     |\n");
   printf("\t\t\t\t|                                                   |\n");
   printf("\t\t\t\t|             1 - Play | 2 - Voltar | 3 - Sair      |\n");
   printf("\t\t\t\t|                                                   |\n");
   printf("\t\t\t\t|___________________________________________________|\n");
   printf("\n\n");
   printf("\t\t\t\tOpção: ");
   scanf("%d", &jogar);
   if (jogar == 1)
   {
      system("cls");
      play();
   }
   if (jogar == 2)
   {
      system("cls");
      inicio();
   }
   if (jogar == 3)
   {
      system("cls");
      printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
   }
   if (jogar >= 4)
   {
      system("cls");
      printf("\nopção invalida!\n");
      system("pause");
      system("cls");
      creditos();
   }
}

// tela principal................................................................
void inicio(void)
{
   int opcao, referencia(void), capadojogoveia(void), Avaliacao(void);
   setlocale(LC_ALL, "Portuguese");
   capadojogoveia();
   printf("\n\n");
   printf("Digite a sua opcao: ");
   scanf("%d", &opcao);

   if (opcao == 1)
   {
      system("cls");
      play();
   }
   if (opcao == 2)
   {
      system("cls");
      instrucoes();
   }
   if (opcao == 3)
   {
      system("cls");
      creditos();
   }
   if (opcao == 4)
   {
      system("cls");
      referencia();
   }
   if (opcao == 5)
   {
      system("cls");
      printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
   }
   if (opcao >= 6)
   {
      system("cls");
      printf("\nopção invalida!\n");
      system("pause");
      system("cls");
      inicio();
   }
}

// referencia.............................................................................................
void referencia(void)
{
   int jogar, inicio(void);
   setlocale(LC_ALL, "Portuguese");
   printf("\t\t______________________________________________________________________________________\n");
   printf("\t\t|                                                                                    |\n");
   printf("\t\t|                                   Referencia                                       |\n");
   printf("\t\t|                  https://www.bigmae.com/regras-jogo-da-velha                       |\n"); // regras
   printf("\t\t|                           https://github.com/samuelCupertino                       |\n"); // desenho
   printf("\t\t|                                                                                    |\n");
   printf("\t\t|____________________________________________________________________________________|\n");
   printf("\t\t|                                                                                    |\n");
   printf("\t\t|                                                                                    |\n");
   printf("\t\t|                      MENU:   1 - Play | 2 - Voltar | 3 - Sair                      |\n");
   printf("\t\t|                                                                                    |\n");
   printf("\t\t|____________________________________________________________________________________|\n");
   printf("\n\n");
   printf("\t\t\t\tOpção: ");
   scanf("%d", &jogar);
   if (jogar == 1)
   {
      system("cls");
      play();
   }
   if (jogar == 2)
   {
      system("cls");
      inicio();
   }
   if (jogar == 3)
   {
      system("cls");
      printf("\nObrigado por utilizar nosso programa! Ate mais!\n");
   }
   if (jogar >= 4)
   {
      system("cls");
      printf("\nopção invalida!\n");
      system("pause");
      system("cls");
      referencia();
   }
}

// programa principal............................................................
int main()
{
   setlocale(LC_ALL, "Portuguese");
   system("title Jogo da velha - Prova do Douglas");
   system("Color 0A");
   inicio();
   printf("\n\n\n");
   system("pause");
   return 0;
}

///////voidsssss///////////

void pause()
{
   system("pause");
}

void limpar()
{
   system("cls");
}

// capa do jogo da velha.................
void capadojogoveia()
{
   printf("____________________________________________________________________________________________________________________ \n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|     *-------*   *----*    *-----*   *----*                      *--* *--*  *------*  *---*      *                 |\n");
   printf("|      |__. .__|  |      |  |  .__.|  |      |                    |  | |  |  |  ____|  |   |     / \\                |\n");
   printf("|         | |     | *--* |  | |       | *--* |       -> DA <-     *  * *  *  | |__.    |   |    /   \\               |\n");
   printf("|         | |     | |  | |  | |  *-*  | |  | |         *-*         \\  *  /   |  __|    |   |   /  *  \\              |\n");
   printf("|      *--* |     | *--* |  | |  | |  | *--* |         / /          \\   /    | |____.  |   |  *  * *  *             |\n");
   printf("|      |    |     |      |  | *--* |  |      |         *-*           \\ /     |      |  |   |  |  | |  |             |\n");
   printf("|      *----*     *----*    *----*    *----*                          *      *--**--*  *---*  *-------*             |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                     by Stella Karolina            |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                Menu: 1 - Play | 2 - Instruções | 3 - Creditos | 4 - referencia | 5 - Finalizar Programa           |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
}

void capaplay()
{
   printf("____________________________________________________________________________________________________________________ \n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|     *-------*   *----*    *-----*   *----*                      *--* *--*  *------*  *---*      *                 |\n");
   printf("|      |__. .__|  |      |  |  .__.|  |      |                    |  | |  |  |  ____|  |   |     / \\                |\n");
   printf("|         | |     | *--* |  | |       | *--* |       -> DA <-     *  * *  *  | |__.    |   |    /   \\               |\n");
   printf("|         | |     | |  | |  | |  *-*  | |  | |         *-*         \\  *  /   |  __|    |   |   /  *  \\              |\n");
   printf("|      *--* |     | *--* |  | |  | |  | *--* |         / /          \\   /    | |____.  |   |  *  * *  *             |\n");
   printf("|      |    |     |      |  | *--* |  |      |         *-*           \\ /     |      |  |   |  |  | |  |             |\n");
   printf("|      *----*     *----*    *----*    *----*                          *      *--**--*  *---*  *-------*             |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                     by Stella Karolina            |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                   Menu: 1 - Player X Player | 2 - Computador | 3 - Voltar                         |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
}

void menuplayfim()
{
   printf(" ___________________________________________________________________________________________________________________ \n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                             Menu: 1 - Play | 2 - Menu |                                           |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
   printf("\n\n");
}

void veiacomputador()
{
   printf(" ___________________________________________________________________________________________________________________ \n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|                                  Escolha dificuldade:   1 - Facil | 2 - medio |                                   |\n");
   printf("|                                                                                                                   |\n");
   printf("|___________________________________________________________________________________________________________________|\n");
   printf("\n\n");
}

// capa jogo play
void capa()
{
   system("cls");
   printf("\t##############JOGO DA VELHA ####################");
   printf("\n\n");
}

// capa jogo da velha inicial
void capa2()
{
   system("cls");
   printf("##############JOGO DA VELHA ####################");
   printf("\n\n");
   printf("\nJOGADOR 1 = X\nJOGADOR 2 = O\n");
   printf("\n\n");
}

// legenda do jogo da veia [play]
void legenda()
{
   printf("\n");
   printf("\t*-----OBS---* \n");
   printf("\t| 1 | 2 | 3 |\n");
   printf("\t| 4 | 5 | 6 |\n");
   printf("\t| 7 | 8 | 9 |\n");
   printf("\t*-----------*\n");
   printf("\n");
}
