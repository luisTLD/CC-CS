#ifndef readCsv_h
#define readCsv_h

#define lineMax 1000
#define structList 500
#define attributes 18

#include "personagem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Declaração das funções
void readCsv(Personagem personagens[], char* fileToRead);
void stringBooleanFormat(char* aux);
int stringIntFormat(const char* aux);
LocalDate stringDateFormat(char* aux);
void removeStringChar(char* aux, char c);


// Struct para fazer um "split" enquanto lee o CSV
typedef struct{
    char stringSplited[attributes][auxStringTam];
} Split;


// Função para ler o CSV e armazenar na struct principal
void readCsv(Personagem personagens[], char* fileToRead){
    char aux[lineMax];
    Split split;

    FILE* arq; 
    arq = fopen(fileToRead, "r");
    if ( arq == NULL ) {
        printf("Erro ao abrir arquivo");
        return;
    }

    fgets(aux, sizeof(aux), arq);

    // Ler uma linha do CSV separando os atributos em cada posição do split, e depois ir setando na struct pricipal, formatando quando necessário
    int k = 0;
    while ( !(feof(arq)) ){
        for ( int i = 0; i < attributes; i++ ) {
            fscanf(arq, "%[^;\n]", split.stringSplited[i]);
            fgetc(arq);
        }

        strcpy(personagens[k].id, split.stringSplited[0]);

        strcpy(personagens[k].name, split.stringSplited[1]);

            removeStringChar(split.stringSplited[2], '[');
            removeStringChar(split.stringSplited[2], ']');
            removeStringChar(split.stringSplited[2], '\'');
        strcpy(personagens[k].alternateNames, split.stringSplited[2]);

        strcpy(personagens[k].house, split.stringSplited[3]);

        strcpy(personagens[k].ancestry, split.stringSplited[4]);

        strcpy(personagens[k].species, split.stringSplited[5]);

        strcpy(personagens[k].patronus, split.stringSplited[6]);

        stringBooleanFormat(split.stringSplited[7]);
        strcpy(personagens[k].hogwartsStaff, split.stringSplited[7]);

        stringBooleanFormat(split.stringSplited[8]);
        strcpy(personagens[k].hogwartsStudent, split.stringSplited[8]);

        strcpy(personagens[k].actorName, split.stringSplited[9]);

        stringBooleanFormat(split.stringSplited[10]);
        strcpy(personagens[k].alive, split.stringSplited[10]);

        strcpy(personagens[k].alternateActors, split.stringSplited[11]);

        personagens[k].dateOfBirth = stringDateFormat(split.stringSplited[12]);

        personagens[k].yearOfBirth = atoi(split.stringSplited[13]);

        strcpy(personagens[k].eyeColor, split.stringSplited[14]);

        strcpy(personagens[k].gender, split.stringSplited[15]);

        strcpy(personagens[k].hairColor, split.stringSplited[16]);

        stringBooleanFormat(split.stringSplited[17]);
        strcpy(personagens[k].wizard, split.stringSplited[17]);

        for ( int i = 0; i < attributes; i++ ) split.stringSplited[i][0] = 0;

        k++;
    }

    personagens[k].id[0] = '\0';

    fclose(arq);
}

// -------------------------------------------------------------------------------------------------------------------------

                        // Funções auxiliares para formatar uma string expecifica

// Mudar de VERDADEIRO ou FALSO para true or false
void stringBooleanFormat(char* aux){
    aux[0] == 'V' ? strcpy(aux, "true") : strcpy(aux, "false");
}

// Passar uma string para int
int stringIntFormat(const char* aux){
    return atoi(aux);
}

// Passar uma string para LocalDate
LocalDate stringDateFormat(char* aux){
    LocalDate formated;

    sscanf(aux, "%d-%d-%d", &formated.day, &formated.month, &formated.year);
    
    return formated;
}

// Remover o char 'c' da string
void removeStringChar(char* aux, char c){
    int i = 0;
    int j = 0;
    while (aux[i] != '\0') {
        if (aux[i] != c) aux[j++] = aux[i];
        i++;
    }
    aux[j] = '\0';
}

#endif 