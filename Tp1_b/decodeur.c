#include "decodeur.h"


/**
 * \fn void decodeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith)
 * 
 * \param type, le type de codage souhaité (1 arithmétique, 2 hdb2, 3 hdb3, 4 hdb4)
 * \param *mess_hdbn, Structure contenant le message d'origine pour un décodage hdbn (peut être NULL si codage arithmétique)
 * \param *mess_arith, Structure contenant le message d'origine pour un décodage arithmétique (peut être NULL si codage hdbn)
 * \param *cod_hdbn, Structure contenant le message codé par un codage hdbn (peut être NULL si codage arithmétique)
 * \param *cod_arith, Structure contenant le message codé par un codage arithmétique (peut être NULL si codage hdbn)
 * 
 * \brief Fonction qui selon les paramètres passés, permet de décoder un message soit avec le décodeur HDBN soit avec le décodeur arithmétique
 */ 
void decodeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith){

    if(type >= HDB2){
        int i, j;
        int signe = -1;

        //Application de la formule S = P - N pour n'avoir plus qu'un seul message
        for(i = 0; i<cod_hdbn->taille; i++){
            mess_hdbn->message[i] = cod_hdbn->P[i] - cod_hdbn->N[i];
        }

        for(i = 0; i<mess_hdbn->taille; i++){

            if(mess_hdbn->message[i] == 1){
                //Si les deux derniers bits différents de 0 ne sont pas alternés (1 et 1)
                if(signe == 1){

                    //On met les N précédents bits a 0 pour supprimer le viol
                    for(j = type; j >= 0; j--){
                        mess_hdbn->message[i - j] = 0;                      
                    }
                }
                else{
                    signe = 1;
                }
            }

            if(mess_hdbn->message[i] == -1){
                //Si les deux derniers bits différents de 0 ne sont pas alternés (-1 et -1)
                if(signe == -1){

                    //On met les N précédents bits a 0 pour supprimer le viol
                    for(j = type; j >= 0; j--){
                        mess_hdbn->message[i - j] = 0;                      
                    }
                }
                else{
                    signe = -1;
                }
            }

        }

        //On remet tous les -1 a 1
        for(i = 0; i<mess_hdbn->taille; i++){
            if(mess_hdbn->message[i] == -1){
                mess_hdbn->message[i] = 1;
            }
        }

    }
    else{
    // Décodage arithmétique
        int j = 0, k = 0;

        while(cod_arith->frequences.tailleCh > k){

            for(int i = 0; i < cod_arith->frequences.taille; i++){
                
                if(cod_arith->F >= cod_arith->frequences.freq[i][0] && cod_arith->F < cod_arith->frequences.freq[i][1]){
                    mess_arith->message[j++] = cod_arith->frequences.lettre[i];
                    cod_arith->F = (cod_arith->F - cod_arith->frequences.freq[i][0]) / (cod_arith->frequences.freq[i][1] - cod_arith->frequences.freq[i][0]);
                    k++;
                }
            }
        }
        mess_arith->message[j] = '\0';
    }
}