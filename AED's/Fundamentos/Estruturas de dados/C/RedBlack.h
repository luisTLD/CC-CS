#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdlib.h>
#include <stdio.h>

#define RED 1
#define BLACK 0

typedef struct Node_RB Node_RB;
typedef struct Red_Black Red_Black;

    // Declaracoes das funcoes

// Iniciar raiz com NULL
void startRB(Red_Black* rb);
// Criar novo no RED
Node_RB* newNodeRB(int x);
// Rotacao para esquerda
void leftRotateRB(Node_RB** root, Node_RB* actual);
// Rotacao para direita
void rightRotateRB(Node_RB** root, Node_RB* actual);
// Inserir na RB
void insertRB(Red_Black* rb, int value);
// Corrigir o balanceamento da RB apos inserir
void balanceRB(Node_RB** root, Node_RB* actual);
// Printar a RB em niveis
void printLevelOrderRB(Red_Black* rb);
// Reorganizar a fila para printar em nivel
void compactQueueRB(Node_RB* queue[], int* start, int* end);

struct Red_Black
{
    Node_RB* root;
};

struct Node_RB
{
    int color;
    int value;

    Node_RB* right;
    Node_RB* left;
    Node_RB* parent;
};

void startRB(Red_Black* rb)
{
    rb->root = NULL;
}

Node_RB* newNodeRB(int x)
{
    Node_RB* tmp = (Node_RB*)malloc(1 * sizeof(Node_RB));

    tmp->color = RED;
    tmp->value = x;

    tmp->right = NULL;
    tmp->left = NULL;
    tmp->parent = NULL;

    return tmp;
}

void leftRotateRB(Node_RB** root, Node_RB* actual)
{
    
    Node_RB* actual_right = actual->right;  // Salva o no a direita do no atual
    actual->right = actual_right->left;     // Desce o no atual a esquerda do no a direita

    // Se o no a direita tiver um filho a esquerda, atualiza seu pai
    if (actual_right->left) actual_right->left->parent = actual;

    actual_right->parent = actual->parent;  // Atualiza o pai do no a direita

    // Se o no atual for a raiz, atualiza a raiz
    if (actual->parent == NULL) *root = actual_right;
    // Se o no atual for filho esquerdo, atualiza o pai
    else if (actual == actual->parent->left) actual->parent->left = actual_right;
    // Se o no atual for filho direito, atualiza o pai
    else actual->parent->right = actual_right;

    actual_right->left = actual;      // Coloca o no atual a esquerda do no a direita
    actual->parent = actual_right;    // Atualiza o pai do no atual
}

void rightRotateRB(Node_RB** root, Node_RB* actual)
{
    Node_RB* actual_left = actual->left;   // Salva o no a esquerda do no atual
    actual->left = actual_left->right;     // Desce o no atual a direita do no a esquerda

    // Se o no a esquerda tiver um filho a direita, atualiza seu pai
    if (actual_left->right) actual_left->right->parent = actual;

    actual_left->parent = actual->parent;  // Atualiza o pai do no a esquerda

    // Se o no atual for a raiz, atualiza a raiz
    if (actual->parent == NULL) *root = actual_left;
    // Se o no atual for filho direito, atualiza o pai
    else if (actual == actual->parent->right) actual->parent->right = actual_left;
    // Se o no atual for filho esquerdo, atualiza o pai
    else actual->parent->left = actual_left;

    actual_left->right = actual;      // Coloca o no atual a direita do no a esquerda
    actual->parent = actual_left;     // Atualiza o pai do no atual
}

