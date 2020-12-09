#include "commun.h"

#include "codeur.h"
#include "decodeur.h"

int main(void){

    ///////VALEURS A CHANGER
    //Message du td HDB2
    //int message[] = {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0};

    //Message HDB3
    int message[] = {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    int type = HDB3;


    hdbnIn mess;
    hdbnOut code;
    hdbnIn decode;

    //Calcul de la taille des messages
    mess.taille = sizeof(message) / sizeof(int);
    code.taille = mess.taille;
    decode.taille = mess.taille;

    memmove(mess.message, message, sizeof(int) * mess.taille);

    //Affichage envoie
    printf("M envoyé : ");
    for(int i = 0; i < mess.taille; i++)
        printf("%d ", mess.message[i]);
    printf("\n");

    //Codage
    codeur(type, &mess, NULL, &code, NULL);

    //Affichage une fois codé
    printf("\nCodage P : ");
    for(int i = 0; i<code.taille; i++)
        printf("%d ", code.P[i]);
    printf("\n");

    printf("Codage N : ");
    for(int i = 0; i<code.taille; i++)
        printf("%d ", code.N[i]);
    printf("\n");

    //Decodage
    decodeur(type, &decode, NULL, &code, NULL);

    //Affichage une fois décodé
    printf("\nDecodage : ");
    for(int i = 0; i<decode.taille; i++)
        printf("%d ", decode.message[i]);
    printf("\n");

    return 0;
}