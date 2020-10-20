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

	} else if (y < 0) {

		printf("\033[%dB", -y);

	}


	if (x > 0) {

		printf("\033[%dC", x);

	} else if (x < 0) {

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


void translation_char_to_fgcolor(char i) {
	int fg;

	switch(i) {
				case 'b' : fg = 4; break;
				case 'v' : fg = 2; break;
				case 'j': fg = 3; break;
				case 'w' : fg = 15; break;
				default : fg = 15; break;
		}

		set_foreground_color(fg);

}

void translation_char_to_bgcolor(char i) {
	int bg;

	switch(i) {
				case 'q' : bg = 242; break;
				case 's' : bg = 236; break;
				case 'e' : bg = 232; break;
				case 'b' : bg = 249; break;
				case 'l' : bg = 251; break;
				case 'j': bg = 244; break;
				case 'r': bg = 88; break; //phare rouge arrière
				default : bg = 232;
		}

		set_background_color(bg);


}

