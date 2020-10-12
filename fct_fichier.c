#include <stdio.h>
#include <stdlib.h>
#include "fct_fichier.h"
#include "fct_cursor.h"



//alloue un tableau contenant le contenu du fichier filename
char* stock_file(char *filename, int taille) {

	char* tableaux = malloc(taille*sizeof(char));

	FILE *fichier;
	fichier = fopen(filename,"r");

	int compteur = 0;

	do {
		
		tableaux[compteur] = fgetc(fichier);
		compteur += 1;

	} while(tableaux[compteur-1] != EOF);

	//realloc(tableaux, compteur*sizeof(char));

	return tableaux;

}

void printf_file(char * tab_caractere, char * tab_fgcolor, char * tab_bgcolor, int taille, int decalage) {
	int fg, bg;
	

	for (int i = 0; i < taille; i++) {


		switch(tab_fgcolor[i]) {
				case 'b' : fg = 4; break;
				case 'v' : fg = 2; break;
				case 'j': fg = 3; break;
				default : fg = 15; break;
		}

		switch(tab_bgcolor[i]) {
				case 'q' : bg = 242; break;
				case 'r' : bg = 232; break;
				case 's' : bg = 232; break;
				case 'e' : bg = 232; break;
				case 'b' : bg = 249; break;
				default : bg = 232;
		}

		set_foreground_color(fg);
		set_background_color(bg);
		
		if (tab_caractere[i] == 'e') {
			printf(" ");
		} 
		else {
			printf("%c", tab_caractere[i] );

			if ( tab_caractere[i] == '\n' && decalage !=0 ) {
				//move_cursor(-decalage,0);

			}
		}




	} 


}
