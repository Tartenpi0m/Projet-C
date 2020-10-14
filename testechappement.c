#include <stdio.h>
#include <stdlib.h>
#include "fct_cursor.h"
#include "fct_fichier.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {

    

	clear_screen();

    
    char * TabFichierFgColor = stock_file("objet/gare/fgcolor.txt", 9300);
    char * TabFichierBgColor = stock_file("objet/gare/bgcolor.txt", 9300);
    char * TabFichierCaractere = stock_file("objet/gare/gare.txt", 9300);
    set_cursor(0,0);
    printf_file(TabFichierCaractere, TabFichierFgColor, TabFichierBgColor, 9299, 0, 0);

    set_cursor(13,11);



    TRAIN train_haut_ouest;
    train_haut_ouest =  init_train(train_haut_ouest, 'O', 'A');



    train_haut_ouest.tab_train = stock_file("objet/train.txt", train_haut_ouest.taille_tab_train);
    printf_file(train_haut_ouest.tab_train, TabFichierFgColor, TabFichierBgColor, train_haut_ouest.taille_tab_train, train_haut_ouest.taille_ligne_train,13);







    set_background_color(300);

    getchar();
  
    clear_screen();
	return 0;
}
