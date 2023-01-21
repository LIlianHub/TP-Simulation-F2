#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lapin.h"
#include "mt.h"

/*-------------------------------------------------------------------------*/
/* RabbitFibo :  Représente la suite de fibbonnaci pour simuler nos lapins */
/*                                                                         */
/* En entrée  :            iteration : int du nombre total d'iteration de  */
/*                        la suite                                         */
/*                                                                         */
/*                                                                         */
/* En sortie  :            long  derniere valeur de la suite de fibbonacci */
/*                                                                         */
/*-------------------------------------------------------------------------*/


long RabbitFibo( int iteration ){

    long u0  = 0,
        u1  = 1,
        cpt = 0,
        temp;

    while( cpt < iteration ){

        temp = u1;
        u1   = u0 + u1;
        u0   = temp;
        cpt ++;
        //printf("%ld\n", u0);

    }

    return u0;
}

/*-------------------------------------------------------------------------*/
/* AfficheListLapin  :    Affiche l'intégralité des lapins présents dans   */
/*                        la liste de lapin ainsi que leurs attributs      */
/*                                                                         */
/* En entrée :            number : int du nombre total de lapin            */
/*                        listLapin : Référence vers la liste de Lapins    */
/*                                                                         */
/*                                                                         */
/* En sortie :            Affichage de tous les Lapins                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void AfficheListLapin( int number , lapin_t * listLapin ){

    printf("Nombre total de Lapin: %d\n", number );

    for( int i = 0 ; i < number ; i++ ){

        printf("Lapin n° %d: %d %d %d %d %d \n",    i + 1,
                                                    listLapin[i].age,
                                                    listLapin[i].adult,                
                                                    listLapin[i].isMale,
                                                    listLapin[i].used,
                                                    listLapin[i].nbLitterThisyear);

    }

}



/*-------------------------------------------------------------------------*/
/* AfficheListCouple  :   Affiche l'intégralité des couples créer pour     */
/*                        l'implémentation de la reproduction              */
/*                                                                         */
/* En entrée :            number : int du nombre total de couple de lapin  */
/*                        listCouple : Référence vers la liste de Couples  */
/*                                                                         */
/*                                                                         */
/* En sortie :            Affichage de tous les couples : male  / female   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void AfficheListCouple( int number , couple_t * listCouple ){

    printf("Nombre total de couple: %d\n", number );

    for( int i = 0 ; i < number ; i++ ){

        printf("Couple n° %d: %d %d \n", i + 1,
                                         listCouple[i].male,
                                         listCouple[i].female);

    }

}




/*-------------------------------------------------------------------------*/
/* InitListRabbit  :   Initialisation de la liste de lapin de depart pour  */
/*                     la simulation. Naissant à l'age 0 et male et female */
/*                     du même nombre                                      */
/*                                                                         */
/* En entrée :            number : int du nombre de lapin de depart        */
/*                        areMature : boolean pour savoir si lapin adultes */
/*                        ou non                                           */
/*                        age : int du nombre de mois des lapins crées     */
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void InitListRabbit( int number , boolean_t areMature , int age , lapin_t * listLapin ){

    for( int i = 0 ; i < number ; i++ ){

        listLapin[i].age              = age;
        listLapin[i].adult            = areMature;
        listLapin[i].isMale           = i % 2;
        listLapin[i].nbLitterThisyear = 0;
        listLapin[i].used             = false;

    }

}



