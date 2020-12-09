#ifndef __COMMUN_H__
    #define __COMMUN_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>

    typedef enum{arith = 1, hdb2, hdb3, hdb4, decod_arith, decod_hdb2, decod_hdb3, decod_hdb4}type_fonc;
    typedef enum{initialiser, actif, suspendu, attente}states;

    typedef struct{
        pthread_t *thread;
        int etat;
    }agent;

#endif