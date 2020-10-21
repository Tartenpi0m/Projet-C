#include <stdio.h>
#include <stdlib.h>
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

    int lignetrain = 71;

	clear_screen();




    char * liste = "azertyuiopqsdfghjklmwxcvbn ";
    char *** MatFichierFgColor = stock_file("objet/gare/fgcolor.txt", colonne, ligne, liste);
    char *** MatFichierBgColor = stock_file("objet/gare/bgcolor.txt", colonne, ligne, liste);
    char *** MatFichierCaractere = stock_file("objet/gare/gare.txt", colonne, ligne, liste);
    
    printf_gare(MatFichierCaractere, MatFichierFgColor, MatFichierBgColor, colonne, ligne);

    

    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train(train_haut_ouest, stock_file("objet/train/train.txt", lignetrain, 5, liste), stock_file("objet/train/train_fgcolor.txt", lignetrain, 5, liste), stock_file("objet/train/train_bgcolor.txt", lignetrain, 5, liste), 'O', 'A');

    
    
    int compteur = 0;
    train_haut_ouest.vitesse = 10;
    train_haut_ouest.posx = 184;


    time_t THE_time_init = init_time();   
    int THE_minute_time = 0; //doit augmenter de 1 toute les minutes
    set_cursor(20,10);
    printf_chiffre("objet/chiffre/1.txt", 20);
    getchar();
    set_cursor(20,10);
    printf_chiffre("objet/chiffre/0.txt", 20);

    //printf_time(THE_time_init, 20, 10);
    
    while (1) {

        
            compteur += train_haut_ouest.vitesse;


            if (compteur > 100000000) {

                train_haut_ouest.posx -= 1;
                printf_TRAIN(train_haut_ouest);
                //printf("%d", train_haut_ouest.posx);
                compteur  = 0;

            }

            if(  get_time_min(THE_time_init)    >    THE_minute_time) {

                THE_minute_time +=1;
                //printf_time(THE_time_init, 20, 10);

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
