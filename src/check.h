#ifndef CHECK_H
#define CHECK_H

/* Macros compativeis com a ADT pool */
#define Item1 Check
#define Key1 long int
#define key1(A) A->refc
#define less1(A,B) key1(A) < key1(B)
#define deleteItem1 free
#define NULLitem1 NULL

/**
 * Estrutura check - Representa um cheque com referencia ou chave, emitido pelo
 * cliente de referencia refe e destinado ao cliente com referencia refb, num
 * montante de value
 */
typedef struct check {
    int value;
    long int refe, refb, refc;
} *Check;

Check newCHECK(int, long int, long int, long int); /* Cria um cheque */

/* Getters/Acessores */
long int CHECKrefb(Check); /* Referencia do cliente benificiario */
long int CHECKrefc(Check); /* Referencia do cheque */
long int CHECKrefe(Check); /* Referencia do cliente emissor */
int CHECKvalue(Check); /* Valor do cheque */

/* Testes */
int CHECKexists(Check); /* Verifica se o check "existe" (apontador nao nulo) */

/* Representacao */
void CHECKinfo(Check); /* Imprime a informacao de um cheque */

#endif /* CHECK_H */