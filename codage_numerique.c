//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "codage_numerique.h"
#include "nim_ihm.h"


int codage_inverser_tab_bits(int tab_bits[], int nb_bits) {


    ihm_printf("\nliste initiale : ");
    for (int i = 0; i<nb_bits; i++){

        ihm_printf("%d, ", tab_bits[i]);

    }
    int tab_bits_inverse[nb_bits];                            // permet de compter postion tab_bits_inverse[]
    for (int i = 0; i < nb_bits; i++) {
        tab_bits_inverse[(nb_bits-i-1)] = tab_bits[i];           // la valeur du dernier tab_bits[] devient la premiere valeur du tab_bits_inverse[]
    }
    tab_bits = tab_bits_inverse;

    ihm_printf("\nliste finale : ");
    for (int i = 0; i<6; i++){

        ihm_printf("%d, ", tab_bits[i]);

    }
    return 1;


}