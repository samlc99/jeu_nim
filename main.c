#include <stdlib.h>
#include "nim_ihm.h"
#include "nim.h"
#include "m_distributions.h"
#include "codage_numerique.h"
#include "nim_io.h"

int main(int argc, char *argv[]) {
    md_srand_interne();
    if (!ihm_init_ecran(0, 0)) {
        system("pause");
        return EXIT_FAILURE;
    }

    demarrer_jeu(0);
    ihm_printf("Votre coquille du projet fonctionne convenablement. \n");
    //cd_test();
    nim_tester();
    ihm_pause();


    return 0;
}