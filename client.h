#ifndef CLIENT_H
#define CLIENT_H

/* Macros compativeis com o ADT tree */
#define Item2 Client
#define Key2 long int
#define key2(A) A->ref
#define less2(A, B) key2(A) < key2(B)
#define deleteItem2 free
#define NULLitem2 NULL

/**
 * Estrutura client - Representa um cliente de referencia/chave ref. Emitiu
 * nche cheques num valor total de vche e benificiou de nchb cheques num valor
 * de vchb (inicialmente, sao campos todos a zero, exepto a referencia)
 */
typedef struct client {
    long int ref, nche, vche, nchb, vchb;
} *Client;

/* Construtor */
Client newCLIENT(long int ref); /* Cria um novo cliente com a referencia ref */

/* Getters/Acessores */
long int CLIENTref(Client); /* Referencia do cliente */
long int CLIENTnche(Client); /* Numero de cheques emitidos */
long int CLIENTnchb(Client); /* Numero de cheques benificiados */
long int CLIENTvche(Client); /* Valor total dos cheques emitidos */
long int CLIENTvchb(Client); /* Valor total dos cheques benificiados*/

/* Setters/Mutadores */
void CLIENTaddChe(Client); /* Incrementa o numero de cheques emitidos */
void CLIENTremoveChe(Client); /* Decrementa o numero de cheques emitidos */
void CLIENTaddChb(Client); /* Incrementa o numero de cheques benificiados */
void CLIENTremoveChb(Client); /* Decrementa o numero de cheques benificiados */
void CLIENTupdateVChe(Client, int); /* Soma ao valor total de emitidos */
void CLIENTupdateVChb(Client, int); /* Soma ao valor total de benificiados */

/* Testes */
int CLIENTexists(Client); /* Verifica se o cliente "existe" (nao nulo) */

/* Representacao */
void CLIENTinfo(Client); /* Imprime a informacao do cliente */
void CLIENTinfoOrdered(Client); /* Representacao alternativa da informacao */

#endif /* CLIENT_H */