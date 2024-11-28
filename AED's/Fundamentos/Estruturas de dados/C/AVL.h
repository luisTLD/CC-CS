#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node_AVL Node_AVL;
typedef struct Avl Avl;

    // Declaracoes das funcoes

// Função para inicializar a árvore AVL
void start(Avl* avl);
// Altura de um no
int getHeight(Node_AVL* n);
// Maior altura entre os 2 filhos de um no
int maxSubHeight(Node_AVL* n);
// Fator balanceamento de um no
int getBalance(Node_AVL* n);
// Printar arvore por altura
void printLevelOrder(Avl* avl);
void compactQueue(Node_AVL* queue[], int* start, int* end);
// Funcao para balancear e retornar o no
Node_AVL* balanceNode(Node_AVL* node);
// Rotacao simples direita
Node_AVL* rightRotate(Node_AVL* actual);
// Rotacao simples esquerda
Node_AVL* leftRotate(Node_AVL* actual);
// Rotacao esquerda direita
Node_AVL* leftRightRotate(Node_AVL* node);
// Rotacao direita esquerda
Node_AVL* rightLeftRotate(Node_AVL* node);
// Criar um novo no
Node_AVL* newNode(int x);
// Criar e inserir um novo no
void insert(Avl* avl, int value);
Node_AVL* insertCall(Node_AVL* node, int value);

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

void start(Avl* avl)
{
    avl->root = NULL;
}

Node_AVL* newNode(int x)
{
    Node_AVL* tmp = (Node_AVL*)malloc(sizeof(Node_AVL));

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    tmp->value = x;

    return tmp;
}

int getHeight(Node_AVL* n)
{
    return n ? n->height : 0;
}

int maxSubHeight(Node_AVL* n)
{
    int l = getHeight(n->left);
    int r = getHeight(n->right);
    return l > r ? l : r;
}

int getBalance(Node_AVL* n)
{
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node_AVL* balanceNode(Node_AVL* node)
{
    int balance = getBalance(node);
    int left_balance = getBalance(node->left);
    int right_balance = getBalance(node->right);

    // Desbalanceamento a esquerda (rotação simples a direita)
    if (balance > 1 && left_balance >= 0) return rightRotate(node);

    // Desbalanceamento a direita (rotação simples a esquerda)
    if (balance < -1 && right_balance <= 0) return leftRotate(node);

    // Desbalanceamento a esquerda-direita (rotação dupla a esquerda)
    if (balance > 1 && left_balance < 0) return leftRightRotate(node);

    // Desbalanceamento a direita-esquerda (rotação dupla a direita)
    if (balance < -1 && right_balance > 0) return rightLeftRotate(node);

    // Se o no estiver balanceado
    return node;
}

Node_AVL* rightRotate(Node_AVL* actual)
{
    Node_AVL* actual_left = actual->left;         // O filho a esquerda de "actual"
    Node_AVL* actual_left_right = actual_left->right;    // O filho a direita de "left"

    // Realizando a rotação
    actual_left->right = actual;
    actual->left = actual_left_right;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeight(actual);
    actual_left->height = 1 + maxSubHeight(actual_left);

    // Retornando o novo no raiz
    return actual_left;
}

Node_AVL* leftRotate(Node_AVL* actual)
{
    Node_AVL* actual_right = actual->right;        // O filho a direita de "actual"
    Node_AVL* actual_right_left = actual_right->left;     // O filho a esquerda de "right"

    // Realizando a rotação
    actual_right->left = actual;
    actual->right = actual_right_left;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeight(actual);
    actual_right->height = 1 + maxSubHeight(actual_right);

    // Retornando o novo no raiz
    return actual_right;
}

Node_AVL* leftRightRotate(Node_AVL* node)
{
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

Node_AVL* rightLeftRotate(Node_AVL* node)
{
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

void insert(Avl* avl, int value)
{
    avl->root = insertCall(avl->root, value);
}

Node_AVL* insertCall(Node_AVL* node, int value)
{
    if (!node) return newNode(value);  // Cria um novo no se o no atual for NULL
    else if (value < node->value) node->left = insertCall(node->left, value); 
    else if (value > node->value) node->right = insertCall(node->right, value);
    else return node;  // Nao permite duplicatas

    node->height = 1 + maxSubHeight(node);

    return balanceNode(node);  // Realiza o balanceamento apos a insercao
}

void printLevelOrder(Avl* avl)
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
        if (end > 96) compactQueue(queue, &start, &end);

        // Adicionar os filhos a lista
        if (node->left) queue[end++] = node->left;
        if (node->right) queue[end++] = node->right;
    }
}

void compactQueue(Node_AVL* queue[], int* start, int* end)
{
    int j = 0;

    // Desloca todos os elementos para o início do array
    for (int i = *start; i < *end; i++) queue[j++] = queue[i];
   
    // Ajusta os ponteiros para refletir a nova posicao
    *start = 0;
    *end = j;
}

#endif
