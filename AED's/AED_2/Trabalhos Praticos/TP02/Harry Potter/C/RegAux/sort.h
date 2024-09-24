#ifndef sort_h
#define sort_h

#include "personagem.h"
#include <ctype.h>



// Declaração das funções
void selectionSortName(Personagem personagens[]);
void selectionSortRecName(Personagem personagens[], int max);
void shellSortEyeColor(Personagem personagens[]);
void quickSortHouse(Personagem personagens[]);
void quickSortHouseCall(Personagem personagens[], int left, int right);
void bubbleSortHairColor(Personagem personagens[]);
void heapSortHairColor(Personagem personagens[]);
void radixSortId(Personagem personagens[]);
void radixCountingSort(int exp, Personagem personagens[]);
void swap(Personagem *x, Personagem *y);
int compareName(Personagem x, Personagem y);
int compareEyeColor(Personagem x, Personagem y);
int compareHouse(Personagem x, Personagem y);
int compareHairColor(Personagem x, Personagem y);
void toLowerCase(char *str);



// Função para ordenar em Name usado SelectionSort
void selectionSortName(Personagem personagens[]){
    int max = lengthOfList(personagens);

    for ( int i = 0; i < max - 1; i++ ){
    int aux = i;

        for ( int j = i + 1; j < max; j++ ){
            if ( compareName(personagens[j], personagens[aux]) < 0 ){
                aux = j;
            }
        }

        swap(&personagens[i], &personagens[aux]);
    }
}


// SelectionSort recursivo para Name
void selectionSortRecName(Personagem personagens[], int max){
    int aux = 0;

    for ( int j = 1; j < max; j++ ){
        if ( strcmp(personagens[j].name, personagens[aux].name) > 0 ){
            aux = j;
        }
    }

    swap(&personagens[max - 1], &personagens[aux]);

    if ( max > 1 ) selectionSortRecName(personagens, max - 1);
}


// ShellSort para EyeColor, desempata em Name
void shellSortEyeColor(Personagem personagens[]){
    int length = lengthOfList(personagens);
    int h = 1;

    do {
        h = ( h * 3 ) + 1;
    } while ( h < length );

    do {
        h /= 3;
        for ( int part = 0; part < h; part++ ){
            // Insertion por partes
            for ( int i = ( h + part ); i < length; i += h){
                Personagem tmp = personagens[i];
                int j = i - h;

                while ( (j >= 0) && (compareEyeColor(personagens[j], tmp) > 0) ){
                    personagens[j + h] = personagens[j];
                    j -= h;         
                }

                personagens[j + h] = tmp;
            }
        }
    } while ( h != 1 );

    // InsertionSort por EyeColor
    for ( int i = 1; i < length; i++ ){
        Personagem aux = personagens[i];
        int j = i - 1;

        while (( j >= 0 ) &&  (compareEyeColor(personagens[j], aux) > 0)){
            personagens[j + 1] = personagens[j];
            j -= 1;  
        }

        personagens[j + 1] = aux;
    }
}


// QuickSort por House
void quickSortHouse(Personagem personagens[]){
    quickSortHouseCall(personagens, 0, lengthOfList(personagens) - 1);
}

// Chamada recursiva do quickSort
void quickSortHouseCall(Personagem personagens[], int left, int right){
    int i = left;
    int j = right;
    Personagem piv = personagens[(left + right) / 2];

    while ( i <= j ){
        while ( compareHouse(personagens[i], piv) < 0 ) i++;
        while ( compareHouse(personagens[j], piv) > 0 ) j--;

        if ( i <= j ) {
            swap(&personagens[i], &personagens[j]);
            i++;
            j--;
        }

        if ( left < j ) quickSortHouseCall(personagens, left, j);
        if ( i < right ) quickSortHouseCall(personagens, i, right);
    }
}


// BubbleSort por HairColor
void bubbleSortHairColor(Personagem personagens[]){
    int length = lengthOfList(personagens);

    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (compareHairColor(personagens[j], personagens[j + 1]) > 0) {
                swap(&personagens[j], &personagens[j + 1]);
            }
        }
    }
}


