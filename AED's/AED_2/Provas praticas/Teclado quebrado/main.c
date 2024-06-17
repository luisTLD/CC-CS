/*
Você está digitando um texto longo com um teclado quebrado. 
Bem, não tão quebrado. O único problema com o teclado é que às vezes a tecla "home" ou a tecla "end" 
é automaticamente pressionada (internamente). Você não está ciente deste problema, 
já que você está focado no texto e nem sequer ligou o monitor! 
Depois que você terminar de digitar, você pode ver um texto na tela (se você ligar o monitor). 
Em chinês, podemos chamar este texto de Beiju. Sua tarefa é encontrar o texto Beiju.

Entrada
Há diversos casos de teste. 
Cada teste é uma única linha que contém pelo menos uma e, 
no máximo, 100.000 letras, underscores e dois caracteres especiais '[' e ']'. 
'[' Significa que a tecla "Home" é pressionada internamente, e ']' significa que a tecla "End" é pressionada internamente. 
A entrada é terminada por fim de arquivo (EOF). O tamanho do arquivo de entrada não excede 5MB.

Saída
Para cada caso, imprimir o texto Beiju na tela.
*/

#include <stdio.h>
#include <string.h>

void inserirInicio(char input, char beiju[], int* fim, int* begin);

void inserirFim(char input, char beiju[], int* fim, int* begin);

int main(){
    char input[1000];
    char beiju[1000];

    while (fgets(input, sizeof(input), stdin) != NULL ){

    beiju[0] = '\0';
    int end = 0;
    int begin = 0;
    int ver = 0;
    int nextLine = 0;

        for ( int i = 0; i < strlen(input); i++ ){
            switch (input[i]){
            case '[':
                ver = 1;
                break;
            case ']':
                ver = 0;
                break;
            default:
                if ( ver ) inserirInicio(input[i], beiju, &end, &begin);
                else inserirFim(input[i], beiju, &end, &begin);
            }
        }

        beiju[end] = '\0';

        if (nextLine) printf("\n");
        printf("%s", beiju);
        nextLine = 1;

    }
}

void inserirInicio(char input, char beiju[], int* end, int* begin){
    for ( int i = *end; i > *begin; i-- ){
        beiju[i] = beiju[i - 1];
    }
    beiju[*begin] = input;
    (*end)++;
    (*begin)++;
}

void inserirFim(char input, char beiju[], int* end, int* begin){
    beiju[*end] = input;
    (*end)++;
    *begin = 0;
}