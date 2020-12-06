//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "nim.h"
#include "nim_ihm.h"
#include "nim_io.h"
#include "m_distributions.h"





void nim_plateau_init(int plateau[], int nb_colonnes){

    for(int i = 0; i<nb_colonnes; i++){
        plateau[i]= md_randi(35);
        //plateauConstant = plateau;
    }

}

int nim_qui_commence(void){

    return md_randint(0,1);

}

int nim_jouer_tour(int plateau[], int nb_colonnes, int colonne,
                   int nb_pieces){

    if(colonne>nb_colonnes||nb_pieces>plateau[colonne]) return 0;
    else{
        plateau[colonne]-=nb_pieces;
        return 1;
    }

}

void nim_plateau_supprimer_colonne(int plateau[], int nb_colonnes,
                                   int col_a_supprimer){
    int plateau_temp[20];
    for (int i = col_a_supprimer; i < nb_colonnes; i++) {
        plateau[i]=plateau[i+1];
    }

}

int nim_plateau_defragmenter(int plateau[], int nb_colonnes){

    for (int i = 0; i < nb_colonnes; i++) {
        if(plateau[i]==0) nim_plateau_supprimer_colonne(plateau, nb_colonnes, i);
        nb_colonnes--;
    }

}

void nim_choix_ia(const int plateau[], int nb_colonnes, double difficulte,
                  int *choix_colonne, int *choix_nb_pieces){

    nim_choix_ia_aleatoire(plateau, nb_colonnes, choix_colonne, choix_nb_pieces);

}

void nim_choix_ia_aleatoire(const int plateau[], int nb_colonnes,
                            int * choix_colonne, int * choix_nb_pieces){

}