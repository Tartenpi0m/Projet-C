#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fct_time.h"
#include "fct_cursor.h"
#include "fct_fichier.h"

time_t init_time() {

	return time(NULL); 

}


int get_time_s(time_t time_init) {

	return (int) time(NULL) - time_init;

}

int get_time_min(time_t time_init) {

	return     (int) ( (  (int) time(NULL) - time_init  ) / 60 );
}


void printf_chiffre(char* filename, int x) {

	int ligne = 5;
	int colonne;

	switch(filename[14]) {

		case '1' : colonne = 3; break;
		case '4' : colonne = 8; break;
		case 'p' : colonne = 3; break; //pour ' : '	
		default : colonne = 7; break;
	}
	
	FILE *fichier;
	fichier = fopen(filename,"r");

	fgetc(fichier); //pour commencer à detecter tt de suite les charactère (espace inclus)
	printf(" "); //remplace le  premier chracatere

	for(int j = 0; j < ligne; j++) {   //boucle de sautement de ligne

		for(int i = 0; i < colonne +1 ; i++) {   //boucle des termes dans une ligne

			printf("%c", fgetc(fichier));
		}

		move_cursor(x,0);
	}

}


void printf_time(time_t time_init, int x, int y) {

	//set_cursor(x,y);
	translation_char_to_bgcolor('w');
	translation_char_to_fgcolor('w');

	int time = get_time_min(time_init);

	char* filename = "objet/chiffre/x.txt";
	printf("%c\n", filename[14]);
	printf("%d\n\n", time);

	switch(time) {
		case 0: filename[14] = '0'; break;
		case 1: filename[14] = '1'; break;
		case 2: filename[14] = '2'; break;
		case 3: filename[14] = '3'; break;
		case 4: filename[14] = '4'; break;
		case 5: filename[14] = '5'; break;
		case 6: filename[14] = '6'; break;
		case 7: filename[14] = '7'; break;
		case 8: filename[14] = '8'; break;
		case 9: filename[14] = '9'; break;
		default : filename[14] = '0'; break;  //pour l'instant cette fonction ne peut pas afficher un temps > 9 min
	}

	printf_chiffre(filename, x);

	printf("ALL GOooooooooooOD\n");

}