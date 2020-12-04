#include "commun.h"

#include "codeur.h"

int main(void){

    int message[] = {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0};
    hdbnIn mess;
    hdbnOut recu;

    mess.dernier_viol = 1;
    mess.taille = 23;

    codeur(HDB2, &mess, NULL, &recu, NULL);
    decodeur(HDB2, &mess, NULL, &recu, NULL);
    return 0;
}