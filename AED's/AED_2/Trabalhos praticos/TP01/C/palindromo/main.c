/*
Crie um método iterativo que recebe uma string como parâmetro e retorna true se essa é um Palíndromo.

Na saída padrão, para cada linha de entrada, escreva uma linha de saída com SIM/NÃO 
indicando se a linha é um palíndromo. Destaca-se que uma linha de entrada pode ter caracteres não letras.
*/

#include <stdio.h>
#include <string.h>

int verInput(char* input);

int main(){

    char input[1000];

    int nextLine = 0;

    while( fgets(input, sizeof(input), stdin) ){
        if ( nextLine ) printf("\n");

        if ( input[strlen(input)-1] == '\n' ) input[strlen(input)-1] = 0;

        if ( !strcmp(input, "FIM") ) break;

        verInput(input) == 1 ? printf("SIM") : printf("NAO");
        nextLine = 1;

    }

    return 0;

}

int verInput(char* input){

    int i = 0;
    int j = strlen(input)-1;

    while ( i <= j){

        int skip = 0;

        if ( input[i] == -61 ) i++;
        if ( input[j] == -61 ) j--;

        if ( input[i] == -17 ) i+=2, skip = 1;

        if ( input[i] != input[j] ) return 0;

        if ( skip ) j-=2;

        i++;
        j--;
       
    }
    
    return 1;

}
