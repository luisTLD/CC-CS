#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
0  1  2
3  4  5
6  7  8
*/

void buffer();

void tabuleiro(char *ptr);

void preencherEscolhaInicio(char *ptr);

int verificarVitoria(char escolha[][3]);

void verificarEmpate(int *fim, int *jogador, char *escolha);

int jogada(char *ptr, int posi, int *jogador);

int jogadaMaquina(char *ptr, int *jogador);

void zerar(int *fim, int *jogador, char *escolha);

int main()
{
  char escolha[3][3];
  char *ptr = &escolha[0][0];
  int posi = 0;
  int ver = 1;
  int jogador = 1;
  int fim = 0;
  int teste = 0;
  preencherEscolhaInicio(&escolha[0][0]);
  printf("\n <--- Jogo da velha --->\n");
  printf("\nDigite um numero negativo para encerrar\n\n");
  printf("Para jogar contra um amigo digite 1\nPara jogar contra a maquina "
         "digite 2\n\nDigite sua opcao: ");
  while (ver)
  {
    scanf(" %d", &teste);
    buffer();
    if (teste == 1 || teste == 2)
    {
      break;
    }
    else if (teste < 0)
    {
      ver = 0;
      break;
    }
    else
    {
      printf("\nDigite uma opcao valida: ");
    }
  }
  if (teste == 1)
  {
    while (ver)
    {
      tabuleiro(&escolha[0][0]);
      ver = jogada(&escolha[0][0], posi, &jogador);
      if (verificarVitoria(escolha) == 1)
      {
        jogador = jogador == 1 ? 2 : 1;
        system("cls || clear");
        tabuleiro(&escolha[0][0]);
        printf("Vitoria do jogador %d", jogador);
        zerar(&fim, &jogador, &escolha[0][0]);
      }
      else
      {
        verificarEmpate(&fim, &jogador, &escolha[0][0]);
      }
      system("cls || clear");
    }
  }
  else
  {
    srand(time(0));
    while (ver)
    {
      if (jogador == 1)
      {
        tabuleiro(&escolha[0][0]);
        ver = jogada(&escolha[0][0], posi, &jogador);
        if (verificarVitoria(escolha) == 1)
        {
          jogador = jogador == 1 ? 2 : 1;
          system("cls || clear");
          tabuleiro(&escolha[0][0]);
          printf("Vitoria do jogador %d", jogador);
          zerar(&fim, &jogador, &escolha[0][0]);
        }
        else
        {
          verificarEmpate(&fim, &jogador, &escolha[0][0]);
        }
        system("cls || clear");
      }
      else
      {
        tabuleiro(&escolha[0][0]);
        ver = jogadaMaquina(&escolha[0][0], &jogador);
        if (verificarVitoria(escolha) == 1)
        {
          jogador = jogador == 1 ? 2 : 1;
          system("cls || clear");
          tabuleiro(&escolha[0][0]);
          printf("Vitoria do jogador %d", jogador);
          zerar(&fim, &jogador, &escolha[0][0]);
        }
        else
        {
          verificarEmpate(&fim, &jogador, &escolha[0][0]);
        }
        system("cls || clear");
      }
    }
  }

  tabuleiro(&escolha[0][0]);
  printf("\n <--- Jogo encerrado --->");
  return 0;
}

void buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void tabuleiro(char *ptr)
{
  printf(
      "\n\t1    |2    |3    \n\t  %c  |  %c  | %c   \n\t_____|_____|_____\n\t4 "
      "   |5    |6    \n\t  %c  |  %c  |  %c  \n\t_____|_____|_____\n\t7    |8 "
      "   |9    \n\t  %c  |  %c  |  %c  \n\t     |     |    \n\n",
      *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5),
      *(ptr + 6), *(ptr + 7), *(ptr + 8));
}

void preencherEscolhaInicio(char *ptr)
{
  for (int i = 0; i < 9; i++)
  {
    *(ptr + i) = '.';
  }
}

int jogada(char *ptr, int posi, int *jogador)
{
  printf("Jogador %d, digite a casa: ", *jogador);
  while (1)
  {
    scanf(" %d", &posi);
    buffer();
    if (*(ptr + posi - 1) != '.' && posi >= 0)
    {
      printf("Digite uma posicao valida: ");
    }
    else if (posi < 0)
    {
      return 0;
    }
    else
    {
      break;
    }
  }
  *(ptr + posi - 1) = *jogador == 1 ? 'X' : 'O';
  *jogador = *jogador == 1 ? 2 : 1;
  return 1;
}

int jogadaMaquina(char *ptr, int *jogador)
{
  int posiMaquina = 0;
  while (1)
  {
    posiMaquina = (rand() % 9) + 1;
    if (*(ptr + posiMaquina - 1) != '.' && posiMaquina >= 0)
    {
    }
    else
    {
      break;
    }
  }
  *(ptr + posiMaquina - 1) = 'O';
  *jogador = *jogador == 1 ? 2 : 1;
  return 1;
}

int verificarVitoria(char escolha[][3])
{
  int r = 0;
  for (int i = 0; i < 3; i++)
  {
    r = 0;
    for (int j = 0; j < 2; j++)
    {
      if (escolha[i][j] != '.' && escolha[i][j] == escolha[i][j + 1])
      {
        r++;
      }
      if (r == 2)
      {
        return 1;
      }
    }
  }
  for (int j = 0; j < 3; j++)
  {
    r = 0;
    for (int i = 0; i < 2; i++)
    {
      if (escolha[i][j] != '.' && escolha[i][j] == escolha[i + 1][j])
      {
        r++;
      }
      if (r == 2)
      {
        return 1;
      }
    }
  }
  r = 0;
  for (int i = 0; i < 2; i++)
  {
    if (escolha[i][i] != '.' && escolha[i][i] == escolha[i + 1][i + 1])
    {
      r++;
    }
    if (r == 2)
    {
      return 1;
    }
  }
  r = 0;
  for (int i = 0, j = 2; i < 2; i++, j--)
  {
    if (escolha[i][j] != '.' && escolha[i][j] == escolha[i + 1][j - 1])
    {
      r++;
    }
    if (r == 2)
    {
      return 1;
    }
  }
  return 0;
}

void verificarEmpate(int *fim, int *jogador, char *escolha)
{
  (*fim)++;
  if (*fim == 9)
  {
    system("cls || clear");
    tabuleiro(escolha);
    printf("Empate\n");
    printf("Aperte enter para cotinuar");
    getchar();
    buffer();
    preencherEscolhaInicio(escolha);
    *fim = 0;
    *jogador = 1;
  }
}

void zerar(int *fim, int *jogador, char *escolha)
{
  printf("\nAperte enter para cotinuar");
  getchar();
  buffer();
  preencherEscolhaInicio(escolha);
  *fim = 0;
  *jogador = 1;
}
