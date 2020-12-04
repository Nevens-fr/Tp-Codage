#ifndef __COMMUN__
    #define __COMMUN__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define HDBN 1
    #define ARITHMETIQUE 0

    #define TRUE 1
    #define FALSE 0

    #define TAILLE 100

    typedef struct{
        char lettre[TAILLE];
        double freq[TAILLE][2];
        int taille;
    }matrice;

    typedef struct{
        int message[TAILLE];
        int dernier_viol, taille;
    }hdbnIn;

    typedef struct{
        int dernier_viol, taille;
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