void insertRB(Red_Black* rb, int value)
{
    Node_RB* new_node = newNodeRB(value);   // Cria um novo no vermelho com o valor fornecido
    Node_RB* parent = NULL;                 // Ponteiro para o pai do novo no
    Node_RB* actual = rb->root;             // Ponteiro auxiliar para navegar pela arvore, começa pela raiz

    // Navega pela arvore para encontrar a posicao correta do novo no
    while (actual != NULL)
    {
        parent = actual;  // Atualiza o ponteiro do pai para o no atual

        // Se o valor do novo no for menor, vai para a subarvore esquerda
        if (new_node->value < actual->value) actual = actual->left;
        // Se o valor for maior ou igual, vai para a subarvore direita
        else actual = actual->right;
    }

    // Define o pai do novo no (sera NULL se a arvore estiver vazia)
    new_node->parent = parent;

    // Se a arvore estiver vazia, o novo no se torna a raiz
    if (parent == NULL) rb->root = new_node;
    // Se o valor do novo no for menor que o valor do pai, insere a esquerda
    else if (new_node->value < parent->value) parent->left = new_node;
    // Se o valor for maior ou igual, insere a direita
    else parent->right = new_node;
    
    // Corrige possiveis violacoes das propriedades da arvore Red-Black apos a insercao
    balanceRB(&(rb->root), new_node);
}

void balanceRB(Node_RB** root, Node_RB* actual)
{
    // Enquanto o no atual nao for a raiz e o pai for vermelho (violacao das regras)
    while (actual != *root && actual->parent->color == RED)
    {
        Node_RB* grandparent = actual->parent->parent; // Avo do no atual

        // Se o pai do no atual for o filho esquerdo do avo
        if (actual->parent == grandparent->left)
        {
            Node_RB* uncle = grandparent->right; // Tio do no atual

            // Caso o tio seja vermelho
            if (uncle != NULL && uncle->color == RED)
            {
                // Caso 1: Recoloraçao (Pai e Tio viram preto, Avo vira vermelho)
                actual->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                actual = grandparent; // Subir o no atual para o avo
            }
            else
            {
                // Caso 2: Se o no atual for filho direito, rotaciona a esquerda
                if (actual == actual->parent->right)
                {
                    actual = actual->parent;
                    leftRotateRB(root, actual); // Rotaciona a esquerda
                }

                // Caso 3: Recoloraçao e rotaçao a direita no avo
                actual->parent->color = BLACK;
                grandparent->color = RED;
                rightRotateRB(root, grandparent); // Rotaciona a direita
            }
        }
        else
        {
            Node_RB* uncle = grandparent->left; // Tio do no atual

            // Caso o tio seja vermelho
            if (uncle != NULL && uncle->color == RED)
            {
                // Caso 1: Recoloraçao (Pai e Tio viram preto, Avo vira vermelho)
                actual->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                actual = grandparent; // Subir o no atual para o avo
            }
            else
            {
                // Caso 2: Se o no atual for filho esquerdo, rotaciona a direita
                if (actual == actual->parent->left)
                {
                    actual = actual->parent;
                    rightRotateRB(root, actual); // Rotaciona a direita
                }

                // Caso 3: Recoloraçao e rotaçao a esquerda no avo
                actual->parent->color = BLACK;
                grandparent->color = RED;
                leftRotateRB(root, grandparent); // Rotaciona a esquerda
            }
        }
    }

    (*root)->color = BLACK; // Garantir que a raiz seja sempre preta
}

void printLevelOrderRB(Red_Black* rb)
{
    Node_RB* queue[100];
    int start = 0;
    int end = 0;

    // Adicionar a raiz da fila
    if (rb->root) 
    {
        queue[end] = rb->root;
        end++;
    }

    // Enquanto houver elementos na fila
    while (start < end)
    {
        // Pega o primeiro elemento da fila
        Node_RB* node = queue[start++];

        // Imprime o valor do no e sua cor
        printf("Valor: %d, Cor: %s\n", node->value, node->color == RED ? "Vermelho" : "Preto");

        // Verifica se a fila esta quase cheia e a reorganiza, se necessario
        if (end > 96) compactQueueRB(queue, &start, &end);

        // Adiciona os filhos do no da fila
        if (node->left) queue[end++] = node->left;
        if (node->right) queue[end++] = node->right;
    }
}

void compactQueueRB(Node_RB* queue[], int* start, int* end)
{
    int j = 0;

    // Desloca todos os elementos para o inicio do array
    for (int i = *start; i < *end; i++) queue[j++] = queue[i];

    // Ajusta os ponteiros para refletir a nova posicao
    *start = 0;
    *end = j;
}

#endif