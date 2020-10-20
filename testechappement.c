#include <stdio.h>
#include <stdlib.h>
#include "fct_cursor.h"
#include "fct_fichier.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {

    int ligne = 53;
    int colonne = 185;

	clear_screen();




    char * liste = "bvjqrsew ";
    char *** MatFichierFgColor = stock_file("objet/gare/fgcolor.txt", colonne, ligne, liste);
    char *** MatFichierBgColor = stock_file("objet/gare/bgcolor.txt", colonne, ligne, liste);
    char *** MatFichierCaractere = stock_file("objet/gare/gare.txt", colonne, ligne, liste);
    
    printf_gare(MatFichierCaractere, MatFichierFgColor, MatFichierBgColor, colonne, ligne);

    



    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train(train_haut_ouest, stock_file("objet/train/train.txt", 69, 5, liste), stock_file("objet/train/train_fgcolor.txt", 69, 5, liste), stock_file("objet/train/train_bgcolor.txt", 69, 5, liste), 'O', 'A');

    
    




    int compteur = 0;
    train_haut_ouest.vitesse = 10;
    train_haut_ouest.posx = 184;


    while (1) {

        
            compteur += train_haut_ouest.vitesse;


            if (compteur > 100000000) {

                train_haut_ouest.posx -= 1;
                printf_TRAIN(train_haut_ouest);
                compteur  = 0;

            }
        
            if(train_haut_ouest.posx < -train_haut_ouest.colonne) { //si le train sort entierement de l'écran par la gauche

                break;
            }         
        
    }





    train_haut_ouest.posx = 60;

    printf_TRAIN(train_haut_ouest);




    set_background_color(300);

    getchar();
    
    clear_screen();
	return 0;
}
