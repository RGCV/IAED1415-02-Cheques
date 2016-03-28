#include <stdio.h>
#include <stdlib.h>

#include "pool.h"
#include "check.h"

/* Cria um novo no com o item passado, ficando com next como o seguinte */
pnode newPOOLnode(Item1 item, pnode next)
{
    pnode x = (pnode) malloc(sizeof(struct POOLnode));
    
    x->item = item;
    x->next = next;
    return x;
}

/* Liberta um no da pool (libertando o item e de seguida o ponteiro) */
void freePOOLnode(pnode x)
{
    deleteItem1(x->item);
    free(x);
}

/* Construtor */
Pool POOLinit()
{
    Pool p = (Pool) malloc(sizeof(struct pool));
    
    p->head = NULL;
    p->tail = NULL;
    return p;
}

/* Getters/Acessores */
int POOLcount(Pool p)
{
    int count;
    pnode aux;
    for (count = 0, aux = p->head; aux != NULL; count++, aux = aux->next)
        ;
    return count;
}

Item1 POOLget(Pool p)
{
    if (p->head == NULL) return NULLitem1;
    return p->head->item;
}

Item1 POOLgetByKey(Pool p, Key1 k)
{
    pnode t;
    for(t = p->head; t != NULL; t = t->next) {
        if (key1(t->item) == k) {
            return t->item;
        }
    }
    return NULLitem1;
}

/* Setters/Mutadores*/
void POOLadd(Pool p, Item1 item)
{
    if (p->head == NULL) {
        p->tail = newPOOLnode(item, p->head);
        p->head = p->tail;
        return;
    }
    p->tail->next = newPOOLnode(item, p->tail->next);
    p->tail = p->tail->next;
}

void POOLremove(Pool p)
{
    pnode aux = p->head->next;
    freePOOLnode(p->head);
    p->head = aux;
}

int POOLremoveByKey(Pool p, Key1 k)
{
    pnode t, prev;
    for (t = p->head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (key1(t->item) == k) {
            if (t == p->head){
                p->head = t->next;}
            else {
                if (t == p->tail)
                    p->tail = prev;
                prev->next = t->next;
            }
            freePOOLnode(t);
            return 1;
        }
    }
    return 0;
}

void POOLfree(Pool p)
{
    while (p->head != NULL) {
        pnode aux = p->head->next;
        freePOOLnode(p->head);
        p->head = aux;
    }
    free(p);
}

/* Testes */
int POOLisEmpty(Pool p)
{
    return p->head == NULL;
}

/* Representacao */
void POOLvisitFirst(Pool p, void (*visit)(Item1))
{
    visit(p->head->item);
}

void POOLvisitByKey(Pool p, void (*visit)(Item1), Key1 k)
{
    pnode t;
    for (t = p->head; t != NULL; t = t->next) {
        if (key1(t->item) == k) {
            visit(t->item);
            return;
        }
    }
}

void POOLvisitAll(Pool p, void (*visit)(Item1))
{
    pnode t;
    for (t = p->head; t != NULL; t = t->next) {
        visit(t->item);
    }
}