#include "commun.h"
#include "fonctions.h"

int main(){

    sequence seq1;
    int seqtmp[] = {5, 2};
    seq1.taille = sizeof(seqtmp) / sizeof(int);
    memmove(seq1.seq, seqtmp, sizeof(int) * seq1.taille);

    sequence seq2;
    int seqtmp2[] = {5, 4, 3, 2};
    seq2.taille = sizeof(seqtmp2) / sizeof(int);
    memmove(seq2.seq, seqtmp2, sizeof(int) * seq2.taille);
    

    int etage = 5;

    gold(seq1, seq2, etage);

    return 0;
}