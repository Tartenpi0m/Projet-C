#include <stdio.h>
#include <stdlib.h>
#include "fct_cursor.h"
#include "fct_fichier.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {

    int ligne = 45;
    int colonne = 185;

	clear_screen();

    char * liste = "bvjqrse ";
    char *** MatFichierFgColor = stock_file("objet/gare/fgcolor.txt", colonne, ligne, liste);
    char *** MatFichierBgColor = stock_file("objet/gare/bgcolor.txt", colonne, ligne, liste);
   char *** MatFichierCaractere = stock_file("objet/gare/gare.txt", colonne, ligne, liste);
    
    printf_gare(MatFichierCaractere, MatFichierFgColor, MatFichierBgColor, colonne, ligne);

    /*set_cursor(135,11);



    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train(train_haut_ouest, 'O', 'A');



    train_haut_ouest.tab_train = stock_file("objet/train.txt", train_haut_ouest.taille_tab_train);
    printf_file(train_haut_ouest.tab_train, TabFichierFgColor, TabFichierBgColor, train_haut_ouest.taille_tab_train, train_haut_ouest.taille_ligne_train,135);
*/






    set_background_color(300);

    getchar();
    
    clear_screen();
	return 0;
}