// HeapSortParcial por HairColor
void heapSortHairColor(Personagem personagens[]){
    int length = lengthOfList(personagens);

    for ( int max = 1; max < length; max++ ){

        // Construir Heap, se o filho for maior que o pai, troca e continua verificando com o proximo pai
        for ( int i = max; max > 0 && compareHairColor(personagens[i], personagens[((i - 1) / 2)]) > 0; i = (i - 1) / 2){
            
            swap(&personagens[i], &personagens[((i - 1) / 2)]);
        }
    }

    // Ordenação, taca o primiero pro final, e constroi o Heap novamente, ate ordenar
    int endIndex = length - 1;
    while ( endIndex > 0 ){
        swap(&personagens[0], &personagens[endIndex]);
        endIndex--;

        // Reconstruir o Heap
        int aux = 0; 

        // Entrar em Loop enquando aux tiver filho
        while((aux * 2) + 1 <= endIndex){
            // Obter o maior filho de aux
            int son = 0;

            // Ver se so tem um filho, ou, comparar os 2 para retornar o maior
            if ( (2 * aux) + 1 == endIndex ) son = endIndex;
            else if ( compareHairColor(personagens[(2 * aux) + 1], personagens[(2 * aux) + 2]) > 0 ) son = ((2 * aux) + 1);
            else son = ((2 * aux) + 2);

            // Verificar se o filho é maior que o novo pai, para fazer a troca
            if ( compareHairColor(personagens[son], personagens[aux]) > 0 ){
                swap(&personagens[son], &personagens[aux]);

                // aux ser igual a son, para que verifique se agora ele é filho de algum novo pai menor que ele
                aux = son;
            } else aux = endIndex; // Sair do loop
        }
    }
}


// Função para ordenar Id por radix
void radixSortId(Personagem personagens[]){
    int max = 36;

    for ( int i = max; i >= 0; i-- ){
        radixCountingSort(i, personagens);
    }
}

void radixCountingSort(int exp, Personagem personagens[]) {
    int length = lengthOfList(personagens);
    Personagem* output = (Personagem*)malloc(length * sizeof(Personagem));
    int* counting = (int*)calloc(128, sizeof(int));

    for (int i = 0; i < length; i++){
        counting[personagens[i].id[exp]]++;  
    }

    for (int i = 1; i < 128; i++){
        counting[i] += counting[i - 1];    
    }

    for (int i = length - 1; i >= 0; i--) {
        output[counting[personagens[i].id[exp]] - 1] = personagens[i];
        counting[personagens[i].id[exp]]--;   
    }

    for (int i = 0; i < length; i++){
        personagens[i] = output[i];  
    }

    free(output);
    free(counting);
}

// Função auxiliar para trocar 2 personagens de lugar
void swap(Personagem *x, Personagem *y){
    Personagem aux = *x;
    *x = *y;
    *y = aux;

    
    
    
}


// -------------------------------------------------------------------------------------------------------------------------

                            // Funções para comparação de atributos, desempatando em Name

// Comparar por Name
int compareName(Personagem x, Personagem y){

    return strcmp(x.name, y.name);
}

// Comparar por EyeColor
int compareEyeColor(Personagem x, Personagem y){
    
    int aux = strcmp(x.eyeColor, y.eyeColor);

    if ( aux == 0 ) aux = compareName(x, y);

    return aux;
}

// Comparar por House
int compareHouse(Personagem x, Personagem y){
   
    int aux = strcmp(x.house, y.house);

    if ( aux == 0 ) aux = compareName(x, y);

    return aux;
}

// Compara HairColor
int compareHairColor(Personagem x, Personagem y){

    int aux = strcmp(x.hairColor, y.hairColor);

    if ( aux == 0 ) aux = compareName(x, y);

    return aux;
}

// Passr string toda p minuscula
void toLowerCase(char *str){
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}
#endif 