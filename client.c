#include <stdio.h>
#include <stdlib.h>
#include "client.h"

/* Construtor */
Client newCLIENT(long int ref)
{
    Client c = (Client) malloc(sizeof(struct client));
    
    c->ref = ref;
    c->nche = c->vche = c->nchb = c->vchb = 0;
    return c;
}

/* Getters/Acessores */
long int CLIENTref(Client client) { return client->ref; }
long int CLIENTnche(Client client) { return client->nche; }
long int CLIENTnchb(Client client) { return client->nchb; }
long int CLIENTvche(Client client) { return client->vche; }
long int CLIENTvchb(Client client) { return client->vchb; }

/* Setters/Mutadores */
void CLIENTaddChe(Client client) { client->nche++; }
void CLIENTremoveChe(Client client) { client->nche--; }
void CLIENTaddChb(Client client) { client->nchb++; }
void CLIENTremoveChb(Client client) { client->nchb--; }
void CLIENTupdateVChe(Client client, int value) { client->vche += value; }
void CLIENTupdateVChb(Client client, int value) { client->vchb += value; }

/* Testes */
int CLIENTexists(Client client) { return client != NULL; }

/* Representacao */
void CLIENTinfo(Client client)
{
    printf("Cliente-info: %ld %ld %ld %ld %ld\n",
        client->ref,
        client->nche,
        client->vche,
        client->nchb,
        client->vchb);
}

void CLIENTinfoOrdered(Client client)
{
    printf("*%ld %ld %ld %ld %ld\n",
        client->ref,
        client->nche,
        client->vche,
        client->nchb,
        client->vchb);
}