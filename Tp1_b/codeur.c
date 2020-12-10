#include "codeur.h"


/**
 * \fn int rechercheViol(int type, hdbnIn *mess,int indiceDepart)
 * 
 * \param type, le type de codage HDBN demandé (2, 3, 4)
 * \param *mess, structure contenant le message d'origine
 * \param indiceDepart, le point de départ du codage
 * 
 * \brief Retourne le dernier viol effectué par le codage
 */ 
int rechercheViol(int type, hdbnIn *mess,int indiceDepart){
    for(int j = 1; j <= type; j++){
        if(mess->message[indiceDepart + j] != 0){
            return 0;
        }
    }
    return 1;
}


/**
 * \fn void init_res(hdbnOut *cod, hdbnIn *mess)
 * 
 * \param *cod, structure qui contiendra le message codé
 * \param *mess, structure contenant le message d'origine
 * 
 * \brief Initialise les deux tableaux de pulse positif et négatif à 0
 */ 
void init_res(hdbnOut *cod, hdbnIn *mess){
    for(int i = 0; i < mess->taille; i++){
        cod->P[i] = 0;
        cod->N[i] = 0;
    }
}


/**
 * \fn void codeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith)
 * 
 * \param type, le type de codage souhaité (1 arithmétique, 2 hdb2, 3 hdb3, 4 hdb4)
 * \param *mess_hdbn, Structure contenant le message d'origine pour un codage hdbn (peut être NULL si codage arithmétique)
 * \param *mess_arith, Structure contenant le message d'origine pour un codage arithmétique (peut être NULL si codage hdbn)
 * \param *cod_hdbn, Structure contenant le message codé par un codage hdbn (peut être NULL si codage arithmétique)
 * \param *cod_arith, Structure contenant le message codé par un codage arithmétique (peut être NULL si codage hdbn)
 * 
 * \brief Fonction qui selon les paramètres passés, permet de coder un message soit avec le codage HDBN soit avec le codage arithmétique
 */ 
void codeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith){

    if(type >= HDB2){
        int dernier_choix = 0;
        int violExiste = 0;
        int i, j;

        init_res(cod_hdbn, mess_hdbn);

        for(i = 0; i<mess_hdbn->taille; i++){

            //Si le bit est a 1
            if(mess_hdbn->message[i] == 1){
                if(dernier_choix == 0){
                    cod_hdbn->P[i] = 1;
                    dernier_choix = 1;
                }
                else{
                    cod_hdbn->N[i] = 1;
                    dernier_choix = 0;
                }
            }

            //Si le bit est a 0
            else{

                //Si il n'y a pas de V
                if(rechercheViol(type, mess_hdbn, i) == 0){
                    cod_hdbn->P[i] = 0;
                    cod_hdbn->N[i] = 0;
                }
                else{
                    //Si il y a eu un V
                    if(violExiste == 1){
                        //On place le B
                        if(dernier_choix == 0){
                            cod_hdbn->P[i] = 1;
                            dernier_choix = 1;
                        }
                        else{
                            cod_hdbn->N[i] = 1;
                            dernier_choix = 0;
                        }
                    }
                    //On place le viol
                    if(dernier_choix == 0){
                        i+=type;
                        cod_hdbn->N[i] = 1;
                        dernier_choix = 0;

                    }
                    else{
                        i+=type;
                        cod_hdbn->P[i] = 1;
                        dernier_choix = 1;
                    }

                    if(violExiste == 0){
                        violExiste =1;
                    }
                }
            }
        }
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

        for(i = 1; i < mess_arith->taille; i++){
            old = borne_inf;

            for(j = 0; j < cod_arith->frequences.taille && cod_arith->frequences.lettre[j] != mess_arith->message[i]; j++);

            borne_inf = borne_inf + ((borne_sup - borne_inf) * cod_arith->frequences.freq[j][0]);
            borne_sup = old + ((borne_sup - old) * cod_arith->frequences.freq[j][1]);
        }

        cod_arith->F = borne_inf;
    }
}


/**
 * \fn int occurences(char chaine[TAILLE], char l, int taille)
 * 
 * \param chaine[TAILLE], la chaîne de caractères dans laquelle on cherche une lettre
 * \param l, la lettre pour laquelle on compte les occurences
 * \param taille, la taille de la chaine
 * 
 * \brief Compte et renvoi le nombre d'occurences d'une lettre dans une chaîne de caractères
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
 * \param code, structure matrice qui contient la fréquence d'apparition de chaque lettre du message
 * \param occ[TAILLE], tableau des occurences des lettres
 * \param lettre[TAILLE], tableau des caractères du message originel
 * \param taille, la taille effective des deux tableaux ci-dessus
 * 
 * \brief Permet de ranger par ordre alphabétique et de préciser les fréquences d'apparition des lettres dans le message source
 */ 
void frequences_ordonnees(matrice *code, int occ[TAILLE], char lettre[TAILLE], int taille){

    int i,j,k, tailleChaine=0;

    matrice tmp;

    for(i=0; i<taille; i++){
        tailleChaine += occ[i];
    }

    code->taille = taille;
    code->tailleCh = tailleChaine;

    k = 0;

    for(j = 0; j < taille; j++){
        code->lettre[k] = lettre[j];
        tmp.lettre[k] = lettre[j];

        code->freq[k][0] = (k == 0 ? 0 : code->freq[k-1][1]);
        code->freq[k][1] = ((double)occ[j] / (double)tailleChaine)+ (double)code->freq[k][0];
        k++;
    }
}