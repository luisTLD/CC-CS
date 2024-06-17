#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef union {
  float tempNum;
  char tempChar[50];
} dadoTemp;

typedef struct {
  int id;
  char nome[50];
  char genero[20];
  float preco;
  char status[30];
} livro;

void buffer();

int minusculo();

int contarLinhas();

void menu();

void escolha();

void atualizarStruct();

void salvarNovaStruct();

void atualizarID();

void cadastroCompleto();

void alugarDevolverLivro();

void alugarLivro();

void devolverLivro();

void verLivros();

void verLivrosDisponiveis();

void verLivrosIndisponiveis();

void editarLivros();

void printarID();

void excluirLivros();

int acharID();

int acharIDDisponivel();

int acharIDIndisponivel();

int SimNao();

int main() {
  FILE *livros;
  livro livroStruct[100];
  escolha(livros, livroStruct);
  return 0;
}

void escolha(FILE *livros, livro *livroStruct) {
  int loop = 1;
  menu();
  printf("\nDigite sua opcao: ");
  while (loop) {
    int op = 0;
    atualizarStruct(livroStruct, livros);
    scanf(" %d", &op);
    buffer();
    switch (op) {
    case 1:
      cadastroCompleto(livros, livroStruct);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 2:
      verLivros(livroStruct, livros);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 3:
      verLivros(livroStruct, livros);
      editarLivros(livroStruct, livros);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 4:
      atualizarID(livroStruct, livros);
      salvarNovaStruct(livroStruct, livros);
      verLivros(livroStruct, livros);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 5:
      printf("\nDeseja:\n\n1)Alugar livro\n2)Devolver livro\n\nDigite sua "
             "opcao: ");
      alugarDevolverLivro(livroStruct, livros);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 6:
      verLivros(livroStruct, livros);
      printf("\nQual livro deseja excluir ? Digite o ID: ");
      excluirLivros(livroStruct, livros);
      printf("\nAperte enter 2x para continuar");
      getchar();
      buffer();
      break;
    case 7:
      loop = 0;
      break;
    default:
      printf("\n\tDigite um numero valido: ");
    }
    if (loop == 1) {
      system("cls || clear");
      menu();
      printf("\nDigite sua opcao: ");
    }
  }
}

void atualizarStruct(livro *livroStruct, FILE *livros) {
  int total = 0;
  total = contarLinhas(livros);
  livros = fopen("livros.txt", "r");
  for (int i = 0; i < total; i++) {
    fscanf(livros, "%d", &livroStruct[i].id);
    fgetc(livros);
    fscanf(livros, "%[^;]", livroStruct[i].nome);
    fgetc(livros);
    fscanf(livros, "%[^;]", livroStruct[i].genero);
    fgetc(livros);
    fscanf(livros, "%f", &livroStruct[i].preco);
    fgetc(livros);
    fscanf(livros, "%[^\n]", livroStruct[i].status);
    fgetc(livros);
  }
  fclose(livros);
}

void salvarNovaStruct(livro *livroStruct, FILE *livros) {
  int linhas = 0;
  linhas = contarLinhas(livros);
  livros = fopen("livros.txt", "w");
  for (int i = 0; i < linhas; i++) {
    fprintf(livros, "%d;%s;%s;%.2f;%s\n", livroStruct[i].id,
            livroStruct[i].nome, livroStruct[i].genero, livroStruct[i].preco,
            livroStruct[i].status);
  }
  fclose(livros);
}

void atualizarID(livro *livroStruct, FILE *livros) {
  int linhas = 0;
  linhas = contarLinhas(livros);
  for (int i = 0; i < linhas; i++) {
    livroStruct[i].id = i;
  }
}

