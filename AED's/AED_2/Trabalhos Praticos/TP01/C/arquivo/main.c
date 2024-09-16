/*
Faça um programa que leia um número inteiro n indicando o número de valores reais 
que devem ser lidos e salvos sequencialmente em um arquivo texto. Após a leitura dos valores, 
devemos fechar o arquivo. Em seguida, reabri-lo e fazer a leitura de trás para frente usando os métodos 
getFilePointer e seek da classe RandomAccessFile e mostre todos os valores lidos na tela. Nessa questão, 
você não pode usar, arrays, strings ou qualquer estrutura de dados. 
A entrada padrão é composta por um número inteiro n e mais n números reais. 
A saída padrão corresponde a n números reais mostrados um por linha de saída.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *arq;
    arq = fopen("arquivo.txt", "w");
    if ( arq == NULL ){
        printf("Erro ao abrir arquivo");
        return 1;
    }

    int totalNum = 0;
    float input;

    scanf(" %d", &totalNum);

    for(int i = 0; i < totalNum; i++){
        scanf(" %f", &input);
        fprintf(arq, ";%f", input);
    }

    fclose(arq);

    arq = fopen("arquivo.txt", "r");
    fseek(arq, 0, SEEK_END);

    int savePoint = ftell(arq) - 1;
    float output = 0;
    char ver;

    while ( savePoint >= 0 ){
        ver = fgetc(arq);
        if ( ver == ';' ){
            fscanf(arq, "%f", &output);
            printf("%g\n", output); 
        }
        savePoint--;
        fseek(arq, savePoint, SEEK_SET);
    }

    fclose(arq);
    return 0;
}
