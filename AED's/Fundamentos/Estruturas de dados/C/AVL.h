#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
typedef struct Avl Avl;

    // Declaracoes das funcoes

// Função para inicializar a árvore AVL
void start(Avl* avl);
// Altura de um no
int getHeight(Node* n);
// Maior altura entre os 2 filhos de um no
int maxSubHeight(Node* n);
// Fator balanceamento de um no
int getBalance(Node* n);
// Printar arvore por altura
void printLevelOrder(Avl* avl);
void compactQueue(Node* queue[], int* start, int* end);
// Funcao para balancear e retornar o no
Node* balanceNode(Node* node);
// Rotacao simples direita
Node* rightRotate(Node* actual);
// Rotacao simples esquerda
Node* leftRotate(Node* actual);
// Rotacao esquerda direita
Node* leftRightRotate(Node* node);
// Rotacao esquerda direita
Node* rightLeftRotate(Node* node);
// Criar um novo no
Node* newNode(int x);
// Criar e inserir um novo no
void insert(Avl* avl, int value);
Node* insertCall(Node* node, int value);

struct Avl 
{
    Node* root;
};

struct Node
{
    Node* left;
    Node* right;
    int value;
    int height;
};

void start(Avl* avl)
{
    avl->root = NULL;
}

int getHeight(Node* n)
{
    return n ? n->height : 0;
}

int maxSubHeight(Node* n)
{
    int l = getHeight(n->left);
    int r = getHeight(n->right);
    return l > r ? l : r;
}

int getBalance(Node* n)
{
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* balanceNode(Node* node)
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

Node* rightRotate(Node* actual)
{
    Node* left = actual->left;         // O filho a esquerda de "actual"
    Node* left_right = left->right;    // O filho a direita de "left"

    // Realizando a rotação
    left->right = actual;
    actual->left = left_right;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeight(actual);
    left->height = 1 + maxSubHeight(left);

    // Retornando o novo no raiz
    return left;
}

Node* leftRotate(Node* actual)
{
    Node* right = actual->right;        // O filho a direita de "actual"
    Node* right_left = right->left;     // O filho a esquerda de "right"

    // Realizando a rotação
    right->left = actual;
    actual->right = right_left;

    // Atualizando as alturas
    actual->height = 1 + maxSubHeight(actual);
    right->height = 1 + maxSubHeight(right);

    // Retornando o novo no raiz
    return right;
}

Node* leftRightRotate(Node* node)
{
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

Node* rightLeftRotate(Node* node)
{
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

Node* newNode(int x)
{
    Node* tmp = (Node*)malloc(sizeof(Node));

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    tmp->value = x;

    return tmp;
}

void insert(Avl* avl, int value)
{
    avl->root = insertCall(avl->root, value);
}

Node* insertCall(Node* node, int value)
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
    Node* queue[100];

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
        Node* node = queue[start++];
        printf("%d ", node->value);

        // Verifica se a fila esta quase cheia para reorganizar 
        if (end > 96) compactQueue(queue, &start, &end);

        // Adicionar os filhos a lista
        if (node->left) queue[end++] = node->left;
        if (node->right) queue[end++] = node->right;
    }
}

void compactQueue(Node* queue[], int* start, int* end)
{
    int j = 0;

    // Desloca todos os elementos para o início do array
    for (int i = *start; i < *end; i++) queue[j++] = queue[i];
   
    // Ajusta os ponteiros para refletir a nova posicao
    *start = 0;
    *end = j;
}

#endif
