#include <stdlib.h>
#include "client.h"
#include "tree.h"

/* Cria um novo no cujo elemento e item, tem como filho da esquerda o no l e
da direita o no r */
tnode newTREEnode(Item2 item, tnode l, tnode r)
{
	tnode x = (tnode) malloc(sizeof(struct TREEnode));
	
	x->item = item;
	x->l = l;
	x->r = r;
	x->height = 1;
	return x;
}

/* Liberta um no, libertando o item e de seguida o ponteiro para o mesmo */
void freeTREEnode(tnode x)
{
	deleteItem2(x->item);
	free(x);
}

/* Determina a altura de um no */
int height(tnode h)
{
    if (h == NULL) return 0;
    return h->height;
}

/* Procura qual o elemento maximo de uma arvore (o mais a direita) */
tnode max(tnode h)
{
	if (h == NULL || h->r == NULL) return h;
	else return max(h->r);
}

/* Procura o elemento minimo de uma arvore (o mais a esquerda) */
tnode min(tnode h)
{
	if (h == NULL || h->l == NULL) return h;
	else return min(h->l);
}

/* Determina o factor de balanco/equilibrio entre dois nos (abs(factor) <= 1 ->
equilibrada) */
int Balance(tnode h)
{
    if (h == NULL) return 0;
    else return height(h->l) - height(h->r);
}

/* Aplica uma rotacao a esquerda a um no, restruturando uma sub-arvore */
tnode rotL(tnode h)
{
	int height_l, height_r;
	
	tnode x = h->r;
	h->r = x->l;
	x->l = h;
	
	/* Actualiza ainda os valores das alturas dos nos */
	height_l = height(h->l);
	height_r = height(h->r);
	h->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	height_l = height(x->l);
	height_r = height(x->r);
	x->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	return x;
}

/* Aplica uma rotacao a direita a um no, restruturando a arvore */
tnode rotR(tnode h)
{
	int height_l, height_r;
	
	tnode x = h->l;
	h->l = x->r;
	x->r = h;
	
	height_l = height(h->l);
	height_r = height(h->r);
	h->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	height_l = height(x->l);
	height_r = height(x->r);
	x->height = height_l > height_r ? height_l + 1 : height_r + 1;
	
	return x;
}

/* Dupla rotacao a esquerda e a de seguida a direita */
tnode rotLR(tnode h)
{
	if (h == NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}

/* Dupla rotacao a direita e de seguida a esquerda */
tnode rotRL(tnode h)
{
	if (h == NULL) return h;
	h->r = rotR(h->r);
	return rotL(h);
}

/* Utilizando as funcoes definidas acima, equilibra uma arvore, que ocorre apos
a insercao ou remocao de um elemento */
tnode AVLbalance(tnode h)
{
    int balanceFactor;
    
    if (h == NULL) return h; 
    balanceFactor = Balance(h);
    
    if(balanceFactor > 1) {
        if (Balance(h->l) > 0) h = rotR(h);
        else h =rotLR(h);
    }
    else if(balanceFactor < -1) {
        if (Balance(h->r) < 0) h = rotL(h);
        else h = rotRL(h);
    }
    else {
        int height_l = height(h->l);
        int height_r = height(h->r);
        h->height = height_l > height_r ? height_l + 1 : height_r + 1; 
    } 
    return h;
}

/* Construtor */
Tree TREEinit()
{
	Tree t = (Tree) malloc(sizeof(struct tree));
	
	t->h = NULL;
	return t;
}

/* Getters/Acessores */

/* Percorre a arvore recursivamente e conta o numero de elementos que existem */
int count(tnode h) {
    if (h == NULL) return 0;
    else {
        return 1 + count(h->l) + count(h->r);
    }
}

int TREEcount(Tree t)
{
    return count(t->h);
}

/* Procura um elemento na arvore por chave e retorno o elemento */
Item2 searchR(tnode h, Key2 k)
{
    if (h == NULL) return NULL;
    
    if (k < key2(h->item))
    	return searchR(h->l, k);
    else if (key2(h->item) < k)
    	return searchR(h->r, k);
    else
    	return h->item;
}

Item2 TREEsearch(Tree t, Item2 item)
{
    return searchR(t->h, key2(item));
}

Item2 TREEsearchByKey(Tree t, Key2 k)
{
    return searchR(t->h, k);
}

/* Setters/Mutadores */

/* Insere um no na arvore cujo elemento e item */
tnode insertR(tnode h, Item2 item)
{
	if (h == NULL) return newTREEnode(item, NULL, NULL);
	
	if (less2(item, h->item))
		h->l = insertR(h->l, item);
	else if (less2(h->item, item))
		h->r = insertR(h->r, item);
	
	h = AVLbalance(h);
	
	return h;
}

void TREEadd(Tree t, Item2 item)
{
    t->h = insertR(t->h, item);
}

/* Remove da arvore o no de chave k */
tnode deleteR(tnode h, Key2 k)
{
	if (h == NULL) return h;
	
	if (k < key2(h->item))
		h->l = deleteR(h->l, k);
	else if (key2(h->item) < k)
		h->r = deleteR(h->r, k);
	else {
		if (h->l != NULL && h->r != NULL) { /* Tem 2 filhos */
			tnode aux = max(h->l);
			
			Item2 x = h->item;
			h->item = aux->item;
			aux->item = x;
			
			h->l = deleteR(h->l, key2(aux->item));
		}
		else { /* Apenas um filho ou nenhum */
			tnode aux = h;
			
			if (h->l == NULL && h->r == NULL) h = NULL;
			else if (h->l == NULL)
				h = h->r;
			else if (h->r == NULL)
				h = h->l;
			
			freeTREEnode(aux);
		}
	}
	h = AVLbalance(h);
	return h;
}

void TREEremove(Tree t, Item2 item)
{
    t->h = deleteR(t->h, key2(item));
}

void TREEremoveByKey(Tree t, Key2 k)
{
    t->h = deleteR(t->h, k);
}

/* Percorre os elementos da arvore post-order e liberta os mesmos */
void deleteTree(tnode h)
{
    if (h == NULL) return;
	if (h != NULL) {
			deleteTree(h->l);
			deleteTree(h->r);
			freeTREEnode(h);
	}
}

void TREEfree(Tree t)
{
    deleteTree(t->h);
    free(t);
}

/* Testes */
int TREEisEmpty(Tree t)
{
    return t->h == NULL;
}

/* Aplica a funcao visit aos elementos que precorre in-order */
void traverse(tnode h, void (*visit)(Item2))
{
    if (h == NULL) return;
    traverse(h->l, visit);
    visit(h->item);
    traverse(h->r, visit);
}

/* Representacao */
void TREEtraverse(Tree t, void (*visit)(Item2))
{
	traverse(t->h, visit);
}