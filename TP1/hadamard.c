/**
 * \file hadamard.c
 * \author Tudoret Aurelien, Jourry Axel
 * \brief Fonction principale du programme qui génère une matrice de Hadamard et l'affiche.
 * \version 1.0
 * \date 2020-11-27
 */

#include "commun.h"
#include "fonctions.h"



int main(void){
    int nbUtilisateurs;
    int message[] = {1, 1, 1};
    int message2[] = {1, 0, 1};
    int message4[] = {0, 1, 1};
    int taille_message = 3;
    int **tableau_messages, *mess_etale;

    do{
        printf("Saisissez  le nombre d'utilisateurs : ");
        scanf("%d", &nbUtilisateurs);
        if(nbUtilisateurs %4 != 0 && nbUtilisateurs != 1 && nbUtilisateurs != 2)
            printf("Erreur saisie, nombre non valide\n");
    }while(nbUtilisateurs %4 != 0 && nbUtilisateurs != 1 && nbUtilisateurs != 2);

    MAX = nbUtilisateurs;

    int tableau[nbUtilisateurs][nbUtilisateurs];

    hadamard(tableau, nbUtilisateurs);
   
    afficher_hadamard(tableau, nbUtilisateurs);

    tableau_messages = allocation_tab_message(nbUtilisateurs, taille_message);

    mess_etale = malloc(sizeof(int) * nbUtilisateurs* taille_message);

    mise_a_zero(tableau_messages, nbUtilisateurs, taille_message * nbUtilisateurs);

    codage(0, nbUtilisateurs, tableau, message, taille_message, *(tableau_messages + 0));
    codage(1, nbUtilisateurs, tableau, message2, taille_message, *(tableau_messages + 1));
    codage(3, nbUtilisateurs, tableau, message4, taille_message, *(tableau_messages + 3));

    printf("Messages codés : \n");  
    affichage_codage(taille_message * nbUtilisateurs, *(tableau_messages + 0));
    affichage_codage(taille_message * nbUtilisateurs, *(tableau_messages + 1));
    affichage_codage(taille_message * nbUtilisateurs, *(tableau_messages + 3));

    etalement(tableau_messages, taille_message * nbUtilisateurs, nbUtilisateurs,mess_etale);

    printf("Affichage de l'étalement : \n");
    affichage_codage(nbUtilisateurs* taille_message, mess_etale);

    for(int i = 0; i < nbUtilisateurs; i++)
        free(*(tableau_messages + i));
    free(tableau_messages);

    return 0;
}