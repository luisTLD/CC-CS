/*
Crie um método RECURSIVO que recebe uma string, 
sorteia duas letras minúsculas aleatórias (código ASCII <= 'a' e >= 'z'), 
substitui todas as ocorrências da primeira letra na string pela segunda 
e retorna a string com as alterações efetuadas. Na saída padrão,
para cada linha de entrada, execute o método desenvolvido nesta questão e 
mostre a string retornada como uma linha de saída. 
Abaixo, observamos um exemplo de entrada supondo que 
para a primeira linha as letras sorteados foram o 'a' e o 'q'. Para a segunda linha, foram o 'e' e o 'k'.

EXEMPLO DE ENTRADA:                                     EXEMPLO DE SAÍDA:

o rato roeu a roupa do rei de roma             o rqto roeu q roupq do rei de romq

e qwe qwe qwe ewq ewq ewq                     k qwk qwk qwk kwq kwq kwq

FIM

A classe Random do Java gera números (ou letras)
aleatórios e o exemplo abaixo mostra uma letra minúscula na tela. Em especial, destacamos que:

i) \textit{seed} é a semente para geração de números aleatórios;
ii) nesta questão, por causa da correção automática, a *seed* será quatro;
iii) a disciplina de Estatística e Probabilidade faz uma discussão sobre ``aleatório''.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void randAlt(char* input, int inicio, char new, char rand);

int main(){
    srand(4);

    char newChar;
    char randChar;

    char input[1000];
    int ver = 0;

    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = 0;

    while (strcmp(input, "FIM")){
        if ( ver ){
            printf("\n");
        }
        ver = 1;

        randChar = 'a' + rand() % 26;
        newChar = 'a' + rand() % 26;

        randAlt(input, 0, newChar, randChar);
        printf("%s", input);

        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = 0;
    }

    return 0;
}

void randAlt(char* input, int inicio, char new, char rand){
    if ( inicio < strlen(input)){
        if ( input[inicio] == rand ) input[inicio] = new;
        inicio++;
        randAlt(input, inicio, new, rand);
    }
}