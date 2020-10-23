#include <stdio.h>
#include <stdlib.h>
#include "fct_fichier.h"
#include "fct_cursor.h"

char *** matrice_init(int colonne, int ligne) 
{


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




/////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE/////
GARE init_gare(GARE magare, char * file_gare, char * file_fg, char * file_bg, char * liste) {

	magare.colonne = 185;
	magare.ligne = 53;
    magare.mat_gare = stock_file(file_gare, magare.colonne, magare.ligne, liste);
	magare.mat_fgcolor = stock_file(file_fg, magare.colonne, magare.ligne, liste);
  	magare.mat_bgcolor = stock_file(file_bg, magare.colonne, magare.ligne, liste);
  	return magare;
    
}


void printf_gare(GARE magare) {

	set_cursor(0,0);


	for (int j = 0; j < magare.ligne; j++) { //parcourir les lignes

		for (int i = 0; i < magare.colonne; i++) { //parcourir la ligne

			translation_char_to_fgcolor(magare.mat_fgcolor[i][j][0]);
			translation_char_to_bgcolor(magare.mat_bgcolor[i][j][0]);

			//printf("%c", mat_gare[i][j][0]); //afficher le char. courant

			if(magare.mat_gare[i][j][1] == 'a') { //si char. normal
				
				if(magare.mat_gare[i][j][0] == 'e') { //si char. courant égale e
					printf(" ");                //affichez espace
				}else {							//sinon
				printf("%c", magare.mat_gare[i][j][0]);  //afficher le char. courant

				}

			} else {   //si caractère ASCII etendue
			
				printf("%c%c%c", magare.mat_gare[i][j][0], magare.mat_gare[i][j][1], magare.mat_gare[i][j][2]);
			}
		}

		printf("\n");

	}


}
/////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE//////////GARE/////


/////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN/////


//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char * file_train, char * file_fg, char * file_bg, char direction, char voie, char * liste) {
	montrain.direction = direction;
	montrain.voie = voie;

	montrain.colonne =  82;
	montrain.ligne = 5;

	montrain.mat_train = stock_file(file_train, montrain.colonne, montrain.ligne, liste);
	montrain.mat_fgtrain = stock_file(file_fg, montrain.colonne, montrain.ligne, liste);
	montrain.mat_bgtrain = stock_file(file_bg, montrain.colonne, montrain.ligne, liste);


	montrain.vitesse = 50;
	montrain.porte = 'c';
	//montrain.etat = "dehors";



	//TEMPS
	montrain.temps_1_init = time(NULL);
	montrain.temps_2_init = time(NULL);
	montrain.temps_1_actuel = 0;
	montrain.temps_2_actuel = 0;
	montrain.temps_1 = rand() % 4;
	montrain.temps_2 = ( rand() % (8 - montrain.temps_1) ) + montrain.temps_1 + 1;

	//DIRECTION
	switch(direction) {
		case 'O' : montrain.posx = 300; break;
		case 'E' : montrain.posx = - 300 - montrain.colonne; break;
	}

	//VOIE
	switch(voie) {

		case 'A' : montrain.posy = 16; break;
		case 'B' : montrain.posy = 21; break;
		case 'C' : montrain.posy = 41; break;

	}

	return montrain;
}




void printf_train(TRAIN montrain, GARE magare) {
	set_cursor(montrain.posx + 1, montrain.posy);

	//car le fihcier train commence par un espace or le fgetc de stock_file commence au premier chractère différent de  espace
	

	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = 0; i < montrain.colonne; i++) {


			translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
			translation_char_to_bgcolor(montrain.mat_bgtrain[i][j][0]); //change la couleur de bg du train

			if(montrain.mat_bgtrain[i][j][0] == 's') {
				
				translation_char_to_bgcolor(magare.mat_bgcolor[i + montrain.posx][j + montrain.posy][0]);//    ...couleur des matrices de la gare
			}

			if(montrain.mat_fgtrain[i][j][0] == 'f') {

				translation_char_to_fgcolor(magare.mat_fgcolor[i + montrain.posx][j + montrain.posy][0]);
			}



			if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

			} else {   //sinon (si caractère ASCII etendue)
			
				printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
			}
		}

		printf("\n");
		move_cursor(montrain.posx , 0);

	}

}		