void cadastroCompleto(FILE *livros, livro *livroStruct) {
  int novo = 0;
  int disp = 0;
  novo = contarLinhas(livros);
  printf("\nDigite o titulo do livro: ");
  scanf(" %[^\n]", livroStruct[novo].nome);
  buffer();
  minusculo(livroStruct[novo].nome);
  livroStruct[novo].nome[0] = toupper(livroStruct[novo].nome[0]);
  printf("Digite o genero do livro: ");
  scanf(" %[^\n]", livroStruct[novo].genero);
  buffer();
  minusculo(livroStruct[novo].genero);
  livroStruct[novo].genero[0] = toupper(livroStruct[novo].genero[0]);
  printf("Digite o preco do livro, R$:");
  scanf(" %f", &livroStruct[novo].preco);
  buffer();
  printf("O livro esta disponivel ? responda com SIM ou NAO: ");
  disp = SimNao();
  disp == 1 ? strcpy(livroStruct[novo].status, "Disponivel")
            : strcpy(livroStruct[novo].status, "Indisponivel");
  printarID(novo, livroStruct);
  printf("\nConfirmar livro ? Digite com SIM ou NAO: ");
  if (SimNao()) {
    livros = fopen("livros.txt", "a");
    fprintf(livros, "%d;%s;%s;%.2f;%s\n", (livroStruct[novo - 1].id + 1),
            livroStruct[novo].nome, livroStruct[novo].genero,
            livroStruct[novo].preco, livroStruct[novo].status);
    fclose(livros);
    atualizarStruct(livroStruct, livros);
    printf("\nCadastro completo!\n");
  } else {
    printf("\nCadastro cancelado!\n");
  }
}

void alugarDevolverLivro(livro *livroStruct, FILE *livros) {
  int loop = 1;
  int op = 0;
  while (loop) {
    scanf(" %d", &op);
    buffer();
    switch (op) {
    case 1:
      verLivrosDisponiveis(livroStruct, livros);
      printf("Qual livro deseja alugar ? Digite o ID: ");
      alugarLivro(livroStruct, livros);
      salvarNovaStruct(livroStruct, livros);
      loop = 0;
      break;
    case 2:
      verLivrosIndisponiveis(livroStruct, livros);
      printf("Qual livro deseja devolver ? Digite o ID: ");
      devolverLivro(livroStruct, livros);
      salvarNovaStruct(livroStruct, livros);
      loop = 0;
      break;
    default:
      printf("\nDigite um numero valido: ");
    }
  }
}

void verLivros(livro *livroStruct, FILE *livros) {
  int total = 0;
  total = contarLinhas(livros);
  livros = fopen("livros.txt", "r");
  printf("\n\t<-- Livros cadastrados -->\n\n");
  for (int i = 0; i < total; i++) {
    printf("ID: %d / Livro: %s / Genero: %s / Preco: %.2f / Status: %s\n",
           livroStruct[i].id, livroStruct[i].nome, livroStruct[i].genero,
           livroStruct[i].preco, livroStruct[i].status);
  }
  fclose(livros);
}

void verLivrosDisponiveis(livro *livroStruct, FILE *livros) {
  int total = 0;
  total = contarLinhas(livros);
  livros = fopen("livros.txt", "r");
  printf("\n\t<--- Livros Disponiveis --->\n\n");
  for (int i = 0; i < total; i++) {
    if (strcmp(livroStruct[i].status, "Disponivel") == 0) {
      printf("ID: %d / Livro: %s / Genero: %s / Preco: %.2f / Status: %s\n",
             livroStruct[i].id, livroStruct[i].nome, livroStruct[i].genero,
             livroStruct[i].preco, livroStruct[i].status);
    }
  }
  fclose(livros);
}

void verLivrosIndisponiveis(livro *livroStruct, FILE *livros) {
  int total = 0;
  total = contarLinhas(livros);
  livros = fopen("livros.txt", "r");
  printf("\n\t<--- Livros indisponiveis --->\n\n");
  for (int i = 0; i < total; i++) {
    if (strcmp(livroStruct[i].status, "Indisponivel") == 0) {
      printf("ID: %d / Livro: %s / Genero: %s / Preco: %.2f / Status: %s\n",
             livroStruct[i].id, livroStruct[i].nome, livroStruct[i].genero,
             livroStruct[i].preco, livroStruct[i].status);
    }
  }
  fclose(livros);
}

