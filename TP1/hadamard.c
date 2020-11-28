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
    int taille_message = 3;
    int **tableau_messages, *mess_etale;

    do{
        printf("Saisissez  le nombre d'utilisateurs : ");
        scanf("%d", &nbUtilisateurs);
        if(nbUtilisateurs %4 != 0 && nbUtilisateurs != 1 && nbUtilisateurs != 2)
            printf("Erreur saisie, nombre non valide\n");
    }while(nbUtilisateurs %4 != 0 && nbUtilisateurs != 1 && nbUtilisateurs != 2);

    MAX = nbUtilisateurs;

    int tableau[MAX][MAX];
    int messages[MAX][TAILLE_MESSAGE];

    saisies_utilisateurs(nbUtilisateurs, messages);

    printf("\nCréation et initialisation de la matrice d'Hadamard\nOk\n\n");
    hadamard(tableau, nbUtilisateurs);
   
    printf("Affichage de la matrice d'Hadamard pour le nombre d'utilisateur(s) souhaité(s)\n");
    afficher_hadamard(tableau, nbUtilisateurs);

    tableau_messages = allocation_tab_message(nbUtilisateurs);

    mess_etale = malloc(sizeof(int) * nbUtilisateurs* taille_message);

    mise_a_zero(tableau_messages, nbUtilisateurs, taille_message * nbUtilisateurs);

    codage_utilisateurs(nbUtilisateurs, tableau, messages, tableau_messages);


    printf("\nMessages codés grâce à la matrice: \n");  
    for(int i = 0; i < nbUtilisateurs; i++)
        affichage_codage(taille_message * nbUtilisateurs, *(tableau_messages + i));


    etalement(tableau_messages, taille_message * nbUtilisateurs, nbUtilisateurs,mess_etale);

    printf("\nAffichage des messages étalés (étalement de Hadamard) : \n");
    affichage_codage(nbUtilisateurs* taille_message, mess_etale);


///////////////////////////////////////////////////////////////////////////////////////////
// Libération mémoire
///////////////////////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nbUtilisateurs; i++)
        free(*(tableau_messages + i));
    free(tableau_messages);

    return 0;
}