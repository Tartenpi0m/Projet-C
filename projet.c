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

    int ligne = 53;
    int colonne = 185;
    int lignetrain = 71; //longueur train

	clear_screen();

    //INITIALISATION ALEATOIRE
    init_alea();
    srand(time(NULL));


    //CHARGER ET AFFICHER LA GARE
    char * liste = "azertyuiopqsdfghjklmwxcvbn ";
    char *** MatFichierFgColor = stock_file("objet/gare/fgcolor.txt", colonne, ligne, liste);
    char *** MatFichierBgColor = stock_file("objet/gare/bgcolor.txt", colonne, ligne, liste);
    char *** MatFichierCaractere = stock_file("objet/gare/gare.txt", colonne, ligne, liste);
    
    printf_gare(MatFichierCaractere, MatFichierFgColor, MatFichierBgColor, colonne, ligne);

    
    //INITIALISER UN TRAIN
    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train(train_haut_ouest, stock_file("objet/train/train.txt", lignetrain, 5, liste), stock_file("objet/train/train_fgcolor.txt", lignetrain, 5, liste), stock_file("objet/train/train_bgcolor.txt", lignetrain, 5, liste), 'O', 'A');
    int compteur = 0;



    //INITIALISATION DU TEMPS 

            //temps ecoulé de puis le début
    time_t THE_time_init = init_time();   
    int THE_minute_time = 0; //doit augmenter de 1 toute les minutes
    printf_time(THE_minute_time, 1, 10);


           //temps restant train_haut_ouest
    printf_time(train_haut_ouest.temps_1, 20, 10);
    printf_time(train_haut_ouest.temps_2, 30, 10);





    


    //GRANDE BOUCLE
    while (1) {


        //DEPLACER LE TRAIN
        compteur += train_haut_ouest.vitesse;


        if (compteur > 100000000) {

            train_haut_ouest.posx -= 1;
            printf_TRAIN(train_haut_ouest);
            //printf("%d", train_haut_ouest.posx);
            compteur  = 0;

        }


        //AFFICHER LE TEMPS

            //TRAIN_haut_ouest
                //temps1
        if (get_time_min(train_haut_ouest.temps_1_init)  > train_haut_ouest.temps_1_actuel) {
            train_haut_ouest.temps_1_actuel += 1;
            train_haut_ouest.temps_1 -= 1 ;
            printf_time(train_haut_ouest.temps_1, 20, 10);

        }
                //temps2
        if (get_time_min(train_haut_ouest.temps_2_init)  > train_haut_ouest.temps_2_actuel) {
            train_haut_ouest.temps_2_actuel += 1;
            train_haut_ouest.temps_2 -= 1 ;
            printf_time(train_haut_ouest.temps_2, 30, 10);

        }





        //GENERER LE TEMPS D'ATTENTE DU PROCHAIN TRAIN (SI BESOIN)
       train_haut_ouest = pass_and_init_time(train_haut_ouest);


       //afficher temps ecouler depuis le début
        if(  get_time_min(THE_time_init)    >    THE_minute_time) {

            THE_minute_time +=1;
            printf_time(THE_minute_time, 1, 10);

        }
            
        
    }

































/////DEPLACEMENT DU TRAIN

//TEST SANS FONCTION (FONCTIONELLE)
/*
    while (1) {

        
            compteur += train_haut_ouest.vitesse;


            if (compteur > 100000000) {

                train_haut_ouest.posx -= 1;
                printf_TRAIN(train_haut_ouest);
                //printf("%d", train_haut_ouest.posx);
                compteur  = 0;

            }
            
        
    }*/

//TESTE AVEC FONCTION (NE FONCTIONNE PAS)
    /*while (1) {

        compteur += train_haut_ouest.vitesse;
    
        if (deplacement_train2(train_haut_ouest, compteur)  ==   0) {
            printf("%d", train_haut_ouest.posx);
            compteur = 0;

        }

    }*/










   // train_haut_ouest.posx = 60;

   // printf_TRAIN(train_haut_ouest);




    set_background_color(300);

    getchar();
    
    clear_screen();
	return 0;
    
}
