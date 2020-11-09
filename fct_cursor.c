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
				case 'q' : fg = 232; break; //NOIR
				case 's' : fg = 233; break; 
				case 'd' : fg = 234; break;
				case 'f' : fg = 235; break;
				case 'g' : fg = 236; break; //GRIS FONCE
				case 'h' : fg = 237; break; 
				case 'j' : fg = 238; break;
				case 'k' : fg = 239; break;
				case 'l' : fg = 240; break; 
				case 'm' : fg = 241; break; 
				case 'x' : fg = 242; break;
				case 'c' : fg = 243; break; 
				case 'v' : fg = 244; break;
				case 'b' : fg = 245; break;//GRIS MOYEN
				case 'n' : fg = 246; break;
				case '0' : fg = 247; break;
				case '1' : fg = 248; break;
				case '2' : fg = 249; break;
				case '3' : fg = 250; break;
				case '4' : fg = 251; break;
				case '5' : fg = 252; break;
				case '6' : fg = 253; break;
				case '7' : fg = 254; break;
				case '8' : fg = 255; break;
				case '9' : fg = 256; break;//TRES CLAIR

				case 'w': fg = 256; break;

				case 'p': fg = 29; break; //metro vert clair

				case 'r': fg = 88; break; //phare rouge arrière
				case 't' : fg = 52; break; // +foncé

				default : fg = 15; break;  
		}

		set_foreground_color(fg);

}

void translation_char_to_bgcolor(char i) {
	int bg;

	switch(i) {
				case 'q' : bg = 232; break; //NOIR
				case 's' : bg = 233; break; 
				case 'd' : bg = 234; break;
				case 'f' : bg = 235; break;
				case 'g' : bg = 236; break; //GRIS FONCE
				case 'h' : bg = 237; break; 
				case 'j' : bg = 238; break;
				case 'k' : bg = 239; break;
				case 'l' : bg = 240; break; 
				case 'm' : bg = 241; break; 
				case 'x' : bg = 242; break;
				case 'c' : bg = 243; break; 
				case 'v' : bg = 244; break;
				case 'b' : bg = 245; break;//GRIS MOYEN
				case 'n' : bg = 246; break;
				case '0' : bg = 247; break;
				case '1' : bg = 248; break;
				case '2' : bg = 249; break;
				case '3' : bg = 250; break;
				case '4' : bg = 251; break;
				case '5' : bg = 252; break;
				case '6' : bg = 253; break;
				case '7' : bg = 254; break;
				case '8' : bg = 255; break;
				case '9' : bg = 256; break;//TRES CLAIR

				case 'w': bg = 256; break;

				case 'p': bg = 29; break; //metro vert clair

				case 'r': bg = 88; break; //phare rouge arrière
				case 't' : bg = 52; break; // +foncé

				default : bg = 232;
		}

		set_background_color(bg);


}

