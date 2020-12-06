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

int codage_dec2bin(int nombre, int resultat[]){
    int nb_bit_necessaire;
    while (nombre > 0) {
        for (int nb_bits = 0; nb_bits < CODAGE_NB_BITS; nb_bits++) {
            if (nombre % 2 == 0) {
                resultat[nb_bits] = 0;
                nombre /= 2;
            } else if (nombre % 2 == 1) {
                resultat[nb_bits] = 1;
                nombre /= 2;
                nb_bit_necessaire = nb_bits + 1;
            }
        }
        codage_inverser_tab_bits(resultat, CODAGE_NB_BITS);

    }
    if (nb_bit_necessaire > CODAGE_NB_BITS) {
        return 0;
    }
    return nb_bit_necessaire;

}
