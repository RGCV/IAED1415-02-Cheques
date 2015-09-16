#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TADs */
#include "check.h" /* Cheque */
#include "client.h" /* Cliente */
#include "pool.h" /* Queue modificada (FIFO c/ pesquisa de elementos, ..) */
#include "tree.h" /* Arvore de pesquisa binaria AVL */

#define MAX_CMD 12 /* Tamanho de infocliente (mais comprido) + newLine */

void addCheck(Pool, Tree, int, long int, long int, long int);
void processCheck(Pool, Tree, Check);
void terminate(Pool, Tree);

int main()
{
    /* Armazena o comando que o utilizador introduz */
    char* command = (char*) malloc(sizeof(char)*(MAX_CMD + 1)); /* + NULL */
    
    /* Cheques emitidos (por processar) */
    Pool checks = POOLinit();
    /* Clientes activos */
    Tree clients = TREEinit();
    
    while(1) {
        
        Check ch; /* Cheque arbitrario */
        int value; /* Valor de um cheque arbitrario*/
        /* ref1: emissor ou arbitrario; ref2: benificiario; c: cheque */
        long int ref1, ref2, refc;
        
        scanf("%s", command);
        
        /* Se exceder o limite imposto, corta */
        if(strlen(command) > MAX_CMD) {
            command[MAX_CMD + 1] = '\0';
        }
        
        if (!strcmp(command, "cheque")) {
            /**
             * cheque - adiciona um cheque a pool de cheques. Nao verifica se
             * existem cheques com a mesma referencia.
             */
            scanf("%d %ld %ld %ld", &value, &ref1, &ref2, &refc);
            addCheck(checks, clients, value, ref1, ref2, refc);
        } 
        else if (!strcmp(command, "processa")) {
            /**
             * processa - processa o cheque que foi emitido ha mais tempo. Se
             * a soma do numero de cheques emitidos e do numero de cheques dos
             * quais o cliente e benificiario, remove o cliente do sistema.
             */
            if (!POOLisEmpty(checks) && (ch = POOLget(checks))) {
                processCheck(checks, clients, ch);
                POOLremove(checks);
            }
            else printf("Nothing to process\n");
        }
        else if (!strcmp(command, "processaR")) {
            /**
             * processaR - identico a processa. Difere no facto de que procura
             * o cheque com a referencia introduzida pelo utilizador.
             */
            scanf("%ld", &refc);
            
            if (!POOLisEmpty(checks) && (ch = POOLgetByKey(checks, refc))) {
                processCheck(checks, clients, ch);
                POOLremoveByKey(checks, refc);
            }
            else
                printf("Cheque %ld does not exist\n", refc);
        }
        else if (!strcmp(command, "infocheque")) {
            /**
             * infocheque - imprime a informacao de um determinado cheque.
             * Procura feita por referencia do cheque.
             */
            scanf("%ld", &refc);
            POOLvisitByKey(checks, CHECKinfo, refc);
        }
        else if (!strcmp(command, "infocliente")) {
            /**
             * infocliente - imprime a informacao de um determinado cliente.
             * Procura feita por referencia do cliente.
             */
            Client cl;
            scanf("%ld", &ref1);
            if (!(cl = TREEsearchByKey(clients, ref1)))
                printf("Cliente %ld does not exist\n", ref1);
            else CLIENTinfo(cl);
        }
        else if (!strcmp(command, "info")) {
            /**
             * info - imprime a informacao sobre os clientes activos ordenado
             * por referencia.
             */
            if (!TREEisEmpty(clients))
                TREEtraverse(clients, CLIENTinfoOrdered);
            else
                printf("No active clients\n");
        }
        else if (!strcmp(command, "sair")) {
            /**
             * sair - sai do programa, imprimindo o numero total de cheques que
             * ficou por processar, o numero de clientes activos e o valor total
             * de todos os cheques.
             */
            terminate(checks, clients);
            free(command);
            
            return EXIT_SUCCESS;
        }
        
        getchar(); /* Limpa \n do buffer */
        
    }
    return EXIT_FAILURE;
}

/* Adiciona um cheque a pool checks */
void addCheck(Pool checks, Tree clients, int value, long int refe, long int refb, long int refc)
{
    Client cle, clb; /* Emissor e benificiario */
    POOLadd(checks, newCHECK(value, refe, refb, refc));
    
    cle = TREEsearchByKey(clients, refe);
    clb = TREEsearchByKey(clients, refb);
    
    if (!CLIENTexists(cle)) {
        TREEadd(clients, newCLIENT(refe));
        cle = TREEsearchByKey(clients, refe);
    }
    if (!CLIENTexists(clb)) {
        TREEadd(clients, newCLIENT(refb));
        clb = TREEsearchByKey(clients, refb);
    }
    
    CLIENTaddChe(cle);
    CLIENTaddChb(clb);
    CLIENTupdateVChe(cle, value);
    CLIENTupdateVChb(clb, value);
}

/* Processa o cheque ch na pool checks, removendo-o */
void processCheck(Pool checks, Tree clients, Check ch)
{
    Client cle, clb; /* Emissor e benificiario */
    int value = -CHECKvalue(ch);
    
    cle = TREEsearchByKey(clients, CHECKrefe(ch));
    clb = TREEsearchByKey(clients, CHECKrefb(ch));
    
    CLIENTremoveChe(cle);
    CLIENTupdateVChe(cle, value);
    if (CLIENTnche(cle) + CLIENTnchb(cle) == 0)
        TREEremove(clients, cle);
    
    CLIENTremoveChb(clb);
    CLIENTupdateVChb(clb, value);
    if (CLIENTnche(clb) + CLIENTnchb(clb) == 0)
        TREEremove(clients, clb);
}

/* Termina o programa, imprimindo a informacao sumaria final e libertando as
estruturas que armazenam a essa informacao*/
void terminate(Pool checks, Tree clients)
{
    int numChecks = POOLcount(checks), numClients = TREEcount(clients);
    long int totalValue = 0;
    
    while (!POOLisEmpty(checks)) {
        Check ch = POOLget(checks);
        totalValue += CHECKvalue(ch);
        POOLremove(checks);
    }
    
    printf("%d %d %ld\n", numClients, numChecks, totalValue);
    
    POOLfree(checks);
    TREEfree(clients);
}