#ifndef myLog_h
#define myLog_h

#include <time.h>
#include <stdio.h>

// Variavel global para armazenar o tempo de execução do codigo
clock_t startTime;
clock_t endTime;
int totalComp = 0;
int totalMove = 0;

// Iniciar cronometro
void startTimer() {
    startTime = clock();
}

// Encerrar cronometro
void endTimer() {
    endTime = clock();
}

// Somar 1 no comparador
void countComp() {
    totalComp++;
}

// Somar 1 no movimentador
void countMove() {
    totalMove++;
}

// Criar o TXT de saida
void createLog() {
    FILE* logArq;
    logArq = fopen("000000_heapsort.txt", "w");

    if (logArq == NULL) {
        printf("Erro ao criar o arquivo de log\n");
        return;
    }

    double totalTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    totalTime = totalTime * 1000;

    fprintf(logArq, "%s\t%f\t%d\t%d\n", "000000", totalTime, totalComp, totalMove);

    fclose(logArq);
}


#endif