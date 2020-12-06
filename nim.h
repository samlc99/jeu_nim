//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#ifndef JEU_NIM_NIM_H
#define JEU_NIM_NIM_H

#define PLATEAU_MAX_COLONNES 20
#define PLATEAU_MAX_PIECES 35

#endif //JEU_NIM_NIM_H

/*
Initialise le plateau de jeu en remplissant les nb_colonnes d'un nombre
aléatoire de pièces entre 1 et PLATEAU_MAX_PIECES=35.
 */
void nim_plateau_init(int plateau[], int nb_colonnes);

/*
Fonction qui détermine, aléatoirement, qui doit jouer en premier. Elle
retourne l'identifiant du joueur (JOUEUR_HUMAIN==0 ou JOUEUR_IA==1).
 */
int nim_qui_commence(void);

/*
Applique des changements à la configuration du plateau de jeu en retirant
"nb_pieces" de la colonne "colonne" du plateau.
La fonction s'assure que le jeu est valide et renvoie Vrai si le jeu désiré
a pu s'appliquer à la configuration actuelle du jeu. Pour être valide, la
colonne doit exister et nombre de pièces retirées doit être <= au nombre de
pièces actuellement présentes dans la colonne en question.
 */
int nim_jouer_tour(int plateau[], int nb_colonnes, int colonne,
                   int nb_pieces);
/*
Supprime la colonne col_a_supprimer du plateau.
 */
void nim_plateau_supprimer_colonne(int plateau[], int nb_colonnes,
                                   int col_a_supprimer);
/*
Fonction qui supprime les colonnes vides du tableau en utilisant la fonction
nim_plateau_supprimer_colonne. Le nombre de colonnes restant est retourné.
 */
int nim_plateau_defragmenter(int plateau[], int nb_colonnes);

/*
Fonction qui détermine quel doit être le jeu de l'ordinateur. Cette fonction
implémente l'algorithme décrit dans l'énoncé du TP. Le choix de l'ordinateur
sera stocké dans les références choix_colonne et choix_nb_pieces.
Si une erreur de produit, la fonction stocke la valeur aberrante -1 dans les
références choix_colonne et choix_nb_pieces
 */
void nim_choix_ia(const int plateau[], int nb_colonnes, double difficulte,
                  int *choix_colonne, int *choix_nb_pieces);

/*
Fonction qui effectue un jeu aléatoire en choisissant au hasard une colonne,
puis au hasard le nombre de pièces à jouer de cette colonne.
 */
void nim_choix_ia_aleatoire(const int plateau[], int nb_colonnes,
                            int * choix_colonne, int * choix_nb_pieces);

