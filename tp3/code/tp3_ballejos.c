#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mt.h"

// TP3 BALLEJOS Lilian
// Sujet: https://perso.isima.fr/~dahill/Simu-ZZ2/Lab%20%23%203%20-%20Simu%20PI%20&%20Conf%20Intervals.pdf
// Compilation: make

// Exercice 1

/******************************************************/
/*                      simPi                         */
/*   Tire aléatoirement "nbPoint" dans un demi-cercle */
/*   et approche la valeur de PI                      */
/*                                                    */
/*   nbPoint (int): nombre d'itération de la          */
/*   simulation                                       */
/*                                                    */
/*   Sortie attendue: une approximation de PI         */
/******************************************************/
double simPi(int nbPoint)
{
    double x, y;
    double inCircle = 0;

    for (int i = 0; i < nbPoint; i++)
    {
        x = genrand_real2();
        y = genrand_real2();

        //Si dans le cercle
        if (x * x + y * y < 1)
            inCircle++;
    }
    return inCircle / nbPoint * 4;
}

/******************************************************/
/*                simuleSimPiPourExo1                 */
/*   Appelle simPi() 6 fois en commençant avec 10 000 */
/*   puis en multipliant à chaque fois par 10 jusqu'à */
/*   1 milliard                                       */
/*   Permet de voir la précision des pseudos Pi       */
/*   générés par simPi() selon le nombre de point     */
/******************************************************/
void simuleSimPiPourExo1()
{
    printf("===== Sortie de simPI =====\n");

    for (int i = 10000; i <= 1000000000; i *= 10)
        printf("Pour N = %d\t %lf\n", i, simPi(i));

    printf("===========================\n");
}

// Exercice 2

/******************************************************/
/*                 meanSimpPi                         */
/*   Appelle "nbIter" fois la fonction simPi() avec   */
/*   "nbPoint" en paramètre de celle-ci               */
/*   Calcul la moyenne de toutes les sorties          */
/*                                                    */
/*   nbIter  (int): nombre de fois qu'on appelle      */
/*                     simPi()                        */
/*   nbPoint (int): nombre de point que va tirer      */
/*                     simPi()                        */
/*                                                    */
/*   Sortie attendue: une approximation de PI         */
/******************************************************/
double meanPi(int nbIter, int nbPoint)
{
    double sum = 0;

    for (int i = 0; i < nbIter; i++)
        sum += simPi(nbPoint);

    return sum / nbIter;
}

/******************************************************/
/*                 errorAbsolutePi                    */
/*   Renvoie l'erreur absolu d'un pseudo PI donné     */
/*                                                    */
/*   pseudoPi (double): le PI à tester                */
/*                                                    */
/*   Sortie attendue: l'erreur absolue du pseudi PI   */
/*                   testé (plus on est proche de 0   */
/*                   mieux c'est)                     */
/******************************************************/
double errorAbsolutePi(double pseudoPi)
{
    return M_PI - pseudoPi;
}

/******************************************************/
/*                 errorRelativePi                    */
/*   Renvoie l'erreur relative d'un pseudo PI donné   */
/*                                                    */
/*   pseudoPi (double): le PI à tester                */
/*                                                    */
/*   Sortie attendue: l'erreur relative du pseudi PI  */
/*                   testé (plus on est proche de 1   */
/*                   mieux c'est)                     */
/******************************************************/
double errorRelativePi(double pseudoPi)
{
    return pseudoPi / M_PI;
}

/******************************************************/
/*                simuleMeanPiPourExo2                */
/*   Appelle meanPi() 3 fois en commençant avec 1000  */
/*   puis 1 million de point et 1 milliard de point   */
/*   en appelant n fois la fonction simPi dans meanPi */
/*                                                    */
/*   n  (int): nombre de fois qu'on appelle simPi()   */
/*                     dans meanPi                    */
/*                                                    */
/*   Permet de voir la précision des pseudos Pi       */
/*   générés par mean() selon le nombre de point      */
/*   et le nombre de PI moyenné                       */
/******************************************************/
void simuleMeanPiPourExo2(int n)
{
    double temp;

    printf("===== Sortie de meanPI avec %d appels de simPi =====\n", n);

    temp = meanPi(n, 1000);
    printf("Pour N = 1000\t %lf | Erreur relative: %lf | Erreur absolue: %lf\n", temp, errorRelativePi(temp), errorAbsolutePi(temp));

    temp = meanPi(n, 1000000);
    printf("Pour N = 1 000 000\t %lf | Erreur relative: %lf | Erreur absolue: %lf\n", temp, errorRelativePi(temp), errorAbsolutePi(temp));
    
    temp = meanPi(n, 1000000000);
    printf("Pour N = 1 000 000 000\t %lf | Erreur relative: %lf | Erreur absolue: %lf\n", temp, errorRelativePi(temp), errorAbsolutePi(temp));

    printf("=====================================================\n");
}


// Exercice 3

