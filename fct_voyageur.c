#include <stdio.h>
#include <stdlib.h>
#include "fct_fichier.h"
#include "fct_cursor.h"
#include "fct_time.h"
#include "fct_voyageur.h"

////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////

int ** matrice_init_quai(int colonne, int ligne) {

	int ** mat = malloc(colonne*sizeof(int*));

	for(int i = 0; i < colonne; i ++) {

		mat[i] = malloc(ligne*sizeof(int));
	}

	for(int i =0 ; i < colonne; i++) {
		for(int j = 0; j < ligne; j++) {
			mat[i][j] = 0;

		}
	}	
	return mat;

}




//convertie les couleurs d'arrière plan de la gare dans une matrice de la taille du quai avec des couleurs + clair (de 1er plan pour les voyageurs)
char ** matrice_init_quai_fgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy) {
/////ALLOUE DYNAMIQUEMENT LA MATRICE
	char ** mat = malloc(colonne*sizeof(char*));

	for(int i = 0; i < colonne; i ++) {

		mat[i] = malloc(ligne*sizeof(char));
	}

/////INITIALISE AVEC LES VALEURS PLUS CLAIR

	char liste[] = "qsdfghjklmxcvbn0123456789";
	int l;

	for(int i = 0; i < colonne; i++) {
		for(int j = 0; j < ligne; j++) {

			l = 0;
			while(*matrice_bgcolor[i + posx][j + posy] != liste[l]) {  //ATTENTION pas sur de l'etoile
				l++;
			}
			mat[i][j] = liste[l + 10];

		}
	}


	return mat;
}





QUAI init_quai(GARE magare, char voie) {

	QUAI monquai;
	monquai = malloc(sizeof(struct quai));

	monquai->voie = voie;
	monquai->posx = 51;
	monquai->colonne = 85;
	
	switch(monquai->voie) {
		case 'A' : 	monquai->posy = 7 ;
					monquai->ligne = 10;
					break;
		case 'B' : 	monquai->posy = 26 ;
					monquai->ligne = 7;
					break;
		case 'C' : 	monquai->posy = 34 ;
					monquai->ligne = 7;
					break;
	}

	//rajouter la liste chainé des voyageurs

	monquai->matrice = matrice_init_quai(monquai->colonne, monquai->ligne);
	monquai->mat_fgcolor = matrice_init_quai_fgcolor(magare->mat_bgcolor, monquai->colonne, monquai->ligne, monquai->posx, monquai->posy);

	return monquai;
}






////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////


////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////




void print_voyageur(VOYAGEUR * monvoyageur, QUAI monquai) {


//Enregistre la position en haut a droite du quais (comme point de depart du curseur)
	

	translation_char_to_fgcolor(monvoyageur->couleur); //monquai->mat_fgcolor
	//translation_char_to_bgcolor(monquai)
	set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
	printf("×");
	//printf("■");

}


////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////


LISTE * init_liste() {

	LISTE * maliste = malloc(sizeof(*LISTE));
	VOYAGEUR * monvoyageur = malloc(sizeof(*VOYAGEUR));

	monvoyageur->suivant = NULL;
	maliste->premier = monvoyageur;

	return maliste;

}

///INITVOYAGEUR:)//
void add_liste(LISTE * maliste, char quai, int a, int b, int aa, int bb, char e) {

	VOYAGEUR * monvoyageur;
	monvoyageur = malloc(sizeof(VOYAGEUR*));

	monvoyageur->posx = a;
	monvoyageur->posy = b;
	monvoyageur->destx = aa;
	monvoyageur->desty = bb;
	monvoyageur->etat = e;
	monvoyageur->couleur = '9';
	monvoyageur->quai = quai;


	monvoyageur->suivant = maliste->premier;

	maliste->premier = monvoyageur;
	

}

//parcours la liste chainé
void gestion_voyageur(LISTE * maliste, QUAI monquai) {

	VOYAGEUR *monvoyageur = maliste->premier;

	//Boucle qui passe en revu tt les voyageurs

	while(monvoyageur != NULL) {
		print_voyageur(monvoyageur, monquai);
	}


}