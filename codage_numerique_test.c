//
// Created by Samuel Lavigne-Cloutier on 2020-12-05.
//

#include "codage_numerique.h"
#include "nim_ihm.h"



void cd_test(){

    ihm_printf ("\nTESTS DE CODAGE\n\n");

    int tab_bits [6]= {0,0,1,1,1,0};
    codage_inverser_tab_bits(tab_bits,6);
}
