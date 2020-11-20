#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


#include "fct_menu.h"
#include "fct_cursor.h"
#include "fct_fichier.h"


char key_pressed() {
   	
	struct termios oldterm, newterm;
    int oldfd; 
   	char c, result = 'm';
   	
   	tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);

 	c = getchar();

 	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
  	


 	if (c != EOF) {
   	ungetc(c, stdin); result = getchar();
   	}
   	return result;
}



char menu(TRAIN montrain, GARE magare) {

//GRAS \e[1m
//normal \e[0m

////AFFICHAGE MENU///////
	printf_gare(magare);
    set_cursor(0,0);


	translation_char_to_bgcolor('p'); //couleur ratp

	for(int j = 0; j < magare->ligne - 20; j ++) {

		for(int i = 0; i < magare->colonne; i++) {
			
			printf(" ");

		}
		printf("\n");
	}


	set_cursor(30,3);
	//GRASSOULIGNE
	set_background_color(9);
	set_foreground_color(120);
	printf("\e[1mSUPER SIMULATEUR DE METRO");

	set_cursor(10,8);
	set_background_color(255);
	set_foreground_color(8);
	printf("TRAIN SEULEMENT");

	set_cursor(50,8);
	set_background_color(8);
	set_foreground_color(255);
	printf("\e[0mMODE COMPLET");



///ARRIVE EN GARE//////
	
	while(arrive_en_gare(montrain, magare) != 1) {

		sleep(0.9999);

	}
	


////CHOIX//////	



	int fait = 0;
	char choix = 'a';//a = pas de choix
	char touche;



	while(fait == 0) {

		touche = key_pressed();

	
	
		if(touche == 'q') {
	
				set_cursor(10,8);
			set_background_color(255);
			set_foreground_color(8);
			printf("\e[1mTRAIN SEULEMENT");
		
			set_cursor(50,8);
			set_background_color(8);
			set_foreground_color(255);
			printf("\e[0mMODE COMPLET");
			
			choix = 'q';

			set_cursor(60,15);
	
	
		} else if(touche == 'd') {
	
				set_cursor(50,8);
			set_background_color(255);
			set_foreground_color(8);
			printf("\e[1mMODE COMPLET");
		
			set_cursor(10,8);
			set_background_color(255);
			set_foreground_color(8);
			printf("\e[0mTRAIN SEULEMENT");

			choix = 'd';
			set_cursor(60,15);
	
	
		} 

		if(touche == 'e') {
			
			/////DEPART EN GARE//////
			while(1) {

				if(depart_en_gare(montrain, magare) != 1) {
					break;
				}
			}


			return choix;
		}


	}
		return choix; //cette ligne ne sera jamais executer

}