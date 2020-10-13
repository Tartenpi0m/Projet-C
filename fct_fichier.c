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

	return tableaux;

}

void printf_file(char * tab_caractere, char * tab_fgcolor, char * tab_bgcolor, int taille, int xposition) {
	
	

	for (int i = 0; i < taille; i++) {

		translation_char_to_fgcolor(tab_fgcolor[i]);
		translation_char_to_bgcolor(tab_bgcolor[i]);

		
		if (tab_caractere[i] == 'e') {
			printf(" ");
		} 
		else {
			printf("%c", tab_caractere[i] );
			if (tab_caractere[i] == '\n') {
				
				move_cursor(xposition,0);
			} 

		}

		

	} 

}


//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char direction, char voie ) {
	montrain.direction = direction;
	montrain.voie = voie;
	montrain.taille_tab_train =  346;
	montrain.porte = 'c';
	//montrain.etat = "dehors";
	return montrain;

	switch(voie) {

		case 'A' : montrain.posy = 11; break;
		case 'B' : montrain.posy = 16; break;
		case 'C' : montrain.posy = 31; break;
		case 'D' : montrain.posy = 36; break;

	}

}




