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


	/*translation_char_to_bgcolor('p'); //couleur ratp

	for(int j = 0; j < magare->ligne - 20; j ++) {

		for(int i = 0; i < magare->colonne; i++) {
			
			printf(" ");

		}
		printf("\n");
	}*/ // code plus utile 


	printf_decoration();

///ARRIVE EN GARE//////
	
	while(arrive_en_gare(montrain, magare) != 1) {

		usleep(8000);

	}
	

////CHOIX//////	



	char choix = 'a'; //a = pas de choix
	char touche;



	while(1) {

		touche = key_pressed();

	
	
		if(touche == 'q') {
	
				set_cursor(52,8);
			set_background_color(29);
			set_foreground_color(15);
			printf("\e[1mTrain seulement");
		
			set_cursor(118,8);
			set_background_color(16);
			set_foreground_color(29);
			printf("\e[1mMode complet");
			
			choix = 'q';

			set_cursor(60,15);
	
	
		} else if(touche == 'd') {
	
				set_cursor(118,8);
			set_background_color(29);
			set_foreground_color(15);
			printf("\e[1mMode complet");
		
			set_cursor(52,8);
			set_background_color(16);
			set_foreground_color(29);
			printf("\e[1mTrain seulement"); 

			choix = 'd';
			set_cursor(60,15);
	
	
		}  

		if(touche == 'e') {
			
			break;
		}

	}
	
	/////DEPART EN GARE//////
	/*while(depart_en_gare(montrain, magare) != 1) {

		usleep(8000);
	}*/


	montrain->posx = montrain->posxinit;
	montrain->compteur = 0;
	montrain->vitesse = montrain->vitesseinit;
	montrain->etat = 'g'; 
	return choix;


		//return choix; //cette ligne ne sera jamais executer

}

//Décors du menu. Des modifications peuvent être directement effectuées ici  
void printf_decoration() { 
	
	translation_char_to_bgcolor('q');
	translation_char_to_fgcolor('p');
	set_cursor(0, 0);
	printf("╔═════════════════════════════════════════════════════════════════════════════  Super simulateur de métro  ═════════════════════════════════════════════════════════════════════════════╗\n"); //185 caractères par ligne
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                 ╔               ╗                                                 ╔            ╗                                                      ║\n");
	move_cursor(-1,0);
	printf("║                                                  Train seulement                                                   Mode complet                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                 ╚               ╝                                                 ╚            ╝                                                      ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                         Press 'd' or 'q' to select the mode you want for the simulator then press 'e' to confirm your choice!                                         ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                          Made by Rullier Antoine and Engel Adrien     ║\n");
	move_cursor(-1,0);
	printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}















