#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lapin.h"
#include "mt.h"

// TP4 BALLEJOS Lilian CHARPIN Etienne
// Sujet: https://perso.isima.fr/~dahill/Simu-ZZ2/Lab%20%23%204%20-%20Rabbit%20Population%20growth.pdf
// Compilation: make

/******************************************************/
/*                  Main                              */
/******************************************************/
int main()
{
    // Init
    unsigned long init[4] = { 0x123 , 0x234 , 0x345 , 0x456 },
                   length = 4;

    init_by_array( init , length );

    //printf("%d\n", RabbitFibo(9));				//Question fibbonacci

    lapin_t listLapin[TAILLE_MAX_TAB];

    SimulEvoRabbit( 100 , listLapin , 120 );			//Fonction principale ( nombre de lapin , liste de lapin , nombre de mois de simulation )
    
    return 1;
}