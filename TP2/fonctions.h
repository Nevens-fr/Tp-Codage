#ifndef FONCTIONS_H__
    #define FONCTIONS_H__


    void remplissage_decalage(int tab[MAX][MAX], int longueur, int etage1, int etage2, int val);
    void gold(sequence seq1, sequence seq2, int res[MAX], int longueur);
    void init_matrice(int tab[MAX][MAX], int l, int c);
    void cLM(sequence seq, int etage, int etageMax, int tab[MAX][MAX]);
    void jpl(sequence tabSeq[MAX], int res[MAX], int tailleTabSeq, int longueur);


#endif