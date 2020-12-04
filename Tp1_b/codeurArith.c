#include "commun.h"

#include "codeur.h"
#include "decodeur.h"

int main(void){

    arithIn mess, decoder;
    arithOut res;
    int i;

    printf("******** Codeur arithmetique : ********\n");

    printf("Saisir votre chaine à coder : ");
    scanf("%[^\n]", mess.message);
    getchar();

    for(i = 0; *(mess.message + i); i++);
    
    mess.taille = i;

    codeur(ARITHMETIQUE, NULL, &mess, NULL, &res);
    decodeur(ARITHMETIQUE, NULL, &decoder, NULL, &res);

    printf("\n\nLe message décodé est : %s\n\n", decoder.message);

    return 0;
}