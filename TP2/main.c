#include "commun.h"
#include "fonctions.h"

//main gold
/*int main(){

    sequence seq1;
    int seqtmp[] = {5, 2};
    seq1.taille = sizeof(seqtmp) / sizeof(int);
    memmove(seq1.seq, seqtmp, sizeof(int) * seq1.taille);
    seq1.etage = 5;
    seq1.etageMax = pow(2, seq1.etage) -1;


    sequence seq2;
    int seqtmp2[] = {5, 4, 2, 1};
    seq2.taille = sizeof(seqtmp2) / sizeof(int);
    memmove(seq2.seq, seqtmp2, sizeof(int) * seq2.taille);
    seq2.etage = 5;
    seq2.etageMax = pow(2, seq2.etage) -1;


    int resultat[MAX];

    gold(seq1, seq2, resultat);

    return 0;
}*/

//main jpl

int main(){

    sequence seq1;
    int seqtmp[] = {5, 2};
    seq1.taille = sizeof(seqtmp) / sizeof(int);
    memmove(seq1.seq, seqtmp, sizeof(int) * seq1.taille);
    seq1.etage = 5;
    seq1.etageMax = pow(2, seq1.etage) -1;


    sequence seq2;
    int seqtmp2[] = {5, 4, 2, 1};
    seq2.taille = sizeof(seqtmp2) / sizeof(int);
    memmove(seq2.seq, seqtmp2, sizeof(int) * seq2.taille);
    seq2.etage = 5;
    seq2.etageMax = pow(2, seq2.etage) -1;

    /*sequence seq3;
    int seqtmp3[] = {5, 4, 3, 2};
    seq3.taille = sizeof(seqtmp3) / sizeof(int);
    memmove(seq3.seq, seqtmp3, sizeof(int) * seq3.taille);
    seq3.etage = 5;
    seq3.etageMax = pow(2, seq3.etage) -1;*/

    sequence tabSeq[] = {seq1, seq2};

    int resultat[MAX];

    jpl(tabSeq, resultat);

}