void editarLivros(livro *livroStruct, FILE *livros) {
  char temp[50] = "\0";
  int id = 0;
  int loop = 1;
  int linhas = 0;
  int topico = 0;
  printf("\nDigite o ID do livro que deseja editar: ");
  id = acharID(livroStruct, livros);
  system("cls || clear");
  printarID(id, livroStruct);
  printf("\n1)Livro\n2)Genero\n3)preco\n4)Status\n\nDigite o topico que deseja "
         "editar: ");
  loop = 1;
  while (loop) {
    scanf(" %d", &topico);
    buffer();
    switch (topico) {
    case 1:
      printf("\nDigite o novo titulo: ");
      scanf(" %[^\n]", temp);
      buffer();
      minusculo(temp);
      temp[0] = toupper(temp[0]);
      printf("\nNovo titulo: %s\n", temp);
      printf("Confirmar novo titulo ? Responda com SIM ou NAO: ");
      SimNao() == 1 ? strcpy(livroStruct[id].nome, temp) : 0;
      loop = 0;
      break;
    case 2:
      printf("\nDigite o novo genero: ");
      scanf(" %[^\n]", temp);
      buffer();
      minusculo(temp);
      temp[0] = toupper(temp[0]);
      printf("\nNovo genero: %s\n", temp);
      printf("Confirmar novo genero ? Responda com SIM ou NAO: ");
      SimNao() == 1 ? strcpy(livroStruct[id].genero, temp) : 0;
      loop = 0;
      break;
    case 3:
      printf("\nDigite o novo preco R$: ");
      scanf(" %d", &topico);
      buffer();
      printf("\nNovo preco R$:%d\n", topico);
      printf("Confirmar novo preco ? Responda com SIM ou NAO: ");
      SimNao() == 1 ? livroStruct[id].preco = topico : 0;
      loop = 0;
      break;
    case 4:
      printf("O livro esta disponivel ? responda com SIM ou NAO: ");
      SimNao() == 1 ? strcpy(livroStruct[id].status, "Disponivel")
                    : strcpy(livroStruct[id].status, "Indisponivel");
      loop = 0;
      break;
    default:
      printf("Topico invalido!\n");
      printf("Digite um numero entre 1 e 4: ");
    }
  }
  printf("\nLivro atualizado: ");
  printarID(id, livroStruct);
  salvarNovaStruct(livroStruct, livros);
}

void excluirLivros(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  linhas = contarLinhas(livros);
  id = acharID(livroStruct, livros);
  printarID(id, livroStruct);
  printf("Deseja excluir livro id: %d ? Responder com SIM ou NAO: ",
         livroStruct[id].id);
  if (SimNao()) {
    livros = fopen("livros.txt", "w");
    for (int i = 0; i < linhas; i++) {
      if (i != id) {
        fprintf(livros, "%d;%s;%s;%.2f;%s\n", livroStruct[i].id,
                livroStruct[i].nome, livroStruct[i].genero,
                livroStruct[i].preco, livroStruct[i].status);
      }
    }
    fclose(livros);
    atualizarStruct(livroStruct, livros);
    verLivros(livroStruct, livros);
    printf("\nLivro excluido!\n");
  } else {
    printf("\nCancelado!\n");
  }
}

void alugarLivro(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  linhas = contarLinhas(livros);
  id = acharIDDisponivel(livroStruct, livros);
  printarID(id, livroStruct);
  printf("Deseja alugar livro id: %d ? Responder com SIM ou NAO: ",
         livroStruct[id].id);
  if (SimNao()) {
    strcpy(livroStruct[id].status, "Indisponivel");
    printf("\nLivro alugado com sucesso!\n");
  } else {
    printf("\nAcao cancelada!\n");
  }
}