/*-------------------------------------------------------------------------*/
/* setLitters  :       Tirage de nombres pseudo-aléatoire du nombre de     */
/*                     portées pouvant éffectuer chaque female au cours    */
/*                     d'une année entre 4 et 8                            */
/*                                                                         */
/* En entrée :            nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void setLitters( int nbRabbit , lapin_t * listLapin ){


    double probaLitter;

    for( int i = 0 ; i < nbRabbit ; i++ ){

        if(listLapin[i].isMale == 0){

            probaLitter = genrand_real2();

            if( probaLitter < proba_porte[0] ){

                listLapin[i].nbLitterThisyear = 4;

            }

            else if( probaLitter < proba_porte[1] ){

                listLapin[i].nbLitterThisyear = 5;

            }

            else if( probaLitter < proba_porte[2] ){

                listLapin[i].nbLitterThisyear = 6;

            }

            else if( probaLitter < proba_porte[3] ){

                listLapin[i].nbLitterThisyear = 7;

            }

            else 

                listLapin[i].nbLitterThisyear = 8;

        }
    }

}


/*-------------------------------------------------------------------------*/
/* AddRabbit  :        Création d'une nouveau lapin dans la liste de lapin */
/*                     et remplissage de ses attributs                     */
/*                                                                         */
/* En entrée :            nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void AddRabbit( int * nbRabbit, lapin_t * listLapin  ){

    if( *nbRabbit < TAILLE_MAX_TAB ){

        listLapin[*nbRabbit].age              = 0;
        listLapin[*nbRabbit].adult            = false;
        listLapin[*nbRabbit].isMale           = genrand_int32() % 2;
        listLapin[*nbRabbit].nbLitterThisyear = 0;
        listLapin[*nbRabbit].used             = false;
        (*nbRabbit) ++;

    }

}


/*-------------------------------------------------------------------------*/
/* CreateCouple  :     Création de couple de lapin male et female. Ici     */
/*                     un male peu etre attribué a plusieurs female mais   */
/*                     le code prévoit le cas ou on a 1 male pour 1 female */
/*                                                                         */
/* En entrée :            nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                        listCouple : référence vers la liste de couples  */
/*                                                                         */
/* En sortie :            int du nombre de couples créés                   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

int CreateCouple( int nbRabbit , lapin_t * listLapin , couple_t * listCouple ){

    int
            TempFem         = 0,
            nbCouple        = 0,
            stop            = 0,
            FindMale        = 0,
            FindFem         = 0,
            cptTemp         = 0;


    while( stop != 1 ){

        cptTemp     = 0;
        FindFem     = 0;
        FindMale    = 0;

        while( cptTemp < nbRabbit && FindFem == 0 ){

            if( listLapin[cptTemp].isMale == false && listLapin[cptTemp].used == false && listLapin[cptTemp].adult == true && listLapin[cptTemp].nbLitterThisyear > 0 ){

                TempFem = cptTemp;
                FindFem = 1;

            }

            if( FindFem == 0 ){

                cptTemp++;

            }

        }

        if( cptTemp == nbRabbit ){

            stop = 1;

        }

        cptTemp     = 0;

        while( cptTemp < nbRabbit && FindMale == 0 && stop == 0 ){

            if( listLapin[cptTemp].isMale == true && listLapin[cptTemp].used == false && listLapin[cptTemp].adult == true ){

                listCouple[nbCouple].male   = cptTemp;
                listCouple[nbCouple].female = TempFem;
                listLapin[cptTemp].used     = false;
                listLapin[TempFem].used     = true;
                nbCouple ++;
                FindMale = 1;

            }

            if( FindMale == 0 ){

                cptTemp++;
                
            }

        }

        if( cptTemp == nbRabbit ){

            stop = 1;

        }


    }

    return nbCouple;

}





/*-------------------------------------------------------------------------*/
/* MAJMaturite  :     Mise à jour de la maturité de tous les lapins non    */
/*                    adultes suivant des probabilitées données            */
/*                                                                         */
/* En entrée :            nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void MAJMaturite( int nbRabbit , lapin_t * listLapin ){

    double probMat;


    for( int i = 0 ; i < nbRabbit ; i++ ){

        if( listLapin[i].adult == false && listLapin[i].age > 4 && listLapin[i].age < 9 ){

            probMat = genrand_real2();

            if( probMat < proba_maturite[listLapin[i].age - 5] ){

                listLapin[i].adult = true;

            }

        }
        
    }

}







/*-------------------------------------------------------------------------*/
/* tuer  :     Fonction de suppression de lapin pour éviter la duplication */
/*             de code dans la fonction selectionNaturel                   */
/*                                                                         */
/* En entrée :            indice : int de l'indice du lapin a supprimer    */
/*                        nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                        totaltue : int du total de lapin tué cette année */
/*                        RabCurent : int du nombre courant de lapins      */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void tuer( int indice , int * nbRabbit , lapin_t * listLapin , int * totaltue , int * RabCurent ){

    (*totaltue) ++;
    deleteRabbit(indice, *nbRabbit,listLapin);
    (*nbRabbit)--;
    (*RabCurent)--;

}



