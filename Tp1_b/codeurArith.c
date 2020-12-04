#include "commun.h"

#include "codeur.h"
#include "decodeur.h"

int main(void){

    char message[] = "BILL GATES";
    arithIn mess, decoder;

    strcpy(mess.message, message);
    mess.taille = 10;

    arithOut res;

    codeur(ARITHMETIQUE, NULL, &mess, NULL, &res);
    decodeur(ARITHMETIQUE, NULL, &decoder, NULL, &res);

    printf("\n\nLe message décodé est : %s\n\n", decoder.message);

    return 0;
}