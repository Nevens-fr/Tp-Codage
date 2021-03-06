#include "commun.h"
#include "fonctions.h"


//main jpl

int main(){

    int nb_seq, longueur;
    sequence *tabSeq;

    printf("Combien de séquences souhaitez vous utilisez ? ");
    scanf("%d", &nb_seq);

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

    int resultat[MAX];

    jpl(tabSeq, resultat, nb_seq, longueur);

    free(tabSeq);

    return 0;
}