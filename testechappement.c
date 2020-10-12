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
    printf_file(TabFichierCaractere, TabFichierFgColor, TabFichierBgColor, 9299, 0);

   set_cursor(30,11);
    char * TabTrain = stock_file("objet/train.txt", 351);
    printf_file(TabTrain, TabFichierFgColor, TabFichierBgColor, 350, 70);




    set_background_color(300);

    getchar();
  
    clear_screen();
	return 0;
}