void devolverLivro(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  linhas = contarLinhas(livros);
  id = acharIDIndisponivel(livroStruct, livros);
  printarID(id, livroStruct);
  printf("Deseja devolver livro id: %d ? Responder com SIM ou NAO: ",
         livroStruct[id].id);
  if (SimNao()) {
    strcpy(livroStruct[id].status, "Disponivel");
    printf("\nLivro devolvido com sucesso!\n");
  } else {
    printf("\nAcao cancelada!\n");
  }
}

void menu() {
  printf("\n\t <-- Biblioteca -->\n");
  printf("\n1) Cadastrar livro");
  printf("\n2) Ver livros");
  printf("\n3) Editar livros");
  printf("\n4) Ordenar ID's");
  printf("\n5) Alugar / Devolver livros");
  printf("\n6) Excluir livros");
  printf("\n7) Encerrar\n");
}

int minusculo(char *ver) {
  int tam = 0;
  tam = strlen(ver);
  for (int i = 0; i < tam; i++) {
    ver[i] = tolower(ver[i]);
  }
  return tam;
}

int SimNao() {
  char ver[4];
  int tam = 0;
  while (1) {
    scanf(" %[^\n]", ver);
    buffer();
    tam = minusculo(ver);
    if (strcmp(ver, "sim") == 0 || strcmp(ver, "s") == 0) {
      return 1;
    } else if (strcmp(ver, "nao") == 0 || strcmp(ver, "n") == 0) {
      return 0;
    } else {
      printf("Entrada invalida, Digite SIM ou NAO: ");
    }
  }
}

int acharID(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  int loop = 1;
  int i = 0;
  linhas = contarLinhas(livros);
  while (loop) {
    scanf(" %d", &id);
    buffer();
    for (i = 0; i < linhas; i++) {
      if (livroStruct[i].id == id) {
        loop = 0;
        break;
      }
    }
    if (loop != 0) {
      printf("\nID nao econtrado, digite um ID valido: ");
    }
  }
  return i;
}

int acharIDDisponivel(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  int loop = 1;
  int i = 0;
  linhas = contarLinhas(livros);
  while (loop) {
    scanf(" %d", &id);
    buffer();
    for (i = 0; i < linhas; i++) {
      if (livroStruct[i].id == id &&
          (strcmp(livroStruct[i].status, "Disponivel") == 0)) {
        loop = 0;
        break;
      }
    }
    if (loop != 0) {
      printf("\nID nao econtrado, digite um ID valido: ");
    }
  }
  return i;
}

int acharIDIndisponivel(livro *livroStruct, FILE *livros) {
  int id = 0;
  int linhas = 0;
  int loop = 1;
  int i = 0;
  linhas = contarLinhas(livros);
  while (loop) {
    scanf(" %d", &id);
    buffer();
    for (i = 0; i < linhas; i++) {
      if (livroStruct[i].id == id &&
          (strcmp(livroStruct[i].status, "Indisponivel") == 0)) {
        loop = 0;
        break;
      }
    }
    if (loop != 0) {
      printf("\nID nao econtrado, digite um ID valido: ");
    }
  }
  return i;
}

void printarID(int id, livro *livroStruct) {
  printf("\nLivro: %s / Genero: %s / Preco: %.2f / Status: %s\n",
         livroStruct[id].nome, livroStruct[id].genero, livroStruct[id].preco,
         livroStruct[id].status);
}

int contarLinhas(FILE *livros) {
  int totalLinhas = 0;
  char fimDeLinha;
  livros = fopen("livros.txt", "r");
  while ((fimDeLinha = fgetc(livros)) != EOF) {
    if (fimDeLinha == '\n') {
      totalLinhas++;
    }
  }
  fclose(livros);
  return totalLinhas;
}

void buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

