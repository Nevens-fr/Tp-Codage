#include "fonctions.h"


/**
 * \fn void afficher_hadamard(int tableau[MAX][MAX], int taille)
 * \param tableau, la matrice d'hadamard a afficher.
 * \param taille, la taille de la matrice.
 * \brief Permet d'afficher une matrice de Hadamard
 */
void afficher_hadamard(int tableau[MAX][MAX], int taille){
    int i, j;
    
    for(i=0; i<taille; i++){
        for(j=0; j<taille; j++){
            printf("%3d", tableau[i][j]);
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
 * \fn void codage(int ligne, int taille_ligne,, int tableau[MAX][MAX], int *message, int *res)
 * 
 * \param ligne, représente la séquence utilisée dans le tableau d'Hadamard
 * \param taille_ligne, représente la longueur d'une ligne dans le tableau d'Hadamard
 * \param tableau[MAX][MAX], la matrice d'Hadamard
 * \param *message, le message de l'utilisateur
 * \param *res, pointeur déjà initialisé qui contiendra le résultat du codage
 * \brief Fonction permettant de réaliser la séquence du codage de Hadamard d'un utilisateur
 */ 
void codage(int ligne, int taille_ligne,int tableau[MAX][MAX], int *message, int *res){

    int i, j= 0, k = 0;

    while(j < TAILLE_MESSAGE){
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
 * \param taille la taille de la sequence a afficher
 * \param tab pointeur contenant la sequence codée a afficher
 * 
 * \brief Permet d'afficher une séquence codée
 */
void affichage_codage(int taille, int *tab){

    int i;

    for(i = 0; i < taille; i++){
        printf("%3d ", *(tab + i));
    }
    printf("\n");
}


/**
 * \fn void etalement(int **mess_codes, int taille_mess, int nb_mess,int *res)
 * 
 * \param **mess_codes, le tableau contenant les messages codés
 * \param taille_mess, longueur des messages
 * \param nb_mess, le nombre de messages dans le tableau
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
 * \fn int **allocation_tab_message(int nbUser)
 * 
 * \param nbUser, le nombre de messages dans le tableau
 * 
 * \brief Permet d'allouer la mémoire pour le tableau des messages codés
 * */
int **allocation_tab_message(int nbUser){

    int **tab_message = malloc(sizeof(int*) * nbUser);

    for(int i = 0; i < nbUser; i++){
        *(tab_message + i) = malloc(sizeof(int) * (TAILLE_MESSAGE * nbUser));
        if(! *(tab_message + i))
            printf("Malloc tableau_message, erreur\n");
    }
    return tab_message;
}



/**
 * \fn void saisies_utilisateurs(int nbUser, int messages[MAX][TAILLE_MESSAGE])
 * 
 * \param nbUser, le nombre d'utilisateurs souhaitant envoyer un message
 * \param messages[MAX][TAILLE_MESSAGE], tableau contenant les messages des utilisateurs
 * 
 * \brief Permet de demander aux utilisateurs les messages qu'ils souhaitent envoyer
 * */
void saisies_utilisateurs(int nbUser, int messages[MAX][TAILLE_MESSAGE]){

    for(int i = 0; i < nbUser; i++){
        printf("Utilisateur %d, entrer votre message : ", i);
        scanf("%d%d%d", &messages[i][0], &messages[i][1], &messages[i][2]);
    }
}

/**
 * \fn void codage_utilisateurs(int nbUser, int tableau[MAX][MAX], int messages[MAX][TAILLE_MESSAGE], int **tableau_messages)
 * 
 * \param nbUser, le nombre d'utilisateurs souhaitant envoyer un message
 * \param tableau, la matrice d'Hadamard
 * \param messages[MAX][TAILLE_MESSAGE], tableau contenant les messages des utilisateurs
 * \param **tableau_messages, le tableau stockant les messages codés
 * 
 * \brief Permet d'effectuer le codage du message de chaque utilisateur
 */
void codage_utilisateurs(int nbUser, int tableau[MAX][MAX], int messages[MAX][TAILLE_MESSAGE], int **tableau_messages){
    for(int i = 0; i < nbUser; i++){
            codage(i, nbUser, tableau, messages[i], *(tableau_messages + i));
    }
}


/**
 * \fn int *canal(int *mess_etale)
 * 
 * \param *mess_etale, les messages des utilisateurs, étalés et codés
 * 
 * \brief Envoie par cette fonction canal, un message étalé
 * */
int *canal(int *mess_etale){
    return mess_etale;
}


/**
 * \fn void desetalement(int *mess_recu, int messages_recu[MAX][TAILLE_MESSAGE], int nbUser, int taille_mess, int tableau[MAX][MAX])
 * 
 * \param *mess_recu message des utilisateurs après étalage
 * \param messages_recu tableau recuperant les messages apres desetalage
 * \param nbUser le nombre d'utilisateurs souhaitant envoyer un message
 * \param taille_mess La taille du message apres etalage
 * \param tableau tableau contenant l'étalement de Hadamard
 * 
 * \brief Fonction qui transforme des messages étalés en messages.
 */
void desetalement(int *mess_recu, int messages_recu[MAX][TAILLE_MESSAGE], int nbUser, int taille_mess, int tableau[MAX][MAX]){
    int userActuel, charMess, cmp, bit;
    int res;
    int traitement_mess[taille_mess];

    

    for(userActuel = 0; userActuel < nbUser; userActuel++){

        //Copie du message étalé pour pouvoir le modifier
        for(charMess =0; charMess< taille_mess; charMess++){
            traitement_mess[charMess] = mess_recu[charMess];
        }

        //Multiplication du message étalé par la ligne de l'étalement de Hadamard
        cmp = 0;
        for(charMess = 0; charMess < taille_mess; charMess++){
            traitement_mess[charMess]*= tableau[userActuel][cmp];

            cmp+=1;
            if(cmp == MAX){
                cmp=0;
            }
        }

        //Désétalement du message
        bit = 0;
        for(charMess=0; charMess < taille_mess; charMess++){
            res = 0;
            for(cmp = 0; cmp<nbUser; cmp++){
                res+=traitement_mess[bit];
                bit +=1;
            }
            if(res >= 1){
                messages_recu[userActuel][charMess] = 1;
            }
            else{
                messages_recu[userActuel][charMess] = 0;
            }
        }


    }
   
}