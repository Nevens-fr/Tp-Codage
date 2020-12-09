#include "commun.h"
#include "fonctions.h"
#include "../Tp1_b/codeur.h"
#include "../Tp1_b/decodeur.h"

/**
 * \fn void create_thread(agent **ag)
 * 
 * \param ag, pointeur de pointeur sur une structure agent
 * 
 * \brief Allocaiion dynamique de l'espace mémoire
 */ 
void create_thread(agent **ag){
    *ag = malloc(sizeof(agent));

    if(!*ag)
        exit(0);
    init_thread(*ag);
}


/**
 * \fn void init_thread(agent *ag)
 * 
 * \param ag, pointeur sur une structure agent
 * 
 * \brief initialisation des champs de la structure
 */ 
void init_thread(agent *ag){

    ag->etat = initialiser;
    ag->thread = NULL;
}


/**
 * \fn void init_thread(agent *ag)
 * 
 * \param ag, pointeur sur une structure agent
 * 
 * \brief On lance le thread
 */ 
void activate_thread(agent *ag, int fonction_voulue){
    if(ag->etat != actif){
        ag->etat = actif;
        if(fonction_voulue >= 1 && fonction_voulue <= 4)
            pthread_create(ag->thread, NULL, (void *(*)(void*))codeur, NULL);
        else
            pthread_create(ag->thread, NULL, (void *(*)(void*))decodeur, NULL);
    }
}