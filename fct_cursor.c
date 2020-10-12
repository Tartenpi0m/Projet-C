#include <stdio.h>
#include <stdlib.h>
#include "fct_cursor.h"


//efface l'écran et poistionne le curseur à 0,0
void clear_screen() {

	printf("\033[2J");
	 printf("\033[0;0H");
}

//positionne le curesur à la positio x,y
void set_cursor(int x, int y) {

	printf("\033[%d;%dH", y, x);
}


//déplace le curseur du nombre de y ligne et de x colonne
void move_cursor(int x, int y) {
	if (y > 0) {

		printf("\033[%dA", y);

	} else {

		printf("\033[%dB", -y);

	}


	if (x > 0) {

		printf("\033[%dC", x);

	} else {

		printf("\033[%dD", -x);

	}

}


//modifie le couleur de l'arrière plan (choisir x > 256 pour la couleur par défaut du terminale)
void set_background_color(int x) {
	if (x > 256) {
	
		printf("\033[49m");
	
	} else {

	printf("\033[48;5;%dm", x);
	
	}
}


//modifie le couleur du premier plan (choisir x > 256 pour la couleur par défaut du terminale)
void set_foreground_color(int x) {
	if (x > 255) {
	
		printf("\033[39m");
	
	} else {

	printf("\033[38;5;%dm", x);
	
	}
}