/*-------------------------------------------------------------------------*/
/* selectionNaturel  :  Mise en marche des probabilitées de selection      */
/*                      naturelle pour chaque lapin en fin d'annee         */
/*                      suivant des probabilitées données                  */
/*                                                                         */
/* En entrée :            nbRabbit : int du nombre de lapin dans la liste  */
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void selectionNaturel( int * nbRabbit , lapin_t * listLapin ){

    int             RabCurent  = *nbRabbit,
                    totaltue   = 0;

    double          probaMort;

    for( int i = 0 ; i < RabCurent ; i++ ){

        probaMort = genrand_real2();

        if( listLapin[i].adult == 0 ){

            if( probaMort > proba_survi[0] ){                                          //Cas lapin non mature

                tuer( i , nbRabbit , listLapin , &totaltue , &RabCurent );

            }

        }

        else if( listLapin[i].age < 120 ){

            if( probaMort > proba_survi[1] ){                                       //Cas lapin moins de 10 ans
                
                tuer( i , nbRabbit , listLapin , &totaltue , &RabCurent );

            }

        }

        else if( listLapin[i].age > 192 ){

           tuer( i , nbRabbit , listLapin , &totaltue , &RabCurent );

        }

        else{

            if( probaMort > proba_survi[ ( ( listLapin[i].age ) / 12 ) - 9 ] ){     //Cas lapin mature mais moins de 16 ans

                tuer( i , nbRabbit , listLapin , &totaltue , &RabCurent );

            }

        }

    }

    printf("Total de lapin tué pendant l'année : %d\n",  totaltue );

}




/*-------------------------------------------------------------------------*/
/* deleteRabbit  :      Supression d'un lapin passé en paramettre de la    */
/*                      liste de tous les lapins puis decalage de la liste */
/*                      suivant des probabilitées données                  */
/*                                                                         */
/* En entrée :            indice : int de l'indice du lapin à supprimer    */
/*                        nbRabbaDecaler : int du nombre de lapin à decaler*/
/*                        listLapin : référence vers la liste de lapins    */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void deleteRabbit( int indice , int nbRabbaDecaler , lapin_t * listLapin ){


    int current = indice;

    for( int i = current ; i < nbRabbaDecaler ; i++ ){

        listLapin[i].age                = listLapin[i + 1].age;
        listLapin[i].adult              = listLapin[i + 1].adult;
        listLapin[i].isMale             = listLapin[i + 1].isMale;
        listLapin[i].nbLitterThisyear   = listLapin[i + 1].nbLitterThisyear;
        listLapin[i].used               = listLapin[i + 1].used;

    }


}



/*-------------------------------------------------------------------------*/
/* SimulEvoRabbit  :    Simulation de l'evolution du nombre de lapin durant*/
/*                      un nombre de mois données au vu des contraintes    */
/*                      imposées                                           */
/*                                                                         */
/* En entrée :            nbRabbitStart : int du nombre de lapin de départ */
/*                        listLapin : référence vers la liste de lapins    */
/*                        nbItera : int du nombre de mois de la simulation */
/*                                                                         */
/* En sortie :            Rien                                             */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SimulEvoRabbit( int nbRabbitStart , lapin_t * listLapin , int nbItera ){

    int             nbRabbitCurrent     = nbRabbitStart,
                    time                = 0,
                    nbRabbitNew,
                    nbInLitter,
                    nbCouple;

    double          probaDePondre;

    couple_t        tabCouple[TAILLE_MAX_TAB];

    

    InitListRabbit( nbRabbitStart , true , 5 , listLapin );

    //AfficheListLapin( nbRabbitStart , listLapin );

    for( int i = 0 ; i < nbItera ; i++ ){

        if( i % 12 == 0 ){

            if(i != 0){

                selectionNaturel( &nbRabbitCurrent , listLapin );

            }

            setLitters( nbRabbitCurrent , listLapin );

            printf("Nombre de lapin durant cette année: %d\n", nbRabbitCurrent);
            
        }

        nbRabbitNew = nbRabbitCurrent;

        nbCouple    = CreateCouple( nbRabbitCurrent , listLapin , tabCouple );

        //AfficheListCouple( nbCouple , tabCouple );


        for( int j = 0 ; j < nbCouple ; j++ ){

            probaDePondre = genrand_real2();

            if( probaDePondre < ( listLapin[ tabCouple[ j ].female ].nbLitterThisyear ) / ( 12.0 - ( i % 12) )){

                listLapin[ tabCouple[ j ].female ].nbLitterThisyear--;
                nbInLitter = proba_nb_child[ genrand_int32() % 4 ];
                //printf(" nb de bebe couple n° %d : %d \n", j + 1 , nbInLitter );

                for( int i = 0 ; i < nbInLitter ; i++ ){

                    AddRabbit( &nbRabbitNew , listLapin );

                }

            } 

        }

        nbRabbitCurrent = nbRabbitNew;
        time++;


        for( int i = 0 ; i < nbRabbitCurrent ; i++ ){

            listLapin[i].age ++;
            listLapin[i].used = false;


        }
        printf("Numéro du mois de l'année : %d \n", i % 12 );
        MAJMaturite( nbRabbitCurrent , listLapin );
        //AfficheListLapin( nbRabbitCurrent , listLapin );

    }

    AfficheListLapin( nbRabbitCurrent , listLapin );

    
}