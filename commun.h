#ifndef __COMMUN__
    #define __COMMUN__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define HDB2 2
    #define HDB3 3
    #define HDB4 4
    #define ARITHMETIQUE 1

    #define TRUE 1
    #define FALSE 0

    #define TAILLE 100

    typedef struct{
        char lettre[TAILLE];
        double freq[TAILLE][2];
        int taille;
        int tailleCh;
    }matrice;

    typedef struct{
        int message[TAILLE];
        int taille;
    }hdbnIn;

    typedef struct{
        int taille;
        int P[TAILLE];
        int N[TAILLE];
    }hdbnOut;

    typedef struct{
        char message[TAILLE];
        int taille;
    }arithIn;

    typedef struct{
        double F;
        matrice frequences;
    }arithOut;

#endif