//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "nim.h"
#include "nim_ihm.h"
#include "nim_io.h"


int lire_entier(int min, int max){
    int entier;

    ihm_printf("Entrez une valeur entre %d et %d \n", min, max);
    ihm_scanf("%d", &entier);

    while(entier < min || entier > max){
        ihm_printf("Avec toute votre gentillesse, veuillez s'il vous plait entrez une valeur ENTRE %d et %d\n", min, max);
        ihm_scanf("%d", &entier);
    }

}

void plateau_afficher(const int plateau[], int nb_colonnes){

    for(int i = 0; i<nb_colonnes; i++){
        for (int j = 0; j < plateau[i]; j++) {
            ihm_ajouter_piece(j,i);
        }
    }

}

void tour_humain(int plateau[], int nb_colonnes){

    //plateau = plateau;

}

void tour_ia(int plateau[], int nb_colonnes, double difficulte){

}

void demarrer_jeu(double difficulte){
    ihm_printf("Avec combien de lignes voulez-vous jouer? (max %d)",PLATEAU_MAX_PIECES);
    int nbLignes = lire_entier(1,PLATEAU_MAX_PIECES);
    ihm_printf("Avec combien de colonnes voulez-vous jouer? (max %d)",PLATEAU_MAX_COLONNES);
    int nbColonnes = lire_entier(1,PLATEAU_MAX_PIECES);
    ihm_changer_taille_plateau ((nbLignes+1),(nbColonnes+1));
    nim_plateau_init (plateau,6);
}