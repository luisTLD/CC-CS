#ifndef MyList_h
#define MyList_h

#include <stdlib.h>
#include <stdio.h>

// Pilha / Fila / Lista Dupla / Matriz / Arvore


    // Celula para as estruturas

typedef struct Celula Celula;
struct Celula
{
    int value;
    Celula* prox;
    Celula* ant;
};


    // Pilha

/*
Inicializar com Pilha new = iniciarPilha();

Metodos: 
iniciarPilha();
inserirPilha(Pilha* pilha, int x);
removerPilha(Pilha* pilha);
contarPilha(Pilha* pilha);
mostrarPilha(Pilha* pilha); 
*/
typedef struct Pilha Pilha;
struct Pilha
{
    Celula* topo;
};

// Funcoes

// Pilha new = iniciarPilha();
Pilha iniciarPilha();
// Inserir
void inserirPilha(Pilha* pilha, int x);
// Remover e retornar (-1 caso vazia)
int removerPilha(Pilha* pilha);
// Quantidade de elementos na pilha
int contarPilha(Pilha* pilha);
// Mostra a pilha na ordem que foram inseridos
void mostrarPilha(Pilha* pilha);
// Inverter pilha
void mostrarPilhaCall(Celula* aux);


Pilha iniciarPilha()
{
    Pilha tmp;
    tmp.topo = NULL;
    return tmp;
}

void inserirPilha(Pilha* pilha, int x)
{
    Celula* tmp = (Celula*)malloc(1 * sizeof(Celula));
    tmp->value = x;
    tmp->prox = pilha->topo;
    pilha->topo = tmp;
    tmp = NULL;    
}

int removerPilha(Pilha* pilha)
{
    int resp = 0;
    if (pilha->topo != NULL)
    {
        Celula* tmp = pilha->topo;
        resp = tmp->value;
        pilha->topo = tmp->prox;
        tmp->prox = NULL;
        free(tmp);
    }
    else 
    {
        printf("Pilha vazia");
        resp = -1;
    }

    return resp;
}

int contarPilha(Pilha* pilha)
{
    Celula* aux = pilha->topo;

    int sum = 0;
    while(aux != NULL){
        sum++;
        aux = aux->prox;
    }

    return sum;
}

void mostrarPilha(Pilha* pilha)
{   
    if (pilha->topo == NULL) printf("Pilha vazia");
    else
    {
        Celula* aux = pilha->topo;
        mostrarPilhaCall(aux);
    }
}
void mostrarPilhaCall(Celula* aux)
{
    if (aux->prox != NULL) mostrarPilhaCall(aux->prox);
    printf("%d ", aux->value);
}

void inverterPilha(Pilha* p){
    Pilha aux = iniciarPilha();

    while ( p->topo != NULL ){
        inserirPilha(&aux, removerPilha(p));
    }

    *p = aux; 
}





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
struct Fila{
    Celula* primeiro;
    Celula* ultimo;
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
    tmp.primeiro = (Celula*)malloc(1 * sizeof(Celula));
    tmp.ultimo = tmp.primeiro;
    tmp.primeiro->prox = NULL;

    return tmp;
}

void inserirFila(Fila* fila, int x)
{
    Celula* aux = (Celula*)malloc(1 * sizeof(Celula));
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
        Celula* aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        free(aux);
    }

    return resp;
}

int ContarFila(Fila* fila)
{
    Celula* aux = fila->primeiro->prox;

    int sum = 0;
    while (aux != NULL){
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
        Celula* aux = fila->primeiro->prox;
        while (aux != NULL) {
            printf("%d ", aux->value);
            aux = aux->prox;
        }
    }
}






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
struct Lista{
    Celula* primeiro;
    Celula* ultimo;
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
    Celula *aux = (Celula*)malloc(1 * sizeof(Celula));
    aux->prox = NULL;
    aux->ant = NULL;
    tmp.primeiro = aux;
    tmp.ultimo = aux;
    aux = NULL;

    return tmp;
}

void inserirInicioLista(Lista* lista, int x)
{
    Celula* aux = (Celula*)malloc(1 * sizeof(Celula));
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
    lista->ultimo->prox = (Celula*)malloc(1 * sizeof(Celula));
    lista->ultimo->prox->ant = lista->ultimo;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->value = x;
    lista->ultimo->prox = NULL;
}

void inserirPosiLista(Lista* lista, int x, int posi)
{
    Celula* tmp = lista->primeiro;
    for ( int i = 0; i < posi; i++ )
    {
        if (tmp == NULL)
        {
            printf("Posi invalida");
            return;
        }
        tmp = tmp->prox;
    }
    
    Celula* aux = (Celula*)malloc(1 * sizeof(Celula));
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

    Celula* tmp = lista->primeiro;
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
    Celula* aux = lista->primeiro->prox;

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
        Celula* aux = lista->primeiro->prox;
        while (aux != NULL) {
            printf("%d ", aux->value);
            aux = aux->prox;
        }
    }
}





    // Matriz encadeada







    // Arvore Binaria de Pesquisa


#endif