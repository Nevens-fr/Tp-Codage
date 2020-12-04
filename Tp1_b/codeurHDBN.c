#include "commun.h"

#include "codeur.h"
#include "decodeur.h"

int main(void){

    int message[] = {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0};
    hdbnIn mess;
    hdbnOut recu;

    memmove(mess.message, message, sizeof(int) * 23);

    for(int i = 0; i < 23; i++)
        printf("%d ", mess.message[i]);

    mess.dernier_viol = 1;
    mess.taille = 23;

    codeur(HDB2, &mess, NULL, &recu, NULL);
    decodeur(HDB2, &mess, NULL, &recu, NULL);
    return 0;
}