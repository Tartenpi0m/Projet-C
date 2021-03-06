#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fct_fichier.h"
#include "fct_cursor.h"
#include "fct_time.h"
#include "fct_voyageur.h"

////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////////QUAI////

//initialise une matrice de taille colonne*ligne
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



//Alloue et initialise une matrice au dimension d'un quai, destiné à la couleur de premier plan des voyageur en fonction de l'éclairage
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

//Alloue et initialise une matrice au dimension d'un quai, destiné à la couleur d'arrière plan des voyageur
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



//initialise un quai
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



//affiche un voyageur à la position precisé
void print_voyageur(VOYAGEUR * monvoyageur, QUAI monquai) {


//Enregistre la position en haut a droite du quais (comme point de depart du curseur)
	

	//translation_char_to_fgcolor(monvoyageur->couleur); //monquai->mat_fgcolor
	//translation_char_to_fgcolor(monquai->mat_fgcolor[monvoyageur->posx][monvoyageur->posy]);
	set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
	//printf("×");
	printf("█");

}


////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////////VOYAGEUR////

//initialise une liste de voyageur
LISTE * init_liste() {

	LISTE * maliste = malloc(sizeof(*maliste));
	VOYAGEUR * monvoyageur = malloc(sizeof(*monvoyageur));
	maliste->etat = 'w';


	maliste->compteur_before_porte = 0;
	maliste->compteur = 0;
	maliste->nbrvoyageur = 0;
	maliste->nbrvoyageur_max = 15;
	maliste->nbrvoyageur_max_sortant = 3;
	maliste->couleur = 1;

	maliste->frequence_generation = 120;

	monvoyageur->suivant = NULL;
	maliste->premier = monvoyageur;

	return maliste;

}

//ajoute un voyageur à la liste
void add_liste(LISTE * maliste, QUAI  monquai, int a, int b, int aa, int bb, char etat) {

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
	monvoyageur->quai = monquai->voie;

	monvoyageur->compteur = 0; //ne sert a rien, juste pour eviter un warning

	
	translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
	translation_char_to_fgcolor(monquai->mat_fgcolor[monvoyageur->posx][monvoyageur->posy]);
	if(maliste->etat == 'g') {
		translation_char_to_fgcolor('r');
	} 
	print_voyageur(monvoyageur, monquai);



	//GERE LA LISTE
	monvoyageur->suivant = maliste->premier;

	maliste->premier = monvoyageur;
	

}



//initialise un voyageur et l'ajoute à une liste
void init_voyageur(LISTE * maliste, QUAI monquai) {

	int x = monquai->colonne-1;
	int y;
	int destx;
	int desty;


	def_dest:

	destx = rand() % (monquai->colonne-7) + 3; //entre 3 et 83


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








	add_liste(maliste, monquai, x, y, destx, desty, 'm');

}

//initialise un voyageur à intervalle de temps plus ou moins régulier
void genere_voyageur(LISTE * maliste, QUAI monquai, int frequence_generation) {
	
	//si le train n'est pas en gare et que les voyageurs sont en mode attendre sur le quai
	if (maliste->etat == 'm') {

		//Si le nombre maximum de voyageur permis n'est pas atteint
		if(maliste->nbrvoyageur < maliste->nbrvoyageur_max) {
			
			//on incrémente le compteur
			maliste->compteur_generation ++; //temps entre deux voyageur généré

			//Si il s'est ecoulé un temps aléatoire mais raisonnable entre deux generation de voyageur
			if (maliste->compteur_generation > maliste->frequence_generation) {

				maliste->compteur_generation = 0; // réinitialiser le compteur pour commencer le decompte du temps avant le prochain voyageur
				maliste->frequence_generation = rand() % frequence_generation; //Variation du temps entre deux voyageur
				init_voyageur(maliste, monquai); //initialise un voyageur
				maliste->nbrvoyageur ++; //incrémente le nombre de voyageur
			}

		}
	}
}



