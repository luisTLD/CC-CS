#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node_AVL Node_AVL;
typedef struct Avl Avl;

    // Declaracoes das funcoes

// Função para inicializar a árvore AVL
void startAVL(Avl* avl);
// Altura de um no
int getHeightAVL(Node_AVL* n);
// Maior altura entre os 2 filhos de um no
int maxSubHeightAVL(Node_AVL* n);
// Fator balanceamento de um no
int getBalanceAVL(Node_AVL* n);
// Printar arvore por altura
void printLevelOrderAVL(Avl* avl);
void compactQueueAVL(Node_AVL* queue[], int* start, int* end);
// Funcao para balancear e retornar o no
Node_AVL* balanceNodeAVL(Node_AVL* node);
// Rotacao simples direita
Node_AVL* rightRotateAVL(Node_AVL* actual);
// Rotacao simples esquerda
Node_AVL* leftRotateAVL(Node_AVL* actual);
// Rotacao esquerda direita
Node_AVL* leftRightRotateAVL(Node_AVL* node);
// Rotacao direita esquerda
Node_AVL* rightLeftRotateAVL(Node_AVL* node);
// Criar um novo no
Node_AVL* newNodeAVL(int x);
// Criar e inserir um novo no
void insertAVL(Avl* avl, int value);
Node_AVL* insertCallAVL(Node_AVL* node, int value);

struct Avl 
{
    Node_AVL* root;
};

struct Node_AVL
{
    Node_AVL* left;
    Node_AVL* right;
    int value;
    int height;
};

void startAVL(Avl* avl)
{
    avl->root = NULL;
}

Node_AVL* newNodeAVL(int x)
{
    Node_AVL* tmp = (Node_AVL*)malloc(sizeof(Node_AVL));

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    tmp->value = x;

    return tmp;
}

int getHeightAVL(Node_AVL* n)
{
    return n ? n->height : 0;
}

int maxSubHeightAVL(Node_AVL* n)
{
    int l = getHeightAVL(n->left);
    int r = getHeightAVL(n->right);
    return l > r ? l : r;
}

int getBalanceAVL(Node_AVL* n)
{
    return n ? getHeightAVL(n->left) - getHeightAVL(n->right) : 0;
}

Node_AVL* balanceNodeAVL(Node_AVL* node)
{
    int balance = getBalanceAVL(node);
    int left_balance = getBalanceAVL(node->left);
    int right_balance = getBalanceAVL(node->right);

    // Desbalanceamento a esquerda (rotação simples a direita)
    if (balance > 1 && left_balance >= 0) return rightRotateAVL(node);

    // Desbalanceamento a direita (rotação simples a esquerda)
    if (balance < -1 && right_balance <= 0) return leftRotateAVL(node);

    // Desbalanceamento a esquerda-direita (rotação dupla a esquerda)
    if (balance > 1 && left_balance < 0) return leftRightRotateAVL(node);

    // Desbalanceamento a direita-esquerda (rotação dupla a direita)
    if (balance < -1 && right_balance > 0) return rightLeftRotateAVL(node);

    // Se o no estiver balanceado
    return node;
}

Node_AVL* rightRotateAVL(Node_AVL* actual)
{
    Node_AVL* actual_left = actual->left;         // O filho a esquerda de "actual"
    Node_AVL* actual_left_right = actual_left->right;    // O filho a direita de "left"

    // Realizando a rotação
    actual_left->right = actual;
    actual->left = actual_left_right;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeightAVL(actual);
    actual_left->height = 1 + maxSubHeightAVL(actual_left);

    // Retornando o novo no raiz
    return actual_left;
}

Node_AVL* leftRotateAVL(Node_AVL* actual)
{
    Node_AVL* actual_right = actual->right;        // O filho a direita de "actual"
    Node_AVL* actual_right_left = actual_right->left;     // O filho a esquerda de "right"

    // Realizando a rotação
    actual_right->left = actual;
    actual->right = actual_right_left;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeightAVL(actual);
    actual_right->height = 1 + maxSubHeightAVL(actual_right);

    // Retornando o novo no raiz
    return actual_right;
}

Node_AVL* leftRightRotateAVL(Node_AVL* node)
{
    node->left = leftRotateAVL(node->left);
    return rightRotateAVL(node);
}

Node_AVL* rightLeftRotateAVL(Node_AVL* node)
{
    node->right = rightRotateAVL(node->right);
    return leftRotateAVL(node);
}

void insertAVL(Avl* avl, int value)
{
    avl->root = insertCallAVL(avl->root, value);
}

Node_AVL* insertCallAVL(Node_AVL* node, int value)
{
    if (!node) return newNodeAVL(value);  // Cria um novo no se o no atual for NULL
    else if (value < node->value) node->left = insertCallAVL(node->left, value); 
    else if (value > node->value) node->right = insertCallAVL(node->right, value);
    else return node;  // Nao permite duplicatas

    node->height = 1 + maxSubHeightAVL(node);

    return balanceNodeAVL(node);  // Realiza o balanceamento apos a insercao
}

void printLevelOrderAVL(Avl* avl)
{
    Node_AVL* queue[100];

    int start = 0;
    int end = 0;

    // Adicionar a raiz a fila
    if (avl->root) 
    {
        queue[end] = avl->root;
        end++;
    }

    // Enquanto houver elementos na fila
    while (start < end)
    {
        // Pegar o primeiro elemento e printar
        Node_AVL* node = queue[start++];
        printf("%d ", node->value);

        // Verifica se a fila esta quase cheia para reorganizar 
        if (end > 96) compactQueueAVL(queue, &start, &end);

        // Adicionar os filhos a lista
        if (node->left) queue[end++] = node->left;
        if (node->right) queue[end++] = node->right;
    }
}

void compactQueueAVL(Node_AVL* queue[], int* start, int* end)
{
    int j = 0;

    // Desloca todos os elementos para o início do array
    for (int i = *start; i < *end; i++) queue[j++] = queue[i];
   
    // Ajusta os ponteiros para refletir a nova posicao
    *start = 0;
    *end = j;
}

#endif