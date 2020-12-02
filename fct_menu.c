#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


#include "fct_menu.h"
#include "fct_cursor.h"
#include "fct_fichier.h"
#include "fct_voyageur.h"


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


//affiche les voyageurs dans le menu
void affichage_voyageur(int a, QUAI monquai) {

	if(a == 1) {

		set_cursor(monquai->posx + 10, monquai->posy +  3);
		set_foreground_color(29);
		printf("█");
		set_cursor(monquai->posx + 22, monquai->posy + 3);
		set_foreground_color(29);
		printf("█");
		set_cursor(monquai->posx + 45, monquai->posy + 3);
		set_foreground_color(29);
		printf("█");
		set_cursor(monquai->posx + 65, monquai->posy + 3);
		set_foreground_color(29);
		printf("█");

	} else {

		set_cursor(monquai->posx + 10, monquai->posy + 3);
		translation_char_to_bgcolor(monquai->mat_bgcolor[10][4]);
		printf(" ");
		set_cursor(monquai->posx + 22, monquai->posy + 3);
		translation_char_to_bgcolor(monquai->mat_bgcolor[22][4]);
		printf(" ");
		set_cursor(monquai->posx + 45, monquai->posy + 3);
		translation_char_to_bgcolor(monquai->mat_bgcolor[45][4]);
		printf(" ");
		set_cursor(monquai->posx + 65, monquai->posy + 3);
		translation_char_to_bgcolor(monquai->mat_bgcolor[65][4]);
		printf(" ");





	}
}

//fonction de selection du mode, d'animation et d'affichage du menu
int menu(TRAIN montrain, GARE magare, QUAI monquai, LISTE * maliste) {

//GRAS \e[1m
//normal \e[0m

////AFFICHAGE MENU///////
	printf_gare(magare);
    set_cursor(0,0);

	printf_decoration2();
	

	int vitesse_train = 100; //300

	montrain->posx = 45;
	printf_TRAIN(montrain, magare);



///ARRIVE EN GARE//////
	/*
	while(arrive_en_gare(montrain, magare, vitesse_train) != 1) {

		usleep(8000);

	}*/
	
//15 blanc, 16 noir , 29 vert
////CHOIX//////	


	char touche;

	int cursor = 0;

	set_cursor(25, 20);
	set_foreground_color(29);
	set_background_color(16);
	fflush(stdout);
	printf("Attention : Une fois le simulateur lancé,\033[38;5;9m appuyez sur P\033[38;5;29m  pour quitter !");
	set_cursor(25, 23);
	printf("Fonctionnalitées : 1- Vous pouver changez la couleur des voyageurs entrant est sortant en appuyant sur i (entrant) et o (sortant)");
	set_cursor(25, 24);
	printf("                      pendant que ceci apparaissent à l'écran.");
	set_cursor(25, 26);
	printf("                   2- Vous pourrez dirigez un voyageur avec les \033[38;5;9mtouches zqsd et espace\033[38;5;29m pour l'arrêter.");
	set_cursor(25, 27);
	printf("                      Le voyageur-joueur apparaitra en violet, il sortira du premier train sur le quai A, vous pourrez reprendre le train avec. ");
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
			
			printf_TRAIN(montrain, magare);
			affichage_voyageur(0,monquai);
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

			printf_porte(montrain, magare);
			affichage_voyageur(1,monquai);
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

			printf_porte(montrain, magare);
			affichage_voyageur(1,monquai);
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

			printf_porte(montrain, magare);
			affichage_voyageur(1,monquai);
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

	if(cursor != 0) {

		char * p = NULL;
		char nop = 'k';
		p = &nop;

		maliste->etat = 'w';
		maliste->couleur = 0;

		add_liste(maliste, monquai, 10, 3, 17, 6, 'm');
		add_liste(maliste, monquai, 22, 3, 26, 6, 'm');
		add_liste(maliste, monquai, 45, 3, 46, 7, 'm');
		add_liste(maliste, monquai, 65, 3, 58, 6, 'm');

		affichage_voyageur(0, monquai);



		while (1) { //LA GRANDE BOUCLE

	        fflush(stdout);

			deplacement_voyageur(maliste, monquai, 10, p);

			if(maliste->etat == 'm') {
				break;
			}

			usleep(30000);
	  
	      }       

	    maliste->etat = 'w';
	    sleep(1);
	    printf_TRAIN(montrain, magare);

	}
	maliste->couleur = 1;
    sleep(1);




	
	/////DEPART EN GARE//////

	montrain->vitesse = 30;

	while(depart_en_gare(montrain, magare, vitesse_train) != 1) {

		fflush(stdout);
		usleep(8000);
	}



	//réinitialisation du train pour la simulation
	montrain->posx = montrain->posxinit;
	montrain->compteur = 0;
	montrain->vitesse = montrain->vitesseinit;
	montrain->etat = 'g'; 
	return cursor;


		//return choix; //cette ligne ne sera jamais executer

}

//affiche le cadre du menu
void printf_decoration2() {
	//translation_char_to_bgcolor('q');
	set_background_color(16);
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

//affiche la fleche gauche du menu, en couleur
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

//affiche le fleche droite du menu, en couleur
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

//active le mode d'affichage gras
void set_gras(int i) {
	if (i == 1) {
		printf("\e[1m");
	} else {
		printf("\e[0m");
	}
}



//affiche l'écran de fermeture du simulateur et ferme le simulateur
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







