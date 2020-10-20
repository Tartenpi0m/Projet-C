//FONCTION MATRICE, FICHIER, AFFFICHAGE


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






//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char *** mat_train, char *** mat_fgtrain, char direction, char voie ) {
	montrain.direction = direction;
	montrain.voie = voie;
	montrain.mat_train = mat_train;
	montrain.mat_fgtrain = mat_fgtrain;

	montrain.colonne =  66;
	montrain.ligne = 5;
	montrain.porte = 'c';
	//montrain.etat = "dehors";

	switch(voie) {

		case 'A' : montrain.posy = 16; break;
		case 'B' : montrain.posy = 21; break;
		case 'C' : montrain.posy = 41; break;

	}

	return montrain;
}

void printf_train(TRAIN montrain, char *** mat_bgcolor, int x) {
	set_cursor(x, montrain.posy);

	translation_char_to_bgcolor(mat_bgcolor[x][montrain.posy][0]);
	printf(" ");

	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = 0; i < montrain.colonne; i++) {

			translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
			translation_char_to_bgcolor(mat_bgcolor[x+i][montrain.posy+j][0]); //change la couleur de bg par rapport au fond de la gare

			if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

			} else {   //sinon (si caractère ASCII etendue)
			
				printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
			}
		}

		printf("\n");
		move_cursor(x , 0);

	}

}		



//pour afficher le train quand x > 120
void printf_train_droite(TRAIN montrain, char *** mat_bgcolor, int x) {

	set_cursor(x, montrain.posy);

	translation_char_to_bgcolor(mat_bgcolor[x][montrain.posy][0]);
	printf(" ");


	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = 0; i < montrain.colonne; i++) {


			if(i < (185 - x )) { //colonne(185) = largeur de la gare //Si le curseure ne dépasse pasà droite

				translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
				translation_char_to_bgcolor(mat_bgcolor[x+i][montrain.posy+j][0]); //change la couleur de bg par rapport au fond de la gare

				if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

				} else {   //sinon (si caractère ASCII etendue)
			
					printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
				}
			} else {
				printf("\n");
				move_cursor(x , 0);
				break;
			}





		}
			
	}

}

//afficher le train quand x < 0
void printf_train_gauche(TRAIN montrain, char *** mat_bgcolor, int x) {

	set_cursor(0, montrain.posy);
	x = montrain.colonne - (montrain.colonne + x); //distance entre la bordure driote et le bout du train hors champ


	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = x; i < montrain.colonne; i++) {

			translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
			translation_char_to_bgcolor(mat_bgcolor[x+i][montrain.posy+j][0]); //change la couleur de bg par rapport au fond de la gare

			if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

			} else {   //sinon (si caractère ASCII etendue)
			
				printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
			}
		}

		printf("\n");

	}



}


void printf_TRAIN(TRAIN montrain, char *** mat_bgcolor, int x) {
	
	if (x < 0) {

		printf_train_gauche(montrain, mat_bgcolor, x);

	} else if(x > 185 - montrain.colonne-2) {

		printf_train_droite(montrain, mat_bgcolor, x);

	} else {

		printf_train(montrain, mat_bgcolor, x);
	}

}		













