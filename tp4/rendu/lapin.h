#ifndef LAPIN_H
#define LAPIN_H

typedef enum {			//Création du type boolean pour une utilisation simplifié
  false = 0,
  true = 1
} boolean_t;

typedef struct{			//Structure représentatant un lapin
    int       age;
    boolean_t adult;
    boolean_t isMale;
    int       nbLitterThisyear;
    boolean_t used;
}lapin_t;


typedef struct{			//Structure représentant un couple de lapin
	int male;
	int female;
}couple_t;

#define TAILLE_MAX_TAB 102400	//Taille maximum de notre liste de lapins

static double proba_porte[5]    = { 0.125 , 0.375 , 0.625 , 0.875 , 1 };		//Tableau des probabilitées du nombre de portées/ans
static int proba_nb_child[4] 	= { 3 , 4 , 5 , 6 };							//Tableau des probabilitées du nombre de petits par portées
static double proba_maturite[4] = { 0.15 , 0.25 , 0.5 , 1 };					//Tableau des probabilitées du passage à la maturité
static double proba_survi[7]    = { 0.35 , 0.6 , 0.5 , 0.4 , 0.3 , 0.2 , 0.1 }; //Tableau des probabilitées du pourcentage de chance de survivre à la fin d'une année


/*Fonction*/

long RabbitFibo( int iteration );
void SimulEvoRabbit( int nbRabbitStart , lapin_t * listLapin , int nbItera );
void InitListRabbit( int number , boolean_t areMature , int age , lapin_t * listLapin );
void AfficheListLapin( int number , lapin_t * listLapin );
void AfficheListCouple( int number , couple_t * listCouple );
int CreateCouple( int nbRabbit , lapin_t * listLapin , couple_t  * listCouple );
void selectionNaturel( int * nbRabbit , lapin_t * listLapin );
void deleteRabbit( int indice , int nbRabbaDecaler , lapin_t * listLapin );
void setLitters( int nbRabbit , lapin_t * listLapin );
void tuer( int indice , int * nbRabbit , lapin_t * listLapin , int * totaltue , int * RabCurent );

#endif