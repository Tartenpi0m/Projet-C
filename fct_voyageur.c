#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


char ** matrice_init_quai_bgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy) {

	char ** mat = malloc(colonne*sizeof(char*));

	for(int i = 0; i < colonne; i ++) {

		mat[i] = malloc(ligne*sizeof(char));
	}

	for(int i = 0; i < colonne; i++) {

		for(int j = 0; j < ligne; j++) {

			mat[i][j] = matrice_bgcolor[i + posx -1][j + posy-1][0];
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
	monquai->mat_bgcolor = matrice_init_quai_bgcolor(magare->mat_bgcolor, monquai->colonne, monquai->ligne, monquai->posx, monquai->posy);

	return monquai;
}






////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////


////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////




void print_voyageur(VOYAGEUR * monvoyageur, QUAI monquai) {


//Enregistre la position en haut a droite du quais (comme point de depart du curseur)
	

	//translation_char_to_fgcolor(monvoyageur->couleur); //monquai->mat_fgcolor
	translation_char_to_fgcolor(monquai->mat_fgcolor[monvoyageur->posx][monvoyageur->posy]);
	set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
	printf("×");
	//printf("■");

}


////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////


LISTE * init_liste() {

	LISTE * maliste = malloc(sizeof(*maliste));
	VOYAGEUR * monvoyageur = malloc(sizeof(*monvoyageur));
	maliste->etat = 'm';
	maliste->compteur = 0;
	maliste->nbrvoyageur = 0;
	maliste->nbrvoyageur_max = 20;

	monvoyageur->suivant = NULL;
	maliste->premier = monvoyageur;

	return maliste;

}

///INITVOYAGEUR:)//
void add_liste(LISTE * maliste, char quai, int a, int b, int aa, int bb, char etat) {

	//attribution de la mémoire
	VOYAGEUR * monvoyageur;
	monvoyageur = malloc(sizeof(*monvoyageur));

	//initialisation des valeurs
	monvoyageur->posx = a;
	monvoyageur->posy = b;
	monvoyageur->destx = aa;
	monvoyageur->desty = bb;
	monvoyageur->etat = etat;
	monvoyageur->couleur = '9';
	monvoyageur->quai = quai;

	monvoyageur->compteur = 0; //ne sert a rien, juste pour eviter un warning

	//GERE L4ATTRIBUTION DES DESTINATION



	//GERE LA LISTE
	monvoyageur->suivant = maliste->premier;

	maliste->premier = monvoyageur;
	

}




void init_voyageur(LISTE * maliste, QUAI monquai) {

	int x = monquai->colonne-1;
	int y;
	int destx;
	int desty;


	def_dest:

	destx = rand() % (monquai->colonne+1) + 3; //entre 3 et 83


	switch(monquai->voie) {

		case 'A' : 	y = monquai->ligne/2 - 1 + (rand()%2) - 1;
					desty = rand() % (monquai->ligne - 2) ;// tt les lignes sauf les 2 dernières 
					break;

		case 'B' : 	y = monquai->ligne - 3 + (rand() % 2);
					desty = rand() % (monquai->ligne - 2) + 2;
					break;

		case 'C' : 	y = 0 + (rand() % 2);
					desty = rand() % (monquai->ligne - 2) ;// tt les lignes sauf les 2 dernières 
					break;
	}



		VOYAGEUR *monvoyageur = maliste->premier;

		while(monvoyageur->suivant != NULL) {

			if (desty == monvoyageur->desty && destx == monvoyageur->destx) {
				goto def_dest;
			} 


			monvoyageur = monvoyageur->suivant;
		}








	add_liste(maliste, monquai->voie, x, y, destx, desty, 'm');

}

//initialise un voyageur à intervalle de temps plus ou moins régulier
void genere_voyageur(LISTE * maliste, QUAI monquai, int frequence_generation) {
	
	//si le train n'est pas en gare et que les voyageurs sont en mode attendre sur le quai
	if (maliste->etat == 'm') {

		//Si le nombre maximum de voyageur permis n'est pas atteint
		if(maliste->nbrvoyageur < maliste->nbrvoyageur_max) {
			
			//on incrémente le compteur
			maliste->compteur_generation ++;

			//Si il s'est ecoulé un temps aléatoire mais raisonnable entre deux generation de voyageur
			if (maliste->compteur_generation > maliste->frequence_generation) {

				maliste->compteur_generation = 0; // réinitialiser le compteur pour commencer le decompte du temps avant le prochain voyageur
				maliste->frequence_generation = frequence_generation + (rand() % 500); //Variation du temps entre deux voyageur
				init_voyageur(maliste, monquai); //initialise un voyageur
				maliste->nbrvoyageur ++; //incrémente le nombre de voyageur
			}

		}
	}
}



//cette fonction attribue les coordoonées de la position des porte aux position de destination des voyageurs
void attribution_porte(LISTE * maliste, QUAI monquai, TRAIN montrain) {


	//ajustement de la position des porte
	int dif = monquai->posx - montrain->posx;
	int nbrporte = 6;
	int posporte[nbrporte]; 
	if(montrain->voie == 'B') {
		int fakeposporte[] = {11, 20, 32, 41, 54, 62};
		memcpy(posporte, fakeposporte, nbrporte*sizeof(int));
		
	} else {
		int fakeposporte[] = {21, 30, 42, 51, 64, 72};
		memcpy(posporte, fakeposporte, nbrporte*sizeof(int));
		//positiondes portes en x par rapport au début du train (les phares)
	}
	
	for(int i = 0; i < nbrporte; i++) {

		posporte[i] -= dif;
	}







	VOYAGEUR *monvoyageur = maliste->premier;

	//position verticale correspondant au metro 
	

	//position horizontale correspondant au portes
	while(monvoyageur->suivant != NULL) {

		monvoyageur->desty = montrain->posy - 8;
		//adaptation de cette position au quai B
		if(montrain->voie == 'B') {
			monvoyageur->desty += montrain->ligne;
		}

		if(monvoyageur->posx <= posporte[0] + 3) {

			monvoyageur->destx = posporte[0] + 1;

		} else if (monvoyageur->posx >= posporte[1] - 5 && monvoyageur->posx <= posporte[1] + 7) {

			monvoyageur->destx = posporte[1] + 1;

		} else if (monvoyageur->posx >= posporte[2] - 4 && monvoyageur->posx <= posporte[2] + 5) {

			monvoyageur->destx = posporte[2] + 1;
			
		} else if (monvoyageur->posx >= posporte[3] - 3 && monvoyageur->posx <= posporte[3] + 7) {

			monvoyageur->destx = posporte[3] + 1;
			
		} else if (monvoyageur->posx >= posporte[4] - 5 && monvoyageur->posx <= posporte[4] + 6 ) {

			monvoyageur->destx = posporte[4] + 1;
			
		} else if (monvoyageur->posx >= posporte[5] - 1) {

			monvoyageur->destx = posporte[5] + 1;
			
		}

	monvoyageur = monvoyageur->suivant;			

	}


 }


void efface_voyageur(LISTE * maliste, VOYAGEUR * monvoyageur_precedent, VOYAGEUR * monvoyageur, VOYAGEUR * monvoyageur_suivant) {

	if(monvoyageur_precedent == NULL) {

		maliste->premier = monvoyageur_suivant;
	} else {
		
		monvoyageur_precedent->suivant = monvoyageur_suivant;

	}

	free(monvoyageur);
}




//parcours la liste chainé
void deplacement_voyageur(LISTE * maliste, QUAI monquai) {

	VOYAGEUR *monvoyageur_precedent = NULL;
	VOYAGEUR *monvoyageur = maliste->premier;
	VOYAGEUR *monvoyageur_suivant = monvoyageur->suivant;

	int compteur_nbrvoyageur = 0;

	maliste->compteur ++;
	if (maliste->compteur > 50) {
	//vitesse des voyageurs



		//Boucle qui passe en revu tt les voyageurs
		while(monvoyageur->suivant != NULL) {

				compteur_nbrvoyageur += 1;
				
		

				//enleve la collision du voyageur
				monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 0;
				
				////efface_voyageur
				set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
				translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
				printf(" ");
		
		

				//GESTION DES DEPLACEMENT ET ETVITEMENT DES VOYAGEURS
		
				//if(monvoyageur->posx == monvoyageur->destx && monquai->matrice[monvoyageur->posx][monvoyageur->posy +1] ==  1 && monvoyageur->desty != monvoyageur->posy) {
				//	monvoyageur->posy += 1;
				//} else {

					if(monvoyageur->posx < monvoyageur->destx) {
						if(monquai->matrice[monvoyageur->posx+1][monvoyageur->posy] == 0) {
	
							monvoyageur->posx += 1;
						}
					} else if(monvoyageur->posx > monvoyageur->destx) {
						if(monquai->matrice[monvoyageur->posx-1][monvoyageur->posy] == 0) {
			
							monvoyageur->posx -=1;
						}
					} 

				//}
				//deplace vers la position de destination
		

				//if(monvoyageur->posy == monvoyageur->desty && monquai->matrice[monvoyageur->posx+1][monvoyageur->posy] ==  1 && monvoyageur->destx != monvoyageur->posx) {
				//	monvoyageur->posy += 1;
				//} else {

					if(monvoyageur->posy < monvoyageur->desty) {
	
						if(monquai->matrice[monvoyageur->posx][monvoyageur->posy+1] == 0) {
	
							monvoyageur->posy += 1;
						}
	
					} else if (monvoyageur->posy > monvoyageur->desty) {
	
	
						if(monquai->matrice[monvoyageur->posx][monvoyageur->posy-1] == 0) {	
	
							monvoyageur->posy -=1;
						}
					} 


				////}
				


				//GESTION DU VOYAGEUR EN FONCTION DE L'ETAT DU TRAIN

				//si train en gare
				if(maliste->etat == 'w') {

					//si le voyageur arrive a la porte du train (rentre dans le train)
					if(monvoyageur->posy == monvoyageur->desty && monvoyageur->posx == monvoyageur->destx) {

						//efface le voyageur (collision, charactère, liste)
						set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
						translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
						printf(" ");
						efface_voyageur(maliste, monvoyageur_precedent, monvoyageur, monvoyageur_suivant);
						//on ne remet pas de collision dans matrice


					} else {
						//met la nouvelle collision du voyageur
						monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 1;

					}
				}



				if(maliste->etat != 'w') {
					//met la nouvelle collision du voyageur
					monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 1;
				}
		
		
				//couleur gérer dans voyageur
				translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
				print_voyageur(monvoyageur, monquai); //cette focntion met le curseur a la bonne place 
		
					
				
		
		
			//Avancement dans la liste chaîné
			monvoyageur_precedent = monvoyageur;
			monvoyageur = monvoyageur->suivant;
			monvoyageur_suivant = monvoyageur->suivant;


		}//FIN DU WHILE VOYAGEURS


		//si il n'y a plus de voyageur ET que le train est en gare
		if(compteur_nbrvoyageur == 0  && maliste->etat == 'w') {

			//de nouveau voyageurs peuvent arriver sur le quai
			maliste->etat = 'm';

		}

		maliste->compteur = 0;


	}//fin du if compteur


}






void gestion_voyageur(LISTE * maliste, QUAI monquai, TRAIN montrain) {

	//si le train est arrivé en gare
	if(montrain->etat == 'w') {
		//Et que les voyageurs attendent sur la quai
		if(maliste->etat != 'w') {
			
			attribution_porte(maliste, monquai, montrain); //chaque voyageur se voit attribuer une porte
			maliste->etat = 'w'; //liste en mode renter dans le train

		}
	}


	//si le train est reparti
	if(montrain->etat == 'l') {

		//les voyageurs peuvent de nouveau s'aglutiner sur le quai
		maliste->etat = 'm';
	}


}







/////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR/////

VOYAGEUR * init_voyageur_joueur(int a,int b,char quai) {

	//attribution de la mémoire
	VOYAGEUR * monvoyageur;
	monvoyageur = malloc(sizeof(*monvoyageur));

	//initialisation des valeurs
	monvoyageur->posx = a; ///a definir
	monvoyageur->posy = b;
	monvoyageur->destx = 0;  //ne sert a rien juste pour eviter un warning
	monvoyageur->desty = 0;//ne sert a rien juste pour eviter un warning
	monvoyageur->etat = 'm'; //ne sert a rien juste pour eviter un warning

	monvoyageur->couleur = '9';
	monvoyageur->quai = quai;

	monvoyageur->compteur = 0;


	return monvoyageur;


}


void deplacement_joueur(VOYAGEUR * monvoyageur, QUAI monquai, char * p_mini_buffer) {

	monvoyageur->compteur ++;
	if (monvoyageur->compteur > 50) {

		monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 0;
	
		translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
		set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
		printf(" ");
		//printf("%c", touche);
	
		//CES IF NE SONT JAMAIS REMPLI(LA CONDITIONN)
		if(*p_mini_buffer == 'd' && monquai->matrice[monvoyageur->posx + 1][monvoyageur->posy] == 0) {
			monvoyageur->posx +=1;
	
		} else if (*p_mini_buffer == 'q' && monquai->matrice[monvoyageur->posx - 1][monvoyageur->posy] == 0) {
			monvoyageur->posx -= 1;
	
		}else if (*p_mini_buffer == 's' && monquai->matrice[monvoyageur->posx][monvoyageur->posy + 1] == 0) {
			monvoyageur->posy += 1;
	
		}else if (*p_mini_buffer == 'z' && monquai->matrice[monvoyageur->posx][monvoyageur->posy - 1] == 0) {
			monvoyageur->posy -= 1;
	
		} else if(*p_mini_buffer == ' ') {
			pull_mini_buffer(p_mini_buffer);
		}
	
		translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
		print_voyageur(monvoyageur, monquai);
	
		monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 1;



		monvoyageur->compteur = 0;

	}//fin du if compteur
}

void add_mini_buffer(char * p_mini_buffer, char touche) {


//PEUT ETRE QUE CE IF N'EST JAMAIS REMPLI (LA CONDITION)
	if(touche != 'm') {
		*p_mini_buffer = touche;

	}
}



void pull_mini_buffer(char * p_mini_buffer) {

	*p_mini_buffer = 'm';
}