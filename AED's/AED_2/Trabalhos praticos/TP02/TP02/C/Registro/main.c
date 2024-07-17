#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Variavel global para armazenar o tempo de execução do codigo
clock_t startTime;
clock_t endTime;
int totalComp = 0;
int totalMove = 0;

// Define auxiliares para strings, arrays, structs e atributos
#define lineMax 1000
#define auxStringTam 200
#define auxArrayTam 200
#define structList 500
#define attributes 18


// Struct para fazer um "split" enquanto lee o CSV
typedef struct{
    char stringSplited[attributes][auxStringTam];
} Split;


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

// -------------------------------------------------------------------------------------------------------------------------

                            // Declaração das funções criadas

// Ordenação
void selectionSortName(Personagem personagens[]);
void selectionSortRecName(Personagem personagens[], int max);
void quickSortHouseCall(Personagem personagens[], int left, int right);
void quickSortHouse(Personagem personagens[]);
void shellSortEyeColor(Personagem personagens[]);
void bubbleSortHairColor(Personagem personagens[]);
void heapSortHairColor(Personagem personagens[]);
void radixSortId(Personagem personagens[]);
void radixCountingSort(int exp, Personagem personagens[]);
void swap(Personagem *x, Personagem *y);

// Comparação para ordenar
int compareName(Personagem x, Personagem y);
int compareEyeColor(Personagem x, Personagem y);
int compareHouse(Personagem x, Personagem y);
int compareHairColor(Personagem x, Personagem y);
void toLowerCase(char *str);

// Busca
int linearIdSearch(const Personagem personagem[], char* id);
int binaryNameSearch(Personagem personagens[], int begin, int end, char *resp);
void nameVerifierBinarySearch(Personagem personagens[]);

// Expecificas de Personagem
void printPersonagem(const Personagem personagem);
void printAllPersonagens(Personagem personagens[]);
Personagem* mySubList(const Personagem personagens[]);
Personagem* createNewSubList(const Personagem personagens[], int max);
LocalDate stringDateFormat(char* aux);
int endOfList(Personagem personagem);
int lengthOfList(const Personagem personagens[]);

// Leitura de arquivo
void readCsv(Personagem personagens[], char* fileToRead);

// Funções para tempo de execução e comparações
void startTimer();
void endTimer();
void createLog();
void countComp();
void countMove();

// Auxiliares
void stringBooleanFormat(char* aux);
int stringIntFormat(const char* aux);
void removeStringChar(char* aux, char c);

// -------------------------------------------------------------------------------------------------------------------------

                            // Main

int main(){
    startTimer();

    Personagem personagens[structList];
    char input[auxStringTam];

    readCsv(personagens, "/tmp/characters.csv");

    Personagem* using = NULL;
    using = mySubList(personagens);
    heapSortHairColor(using);
    using = createNewSubList(using, 10);
    printAllPersonagens(using);

    endTimer();
    createLog();

    free(using);
    
    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

                            // Funções para busca de personagem

// Função para busca linear por ID
int linearIdSearch(const Personagem personagens[], char* id){
    int index = -1;
    int max = lengthOfList(personagens);

    for ( int i = 0; i < max; i++){
        countComp();

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
        countComp();
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


// -------------------------------------------------------------------------------------------------------------------------

                             // Funções para ordenação

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

                    countMove();
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

            countMove();
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
            countComp();

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

        countMove();
    }

    for (int i = 1; i < 128; i++){
        counting[i] += counting[i - 1];

        countMove();
    }

    for (int i = length - 1; i >= 0; i--) {
        output[counting[personagens[i].id[exp]] - 1] = personagens[i];
        counting[personagens[i].id[exp]]--;

        countMove();
    }

    for (int i = 0; i < length; i++){
        personagens[i] = output[i];

        countMove();
    }

    free(output);
    free(counting);
}

// Função auxiliar para trocar 2 personagens de lugar
void swap(Personagem *x, Personagem *y){
    Personagem aux = *x;
    *x = *y;
    *y = aux;

    countMove();
    countMove();
    countMove();
}


// -------------------------------------------------------------------------------------------------------------------------

                            // Funções para comparação de atributos, desempatando em Name

// Comparar por Name
int compareName(Personagem x, Personagem y){
    countComp();

    return strcmp(x.name, y.name);
}

// Comparar por EyeColor
int compareEyeColor(Personagem x, Personagem y){
    countComp();

    int aux = strcmp(x.eyeColor, y.eyeColor);

    if ( aux == 0 ) aux = compareName(x, y);

    return aux;
}

// Comparar por House
int compareHouse(Personagem x, Personagem y){
    countComp();

    int aux = strcmp(x.house, y.house);

    if ( aux == 0 ) aux = compareName(x, y);

    return aux;
}

// Compara HairColor
int compareHairColor(Personagem x, Personagem y){
    countComp();

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

// -------------------------------------------------------------------------------------------------------------------------

                            // Funções auxiliares expecifica para Personagem

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

// -------------------------------------------------------------------------------------------------------------------------

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

// -------------------------------------------------------------------------------------------------------------------------

            // Funções para contar o tempo de execução do codigo, comparações, e criar um TXT de saida com as informações

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
    logArq = fopen("761670_heapsort.txt", "w");

    if (logArq == NULL) {
        printf("Erro ao criar o arquivo de log\n");
        return;
    }

    double totalTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    totalTime = totalTime * 1000;

    fprintf(logArq, "%s\t%f\t%d\t%d\n", "761670", totalTime, totalComp, totalMove);

    fclose(logArq);
}
