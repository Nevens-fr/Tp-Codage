#include "commun.h"
#include "fonctions.h"

/**
 * \fn void goldSeq(sequence seq, int etage, int etageMax, int tab[MAX][MAX])
 * 
 * \param seq la sequence d'étage a utiliser 
 * \param etage le nombre d'étages spécifié par l'user 
 * \param etageMax représente la longueur max de la sequence en fonction de l'etage
 * \param tab[MAX][MAX] tableau qui stocke les séquences
 * \brief Permet d'effectuer un xor entre les bits choisis par la sequence et de les stocker dans les étages du tablea
 */
void cLM(sequence seq, int etage, int etageMax, int tab[MAX][MAX]){

    int tmp;

    //Premier etage a 1
    for(int i = 0; i<etage; i++){
        tab[0][i] = 1;
    }

    //Creation du tableau
    for(int i = 0; i<etageMax-1; i++){
        tmp = 0;
        for(int j = 0; j<seq.taille; j++){
            tmp = tmp + tab[i][seq.seq[j] - 1];

            if(tmp == 2)
                tmp = 0;
        }
        //Remplissage de l'étage suivant
        remplissage_decalage(tab, etage, i, i + 1, tmp);
    }
}

/**
 * \fn void gold(sequence seq1, sequence seq2, int etage)
 * 
 * \param seq1 la première sequence d'étage a utiliser 
 * \param seq2 la seconde sequence d'étage a utiliser 
 * \param etage le nombre d'étages spécifié par l'user 
 * \brief Effectue un codage de gold en fonction de deux sequences et d'un nombre d'étage
 */
void gold(sequence seq1, sequence seq2, int res[MAX]){

    int tmp;
    int tab[MAX][MAX];
    int tab2[MAX][MAX];

    init_matrice(tab, seq1.etageMax, seq1.etage);
    init_matrice(tab2, seq1.etageMax, seq2.etage);

    cLM(seq1, seq1.etage, seq1.etageMax, tab);
    cLM(seq2, seq2.etage, seq1.etageMax, tab2);

    for(int i = 0; i<seq1.etageMax; i++){
        tmp = tab[i][seq1.etage-1] + tab2[i][seq2.etage-1];

        if(tmp > 1){
            tmp = 0;
        }

        res[i] = tmp;
        printf("%d ", res[i]);
    }
}

void jpl(sequence tabSeq[MAX], int res[MAX]){

    int tailleTabSeq = sizeof(tabSeq) / sizeof(int);
    int tab[MAX][MAX];

    int tabLigne1[MAX][MAX];
    int tmp;

    printf("%d\n", tailleTabSeq);

    for(int i = 0; i<tailleTabSeq; i++){
       init_matrice(tab, tabSeq[i].etageMax, tabSeq[i].etage);
       cLM(tabSeq[i], tabSeq[i].etage, tabSeq[i].etageMax, tab);

       for(int j = 0; j<tabSeq[i].etageMax; j++){
           tabLigne1[i][j] = tab[j][tabSeq[i].etage-1];
           tabLigne1[i][j] = -1;
       }
    }

    int k =0;
    for(int j = 0; j<31; j++){
        tmp = 0;
        for(int i = 0; i<tailleTabSeq; i++){
            tmp = tmp + tabLigne1[i][j];

            if(tmp > 1){
                tmp = 0;
            }
        }
        
        res[k++] = tmp;
        printf("%d ", res[k]);
    }

}


/**
 * \fn void init_matrice(int tab[MAX][MAX], int l, int c)
 * 
 * \param tab, matrice d'entiers
 * \param l, nombres de lignes de la matrice
 * \param c, nombre de colonnes par lignes
 * 
 * \brief Permet d'initialiser une matrice d'entiers à 0
 */ 
void init_matrice(int tab[MAX][MAX], int l, int c){

    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            tab[i][j] = 1;
        }
    }
}


/**
 * \fn void remplissage_decalage(int tab[MAX][MAX], int longueur, int etage1, int etage2, int val)
 * 
 * \param tab[][], matrice contenant le tableau du code de gold
 * \param longueur, longueur d'une ligne de la matrice
 * \param etage1, l'étage duquel on veut dupliquer la ligne
 * \param etage2, l'étage que l'on va remplir
 * \param val, la valeur à placer en première case de la ligne etage2
 * 
 * \brief A partir de la matrice tab, la ligne etage1 est recopiée dans la ligne etage2, mais décalée d'un cran sur la droite, val est ajouté en première position
 */ 
void remplissage_decalage(int tab[MAX][MAX], int longueur, int etage1, int etage2, int val){
    for(int i = longueur -1; i > 0; i--){
        tab[etage2][i] = tab[etage1][i -1]; 
    }
    tab[etage2][0] = val;
}