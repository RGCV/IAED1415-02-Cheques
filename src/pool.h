#ifndef POOL_H
#define POOL_H

#include "check.h"

/**
 * Estrutura POOLnode - Um no da pool, armazena um item e um ponteiro para
 * o elemento que se lhe segue
 */
typedef struct POOLnode {
    Item1 item;
    struct POOLnode *next;
} *pnode;

/**
 * Estrutura pool - Um ponteiro com dois ponteiros para POOLnodes, permite a
 * criacao e implementacao de multiplas pools
 */
typedef struct pool {
    struct POOLnode *head, *tail;
} *Pool;

/* Construtor */
Pool POOLinit(); /* Inicializa a pool */

/* Getter/Acessores */
int POOLcount(Pool); /* Numero de elementos na Pool */
Item1 POOLget(Pool); /* Procura e devolve um elemento (inserido ha mais tempo) */
Item1 POOLgetByKey(Pool, Key1); /* Procura por chave */

/* Setters/Mutadores */
void POOLadd(Pool, Item1); /* Adiciona um elemento (a cabeca) */
void POOLremove(Pool); /* Remove o elemento que foi inserido ha mais tempo */
int POOLremoveByKey(Pool, Key1); /* Remocao por chave */
void POOLfree(Pool); /* Liberta uma pool e todos os seus elementos */

/* Testes */
int POOLisEmpty(Pool); /* Veriifica se a esta vazia */

/* Representacao */
void POOLvisitFirst(Pool, void (*visit)(Item1)); /* Visita o item mais antigo */
void POOLvisitByKey(Pool, void (*visit)(Item1), Key1); /* Por chave */
void POOLvisitAll(Pool, void (*visit)(Item1)); /* Ou todos */

#endif /* POOL_H */