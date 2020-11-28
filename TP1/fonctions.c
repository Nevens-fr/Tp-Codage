#include "fonctions.h"


/**
 * \fn void afficher_hadamard(int tableau[MAX][MAX], int m)
 * \param tableau, la matrice d'hadamard a afficher.
 * \param taille, la taille de la matrice.
 * \brief Permet d'afficher une matrice de Hadamard
 */
void afficher_hadamard(int tableau[MAX][MAX], int taille){
    int i, j;
    
    for(i=0; i<taille; i++){
        for(j=0; j<taille; j++){
            printf("%2d", tableau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


/**
* \fn void hadamard(int tableau[MAX][MAX], int nbUser)
* \param tableau, la matrice a deux dimensions qui contiendra la matrice d'Hadamard
* \param nbUser, le nombre d'utilisateur qui vont utiliser simultanément le code
* \brief Permet d'initialiser la matrice de Hadamard
*/
void hadamard(int tableau[MAX][MAX], int nbUser){
    int i, j, m = 1;

    tableau[0][0] = 1;

    while (m<nbUser){
        for(i=0; i<m; i++){
            for(j=0; j<m; j++){
                tableau[i+m][j] = tableau[i][j];
                tableau[i][j+m] = tableau[i][j];
                tableau[i+m][j+m]= -tableau[i][j];               
            }
        }
        m = 2*m;
    }
}


/**
 * \fn void codage(int ligne, int taille_ligne,, int *message, int taille_message, int *res)
 * 
 * \param ligne, représente la séquence utilisée dans le tableau d'Hadamard
 * \param taille_ligne, représente la longueur d'une ligne dans le tableau d'Hadamard
 * \param *tableau, la matrice d'Hadamard
 * \param *message, le message de l'utilisateur
 * \param taille_message, le nombre d'éléments du message
 * \param *res, pointeur déjà initialisé qui contiendra le résultat du codage
 * \brief Fonction permettant de réaliser la séquence du codage de Hadamard d'un utilisateur
 */ 
void codage(int ligne, int taille_ligne,int tableau[MAX][MAX], int *message, int taille_message, int *res){

    int i, j= 0, k = 0;

    while(j < taille_message){
        i = 0;
        while(i < taille_ligne){
            if(*(message + j) == 0)
                *(res + k) = tableau[i][ligne] * (-1);
            else
                *(res + k) = tableau[i][ligne];
            
            i++;
            k++;
        }
        j++;
    }
}

/**
 * \fn void affichage_codage(int taille, int *tab)
 * 
 * \param taille 
 * \param tab 
 * 
 * \brief Permet d'afficher une séquence codée
 */
void affichage_codage(int taille, int *tab){

    int i;

    for(i = 0; i < taille; i++){
        printf("%2d ", *(tab + i));
    }
    printf("\n");
}


/**
 * \fn void mise_a_zero(int **tab, int taille, int longueur)
 * 
 * \param **mess_codes, le tableau contenant les messages codés
 * \param nb_mess, le nombre de messages dans le tableau
 * \param taille_mess, longueur des messages
 * \param *res, tableau d'entiers dans lequel est stocké l'étalement
 * 
 * \brief Effectue l'étalement sur les messages codés
 * */
void etalement(int **mess_codes, int taille_mess, int nb_mess,int *res){

    int i, j, k = 0, tmp;

    for(i = 0; i < taille_mess; i++){
        tmp = 0;
        for(j = 0; j < nb_mess; j++){
            tmp += mess_codes[j][i];
        }
        *(res+k) = tmp;
        k++;
    }
}


/**
 * \fn void mise_a_zero(int **tab, int taille, int longueur)
 * 
 * \param **tab, le tableau contenant les messages codés
 * \param taille, le nombre de messages dans le tableau
 * \param longueur, longueur des messages
 * 
 * \brief Permet de mettre à 0 le tableau des messages en vu de l'étalement
 * */
void mise_a_zero(int **tab, int taille, int longueur){
    for(int i = 0; i < taille; i++)
        for(int j = 0; j < longueur; j++)
            tab[i][j] = 0;
}



/**
 * \fn int **allocation_tab_message(int nbUser, int taille_message)
 * 
 * \param nbUser, le nombre de messages dans le tableau
 * \param taille_message, longueur des messages
 * 
 * \brief Permet d'allouer la mémoire pour le tableau des messages codés
 * */
int **allocation_tab_message(int nbUser, int taille_message){

    int **tab_message = malloc(sizeof(int*) * nbUser);

    for(int i = 0; i < nbUser; i++){
        *(tab_message + i) = malloc(sizeof(int) * (taille_message * nbUser));
        if(! *(tab_message + i))
            printf("Malloc tableau_message, erreur\n");
    }
    return tab_message;
}