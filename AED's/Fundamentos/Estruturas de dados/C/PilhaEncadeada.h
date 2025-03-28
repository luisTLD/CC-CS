#ifndef PILHAENCADEADA_H
#define PILHAENCADEADA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CelulaP CelulaP;
struct CelulaP
{
    int value;
    CelulaP* prox;
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
inverterPilha(Pilha* p);
inverterPilhaRec(Pilha* Pilha);
*/
typedef struct Pilha Pilha;
struct Pilha
{
    CelulaP* topo;
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
void mostrarPilhaCall(CelulaP* aux);
// Inverter pilha
void inverterPilha(Pilha* p);
// Inverter Pilha Recursivamente
void inverterPilhaRec(Pilha* Pilha);
void inverterPilhaAux(Pilha* pilha, CelulaP* i, CelulaP* j);


Pilha iniciarPilha()
{
    Pilha tmp;
    tmp.topo = NULL;
    return tmp;
}

void inserirPilha(Pilha* pilha, int x)
{
    CelulaP* tmp = (CelulaP*)malloc(1 * sizeof(CelulaP));
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
        CelulaP* tmp = pilha->topo;
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
    CelulaP* aux = pilha->topo;

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
        CelulaP* aux = pilha->topo;
        mostrarPilhaCall(aux);
    }
}
void mostrarPilhaCall(CelulaP* aux)
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

void inverterPilhaRec(Pilha* pilha)
{
    if (pilha->topo == NULL || pilha->topo->prox == NULL) return;
    CelulaP* aux = pilha->topo->prox;
    pilha->topo->prox = NULL;
    inverterPilhaAux(pilha, pilha->topo, aux);
}

void inverterPilhaAux(Pilha* pilha, CelulaP* i, CelulaP* j)
{
    if (j->prox != NULL) inverterPilhaAux(pilha, j, j->prox);
    else pilha->topo = j;
    j->prox = i;
}


#endif
