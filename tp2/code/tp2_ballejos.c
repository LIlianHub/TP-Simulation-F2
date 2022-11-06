#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// TP2 BALLEJOS Lilian
// Sujet: https://perso.isima.fr/~dahill/Simu-ZZ2/Lab%20%23%202%20-%20Gen%20Rand%20Variates%20(2).pdf
// Compilation: gcc -Wall -Wextra -g -o tp2_ballejos tp2_ballejos.c -lm

// Partie MT

#include <stdio.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti = N + 1;     /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0] = s & 0xffffffffUL;
    for (mti = 1; mti < N; mti++)
    {
        mt[mti] =
            (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i = 1;
    j = 0;
    k = (N > key_length ? N : key_length);
    for (; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL;                                                             /* for WORDSIZE > 32 machines */
        i++;
        j++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
        if (j >= key_length)
            j = 0;
    }
    for (k = N - 1; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i; /* non linear */
        mt[i] &= 0xffffffffUL;                                                  /* for WORDSIZE > 32 machines */
        i++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N)
    { /* generate N words at one time */
        int kk;

        if (mti == N + 1)         /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk = 0; kk < N - M; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < N - 1; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32() >> 1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32() * (1.0 / 4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32() * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5) * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a = genrand_int32() >> 5, b = genrand_int32() >> 6;
    return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}

// Outil
/******************************************************/
/*                   valeurMax                        */
/*   Renvoie la valeur max d'un tableau               */
/*                                                    */
/*   *tab (int): le tableau                           */
/*   taille (int): taille du tableau                  */
/******************************************************/
int valeurMax(int *tab, int taille)
{
    int max = tab[0];
    for (int i = 1; i < taille; i++)
    {
        if (tab[i] > max)
        {
            max = tab[i];
        }
    }
    return max;
}

/******************************************************/
/*                   afficheHistogramme               */
/*   Affiche un histogramme de répartition de données */
/*   dans un tableau une dimension                    */
/*                                                    */
/*   *histogramme (int): le tableau                   */
/*   taille (int): taille du tableau                  */
/*   precision (int): le nombre d'étage de            */
/*                   l'histogramme                    */
/*   *titre (char): le titre de l'histogramme         */
/******************************************************/
void afficheHistogramme(int *histogramme, int taille, int precision, char *titre)
{
    double ValeurPourcentage;
    // valeur maximal du tableau
    int max = valeurMax(histogramme, taille);
    // parcours par étage
    for (int i = precision; i > 0; i--)
    {
        // Calcul de la valeur limite pour afficher à l'étage actuel
        ValeurPourcentage = max * i / precision;
        printf("|");
        // affichage ou non des données
        for (int j = 0; j < taille; j++)
        {
            if ((double)histogramme[j] >= ValeurPourcentage)
                printf("☐");
            else
                printf(" ");
        }
        printf("\n");
    }
    // esthétisme
    for (int i = 0; i < taille; i++)
        printf("-");
    printf("\n%s\n", titre);
}

/******************************************************/
/*                   exportData                       */
/*   Ecrit dans un fichier du repertoire "sorti/" les */
/*   les sorties de proba stocké dans un tableau      */
/*                                                    */
/*   *repartiton (int): le tableau avec les probas    */
/*   nbIte (int): le nombre de tirage                 */
/*   *nom   (char): le nom qu'aura le fichier         */
/*   nb_data (int): taille du tableau                 */
/******************************************************/
void exportData(int *repartition, int nbIte, char *nom, int nb_data)
{
    FILE *fichier = NULL;
    char destination[100];
    // repertoire de sortie concaténé avec le nom du fichier
    strcpy(destination, "sorti/");
    strcat(destination, nom);
    if ((fichier = fopen(destination, "w+")))
    {
        fprintf(fichier, "Valeur de sorti sur %d itérations:\n", nbIte);
        for (int i = 0; i < nb_data; i++)
        {
            fprintf(fichier, "%d; ", repartition[i]);
        }
        fclose(fichier);
    }
}

// Question 1
// ./mt19937ar > test.out
// diff test.out mt19937ar.out
// la sortie du diff est vide donc on a exactment les même sorties

// Question 2

/******************************************************/
/*                   Uniform                          */
/*   Renvoie un double aléatoire tiré dans            */
/*   l'intervalle [ a , b ]                           */
/*                                                    */
/*   a (double): borne minimum                        */
/*   b (double): borne maximal                        */
/******************************************************/
double uniform(double a, double b)
{
    return (a + (b - a) * genrand_real2());
}

// Question 3
// le generateur genrand_real2() semble tres bien réparti sur l'intervalle [0,1]

/******************************************************/
/*                   SimulDiscreteABC                 */
/*   Simule un tirage aléatoire sur 3 classes A, B et */
/*   C                                                */
/*                                                    */
/*   nbIte (int): nombre d'itération de la simulation */
/******************************************************/
void SimulDiscreteABC(int nbIte)
{
    double proba[3] = {0.35, 0.45, 0.20};
    double cdf[3] = {0};

    // calcul de la cdf
    cdf[0] = proba[0];
    cdf[1] = proba[1] + cdf[0];
    cdf[2] = proba[2] + cdf[1];

    double sorti[3] = {0};
    double tirage;

    for (int i = 0; i < nbIte; i++)
    {
        // repartion des sorties dans le tableau "sorti en fonction des valeurs"
        tirage = genrand_real2();
        if (tirage < cdf[0])
            sorti[0]++;
        else if (tirage < cdf[1])
            sorti[1]++;
        else
            sorti[2]++;
    }
    printf("Sortie sur %d itérations:\n", nbIte);
    printf("Class A : Attendu %f\t Sortie:%f\n", proba[0], sorti[0] / nbIte);
    printf("Class B : Attendu %f\t Sortie:%f\n", proba[1], sorti[1] / nbIte);
    printf("Class C : Attendu %f\t Sortie:%f\n", proba[2], sorti[2] / nbIte);
}

/******************************************************/
/*               SimulDiscreteGeneric                 */
/*   Simule un tirage aléatoire sur NbClass classes   */
/*   en créant un tableau cdf (proba cumulée) à partir*/
/*   d'un tableau de proba                            */
/*                                                    */
/*   nbIte (int): nombre d'itération de la simulation */
/*   *proba (int*): tableau contenant les proba de    */
/*                  chaque classe                     */
/*   NbClass (int): le nombre de classe               */
/******************************************************/
void SimulDiscreteGeneric(int NbClass, double *proba, int nbIte)
{
    double *cdf = (double *)malloc(sizeof(double) * NbClass);
    double *sorti = (double *)calloc(NbClass, sizeof(double));

    // Construction CDF
    cdf[0] = proba[0];
    for (int i = 1; i < NbClass; i++)
    {
        cdf[i] = cdf[i - 1] + proba[i];
    }

    int j;
    double tirage;

    for (int i = 0; i < nbIte; i++)
    {
        tirage = genrand_real2();
        j = 0;
        // tant qu'on a pas trouvé la classe qu'il faut on cherche
        while (tirage > cdf[j])
            j++;
        sorti[j]++;
    }

    printf("Sortie sur %d itérations:\n", nbIte);
    for (int i = 0; i < NbClass; i++)
    {
        printf("Class %c : Attendu %f\t Sortie:%f\n", i + 'A', proba[i], sorti[i] / nbIte);
    }

    free(cdf);
    free(sorti);
}

// Question 4

/******************************************************/
/*               negExp                               */
/*   Simule un tirage aléatoire suivant la loi        */
/*    exponentielle inverse                           */
/*                                                    */
/*   mean (double): argument de la loi exponentielle  */
/******************************************************/
double negExp(double mean)
{
    return -mean * log(1 - genrand_real2());
}

/******************************************************/
/*               SimulNegExp                          */
/*   Simule à répétition le tirage de la loi          */
/*   exponentielle négatif sur un nombre d'itération  */
/*   donnée                                           */
/*                                                    */
/*   mean (double): argument de la loi exponentielle  */
/*   nbIte (int): nombre d'itération de la simulation */
/******************************************************/
void SimulNegExp(double mean, int nbIte)
{
    double sorti = 0;

    // Addition des sorties
    for (int i = 0; i < nbIte; i++)
    {
        sorti += negExp(mean);
    }

    // Calcul de la moyenne en divisant par le nombre d'itération
    sorti /= nbIte;

    printf("Moyenne sur %d itérations: %lf\n", nbIte, sorti);
}

/******************************************************/
/*               DiscretDitribNegExp                  */
/*   Effectue plusieurs tirage sur la fonction        */
/*   negExp et affiche la repartition de sortie sur   */
/*   plusieurs intervalles de 0 à +oo                 */
/*                                                    */
/*   mean (double): argument de la loi exponentielle  */
/*   nbIte (int): nombre d'itération de la simulation */
/******************************************************/
void DiscretDitribNegExp(double mean, int nbIte)
{
    int *sorti = (int *)calloc(23, sizeof(int));

    double tirage;

    for (int i = 0; i < nbIte; i++)
    {
        tirage = negExp(mean);
        if (tirage < 23)
            sorti[(int)tirage]++;
        // limite de l'intervalle
        else
            sorti[22]++;
    }

    printf("Sortie sur %d itérations:\n", nbIte);
    for (int i = 0; i < 22; i++)
    {
        printf("Intervalle [ %d , %d [ : %d\n", i, i + 1, sorti[i]);
    }
    printf("Intervalle [ 22 , +oo [ : %d\n", sorti[22]);

    exportData(sorti, nbIte, "negExp.txt", 23);

    free(sorti);
}

// Question 5

/******************************************************/
/*               Dice                                 */
/*   Simule un lancé de dès à 6 faces et renvoie la   */
/*   face choisis                                     */
/*                                                    */
/******************************************************/
int Dice()
{
    return 1 + (6 - 1) * genrand_real2();
}

/******************************************************/
/*               SimulDice                            */
/*   Simule à répétition 30 tirages d'un dès à 6 faces*/
/*   en additionnant les faces obtenues afin          */
/*   d'approcher une gaussienne                       */
/*                                                    */
/*   nbIte (int): nombre d'itération de la simulation */
/******************************************************/
void SimulDice(int nbIte)
{
    int *repartition = (int *)calloc(150, sizeof(int));

    int sorti;

    for (int i = 0; i < nbIte; i++)
    {
        sorti = 0;
        // 30 tirages de dés
        for (int i = 0; i < 30; i++)
        {
            sorti += Dice();
        }
        // -30 pour avoir un intervalle de 0 à 150 compatible avec notre tableau sorti
        repartition[sorti - 30]++;
    }
    exportData(repartition, nbIte, "dice.out", 150);
    afficheHistogramme(repartition, 150, 10, "Histogramme de la Simulation avec lancé de dés");
    free(repartition);
}

/******************************************************/
/*               BoxAndMullerX1                       */
/*   Génére 1 nombre à l'aide de 2 nombres supposés   */
/*   aléatoire selon l'équation de BoxandMuller       */
/*   numéro 1                                         */
/*                                                    */
/*   u1 (double): premier nombre supposé aléatoire    */
/*   u2 (double): deuxième nombre supposé aléatoire   */
/******************************************************/
double BoxAndMullerX1(double u1, double u2)
{
    return sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
}

/******************************************************/
/*               BoxAndMullerX2                       */
/*   Génére 1 nombre à l'aide de 2 nombres supposés   */
/*   aléatoire selon l'équation de BoxandMuller       */
/*   numéro 2                                         */
/*                                                    */
/*   u1 (double): premier nombre supposé aléatoire    */
/*   u2 (double): deuxième nombre supposé aléatoire   */
/******************************************************/
double BoxAndMullerX2(double u1, double u2)
{
    return sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
}

/******************************************************/
/*               SimulBoxAndMuller                    */
/*   Simule à répétition des sorties aléatoires       */
/*   selon la loi de BoxAndMuller afin d'approcher    */
/*   une gaussienne entre -5 et 5                     */
/*                                                    */
/*   nbIte (int): nombre d'itération de la simulation */
/******************************************************/
void SimulBoxAndMuller(int nbIte)
{
    int repartition[20] = {0};
    double u1, u2;

    for (int i = 0; i < nbIte; i++)
    {
        u1 = genrand_real2();
        u2 = genrand_real2();

        // Réajustement sur un tableau de taille 20 entre 0 et 19 (* 10 + 50 / 5)
        repartition[(int)((BoxAndMullerX1(u1, u2) * 10 + 50) / 5)]++;
        repartition[(int)((BoxAndMullerX2(u1, u2) * 10 + 50) / 5)]++;
    }

    exportData(repartition, nbIte, "boxAndMuller.out", 20);
    afficheHistogramme(repartition, 20, 20, "Histogramme de BoxAndMuller");
}

// Question 6
// Boost Random Number Library Distributions peut génèrer des nombres aléatoires sur une loi normale (gaussienne) en C/C++
// Commons Math: The Apache Commons Mathematics Library possède une class "NormalDistribution" en Java

/******************************************************/
/*                  Main                              */
/******************************************************/
int main(int argc, char *argv[])
{
    // Init
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    // Test
    if (argc >= 2)
    {
        // Question 2 : ./tp2_ballejos borneMin borneMax nbIte
        /*for (int i = 1; i < atoi(argv[3]) + 1; i++)
        {
            printf("%lf\t", uniform(atof(argv[1]), atof(argv[2])));
            if (i % 4 == 0)
                printf("\n");
        }
        printf("\n");*/

        // Question 3 : ./tp2_ballejos nbIte
        /*SimulDiscreteABC(atoi(argv[1]));*/

        /*double proba[6] = {0.5, 0.3, 0.1, 0.05, 0.025, 0.025};
        SimulDiscreteGeneric(6, proba, atoi(argv[1]));*/

        // Question 4 : ./tp2_ballejos mean nbIte
        /*SimulNegExp(atof(argv[1]), atoi(argv[2]));*/
        /*DiscretDitribNegExp(atof(argv[1]), atoi(argv[2]));*/

        // Question 5 : ./tp2_ballejos nbIte
        /*SimulDice(atoi(argv[1]));*/
        SimulBoxAndMuller(atoi(argv[1]));
    }
    else
    {
        printf("Entrer le bon nombre d'argument\n");
    }
    return 1;
}

// Remarque sur le TP

// L'expérience de BoxAndMuller semble bien plus rapide pour generer des nombres aléatoires
// simulant une gaussienne que la méthode avec les dès

// Les commentaires /**/ sont voués à être supprimés Ils sont ici pour rendre l'execution du main plus lisible
// et ne pas biaiser les tirages aléatoires
// Pour tester une des fonctions du tp vous avez juste à décommenter la ligne correspondante dans le main

// Bien penser à créer le repertoire "sorti" si vous souhaitez voir les sorties dans des fichiers