/*
Crie um método recursivo que recebe uma string como parâmetro e retorna true se essa é um Palíndromo.

Na saída padrão, para cada linha de entrada, escreva uma linha de saída com SIM/NÃO 
indicando se a linha é um palíndromo. Destaca-se que uma linha de entrada pode ter caracteres não letras.
*/

#include <stdio.h>
#include <string.h>

int isPalindromo(char* input, int tam, int inicio);

int main (){
    char input[1000];
    int tam = 0;
    int ver = 0;

    fgets(input, sizeof(input), stdin);
    if ( input[strlen(input)-1] == '\n' ) input[strlen(input)-1] = 0;

    while ( strcmp(input, "FIM")){
        if ( ver ) printf("\n");
        ver = 1;

        tam = strlen(input);
        isPalindromo(input, tam - 1, 0) ? printf("SIM") : printf("NAO");

        fgets(input, sizeof(input), stdin);
        if ( input[strlen(input)-1] == '\n' ) input[strlen(input)-1] = 0;
    }

    return 0;
}

int isPalindromo(char* input, int tam, int inicio) {
    if (inicio >= tam) {
        return 1;
    }

    int skip = 0;

    if ( input[inicio] == -61 ) inicio++;
    
    if ( input[tam] == -61 ) tam--;

    if ( input[inicio] == -17 ) inicio += 2, skip = 1;

    if ( input[inicio] != input[tam] ) return 0;

    if ( skip ) tam -= 2;

    inicio++;
    tam--;

    return isPalindromo(input, tam, inicio);
}