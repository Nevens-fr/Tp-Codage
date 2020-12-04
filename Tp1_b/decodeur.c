#include "decodeur.h"

void decodeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith){

    if(type >= HDB2){

    }
    else{
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