/******************************************************/
/*                 meanPiWithArray                    */
/*   Appelle "nbIter" fois la fonction simPi() avec   */
/*   "nbPoint" en paramètre de celle-ci               */
/*   Calcul la moyenne de toutes les sorties et stock */
/*   les sorties de Pi dans le tableau "sortie"       */
/*                                                    */
/*   nbIter  (int): nombre de fois qu'on appelle      */
/*                     simPi()                        */
/*   nbPoint (int): nombre de point que va tirer      */
/*                     simPi()                        */
/*   *sortie (double): tableau qui recoit les valeurs */
/*                     de PI renvoyé par simPi()      */
/*                                                    */
/*   Sortie attendue: un pseudi PI en retour et les   */
/*   les valeurs utilisées pour la moyenne dans       */
/*   l'argument *sortie                               */
/******************************************************/
double meanPiWithArray(int nbIter, int nbPoint, double *sortie)
{
    // Stockage de chaque résultat d'experience et calcul moyenne
    double meanExp = 0;

    for (int i = 0; i < nbIter; i++)
    {
        sortie[i] = simPi(nbPoint);
        meanExp += sortie[i];
    }

    return meanExp /= nbIter;
}

/******************************************************/
/*                 EstimateWithoutBiasPi              */
/*   Renvoie l'estimateur non biaisé de PI à partir   */
/*   du nombre de tirage de l'expérience, la moyenne  */
/*   et les pseudos PI tiré                           */
/*                                                    */
/*   nbExp    (int): nombre de tirage de l'expérience */
/*   meanExp (double): moyenne de tout les pseudo PI  */
/*   *resultExp (double): tableau qui contient tout   */
/*                        les pseudos PI tirés        */
/*                                                    */
/*   Sortie attendue: un estimater non biaisé selon   */
/*   les PI tirés et leur moyenne                     */
/******************************************************/

double EstimateWithoutBiasPi(int nbExp, double meanExp, double *resultExp)
{
    // Calcul de l'estimateur non biaisé
    double estimateWB = 0;

    for (int i = 0; i < nbExp; i++)
    {
        estimateWB += (resultExp[i] - meanExp) * (resultExp[i] - meanExp);
    }

    estimateWB /= (nbExp - 1);

    return estimateWB;
}


/******************************************************/
/*                    CalculR                         */
/*   Renvoie la valeur de R à partir de l'estimateur  */
/*   non biaisé de PI et du nombre de tirage          */
/*                                                    */
/*   nbExp    (int): nombre de tirage de l'expérience */
/*   estimateWB (double): estimateur non biaisé de    */
/*                        PI                          */
/*                                                    */
/*   Sortie attendue: une valeur de R calculée selon  */
/*                    un estimateur                   */
/******************************************************/
double CalculR(int nbExp, double estimateWB)
{
    double t05[30] = {12.706, 4.303, 3.182, 2.776, 2.571, 5.447, 2.365, 2.308, 2.262, 2.228,
                      2.201, 2.179, 2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 2.074,
                      2.069, 2.064, 2.060, 2.056, 2.052, 2.048, 2.045, 2.042};

    return t05[nbExp - 1] * sqrt(estimateWB / nbExp);
}


/******************************************************/
/*               showConfidenceInterval               */
/*   Affiche un intervalle de confiance de la valeur  */
/*   de PI à l'aide des fonctions meanPiWithArray(),  */
/*   EstimateWithoutBiasPi() et CalculR()             */
/*                                                    */
/*   nbExp    (int): nombre de tirage de l'expérience */
/*   nbPointMean (int): nombre de point que va tirer  */
/*                     simPi()                        */
/******************************************************/
void showConfidenceInterval(int nbExp, int nbPointMean)
{
    if (nbExp > 30 || nbExp < 1)
    {
        printf("Erreur: le nombre d'experience doit être compris entre 1 et 30, %d est une entrée invalide\n", nbExp);
    }
    else
    {
        // Récuperation moyenne et valeur de PI
        double *sortiePi = (double *)malloc(nbExp * sizeof(double));
        double mean = meanPiWithArray(nbExp, nbPointMean, sortiePi);

        // Calcul de l'estimateur non biaisé
        double estimateWB = EstimateWithoutBiasPi(nbExp, mean, sortiePi);
        printf("Estimateur non biaisé: %lf\n", estimateWB);

        // Calcul de R
        double r = CalculR(nbExp, estimateWB);

        // Affichage de l'intervalle de confiance
        printf("Pour un nombre d'experience de %d avec %d points on a:\n", nbExp, nbPointMean);
        printf("Intervalle de confiance à 95%% : [%lf - %lf]\n", mean - r, mean + r);

        free(sortiePi);
    }
}

/******************************************************/
/*                  Main                              */
/******************************************************/
int main()
{
    // Init
    unsigned long init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    init_by_array(init, length);

    // Exercice 1
    /*simuleSimPiPourExo1();*/

    // Exercice 2
    /*double pi = meanPi(1000, 1000000);
    printf("PI: %lf\nErreur Absolue: %lf\nErreur Relative: %lf\n",pi, errorAbsolutePi(pi), errorRelativePi(pi));*/
    /*simuleMeanPiPourExo2(40);*/

    // Exercice 3
    showConfidenceInterval(30, 1000000);

    return 1;
}