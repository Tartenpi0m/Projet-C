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



int menu(TRAIN montrain, GARE magare) {

//GRAS \e[1m
//normal \e[0m

////AFFICHAGE MENU///////
	printf_gare(magare);
    set_cursor(0,0);

	printf_decoration2();

	int vitesse_train = 100; //300

///ARRIVE EN GARE//////
	
	while(arrive_en_gare(montrain, magare, vitesse_train) != 1) {

		usleep(8000);

	}
	
//15 blanc, 16 noir , 29 vert
////CHOIX//////	


	char touche;

	int cursor = 0;

	while(1) {

		touche = key_pressed();

		if(touche == 'q' && cursor > 0) {
			cursor -= 1;
			printf_fleche_gauche(15,16);
			usleep(100000);
			printf_fleche_gauche(29,16);
		} else if(touche == 'd' && cursor < 3) {
			cursor += 1;
			printf_fleche_droite(15,16);
			usleep(100000);
			printf_fleche_droite(29,16);
		}

	

		if(cursor == 0) {
			
			set_gras(1);
			set_cursor(84,8);
			set_foreground_color(29);
			set_background_color(16);
			printf("MODE TRAIN SEULEMENT ");
			set_gras(0);
			set_cursor(25, 16);
			set_foreground_color(29);
			set_background_color(16);
			printf("Description : Dans ce mode, seulement les trains circuleront (pas les voyageurs). Le temps est accéléré, une minute dure 10 secondes.       ");
	
		} else if(cursor == 1) {

			set_gras(1);
			set_cursor(84,8);
			set_foreground_color(29);
			set_background_color(16);
			printf("MODE COMPLET RAPIDE  ");
			set_gras(0);
			set_cursor(25, 16);
			set_foreground_color(29);
			set_background_color(16);
			printf("Description : Dans ce mode, les trains et les voyageurs circuleront. Le temps est accéléré, une minute dure 10 secondes.                    ");
	
		}  else if(cursor == 2) {

			set_gras(1);
			set_cursor(84,8);
			set_foreground_color(29);
			set_background_color(16);
			printf("MODE COMPLET AJUSTÉ  ");
			set_gras(0);
			set_cursor(25, 16);
			set_foreground_color(29);
			set_background_color(16);
			printf("Description : Dans ce mode, les trains et les voyageurs circuleront. Les minutes dures durent 10 secondes, mais le temps n'est pas accéléré.");

	
		}  else if(cursor == 3) {

			set_gras(1);
			set_cursor(84,8);
			set_foreground_color(29);
			set_background_color(16);
			printf("MODE COMPLET RÉALISTE");
			set_gras(0);
			set_cursor(25, 16);
			set_foreground_color(29);
			set_background_color(16);
			printf("Description : Dans ce mode, les trains et les voyageurs circuleront. Le temps s'écoule normalement. Déconseillé aux impatients !            ");

		}
		

		if(touche == 'e') {
			
			break;
		}

	}
	
	/////DEPART EN GARE//////
	/*while(depart_en_gare(montrain, magare, vitesse_train) != 1) {

		usleep(8000);
	}*/

	//réinitialisation du train pour la simulation
	montrain->posx = montrain->posxinit;
	montrain->compteur = 0;
	montrain->vitesse = montrain->vitesseinit;
	montrain->etat = 'g'; 
	return cursor;


		//return choix; //cette ligne ne sera jamais executer

}

void printf_decoration2() {
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
	printf("║                                                                             ▄█ ╔                       ╗ █▄                                                                           ║\n");
	move_cursor(-1,0);
	printf("║                                                                            ███                           ███                                                                          ║\n");
	move_cursor(-1,0);
	printf("║                                                                             ▀█ ╚                       ╝ █▀                                                                           ║\n");
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
	printf("║                                                          Press 'd' or 'q' to select the mode, then press 'e' to confirm your choice!                                                  ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                                                                       ║\n");
	move_cursor(-1,0);
	printf("║                                                                                                                                          Made by Rullier Antoine and Engel Adrien     ║\n");
	move_cursor(-1,0);
	printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}


void printf_fleche_gauche(int fg, int bg) {
	set_foreground_color(fg);
	set_background_color(bg);

	set_cursor(78, 7);
	printf(" ▄█\n");
	set_cursor(78, 8);
	printf("███\n");
	set_cursor(78, 9);
	printf(" ▀█\n");

}

void printf_fleche_droite(int fg, int bg) {
	set_foreground_color(fg);
	set_background_color(bg);

	set_cursor(108, 7);
	printf("█▄ \n");
	set_cursor(108, 8);
	printf("███\n");
	set_cursor(108, 9);
	printf("█▀ \n");

}


void set_gras(int i) {
	if (i == 1) {
		printf("\e[1m");
	} else {
		printf("\e[0m");
	}
}





void bye(GARE magare) {

	set_cursor(0,6);
	translation_char_to_bgcolor('9');
	set_background_color(16);
	for(int j = 0; j < magare->ligne-10; j++) {
		for(int i = 0; i <magare->colonne; i++) {
				
				printf(" ");

		}
		printf("\n");
	}


	set_foreground_color(29);
	set_background_color(16);
	


	set_cursor(65,15);
	printf(" _____ _____ ____  __  __ _____ _____ _   _ ____  _____ "); set_cursor(65,16);
	printf("|  ___| ____|  _ \\|  \\/  | ____|_   _| | | |  _ \\| ____|"); set_cursor(65,17);
	printf("| |_  |  _| | |_) | |\\/| |  _|   | | | | | | |_) |  _|  "); set_cursor(65, 18);
	printf("|_|   |_____|_| \\_\\_|  |_|_____| |_|  \\___/|_| \\_\\_____|"); set_cursor(65,19);

	fflush(stdout);

	sleep(2);
	system("stty echo");
	printf("\033[?25h"); 
	printf("\e[49m"); //couleur d'arrière plan par défault
	set_cursor(0,0);
    clear_screen();
    set_cursor(0,0);
    exit(0);

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