//pour afficher le train quand x > 120
void printf_train_droite(TRAIN montrain, GARE magare) {

	set_cursor(montrain.posx + 1, montrain.posy);



	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = 0; i < montrain.colonne; i++) {


			if(i < (magare.colonne - montrain.posx )) { //colonne(185) = largeur de la gare //Si le curseure ne dépasse pasà droite

				translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
				translation_char_to_bgcolor(montrain.mat_bgtrain[i][j][0]); //change la couleur de bg du train

				if(montrain.mat_bgtrain[i][j][0] == 's') {
				
					translation_char_to_bgcolor(magare.mat_bgcolor[i + montrain.posx][j + montrain.posy][0]);//    ...couleur des matrices de la gare
				}
				if(montrain.mat_fgtrain[i][j][0] == 's') {

				translation_char_to_fgcolor(magare.mat_fgcolor[i + montrain.posx][j + montrain.posy][0]);
				}


				if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

				} else {   //sinon (si caractère ASCII etendue)
			
					printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
				}
			} else {
				printf("\n");
				move_cursor(montrain.posx , 0);
				break;
			}





		}
			
	}

}

//afficher le train quand x < 0
void printf_train_gauche(TRAIN montrain, GARE magare) {

	set_cursor(0, montrain.posy);
	int x = montrain.colonne - (montrain.colonne + montrain.posx); //distance entre la bordure driote et le bout du train hors champ


	for( int j = 0; j < montrain.ligne; j++) {

		for(int i = x; i < montrain.colonne; i++) {


			translation_char_to_fgcolor(montrain.mat_fgtrain[i][j][0]); //change la couleur de fg du train
			translation_char_to_bgcolor(montrain.mat_bgtrain[i][j][0]); //change la couleur de bg du train

			if(montrain.mat_bgtrain[i][j][0] == 's') {
				
				translation_char_to_bgcolor(magare.mat_bgcolor[i + montrain.posx][j + montrain.posy][0]);//    ...couleur des matrices de la gare
			}
			if(montrain.mat_fgtrain[i][j][0] == 'f') {
				translation_char_to_fgcolor(magare.mat_fgcolor[i + montrain.posx][j + montrain.posy][0]);
			}


			if(montrain.mat_train[i][j][0] == 'e') { //si char. espace
			 
					printf(" ");   //affichez espace

			} else {   //sinon (si caractère ASCII etendue)
			
				printf("%c%c%c",  montrain.mat_train[i][j][0],  montrain.mat_train[i][j][1], montrain.mat_train[i][j][2]);  //affiche le caractère ASCII étendue
				
			}
		}

		printf("\n");

	}



}


void printf_TRAIN(TRAIN montrain, GARE magare) {
	
	if (montrain.posx < 0) {

		printf_train_gauche(montrain, magare);

	} else if(montrain.posx > 185 - montrain.colonne) {

		printf_train_droite(montrain, magare);

	} else {

		printf_train(montrain, magare);
	}

}		

//retourne -1 quand le train est arrivé à destination
//retourn la valeur du compteur sinon
int deplacement_train(TRAIN montrain, GARE magare, int compteur) {


	compteur += montrain.vitesse;


	if (compteur > 1000000) {

		montrain.posx -= 1;
		printf_TRAIN(montrain, magare);
		compteur  = 0;

	}

	return compteur;

}





int deplacement_train2(TRAIN montrain, GARE magare, int compteur) {


	if (compteur > 100000000) {

		montrain.posx -= 1;
		printf_TRAIN(montrain, magare);
		printf("%d", montrain.posx);
		return 0;

	}

	return 1;
}



/////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN//////////TRAIN/////





	






















