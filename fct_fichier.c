#include <stdio.h>
#include <stdlib.h>
#include "fct_fichier.h"
#include "fct_cursor.h"


char *** matrice_init(int colonne, int ligne) {


	char *** matrice = malloc(colonne*sizeof(char**)); 

	for (int i = 0; i < colonne; i++) {

		matrice[i] = malloc(ligne*sizeof(char*));
		
		for (int j = 0; j < ligne; j++) {

			matrice[i][j] = malloc(3*sizeof(char));
		}
				


	}

	return matrice;

}







//alloue une matrice contenant le contenu du fichier filename (prend en charge l'ASCII)

char*** stock_file(char *filename, int colonne, int ligne, char* liste) {

	


	char *** matrice = matrice_init(colonne, ligne);

	FILE *fichier;
	fichier = fopen(filename,"r");

	for(int j = 0; j < ligne; j++) { //boucle de sautement de ligne

		for(int i = 0; i < colonne; i++) {//boucle des termes dans une ligne

			matrice[i][j][0] = fgetc(fichier); //le char. du fichier va dans la matrice

			

			

			

			int boolean = 0, k = 0; 

			while (liste[k] != '\0') {   //while parcours la liste liste[k]  //test si le char. est connu (sinon ASCII etendue)


				if (matrice[i][j][0] == liste[k] ) { //si le char. courant appartient au char. repèrtorier dans liste

					boolean = 1;            
					break;
				}
				k += 1;
			}



			if (boolean == 0) {         //dans le cas de l'ASCII etendue, on stock l'intégralité du char. en 3 fois (1+2)

				matrice[i][j][1] = fgetc(fichier);
				matrice[i][j][2] = fgetc(fichier);
				

			} else if (boolean == 1) {  //dans le cas d'un char. normale

				matrice[i][j][1] = 'a';
				matrice[i][j][2] = 'a';


			}

			



		}

		fgetc(fichier); //prend le \n de fin de ligne
		

	}

	return  matrice;
}


void printf_gare(char *** mat_gare, char *** mat_fgcolor, char *** mat_bgcolor, int colonne, int ligne) {

	set_cursor(0,0);


	for (int j = 0; j < ligne; j++) { //parcourir les lignes

		for (int i = 0; i < colonne; i++) { //parcourir la ligne

			translation_char_to_fgcolor(mat_fgcolor[i][j][0]);
			translation_char_to_bgcolor(mat_bgcolor[i][j][0]);

			//printf("%c", mat_gare[i][j][0]); //afficher le char. courant

			if(mat_gare[i][j][1] == 'a') { //si char. normal
				
				if(mat_gare[i][j][0] == 'e') { //si char. courant égale e
					printf(" ");                //affichez espace
				}else {							//sinon
				printf("%c", mat_gare[i][j][0]);  //afficher le char. courant

				}

			} else {   //si caractère ASCII etendue
			
				printf("%c%c%c", mat_gare[i][j][0], mat_gare[i][j][1], mat_gare[i][j][2]);
			}
		}

		printf("\n");

	}


}


/*
void printf_file(char * tab_caractere, char * tab_fgcolor, char * tab_bgcolor, int taille, int taille_ligne, int xposition) {
	
	int xpositionfixe = xposition;
	
	for (int i =0; i < taille; i++) {

		translation_char_to_fgcolor(tab_fgcolor[i]);
		translation_char_to_bgcolor(tab_bgcolor[i]);

		//Si la curseur est dans le terminale et que le prochain caractère a afficher n'est pas un saut de ligne
		if( xposition < 186 && tab_caractere[i] != '\n') {

			if (tab_caractere[i] == 'e') {
				printf(" ");

			} else {

				printf("%c", tab_caractere[i] );

			}

		} else if (tab_caractere[i] == '\n') {
					
					printf("%c", tab_caractere[i] );
					move_cursor(xpositionfixe,0);
					xposition = xpositionfixe;

		 } else {
		 
		 	 move_cursor(xpositionfixe,0);
		 	 i += (taille_ligne - (xposition - xpositionfixe)-1); //i est avancé juste avant le saut de ligne
		 	 xposition = xpositionfixe;


		 } 

		 xposition +=1;
	}
	
}

*/


//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char direction, char voie ) {
	montrain.direction = direction;
	montrain.voie = voie;
	montrain.taille_tab_train =  351;
	montrain.taille_ligne_train = 70;
	montrain.porte = 'c';
	//montrain.etat = "dehors";

	switch(voie) {

		case 'A' : montrain.posy = 11; break;
		case 'B' : montrain.posy = 16; break;
		case 'C' : montrain.posy = 31; break;
		case 'D' : montrain.posy = 36; break;

	}

	return montrain;
}




