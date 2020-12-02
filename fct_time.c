#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fct_time.h"
#include "fct_cursor.h"
#include "fct_fichier.h"


//initialise une variable au temps actuelle
time_t init_time() {

	return time(NULL); 

}

//retourne le temps écouler depuis init_time en seconde
int get_time_s(time_t time_init) {

	return (int) ( (time(NULL) - time_init));

}

//retourne le temps écouler depuis init_time en minute, moduler par la varibale vitesse
int get_time_min(time_t time_init, int vitesse) {

	return  (int) (  (int) (time(NULL) - time_init)  / vitesse); //temps 10 ou 60 seconde la minute
}

//affiche les chiffres de 0 à 9 contenu dans des fichiers
void printf_chiffre(char filename[], int x) {

	int ligne = 5;
	int colonne = 7;
	
	FILE *fichier;
	fichier = fopen(filename,"r");

	fgetc(fichier); //pour commencer à detecter tt de suite les charactère (espace inclus)
	move_cursor(1,0);
	//printf(" "); //remplace le  premier chracatere

	for(int j = 0; j < ligne; j++) {   //boucle de sautement de ligne

		for(int i = 0; i < colonne + 1; i++) {   //boucle des termes dans une ligne


			printf("%c", fgetc(fichier));
		}

		move_cursor(x,0);
	}

	printf("       ");
}

//affiche le cadran autour des chiffres
void printf_cadran(TRAIN montrain) {
	
	translation_char_to_bgcolor('q');
	translation_char_to_fgcolor('p');
	set_cursor(montrain->temps1_affichage_x-1, montrain->temps_affichage_y);
	printf("╔═       ═╦═       ═╗\n");
	move_cursor(montrain->temps1_affichage_x-2,0);
	printf("║         ║         ║\n");
	move_cursor(montrain->temps1_affichage_x-2,0);
	printf("║         ║         ║\n");
	move_cursor(montrain->temps1_affichage_x-2,0);
	printf("║         ║         ║\n");
	move_cursor(montrain->temps1_affichage_x-2,0);
	printf("║         ║         ║\n");
	//move_cursor(montrain->temps1_affichage_x-2,0);
	//printf("║         ║         ║\n");
	move_cursor(montrain->temps1_affichage_x-2,0);
	printf("╚═       ═╩═       ═╝");
}

//affiche un chiffre à partir d'un temps (minute)
void printf_time(int time, int x, int y) {

	set_cursor(x,y);
	translation_char_to_bgcolor('q');
	translation_char_to_fgcolor('p');

	char filename[] = "objet/chiffre/x.txt";

	switch(time) {
		case 0 : 	filename[14] = '0'; 
					printf("\e[5m"); //Texte clignotant
					break;
		case 1: filename[14] = '1'; break;
		case 2: filename[14] = '2'; break;
		case 3: filename[14] = '3'; break;
		case 4: filename[14] = '4'; break;
		case 5: filename[14] = '5'; break;
		case 6: filename[14] = '6'; break;
		case 7: filename[14] = '7'; break;
		case 8: filename[14] = '8'; break;
		case 9: filename[14] = '9'; break;
		default : filename[14] = '0'; printf("\e[5m"); break;  //pour l'instant cette fonction ne peut pas afficher un temps > 9 min
	}

	printf_chiffre(filename, x);
	printf("\e[25m"); //Texte normale (pas clignotant)


}

//initialise l'aléatoire
void init_alea() {

	srand(time(NULL));
}


//genere un temps aléatoire entre 1 et 9 min et trasnfert le temps du prochain prochain train au temps du prochain train quand celui-ci est arrivé en gare
void pass_and_init_time(TRAIN montrain) {

	//Le temps 2 va au temps 1
	montrain->temps_1 = montrain->temps_2;
	montrain->temps_1_init = montrain->temps_2_init;
	montrain->temps_1_actuel = montrain->temps_2_actuel;

	//Le temps 2 est générer
	montrain->temps_2 = ( rand() % (7 - montrain->temps_1) ) + montrain->temps_1 + 2;
	montrain->temps_2_init = time(NULL);
	montrain->temps_2_actuel = 0;

}

//compte les minute qui passe et affiche le temps en conséquences
void decompte_and_print_time(TRAIN montrain, int vitesse) {

	if (get_time_min(montrain->temps_1_init, vitesse)  > montrain->temps_1_actuel) { //si une minute c'est écoulé

            montrain->temps_1_actuel += 1; //actualiser le temps qui passe
            montrain->temps_1 -= 1 ;       //actualiser le temps restant
            printf_time(montrain->temps_1, montrain->temps1_affichage_x, montrain->temps_affichage_y);  //affiher le temps à la case (20,10)

        }
                //temps2
        if (get_time_min(montrain->temps_2_init, vitesse)  > montrain->temps_2_actuel) { //si une minute c'est écoulé

            montrain->temps_2_actuel += 1;     //actualiser le temps qui passe

        	if (montrain->etat == 'w' || montrain->etat == 'l' || montrain->etat == 'i' ) {
        		if(montrain->temps_2 == 1) {
        			montrain->temps_2 += 1 ; 

        		}
        	}

            montrain->temps_2 -= 1 ;            //actualiser le temps restant    	
            printf_time(montrain->temps_2, montrain->temps2_affichage_x, montrain->temps_affichage_y);  //affiher le temps2 à la case (20,10)


        }



}

