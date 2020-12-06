//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "nim_io.h"
#include "nim_ihm.h"

int lire_entier(int min, int max){
    int entier;

    ihm_printf("Entrez une valeur entre %d et %d \n", min, max);
    ihm_scanf("%d", &entier);

    while(entier < min || entier > max){
        printf("Avec toute votre gentillesse, veuillez s'il vous plait entrez une valeur ENTRE %d et %d\n", min, max);
        scanf("%d", &entier);
    }

}

void plateau_afficher(const int plateau[], int nb_colonnes){

    for()

}

void tour_humain(int plateau[], int nb_colonnes){

}

void tour_ia(int plateau[], int nb_colonnes, double difficulte){

}

void demarrer_jeu(double difficulte){

}