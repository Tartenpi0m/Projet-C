#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "fct_cursor.h"
#include "fct_fichier.h"
#include "fct_time.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {


    int lignetrain = 71; //longueur train

	clear_screen();

    //INITIALISATION ALEATOIRE
    init_alea();
    srand(time(NULL));


    //CHARGER ET AFFICHER LA GARE
    char * liste = "azertyuiopqsdfghjklmwxcvbn0123456789 ";
   
    GARE gare1;
    gare1 = init_gare(gare1, "objet/gare/gare.txt", "objet/gare/fgcolor.txt", "objet/gare/bgcolor.txt", liste); 
    printf_gare(gare1);

    
    //INITIALISER UN TRAIN

    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train("objet/train/train.txt", "objet/train/train_fgcolor.txt", "objet/train/train_bgcolor.txt", 'O', 'A', liste);
    int compteur = 0;



    //INITIALISATION DU TEMPS 

            //temps ecoulé de puis le début
    time_t THE_time_init = init_time();   
    int THE_minute_time = 0; //doit augmenter de 1 toute les minutes
    printf_time(THE_minute_time, 1, 10);


           //temps restant train_haut_ouest
    printf_time(train_haut_ouest->temps_1, 20, 10);
    printf_time(train_haut_ouest->temps_2, 30, 10);



    train_haut_ouest->posx = 185;
    


/////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE/////
    while (1) {


        //DEPLACER LE TRAIN

        if ( train_haut_ouest->etat == 'i') { // et que minute1 = 0
            
            if (arrive_en_gare(train_haut_ouest, gare1) == 1) {
                train_haut_ouest->etat = 'l';//REMPLACER PAR WAITING
            }
        }


        if( train_haut_ouest->etat == 'l') {

            depart_en_gare(train_haut_ouest, gare1);

            //if (depart_en_gare(train_haut_ouest, gare1) == 1) {

                //changer le temps des minutes
            //}
        }


       
  


        ///AFFICHER LE TEMPS//////AFFICHER LE TEMPS//////AFFICHER LE TEMPS///

            //TRAIN_haut_ouest
                //temps1
        if (get_time_min(train_haut_ouest->temps_1_init)  > train_haut_ouest->temps_1_actuel) {
            train_haut_ouest->temps_1_actuel += 1;
            train_haut_ouest->temps_1 -= 1 ;
            printf_time(train_haut_ouest->temps_1, 20, 10);

        }
                //temps2
        if (get_time_min(train_haut_ouest->temps_2_init)  > train_haut_ouest->temps_2_actuel) {
            train_haut_ouest->temps_2_actuel += 1;
            train_haut_ouest->temps_2 -= 1 ;
            printf_time(train_haut_ouest->temps_2, 30, 10);

        }





        //GENERER LE TEMPS D'ATTENTE DU PROCHAIN TRAIN (SI BESOIN)
       train_haut_ouest = pass_and_init_time(train_haut_ouest);


       //afficher temps ecouler depuis le début
        if(  get_time_min(THE_time_init)    >    THE_minute_time) {

            THE_minute_time +=1;
            printf_time(THE_minute_time, 1, 10);

        }
            
        
    }
    





/////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN//////

    set_background_color(300);

    getchar();
    
    clear_screen();
	return 0;
    
}
