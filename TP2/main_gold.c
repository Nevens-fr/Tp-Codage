#include "commun.h"
#include "fonctions.h"

//main gold
int main(){

    int nb_seq = 2, longueur;
    sequence *tabSeq;

    tabSeq = malloc(sizeof(sequence) * nb_seq);

    if(!tabSeq){
        printf("Problème allocation mémoire\n");
        return -1;
    }

    for(int i = 0; i < nb_seq; i++){
        printf("Nombre d'étages : ");
        scanf("%d", &tabSeq[i].etage);

        int taille = 0, nb = 0;

        printf("Veuillez entrer votre séquence séparé par des espaces (-1 pour la terminer) : ");
        while(nb != -1){
            scanf("%d", &nb);
            if(nb != -1)
                tabSeq[i].seq[taille++] = nb;
        }
        tabSeq[i].taille = taille;

        tabSeq[i].etageMax = pow(2, tabSeq[i]. etage) - 1;
    }

    printf("Saisir la longueur du message final : ");
    scanf("%d", &longueur);

    int resultat[longueur];

    gold(tabSeq[0], tabSeq[1], resultat, longueur);

    printf("\n");

    free(tabSeq);

    return 0;
}