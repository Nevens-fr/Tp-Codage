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
        
        ///////////// Construction de la table de fréquences
        frequences_ordonnees(&cod_arith->frequences, occ, lettre, k);

        ///////////// Calcul du message
        double borne_inf = cod_arith->frequences.freq[0][0], borne_sup = cod_arith->frequences.freq[0][1], old;
        printf("min : %.10g, max : %.10g, taille %d\n", borne_inf, borne_sup, cod_arith->frequences.taille);

        for(i = 1; i < mess_arith->taille; i++){
            old = borne_inf;
            for(j = 0; j < cod_arith->frequences.taille && cod_arith->frequences.lettre[j] != mess_arith->message[i]; j++);

            printf("lettre : %5c ", cod_arith->frequences.lettre[j]);
            if(cod_arith->frequences.freq[j][0] != 0){
                borne_inf = borne_inf + (borne_sup - borne_inf) * cod_arith->frequences.freq[j][0];
                borne_sup = old + (borne_sup - old) * cod_arith->frequences.freq[j][1];
            }
            else{
                borne_inf = old;
                borne_sup = old + (borne_sup - old)/10;
            }
            printf("Borne inf %.10g   ", borne_inf);
            
            printf("Borne supp %.10g\n", borne_sup);
        }
        printf("%.10g\n", borne_inf);

        cod_arith->F = borne_inf;
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
    for(i = 0; i < taille; i++)
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
void frequences_ordonnees(matrice *code, int occ[TAILLE], char lettre[TAILLE], int taille){

    int i,j,k, ind_espace, tailleChaine=0;

    matrice tmp;

    for(i=0; i<taille; i++){
        tailleChaine += occ[i];
    }

    code->taille = taille;

    for(i = 0; i < taille; i++)
        if(lettre[i] == ' ')
            ind_espace = i;

    k = 0;
    
    //on rajoute l'espace comme caractère
    tmp.lettre[k] = lettre[ind_espace];
    tmp.freq[k][0] = 0;
    tmp.freq[k][1] = ((double)occ[ind_espace] / (double)tailleChaine) + (double)tmp.freq[k][0];
    code->freq[ind_espace][0] = tmp.freq[k][0];
    code->freq[ind_espace][1] = tmp.freq[k][1];
    k++;

    for(i = 0; i < 26; i++){
        for(j = 0; j < taille; j++){
            if(lettre[j] - 'A' == i){
                code->lettre[j] = lettre[j];
                tmp.lettre[k] = lettre[j];

                tmp.freq[k][0] = tmp.freq[k-1][1];
                tmp.freq[k][1] = ((double)occ[j] / (double)tailleChaine)+ (double)tmp.freq[k][0];
                code->freq[j][0] = tmp.freq[k][0];
                code->freq[j][1] = tmp.freq[k][1];

                k++;
            }
        }
    }
}