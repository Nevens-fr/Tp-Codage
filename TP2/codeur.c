#include "codeur.h"


void codeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith){

    if(type == HDBN){

    }
    else{
        
        ///////////// Recherche des occurences
        int occ[TAILLE], k = 0, i, j;
        char lettre[TAILLE];

        for(i = 0; i < mess_arith->taille; i++){
            for(j = 0; j < k && lettre[j] != mess_arith->message[i]; j++);

            if(j == k){
                occ[k] = occurences(mess_arith->message, mess_arith->message[i], mess_arith->taille);
                lettre[k++] = mess_arith->message[i];
            }
        }
        printf("%d k\n", k);
        
        ///////////// Construction de la table de fréquences
        frequences_ordonnees(cod_arith->frequences, occ, lettre, k);

        ///////////// Calcul du message
        float borne_inf = cod_arith->frequences.freq[0][0], borne_sup = cod_arith->frequences.freq[0][1];
        printf("min : %f, max : %f\n", borne_inf, borne_sup);

        for(i = 1; i < cod_arith->frequences.taille; i++){
            borne_inf = borne_inf + (borne_sup - borne_inf) * cod_arith->frequences.freq[i][0];
            borne_sup = borne_sup + (borne_sup - borne_inf) * cod_arith->frequences.freq[i][1];
        }
        printf("%f\n", borne_inf);
    }
}


/**
 * \fn int occurences(char chaine[TAILLE], char l)
 * 
 * \param chaine[TAILLE], la chaîne de caractère dans laquelle on cherche une lettre
 * \param l, la lettre pour laquelle on compte les occurences
 * 
 * \brief Compte et renvoi le nombre d'occurences d'une lettre dans une chaîne de caractère
 */
int occurences(char chaine[TAILLE], char l, int taille){

    int i, cpt = 0;
    for(i = 0; i < TAILLE; i++)
        if(chaine[i] == l)
            cpt++;
    return cpt;
}


/**
 * \fn void frequences_ordonnees(matrice code, int occ[TAILLE], char lettre[TAILLE], int taille)
 * 
 * \param code, structure matrice qui contient la frequece d'apparition de chaque lettre du message
 * \param occ[TAILLE], tableau des occurences des lettres
 * \param lettre[TAILLE], tableau des caractères du message originel
 * \param taille, la taille effective des deux tableaux ci-dessus
 * 
 * \brief Permet de ranger par ordre alphabétique et de préciser les fréquences d'apparition des lettres dans le message source
 */ 
void frequences_ordonnees(matrice code, int occ[TAILLE], char lettre[TAILLE], int taille){

    int i,j,k, freq = 0, ind_espace, tailleChaine=0;

    for(i=0; i<taille; i++){
        tailleChaine += occ[i];
    }

    code.taille = taille;

    k = 0;

    for(i = 0; i < 26; i++){
        for(j = 0; j < taille; j++){
            if(lettre[j] - 'A' == i){
                code.lettre[k] = lettre[j];
                printf("cococ %d\n", k);
                if(k==0){
                    code.freq[k][0] = 0;
                    printf("por aki\n");
                }
                else{
                    code.freq[k][0] = code.freq[k-1][1];
                }
                
                code.freq[k++][1] = (occ[j] / tailleChaine) + code.freq[k][0];
                freq += occ[j];
            }
            else if(lettre[j] == ' ')
                ind_espace = j;

        }
    }
    //on rajoute l'espace comme caractère
    code.lettre[k] = lettre[ind_espace];
    code.freq[k][0] = code.freq[k-1][1];
    code.freq[k][1] = (occ[ind_espace] / tailleChaine) + code.freq[k][0];
}