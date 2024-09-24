#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "personagem.h"
#include "myLog.h"
#include "readCsv.h"
#include "sort.h"


// Para compilar incluindo as bibliotecas da pasta RegAux: gcc -IRegAux -o main main.c

int main(){
    // Iniciar o cronometro
    startTimer();

    Personagem personagens[structList];
    char input[auxStringTam];

    // Ler o CSV, e passar tudo para uma List
    readCsv(personagens, "characters.csv");

    // Criar uma List secundaria, apenas com os Personagens que serao utilizados no exercicio
    Personagem* using = NULL;
    using = mySubList(personagens);

    // Realizar a questao expecifica e printar a saida
    heapSortHairColor(using);
    using = createNewSubList(using, 10);
    printAllPersonagens(using);

    // Encerrar o cronometro e criar o log de saida
    endTimer();
    createLog();

    free(using);
    
    return 0;
}
