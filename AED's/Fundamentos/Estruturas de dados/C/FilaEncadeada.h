#ifndef FILAENCADEADA_H
#define FILAENCADEADA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct CelulaF CelulaF;
struct CelulaF
{
    int value;
    CelulaF* prox;
    CelulaF* ant;
};

    // Fila encadeada

/*
Inicializar com Fila new = iniciarFila();

Metodos:
iniciarFila(); 
inserirFila(Fila* fila, int x);
removerFila(Fila* fila);
ContarFila(Fila* fila);
mostrarFila(Fila* fila);
*/
struct Fila
{
    CelulaF* primeiro;
    CelulaF* ultimo;
};


// Fila new = iniciarFila();
Fila iniciarFila(); 
// Adicionar
void inserirFila(Fila* fila, int x);
// Remover e retornar (-1 caso vazia)
int removerFila(Fila* fila);
// Total de elementos na fila
int ContarFila(Fila* fila);
// Mostrar todos elementos
void mostrarFila(Fila* fila);
  

Fila iniciarFila()
{
    Fila tmp;
    tmp.primeiro = (CelulaF*)malloc(1 * sizeof(CelulaF));
    tmp.ultimo = tmp.primeiro;
    tmp.primeiro->prox = NULL;

    return tmp;
}

void inserirFila(Fila* fila, int x)
{
    CelulaF* aux = (CelulaF*)malloc(1 * sizeof(CelulaF));
    aux->value = x;
    aux->prox = NULL;
    fila->ultimo->prox = aux;
    fila->ultimo = aux;
    aux = NULL;
}

int removerFila(Fila* fila)
{
    int resp = 0;

    if (fila->primeiro == fila->ultimo) 
    {
        printf("Fila vazia!\n");
        resp = -1;
    }
    else
    {
        resp = fila->primeiro->prox->value;
        CelulaF* aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        free(aux);
    }

    return resp;
}

int ContarFila(Fila* fila)
{
    CelulaF* aux = fila->primeiro->prox;

    int sum = 0;
    while (aux != NULL)
    {
        sum++;
        aux = aux->prox;
    }

    return sum;
}

void mostrarFila(Fila* fila)
{
    if (fila->primeiro->prox == NULL) printf("Lista vazia");
    else
    {
        CelulaF* aux = fila->primeiro->prox;
        while (aux != NULL) {
            printf("%d ", aux->value);
            aux = aux->prox;
        }
    }
}


#endif
