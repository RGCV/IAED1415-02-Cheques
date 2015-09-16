#include <stdio.h>
#include <stdlib.h>
#include "check.h"

/* Construtor */
Check newCHECK(int value, long int refe, long int refb, long int refc)
{
    Check check = (Check)malloc(sizeof(struct check));
    check->value = value;
    check->refe = refe;
    check->refb = refb;
    check->refc = refc;
    return check;
}

/* Getters/Mutadores */
long int CHECKrefe(Check check) { return check->refe; }
long int CHECKrefb(Check check) { return check->refb; }
long int CHECKrefc(Check check) { return check->refc; }
int CHECKvalue(Check check) { return check->value; }

/* Testes */
int CHECKexists(Check check) { return check != NULL; }

/* Representacao */
void CHECKinfo(Check check)
{
    printf("Cheque-info: %ld %d %ld --> %ld\n",
        check->refc,
        check->value,
        check->refe,
        check->refb);
}