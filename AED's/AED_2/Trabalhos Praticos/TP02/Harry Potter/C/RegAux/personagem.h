#ifndef personagem_h
#define personagem_h

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define auxStringTam 200
#define auxArrayTam 200

// Struct para o LocalDate
typedef struct{
    int day;
    int month;
    int year;
} LocalDate;

// Struct principal
typedef struct{
    char id[auxStringTam];
    char name[auxStringTam];
    char alternateNames[auxArrayTam];
    char house[auxStringTam];
    char ancestry[auxStringTam];
    char species[auxStringTam];
    char patronus[auxStringTam];
    char hogwartsStaff[auxStringTam];
    char hogwartsStudent[auxStringTam];
    char actorName[auxStringTam];
    char alive[auxStringTam];
    char alternateActors[auxStringTam];
    LocalDate dateOfBirth;
    int yearOfBirth;
    char eyeColor[auxStringTam];
    char gender[auxStringTam];
    char hairColor[auxStringTam];
    char wizard[auxStringTam];
} Personagem;


// Função para printar todos os atributos de um personagem expecifico
void printPersonagem(const Personagem personagem) { //                             LocalDate
    printf("[%s ## %s ## {%s} ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %s ## %02d-%02d-%02d ## %d ## %s ## %s ## %s ## %s]\n",
            personagem.id,
            personagem.name,
            personagem.alternateNames,
            personagem.house,
            personagem.ancestry,
            personagem.species,
            personagem.patronus,
            personagem.hogwartsStaff,
            personagem.hogwartsStudent,
            personagem.actorName,
            personagem.alive,
            personagem.dateOfBirth.day,
            personagem.dateOfBirth.month,
            personagem.dateOfBirth.year,
            personagem.yearOfBirth,
            personagem.eyeColor,
            personagem.gender,
            personagem.hairColor,
            personagem.wizard);
}


// Declaração das funções
void printPersonagem(const Personagem personagem);
void printAllPersonagens(Personagem personagens[]);
Personagem* mySubList(const Personagem personagens[]);
Personagem* createNewSubList(const Personagem personagens[], int max);
int endOfList(Personagem personagem);
int lengthOfList(const Personagem personagens[]);
int linearIdSearch(const Personagem personagens[], char* id);
int binaryNameSearch(Personagem personagens[], int begin, int end, char *resp);
void nameVerifierBinarySearch(Personagem personagens[]);


// Printar todos os personagens da lista
void printAllPersonagens(Personagem personagens[]){
    Personagem* aux = &personagens[0];

    while ( !endOfList(*aux) ){
        printPersonagem(*aux);
        aux++;
    }
}

// Retorna uma subLista de personagens, contendo apenas os pesquisados
Personagem* mySubList(const Personagem personagens[]){
    Personagem* aux = (Personagem*)malloc(100 * sizeof(Personagem));
    int length = 0;

    char id[auxStringTam];
    scanf(" %s", id);

    while(strcmp(id, "FIM")){
        int i = linearIdSearch(personagens, id);

        if ( i != -1 ) aux[length++] = personagens[i];
        else printf("Personagem %s nao encontrado\n", id);

        scanf(" %s", id);
    }

    aux[length++].id[0] = '\0';

    aux = (Personagem*)realloc(aux, length * sizeof(Personagem));

    return aux;
}

// Cria uma subLista com os N primeiros elementos de outra lista
Personagem* createNewSubList(const Personagem personagens[], int max){
    Personagem* aux = (Personagem*)malloc((max + 1) * sizeof(Personagem));

    for ( int i = 0; i < max; i++ ){
        aux[i] = personagens[i];
    }

    aux[max].id[0] = '\0';

    return aux;
}

// Verificar se chegou no ultimo elemento do array preenchido
int endOfList(Personagem personagem){
    return personagem.id[0] == '\0';
}

// Retornar o tamanho do array
int lengthOfList(const Personagem personagens[]){
    int length = 0;

    while (!endOfList(personagens[length])) length++;

    return length;
}

// Função para busca linear por ID
int linearIdSearch(const Personagem personagens[], char* id){
    int index = -1;
    int max = lengthOfList(personagens);

    for ( int i = 0; i < max; i++){

        if ( strcmp(personagens[i].id, id) == 0 ){
            index = i;
            break;
        }
    }

    return index;
}

// Função para busca Binaria por Name
int binaryNameSearch(Personagem personagens[], int begin, int end, char *resp){
    if (begin <= end) {
        int middle = ((begin + end) / 2);

        if (strcmp(personagens[middle].name, resp) == 0) return middle;
        else if (strcmp(personagens[middle].name, resp) < 0) return binaryNameSearch(personagens, middle + 1, end, resp);
        else return binaryNameSearch(personagens, begin, middle - 1, resp);
    }

    return -1;
}

// Verificar se o nome esta presente em um array ordenado
void nameVerifierBinarySearch(Personagem personagens[]){
    char input[auxStringTam];

    scanf(" %[^\r]", input);
    while ( (strcmp(input, "FIM") != 0) ){

        int index = binaryNameSearch(personagens, 0, lengthOfList(personagens), input);

        if ( index != -1 ) printf("SIM\n");
        else printf("NAO\n");

        scanf(" %[^\r]", input);
    }
}


#endif