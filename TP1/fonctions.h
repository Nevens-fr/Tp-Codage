#ifndef __FONCTIONS__
    #define __FONCTIONS__

#include "commun.h"

void afficher_hadamard(int tableau[MAX][MAX], int m);
void hadamard(int tableau[MAX][MAX], int nbUser);
void codage(int ligne, int taille_ligne,int tableau[MAX][MAX], int *message, int taille_message, int *res);
void affichage_codage(int taille, int *tab);
void etalement(int **mess_codes, int taille_mess, int nb_mess,int *res);
void mise_a_zero(int **tab, int taille, int longueur);
int **allocation_tab_message(int nbUser, int taille_message);

#endif