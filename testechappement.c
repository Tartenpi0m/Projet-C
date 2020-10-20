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

    set_cursor(135,11);



    TRAIN train_haut_ouest;


    train_haut_ouest =  init_train(train_haut_ouest, stock_file("objet/train/train.txt", 66, 5, liste), stock_file("objet/train/train_fgcolor.txt", 66, 5, liste), 'O', 'A');

    printf_TRAIN(train_haut_ouest, MatFichierBgColor, 40);







    set_background_color(300);

    getchar();
    
    clear_screen();
	return 0;
}