//Attribue les coordoonées de la position des porte aux position de destination de chaque voyageur
void attribution_porte(LISTE * maliste, QUAI monquai, TRAIN montrain) {


	//ajustement de la position des porte
	int dif = monquai->posx - montrain->posx;
	int nbrporte = 6;
	int posporte[nbrporte]; 
	if(montrain->voie == 'B') {
		int fakeposporte[] = {11, 20, 32, 41, 54, 62};
		memcpy(posporte, fakeposporte, nbrporte*sizeof(int));
		
	} else {
		int fakeposporte[] = {20, 29, 41, 50, 63, 71};
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

		monvoyageur->desty = 8;
		//adaptation de cette position au quai B
		if(montrain->voie == 'B') {
			monvoyageur->desty = 0;
		} 
		if(montrain->voie == 'C') {
			monvoyageur->desty = 6;
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

//enleve le voyageur de sa liste
void efface_voyageur(LISTE * maliste, VOYAGEUR * monvoyageur_precedent, VOYAGEUR * monvoyageur, VOYAGEUR * monvoyageur_suivant) {

	if(monvoyageur_precedent == NULL) {

		maliste->premier = monvoyageur_suivant;
	} else {
		
		monvoyageur_precedent->suivant = monvoyageur_suivant;

	}

	free(monvoyageur);
}




//parcours la liste chainé de voyageurs et les déplacent un à un
void deplacement_voyageur(LISTE * maliste, QUAI monquai, int vitesse_voyageur, char * p_couleur_buffer) {

	VOYAGEUR *monvoyageur_precedent = NULL;
	VOYAGEUR *monvoyageur = maliste->premier;
	VOYAGEUR *monvoyageur_suivant = monvoyageur->suivant;

	int compteur_nbrvoyageur = 0;

	maliste->compteur ++;
	if (maliste->compteur > vitesse_voyageur) {
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
		
			if(monvoyageur->posx == monvoyageur->destx && monquai->matrice[monvoyageur->posx][monvoyageur->posy +1] ==  1 && monvoyageur->desty != monvoyageur->posy) {
				if(monquai->voie != 'B') {
						monvoyageur->posy += 1;
				} else {
					monvoyageur->posy -=1;
				}
			} else {

				if(monvoyageur->posx < monvoyageur->destx) {
					if(monquai->matrice[monvoyageur->posx+1][monvoyageur->posy] == 0) {
	
						monvoyageur->posx += 1;
					}
				} else if(monvoyageur->posx > monvoyageur->destx) {
					if(monquai->matrice[monvoyageur->posx-1][monvoyageur->posy] == 0) {
			
						monvoyageur->posx -=1;
					}
				} 

			}
				//deplace vers la position de destination
		

			if(monvoyageur->posy == monvoyageur->desty && monquai->matrice[monvoyageur->posx+1][monvoyageur->posy] ==  1 && monvoyageur->destx != monvoyageur->posx) {
					monvoyageur->posy += 1;
			} else {

				if(monvoyageur->posy < monvoyageur->desty) {
	
					if(monquai->matrice[monvoyageur->posx][monvoyageur->posy+1] == 0) {
	
						monvoyageur->posy += 1;
					}
	
				} else if (monvoyageur->posy > monvoyageur->desty) {
	
	
					if(monquai->matrice[monvoyageur->posx][monvoyageur->posy-1] == 0) {	
	
						monvoyageur->posy -=1;
					}
				} 


			}

			//couleur gérer dans voyageur
			if(*p_couleur_buffer == 'i') {
				
				pull_mini_buffer(p_couleur_buffer);
				
				if (maliste->couleur == 1) {
					maliste->couleur = 0;
				} else {
					maliste->couleur = 1;
				}
			}

			if(maliste->couleur == 1) {

				translation_char_to_fgcolor(monquai->mat_fgcolor[monvoyageur->posx][monvoyageur->posy]);
			} else {

				translation_char_to_fgcolor('p');
			}

			print_voyageur(monvoyageur, monquai); //cette focntion met le curseur a la bonne place 
		

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
					monvoyageur_precedent = monvoyageur;

				}
			}



			if(maliste->etat != 'w') {
				//met la nouvelle collision du voyageur
				monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 1;
			}
	
		
					
				
		
		
			//Avancement dans la liste chaîné
			
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



//initialise un voyageur et l'ajoute à une liste
void init_voyageur_sortant(LISTE * maliste, QUAI monquai) {

	//POSITION DES PORTES
	int nbrporte = 6;
	int posporte[nbrporte]; 
	if(monquai->voie == 'B') {
		int fakeposporte[] = {11, 20, 32, 41, 54, 62};
		memcpy(posporte, fakeposporte, nbrporte*sizeof(int));
		
	} else {
		int fakeposporte[] = {21, 30, 42, 51, 64, 72};
		memcpy(posporte, fakeposporte, nbrporte*sizeof(int));
		//positiondes portes en x par rapport au début du train (les phares)
	}


	//initialisation de la position de départ en y
	int y = 0;
	int decalage_porte;
	//adaptation de cette position au quai A
	if(monquai->voie == 'A') {
		y = 8;
		decalage_porte = -4;
	}
	//adaptation de cette position au quai B
	if(monquai->voie == 'B') {
		y = 0;
		decalage_porte = +7;
	} 
	//adaptation de cette position au quai C
	if(monquai->voie == 'C') {
		y = 6;
		decalage_porte = -4;
	} 



	for(int i = 0; i < rand() % 5 + 1; i++) {

		//initialisation de la position de départ en x
		//initialisation de laporte par laquel le.s voyageur.s vas sortir (A MODIFIER)
		
		//int p = rand() % 6;

		//int x = posporte[p] + decalage_porte;
		int x = posporte[rand() % 6] + decalage_porte;



		//initialisation de la position de d'arrivé en x
	    int destx = monquai->colonne-2;
	    int desty;
	    switch(monquai->voie) {

			case 'A' : 	desty = monquai->ligne/2 - 1 + (rand()%2) - 1;
						break;

			case 'B' : 	desty = monquai->ligne - 3 + (rand() % 2);
						break;

			case 'C' : 	desty = 0 + (rand() % 2);
						break;
		}


		add_liste(maliste, monquai, x, y, destx, desty, 'm');

	}
}
	

//initialise un voyageur à intervalle de temps plus ou moins régulier
void genere_voyageur_sortant(LISTE * maliste, QUAI monquai, int frequence_generation) {

	if(maliste->etat == 'g') {

		maliste->compteur_before_porte +=1; //temps avant l'ouverture des portes
		//si les portes ont eu le temps de s'ouvrir (120 = 100 + 20 = temps d'ouverture des porte + 20)
		if(maliste->compteur_before_porte > 120) {

			if(maliste->nbrvoyageur < maliste->nbrvoyageur_max_sortant) {

				maliste->compteur_generation ++;

				//Si il s'est ecoulé un temps aléatoire mais raisonnable entre deux generation de voyageur
				if (maliste->compteur_generation > frequence_generation) {

					maliste->compteur_generation = 0; // réinitialiser le compteur pour commencer le decompte du temps avant le prochain voyageur
					init_voyageur_sortant(maliste, monquai); //initialise un voyageur
					maliste->nbrvoyageur ++; //incrémente le nombre de voyageur
				}


			} else {
				maliste->etat = 'm';
			}

		}


	}

}



//parcours la liste chainé de voyageurs et les déplacent un à un
void deplacement_voyageur_sortant(LISTE * maliste, QUAI monquai, int vitesse_voyageur, char * p_couleur_buffer) {

	VOYAGEUR *monvoyageur_precedent = NULL;
	VOYAGEUR *monvoyageur = maliste->premier;
	VOYAGEUR *monvoyageur_suivant = monvoyageur->suivant;

	int compteur_nbrvoyageur = 0;

	maliste->compteur ++;
	if (maliste->compteur > vitesse_voyageur) {
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
		

			if(monvoyageur->posx < monvoyageur->destx) {
				if(monquai->matrice[monvoyageur->posx+1][monvoyageur->posy] == 0) {
	
					monvoyageur->posx += 1;
				}
			} else if(monvoyageur->posx > monvoyageur->destx) {
				if(monquai->matrice[monvoyageur->posx-1][monvoyageur->posy] == 0) {
			
					monvoyageur->posx -=1;
				}
			} 

				

			if(monvoyageur->posy < monvoyageur->desty) {
	
				if(monquai->matrice[monvoyageur->posx][monvoyageur->posy+1] == 0) {
	
							monvoyageur->posy += 1;
				}
	
			} else if (monvoyageur->posy > monvoyageur->desty) {
	
	
				if(monquai->matrice[monvoyageur->posx][monvoyageur->posy-1] == 0) {	
	
					monvoyageur->posy -=1;
				}
			} 


			//couleur gérer dans voyageur
			if(*p_couleur_buffer == 'o') {

				pull_mini_buffer(p_couleur_buffer);
				if (maliste->couleur == 1) {
					maliste->couleur = 0;
				} else {
					maliste->couleur = 1;
				}
			}

			if(maliste->couleur == 1) {

				translation_char_to_fgcolor(monquai->mat_fgcolor[monvoyageur->posx][monvoyageur->posy]);
			} else {

				translation_char_to_fgcolor('r');
			}

			print_voyageur(monvoyageur, monquai); //cette focntion met le curseur a la bonne place 
			

			//GESTION DU VOYAGEUR EN FONCTION DE L'ETAT DU TRAIN

				

				//si le voyageur arrive a la sortie (rentre dans le train)
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
				monvoyageur_precedent = monvoyageur;

			}
		
			//Avancement dans la liste chaîné
			
			monvoyageur = monvoyageur->suivant;
			monvoyageur_suivant = monvoyageur->suivant;


		}//FIN DU WHILE VOYAGEURS

		maliste->compteur = 0;

	}//fin du if compteur

}





//fonction qui coordoone les flux de voyageurs entrant et sortant
void gestion_voyageur(LISTE * maliste, LISTE * maliste_sortant, QUAI monquai, TRAIN montrain) {


	/*maliste = m     et maliste_sortant = w

	1er phase (train->etat != 'w')
	Les voyageur entrant arrive sur le quai
	Les voyageurs sortant n'existe pas

	2eme phase  (le stationne en gare cad montrain->etat = 'w') (liste m   liste sortant g )
	Les voyageurs entrant continue d'arriver sur le quai (rien ne change)
	Les voyageurs sortant sont créer au porte du train et se dirige vers la sortie

	3eme phase (les voyageurs sortant sont sortis) le stationne en gare cad montrain->etat = 'w') liste w) liste sortan m
	Les voyageurs entrant se dirige vers les portes (et rentrent dans le train)
	Les voyageurs sortant continue leur chemin vers la sorite (mais n'aparaissent plus au niveau des portes)

	*/

//PHASE 1
	//si le train n'est pas en gare
	if(montrain->etat != 'w') {
		//Et que les voyageurs ne sont pas en mode "affluer sur le quai"
		if(maliste->etat == 'w') {
			
			maliste->nbrvoyageur = 0; //on reinitialise le nombre de voyageurs à 0
			maliste->etat = 'm'; //les voyageurs peuvent de nouveau s'aglutiner sur le quai	
			maliste_sortant->etat = 'w'; //ligne facultative(pas sur)
		}


	}

//PHASE 2
	if(montrain->etat == 'w' && maliste_sortant->etat == 'w') {
		
		if(maliste_sortant->nbrvoyageur != maliste_sortant->nbrvoyageur_max_sortant) {

			maliste_sortant->etat = 'g';
		}
		//maliste->etat = 'm'; ne change pas (ligne facultative)

	}


//PHASE 3
	//si le train est arrivé en gare   //ET LES voyageurs sonrtant snt sortis (liste_sortant = 'm') (se set à m dans generation_voyageur_sortant )
	if(montrain->etat == 'w' && maliste_sortant->etat == 'm') {

		//S les voyageurs attendent sur la quai  (// et que les voyageurs sortant sont sorti)
		if(maliste->etat != 'w') {
			attribution_porte(maliste, monquai, montrain); //chaque voyageur se voit attribuer une porte
			maliste->etat = 'w'; //liste en mode renter dans le train

			maliste_sortant->nbrvoyageur = 0;
			maliste->nbrvoyageur_max_sortant = rand() % 4 + 1;
			maliste_sortant->etat = 'm'; //ligne facultative
			maliste->compteur_before_porte = 0; //remet le compteur à 0

		}		
	}
}







/////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR//////////DEPLACEMENT_VOYAGEUR_JOUEUR/////


//initialise le voyageur qui sera utilisé comme joueur
VOYAGEUR * init_voyageur_joueur(int a,int b,char quai) {

	//attribution de la mémoire
	VOYAGEUR * monvoyageur;
	monvoyageur = malloc(sizeof(*monvoyageur));

	//initialisation des valeurs
	monvoyageur->posx = a; ///a definir
	monvoyageur->posy = b;
	monvoyageur->destx = 0;  //ne sert a rien juste pour eviter un warning
	monvoyageur->desty = 0;//ne sert a rien juste pour eviter un warning
	monvoyageur->etat = 'g'; //out of the train

	monvoyageur->couleur = '9';
	monvoyageur->quai = quai;

	monvoyageur->compteur = 0;


	return monvoyageur;


}

//déplace le jouer en fonction de stdin
void deplacement_joueur(VOYAGEUR * monvoyageur, QUAI monquai, TRAIN montrain, char * p_mini_buffer) {

	monvoyageur->compteur ++;
	if (monvoyageur->compteur > 10) {





		//INTERACTION METRO (INITIALISTAION DES PORTES)
		int dif = monquai->posx - montrain->posx -1;
		int nbrporte = 6;
        int posporte[] = {21, 30, 42, 51, 64, 72};		
		for(int i = 0; i < nbrporte; i++) {
			posporte[i] -= dif;


			//Si le voyageur rentre dans le train
			if(monvoyageur->posx == posporte[i] && monvoyageur->posy == monquai->ligne - 2 && montrain->porte == 'o' && monvoyageur->etat == 'i') {

				//le faire sortir et le mode en mode ghost
				set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
				//set_background_color(29);
				translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
				printf(" ");
				monvoyageur->etat = 'b';
				pull_mini_buffer(p_mini_buffer);

			}


		}

		//Si le train quitte la gare et voyageur en mode 'babyghost' 
		if(montrain->etat == 'l' && monvoyageur->etat == 'b') {
			
			monvoyageur->etat = 'g'; //Passer en mode ghost
		}

		


		//si le train arrive en gare
		if(montrain->etat == 'i' && monvoyageur->etat != 'g') {//doute ici 

			monvoyageur->etat = 'i'; //le joueur passe en mode in (peut rentrer dans le train)
		}
		

		//Si le voyageur n'est pas en mode fantôme
		if(monvoyageur->etat != 'g' && monvoyageur->etat != 'b') {


			monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 0;
		
			translation_char_to_bgcolor(monquai->mat_bgcolor[monvoyageur->posx][monvoyageur->posy]);
			set_cursor(monquai->posx + monvoyageur->posx, monquai->posy + monvoyageur->posy);
			printf(" ");
			//printf("%c", touche);
		
			//CES IF NE SONT JAMAIS REMPLI(LA CONDITIONN)
			if(*p_mini_buffer == 'd' && monquai->matrice[monvoyageur->posx + 1][monvoyageur->posy] == 0 && monvoyageur->posx < monquai->colonne - 2) {
				monvoyageur->posx +=1;
		
			} else if (*p_mini_buffer == 'q' && monquai->matrice[monvoyageur->posx - 1][monvoyageur->posy] == 0 && monvoyageur->posx > 1) {
				monvoyageur->posx -= 1;
		
			}else if (*p_mini_buffer == 's' && monquai->matrice[monvoyageur->posx][monvoyageur->posy + 1] == 0 && monvoyageur->posy < monquai->ligne - 2) {
				monvoyageur->posy += 1;
		
			}else if (*p_mini_buffer == 'z' && monquai->matrice[monvoyageur->posx][monvoyageur->posy - 1] == 0 && monvoyageur->posy > 0)  {
				monvoyageur->posy -= 1;
		
			} else if(*p_mini_buffer == ' ') {
				pull_mini_buffer(p_mini_buffer);
			}
		
			//translation_char_to_bgcolor();
			set_foreground_color(56);
			print_voyageur(monvoyageur, monquai);
		
			monquai->matrice[monvoyageur->posx][monvoyageur->posy] = 1;


		} else if (monvoyageur->etat == 'g') { //si mode ghost
			//et si porte ouvert
			if(montrain->porte == 'o' ) {

				//LE VOYAGEUR SORT DU TRAIN
				monvoyageur->etat = 'o'; //voyageur passe en mode out
				monvoyageur->posx = posporte[rand() % 6];
				monvoyageur->posy = monquai->ligne - 2;
				set_foreground_color(56);
				print_voyageur(monvoyageur, monquai);
			}

		}

		monvoyageur->compteur = 0;

	}//fin du if compteur
}


//ajoute dans un buffer l'entrée clavier
void add_mini_buffer(char * p_mini_buffer, char touche) {

	if(touche != 'm') {
		*p_mini_buffer = touche;

	}
}


//vide le buffer
void pull_mini_buffer(char * p_mini_buffer) {

	*p_mini_buffer = 'm';
}