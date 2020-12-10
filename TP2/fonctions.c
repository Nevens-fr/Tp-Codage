#include "commun.h"
#include "fonctions.h"

/**
 * \fn void cLM(sequence seq, int etage, int etageMax, int tab[MAX][MAX])
 * 
 * \param seq la séquence d'étage a utiliser 
 * \param etage le nombre d'étages spécifié par l'user 
 * \param etageMax représente la longueur max de la séquence en fonction de l'étage
 * \param tab[MAX][MAX] tableau qui stock les séquences
 * \brief Permet d'effectuer un XOR entre les bits choisis par la séquence et de les stocker dans les étages du tableau
 */
void cLM(sequence seq, int etage, int etageMax, int tab[MAX][MAX]){

    int tmp;

    //Premier étage a 1
    for(int i = 0; i<etage; i++){
        tab[0][i] = 1;
    }

    //Création du tableau
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
 * \fn void gold(sequence seq1, sequence seq2, int res[], int longueur)
 * 
 * \param seq1 la première séquence d'étage a utiliser 
 * \param seq2 la seconde séquence d'étage a utiliser 
 * \param etage le nombre d'étages spécifié par l'user
 * \param longueur La longueur de la séquence finale choisie par l'utilisateur
 * \brief Effectue un codage de gold en fonction de deux séquences et d'un nombre d'étage
 */
void gold(sequence seq1, sequence seq2, int res[], int longueur){

    int tmp, taille = 0;
    int tab[MAX][MAX];
    int tab2[MAX][MAX];

    if(seq1.etage == seq2.etage){
        init_matrice(tab, seq1.etageMax, seq1.etage);
        init_matrice(tab2, seq1.etageMax, seq2.etage);

        cLM(seq1, seq1.etage, seq1.etageMax, tab);
        cLM(seq2, seq2.etage, seq1.etageMax, tab2);

        for(int i = 0; i<seq1.etageMax && taille < longueur; i++){
            tmp = tab[i][seq1.etage-1] + tab2[i][seq2.etage-1];

            if(tmp > 1){
                tmp = 0;
            }
            if(taille < longueur){
                res[i] = tmp;
                taille++;
                printf("%d ", res[i]);
            }
        }
    }
    else{
        printf("Les tailles des tableaux de séquences ne sont pas identiques, codage impossible\n");
    }
}

/**
 * \fn jpl(sequence tabSeq[MAX], int res[MAX], int tailleTabSeq, int longueur)
 * 
 * \param tabSeq tableau contenant toutes les séquences à utiliser
 * \param res tableau stockant la séquence finale
 * \param tailleTabSeq taille du tableau tabSeq
 * \param longueur La longueur de la séquence finale choisie par l'utilisateur
 * \brief fonction réalisant un codage JPL sur un nombre de fonctions choisies par l'utilisateur
 */
void jpl(sequence tabSeq[], int res[], int tailleTabSeq, int longueur){

    int tab[MAX][MAX], taille = 0;

    int tabLigne1[MAX][MAX];
    int tmp, pluslongue = 0, etagePremier = 0;

    for(int i = 0; i< tailleTabSeq; i++){
        for(int j = 0; j < tailleTabSeq; j++){
            if(i != j){
                if((tabSeq[i].etage > tabSeq[j].etage && tabSeq[i].etage % tabSeq[j].etage == 0) || (tabSeq[i].etage < tabSeq[j].etage && tabSeq[j].etage % tabSeq[i].etage == 0)){
                    printf("Les nombres d'étages ne sont pas premiers entre eux.\n");
                    etagePremier = 1;
                }
            }
        }
    }


    if(!etagePremier){
        for(int i = 0; i < tailleTabSeq; i++)
            if(tabSeq[i].etageMax > pluslongue)
                pluslongue = tabSeq[i].etageMax;

        printf("Nombre de séquences %d\n", tailleTabSeq);

        for(int i = 0; i<tailleTabSeq; i++){
        init_matrice(tab, tabSeq[i].etageMax, tabSeq[i].etage);
        cLM(tabSeq[i], tabSeq[i].etage, tabSeq[i].etageMax, tab);

        for(int j = 0; j<tabSeq[i].etageMax; j++){
            tabLigne1[i][j] = tab[j][tabSeq[i].etage-1];
                printf("%d ", tabLigne1[i][j]);
        }
        printf("\n");
        }

        printf("\n");

        int k =0;
        for(int j = 0; j< pluslongue && taille < longueur; j++){
            tmp = 0;
            for(int i = 0; i<tailleTabSeq && taille < longueur; i++){
                tmp = tmp + tabLigne1[i][j];
                
                if(tmp > 1){
                    tmp = 0;
                }
            }
            if(taille < longueur){
                res[k] = tmp;
                taille++;
                printf("%d ", res[k++]);
            }
        }
        printf("\n");
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
 * \param tab[MAX][MAX], matrice contenant le tableau du code de gold
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
