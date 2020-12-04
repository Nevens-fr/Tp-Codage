#ifndef __CODEUR_H__
    #define __CODEUR_H__

    #include "commun.h"

    void codeur(int type, hdbnIn *mess_hdbn, arithIn *mess_arith, hdbnOut *cod_hdbn, arithOut *cod_arith);

    int occurences(char chaine[TAILLE], char l, int taille);

    void frequences_ordonnees(matrice *code, int occ[TAILLE], char lettre[TAILLE], int taille);
#endif