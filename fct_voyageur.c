#include <stdio.h>
#include <stdlib.h>
#include "fct_fichier.h"
#include "fct_cursor.h"
#include "fct_time.h"
#include "fct_voyageur.h"



VOYAGEUR ** matrice_init_quai(int colonne, int ligne) {

	VOYAGEUR ** mat = malloc(colonne*sizeof(VOYAGEUR*));

	for(int i = 0; i < colonne; i ++) {

		mat[i] = malloc(ligne*sizeof(VOYAGEUR));
	}

	for(int i =0 ; i < colonne; i++) {
		for(int j = 0; j < ligne; j++) {
			mat[i][j] = NULL;

		}
	}	
	return mat;

}




//convertie les couleurs d'arrière plan de la gare dans une matrice de la taille du quais avec des couleurs + clair (de 1er plan pour les voyageurs)
char ** matrice_init_quai_fgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy) {
/////ALLOUE DYNAMIQUEMENT LA MATRICE
	char ** mat = malloc(colonne*sizeof(char**));

	for(int i = 0; i < colonne; i ++) {

		mat[i] = malloc(ligne*sizeof(char**));
	}

/////INITIALISE AVEC LES VALEURS PLUS CLAIR

	char liste[] = "qsdfghjklmxcvbn0123456789";
	int l;

	for(int i = posx; i < colonne + posx; i++) {
		for(int j = posy; j < ligne + posy; j++) {

			l = 0;
			while(*matrice_bgcolor[i][j] != liste[l]) {  //ATTENTION pas sur de l'etoile
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
	monquai->posx = 6;
	monquai->colonne = 85;
	
	switch(monquai->voie) {
		case 'A' : 	monquai->posy = 6 ;
					monquai->ligne = 10;
					break;
		case 'B' : 	monquai->posy = 26 ;
					monquai->ligne = 7;
					break;
		case 'C' : 	monquai->posy = 34 ;
					monquai->ligne = 7;
					break;
	}


	monquai->matrice = matrice_init_quai(monquai->colonne, monquai->ligne);
	//monquai->mat_fgcolor = matrice_init_quai_fgcolor(magare->mat_bgcolor, monquai->colonne, monquai->ligne, monquai->posx, monquai->posy);

	return monquai;
}



//parametre provisoire
VOYAGEUR init_voyageur(char quai, int a, int b, int aa, int bb, char e) {

	VOYAGEUR monvoyageur;
	monvoyageur = malloc(sizeof(struct voyageur));

	monvoyageur->posx = a;
	monvoyageur->posy = b;
	monvoyageur->destx = aa;
	monvoyageur->desty = bb;
	monvoyageur->etat = e;
	monvoyageur->couleur = '9';
	monvoyageur->quai = quai;

	return monvoyageur;
}


void print_voyageur(VOYAGEUR monvoyageur, QUAI monquai) {


//Enregistre la position en haut a droite du quais (comme point de depart du curseur)
	

	translation_char_to_fgcolor(monvoyageur->couleur); //monquai->mat_fgcolor
	//translation_char_to_bgcolor(monquai)
	set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
	printf("×");
	//printf("■");

}