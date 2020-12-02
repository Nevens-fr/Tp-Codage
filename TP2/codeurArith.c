#include "commun.h"

#include "codeur.h"

int main(void){

    char message[] = "BILL GATES";
    arithIn mess;

    strcpy(mess.message, message);
    mess.taille = 10;

    arithOut res;

    codeur(ARITHMETIQUE, NULL, &mess, NULL, &res);

    return 0;
}