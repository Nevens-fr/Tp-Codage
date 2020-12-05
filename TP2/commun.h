#ifndef __COMMUN_H__
    #define __COMMUN_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>

    #define MAX 1000

    typedef struct{
        int seq[MAX];
        int taille;
        int etage;
        int etageMax;
    }sequence;

#endif