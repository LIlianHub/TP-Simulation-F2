#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TP1 de BALLEJOS Lilian
// Sujet: https://perso.isima.fr/~dahill/Simu-ZZ2/Lab%20%23%201%20-%20Rand%20Simu.pdf
// Compilation: gcc -Wall -Wextra tp1_ballejos.c -o tp1_ballejos

// Question 1
void JohnVonNeumann(int seed, int iteration)
{
    int val = seed;
    for (int i = 0; i < iteration; i++)
    {
        printf("N°%d\t", i);
        val = val * val;
        printf("%08d  ", val);
        val = val / 100;
        printf("%06d  ", val);
        val = val % 10000;
        printf(">%04d<\n", val);
    }
}

// Question 3 : Non la fonction semble insuffisante dès que l'on va en 3 dimensions,
// elle est simplement utile pour des simples tests

// Question 4
void Toss(int iteration)
{
    int cptPile = 0;
    int tirage;
    for (int i = 0; i < iteration; i++)
    {
        tirage = rand() % 2;
        if (tirage)
        {
            cptPile++;
        }
    }
    printf("Ratio tirage Toss: %d / %d\n", cptPile, iteration - cptPile);
}

// Question 5
void Dice(int iteration, int nbFace)
{
    int *result = (int *)calloc(nbFace, sizeof(int));
    int tirage;
    for (int i = 0; i < iteration; i++)
    {
        tirage = rand() % nbFace;
        result[tirage] += 1;
    }

    printf("Ratio tirage:\n");
    for (int i = 0; i < nbFace; i++)
    {
        printf("Nombre de %d: %d\n", i + 1, result[i]);
    }

    free(result);
}

// Question 6

// Variable Générale pour mémoriser la dernière valeur de la fonction et ressembler au plus
// au comportement de la fonction srand() de stdlib
int SEED = 0;

int intRand()
{
    SEED = (5 * SEED + 1) % 16;
    return SEED;
}

void intSrand(int seed)
{
    SEED = seed;
}

// Question 7
float floatRand()
{
    float result = intRand();
    result /= 16;
    return result;
}

// Question 9 Avec Turbo Pascal (source Wikipedia)
long SEED_LONG = 0;

void longSrand(int seed)
{
    SEED_LONG = seed;
}

long longRandOpti()
{
    SEED_LONG = (134775813 * SEED_LONG + 1) % 4294967296;
    return SEED_LONG;
}

// Question 10 : Intel® oneAPI Math Kernel Library (for C and C++) : Elle semble à jour
//              et possède des générateurs aléatoires

// Question 11 : TestU01: A C library for empirical testing of random number generators

// Question Bonus

// La taille du mot binaire
#define TAILLE_BINAIRE 4

// Nécessaire car pas de \0 à la fin de ma chaines de caractères
void AfficheBinaire(char *binaire)
{
    for (int i = 0; i < TAILLE_BINAIRE; i++)
    {
        printf("%c", binaire[i]);
    }
    printf("\n");
}

void BitsShiftRandom(int iteration, char *seed)
{
    printf("SEED :");
    AfficheBinaire(seed);

    int tmp;
    for (int i = 0; i < iteration; i++)
    {

        // Opération XOR
        tmp = (seed[2] - '0') ^ (seed[3] - '0');

        // Décalage à droite
        for (int k = TAILLE_BINAIRE - 1; k > 0; k--)
            seed[k] = seed[k - 1];

        // Ajout du résultat de l'opération XOR au debut
        seed[0] = tmp + '0';

        // Affichage
        printf("N°%d\t", i + 1);
        AfficheBinaire(seed);
    }
}

// Main
int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        //JohnVonNeumann(atoi(argv[1]), atoi(argv[2]));

        //Toss(atoi(argv[1]));

        //Dice(atoi(argv[1]), atoi(argv[2]));

        /*intSrand(atoi(argv[1]));
        int test;
        for(int i = 0; i < 32; i++){
            test = intRand();
            printf("%d ", test);
        }*/

        /*intSrand(atoi(argv[1]));
        float test;
        for(int i = 0; i < 32; i++){
            test = floatRand();
            printf("%f ", test);
        }*/

        /*longSrand(atoi(argv[1]));
        long test;
        for(int i = 0; i < 32; i++){
            test = longRandOpti();
            printf("%ld ", test);
        }*/

        char seed[TAILLE_BINAIRE] = {'0', '1', '1', '0'};
        BitsShiftRandom(atoi(argv[1]), seed);

        printf("\nFin du Programme\n");
    }
    else
    {
        printf("Faire : ./tp1_ballejos argument1 argument2 (varie selon fonction)\n");
    }
    return 1;
}

// Remarque
/*Pour la question Bonus j'ai appelé le programme avec la commande : "./tp1_ballejos 100 | grep 1011" afin
de chercher le nombre de fois où la chaine de caractère "1011" est présente dans la sortie du programme.
On observe bien des cycles de 15 avant de retomber sur cette valeur comme dit dans le cours (c'est à dire 4 bits soit 16 valeurs sans la valeur 0000 absorbante)
La sortie étant :
N°1	    1011
N°16	1011
N°31	1011
N°46	1011
N°61	1011
N°76	1011
N°91	1011*/