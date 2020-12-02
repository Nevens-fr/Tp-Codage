#ifndef __COMMUN__
    #define __COMMUN__

    #include <stdio.h>
    #include <stdlib.h>

    #define HDBN 1
    #define ARITHMETIQUE 0

    #define TRUE 1
    #define FALSE 0

    #define TAILLE 20

    typedef struct{
        int message[TAILLE];
        int dernier_viol, taille;
        int P[TAILLE];
        int N[TAILLE];
    }hdbn;

    typedef struct{
        int message[TAILLE];
        int taille;
        float F;
    }arithmetique;

#endif