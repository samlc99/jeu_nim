//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "nim.h"
#include "nim_ihm.h"
#include "nim_io.h"
#include "codage_numerique.h"



void nim_tester () {

    ihm_printf("Choisir le nombre de colonnes : ");

    ihm_printf("Nombre de colonnes choisi : [%d]",lire_entier(1,PLATEAU_MAX_COLONNES));
    nim_plateau_init(tab,6);
    plateau_afficher(tab,6);
    ihm_printf("Afficher qui commence : [%d]",nim_qui_commence());
    ihm_pause();
}

