//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#ifndef JEU_NIM_NIM_IO_H
#define JEU_NIM_NIM_IO_H

#endif //JEU_NIM_NIM_IO_H

extern int const plateauConstant [20];


/*
Demande à l'usager de saisir un entier entre les bornes min et max
(inclusivement). La fonction doit valider la saisie et redemander à l'usager
de saisir une valeur jusqu'à l'obtention d'une valeur satisfaisante.*/
int lire_entier(int min, int max);

/*Affiche la configuration du plateau à l'écran. Elle affiche chacune des
colonnes en mettant une pièce par ligne, selon le nombre de pièces présentes
dans la colonne en question.
*/
void plateau_afficher(const int plateau[], int nb_colonnes);

/*
 Déclenche le tour de l'humain en demandant à l'usager de choisir la colonne
(appel à ihm_choisir_colonne) et le nombre de pièces à retirer du plateau de
jeu. Une fois le choix effectué, la fonction doit faire appel à
nim_jouer_tour pour appliquer les changements au plateau.
 */
void tour_humain(int plateau[], int nb_colonnes);

/*Déclenche le tour de l'ordinateur. Pour connaitre le choix de l'ordinateur,
on faisant appel à la fonction nim_choix_ia.
Une fois le choix effectué, la fonction doit faire appel à nim_jouer_tour
pour appliquer les changements au plateau.
*/
void tour_ia(int plateau[], int nb_colonnes, double difficulte);

/*
 * Fonction qui contrôle le jeu de nim: elle donne la main, tour à tour, à
chacun des deux joueurs et déclare le gagnant une fois la partie terminée.
On quitte cette fonction quand la partie est terminée.
Pour donner la main aux joueurs, on appelle les fonctions tour_humain et
tour_ia. Après chaque tour, cette fonction se charge de défragmenter le
plateau de jeu, de modifier la taille du plateau à l'écran et d'afficher la
nouvelle configuration du plateau de jeu.
 */
void demarrer_jeu(double difficulte);

