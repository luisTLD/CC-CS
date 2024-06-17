#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void buffer();

int zerarResposta(char* segredo, char* resposta);

void forca(int *tentativas, char* resposta, char* segredo, int *ver, int tamanho);

void verificarLetra(char* letra, char* segredo, char* resposta, int tamanho, int* tentativas);

void verificarVitoria(char* resposta, char* segredo, int tamanho, int *ver);

int main() {
  int temp = 0;
  int tentativas = 0; int escolha = 0; int tamanho = 0; int ver = 1;
  char letra[3]; char segredo[12]; char resposta[12];
  char banco[5][12] = {{"ABACAXI"},{"ELEFANTE"},{"COMPUTADOR"},{"GIRASSOL"},{"MONTANHA"}};
  printf("\n\t <--- Jogo da forca --->\n");
  printf("\nDigite um numero negativo para sair");
  printf("\nDigite um numero de 1 a 5 para escolher uma palavra secreta: ");
  while(1){
    scanf(" %d", &escolha); buffer();
    if ( escolha == 0 || escolha > 5 ){
      printf("Numero invalido, digite um numero de 1 a 5: ");
    }
    else if ( escolha < 0) {
      printf("\n\t <--- Jogo encerrado --->");
      return 0;
    }
    else {
      strcpy(segredo,banco[escolha-1]);
      break;
    }
  }
  temp = strlen(segredo);
  resposta[temp] = '\0';
  tamanho = zerarResposta(segredo, resposta);
  forca(&tentativas, resposta, segredo, &ver, tamanho);
  while(ver){
    verificarLetra(letra, segredo, resposta, tamanho, &tentativas);
    forca(&tentativas, resposta, segredo, &ver, tamanho);
    verificarVitoria(resposta, segredo, tamanho, &ver);
  }
}

void forca(int *tentativas, char* resposta, char* segredo, int *ver, int tamanho){
  system("cls || clear");
  printf("\n\t <--- Jogo da forca --->\n");
  switch(*tentativas){
    case 0:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 1:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 2:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |    |  ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 3:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |    |/ ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 4:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |   \\|/ ");
      printf("\n    |       ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 5:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |   \\|/ ");
      printf("\n    |    |  ");
      printf("\n    |     \\ ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Palavra chave: %s, %d letras", resposta, tamanho);
      break;
    case 6:
      printf("\n    ._______");
      printf("\n    |    :  ");
      printf("\n    |   ( ) ");
      printf("\n    |   \\|/ ");
      printf("\n    |    |  ");
      printf("\n    |   / \\ ");
      printf("\n    |       ");
      printf("\n ___|_________");
      printf("\n\n\t Fim de jogo, voce perdeu");
      printf("\n\n\t A resposta era: %s", segredo);
      *ver = 0;
      printf("\n\nAperte enter para encerrar"); getchar();
      break;
  }
}

void verificarLetra(char* letra, char* segredo, char* resposta, int tamanho, int* tentativas){
  int temp = 0;
  printf("\n\nDigite uma letra: ");
  while(1){
    scanf(" %s", letra); buffer();
    if ( strlen(letra) != 1 || ( letra[0] >= '0' && letra[0] <= '9' )){
      printf("\nDigite apenas 1 letra, valida: ");
    }
    else {
      break;
    }
  }
  letra[0] = toupper(letra[0]);
  for ( int i = 0; i < tamanho; i++ ){
    if ( letra[0] == segredo[i] ){
      resposta[i] = letra[0];
      temp = 1;
    }
  }
  if ( temp == 0 ) (*tentativas)++;
}

void verificarVitoria(char* resposta, char* segredo, int tamanho, int *ver){
  for ( int i = 0; i < tamanho; i++ ){
    if ( strcmp(resposta, segredo) == 0 ){
      printf("\n\nVoce ganhou, a palavra era: %s", segredo);
      *ver = 0;
      printf("\n\nAperte enter para encerrar"); getchar();
      break;
    }
  }
}

int zerarResposta(char* segredo, char* resposta){
  int temp = 0;
  temp = strlen(segredo);
  for ( int i = 0; i < temp; i++ ){
    resposta[i] = '_';
  }
  return temp;
}

void buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
