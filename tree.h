#ifndef TREE_H
#define TREE_H

#include "client.h"

/**
 * Estrutura TREEnode - Um no de uma tree que armazena um item, dois ponteiros.
 * um para o filho da esquerda, outro para o da direita e a propriedade height
 * que permite o calculo da altura dos nos e do factor de balanco
 */
typedef struct TREEnode {
    Item2 item;
    int height;
    struct TREEnode *l, *r;
} *tnode;

/**
 * Estrutura tree - Um ponteiro para um TREEnode, em particular, a raiz da
 * instancia da arvore
 */
typedef struct tree {
    struct TREEnode *h;
} *Tree;

/* Construtor */
Tree TREEinit(); /* Inicializa a arvore */

/* Getters/Acessores */
int TREEcount(Tree);
Item2 TREEsearch(Tree, Item2);
Item2 TREEsearchByKey(Tree, Key2);

/* Setters/Mutadores */
void TREEadd(Tree, Item2); /* Adiciona um elemento a arvore */
void TREEremove(Tree, Item2); /* Remove o elemento passado como arg da arvore */
void TREEremoveByKey(Tree, Key2); /* Remove um elemento por chave */
void TREEfree(Tree); /* Liberta uma arvore e todos os seus elementos */

/* Testes */
int TREEisEmpty(Tree t); /* Verifica se a arvore se encontra vazia */

/* Representacao */
void TREEtraverse(Tree, void (*visit)(Item2)); /* Visita os elementos in-order */

#endif /* TREE_H */