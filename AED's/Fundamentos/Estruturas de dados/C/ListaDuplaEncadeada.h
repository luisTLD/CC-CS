#ifndef ListaDuplaEncadeada_h
#define ListaDuplaEncadeada_h

#include <stdlib.h>
#include <stdio.h>

typedef struct CelulaL CelulaL;
struct CelulaL
{
    int value;
    CelulaL* prox;
    CelulaL* ant;
};

    // Lista Dupla

/*
Inicializar com Lista new = iniciarLista();

Metodos:
Lista iniciarLista();
void inserirInicioLista(Lista* lista, int x);
void inserirFimLista(Lista* lista, int x);
void inserirPosiLista(Lista* lista, int x, int posi);
int removerInicioLista(Lista* lista);
int removerFimLista(Lista* lista);
int removerPosiLista(Lista* lista, int resp);
int contarLista(Lista* lista);
void mostrarLista(Lista* lista);
*/
typedef struct Lista Lista;
struct Lista
{
    CelulaL* primeiro;
    CelulaL* ultimo;
};


// Lista new = iniciarLista()
Lista iniciarLista();
// Inserir inicio
void inserirInicioLista(Lista* lista, int x);
// Inserir final
void inserirFimLista(Lista* lista, int x);
// Inserir na posição expecifica da Lista
void inserirPosiLista(Lista* lista, int x, int posi);
// Remover Inicio e retornar (-1 caso vazia)
int removerInicioLista(Lista* lista);
// Remover Final da Lista
int removerFimLista(Lista* lista);
// Remover posição expecifica da Lista
int removerPosiLista(Lista* lista, int resp);
// Total de elementos na lista
int contarLista(Lista* lista);
// Mostrar a lista
void mostrarLista(Lista* lista);


Lista iniciarLista()
{
    Lista tmp;
    CelulaL *aux = (CelulaL*)malloc(1 * sizeof(CelulaL));
    aux->prox = NULL;
    aux->ant = NULL;
    tmp.primeiro = aux;
    tmp.ultimo = aux;
    aux = NULL;

    return tmp;
}

void inserirInicioLista(Lista* lista, int x)
{
    CelulaL* aux = (CelulaL*)malloc(1 * sizeof(CelulaL));
    aux->value = x;
    aux->ant = lista->primeiro;
    aux->prox = lista->primeiro->prox;
    lista->primeiro->prox = aux;

    if (lista->primeiro == lista->ultimo) lista->ultimo = aux;
    else aux->prox->ant = aux;

    aux = NULL;
}

void inserirFimLista(Lista* lista, int x)
{
    lista->ultimo->prox = (CelulaL*)malloc(1 * sizeof(CelulaL));
    lista->ultimo->prox->ant = lista->ultimo;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->value = x;
    lista->ultimo->prox = NULL;
}

void inserirPosiLista(Lista* lista, int x, int posi)
{
    CelulaL* tmp = lista->primeiro;
    for ( int i = 0; i < posi; i++ )
    {
        if (tmp == NULL)
        {
            printf("Posi invalida");
            return;
        }
        tmp = tmp->prox;
    }
    
    CelulaL* aux = (CelulaL*)malloc(1 * sizeof(CelulaL));
    aux->value = x;
    aux->prox = tmp->prox;
    aux->ant = tmp;
    tmp->prox = aux;
    if (lista->ultimo == tmp) lista->ultimo = aux;
    else aux->prox->ant = aux;

    aux = NULL;
    tmp = NULL;
}

int removerInicioLista(Lista* lista)
{
    int resp = 0;
    if (lista->primeiro == lista->ultimo)
    {
        printf("Lista vazia");
        resp = -1;
    }
    else
    {
        resp = lista->primeiro->prox->value;
        lista->primeiro->prox = lista->primeiro->prox->prox;
        free(lista->primeiro->prox->ant);
        lista->primeiro->prox->ant = lista->primeiro;
    }

    return resp;
}

int removerFimLista(Lista* lista)
{
    int resp = 0;

    if (lista->primeiro == lista->ultimo)
    {
        printf("Lista vazia");
        resp = -1;
    }
    else
    {
    resp = lista->ultimo->value;
    lista->ultimo = lista->ultimo->ant;
    free(lista->ultimo->prox);
    lista->ultimo->prox = NULL;
    }

    return resp;
}

int removerPosiLista(Lista* lista, int posi)
{   
    int resp = 0;

    CelulaL* tmp = lista->primeiro;
    for ( int i = 0; i < posi + 1; i++ )
    {
        if (tmp == NULL)
        {
            printf("Posi invalida");
            return -1;
        }
        tmp = tmp->prox;
    }

    if (lista->ultimo == tmp)
    {
        resp = tmp->value;
        lista->ultimo = tmp->ant;
        free(lista->ultimo->prox);
        lista->ultimo->prox = NULL;
    }
    else
    {
        tmp->prox->ant = tmp->ant;
        tmp->ant->prox = tmp->prox;
        resp = tmp->value;
        free(tmp);
    }

    return resp;
}

int contarLista(Lista* lista)
{
    CelulaL* aux = lista->primeiro->prox;

    int total = 0;
    while ( aux != NULL )
    {
        total++;
        aux = aux->prox;
    }

    return total;
}

void mostrarLista(Lista* lista)
{   
    if (lista->primeiro->prox == NULL) printf("Lista vazia");
    else
    {
        CelulaL* aux = lista->primeiro->prox;
        while (aux != NULL) {
            printf("%d ", aux->value);
            aux = aux->prox;
        }
    }
}

#endif
