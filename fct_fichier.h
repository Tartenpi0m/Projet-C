#include <time.h>

typedef struct Liste LISTE;



//initialise une matrice de taille colonne*ligne*3
char *** matrice_init(int colonne, int ligne);

//Remplie une matrice avec le contenu du fichier filename (prend en charge l'ASCII)
char *** stock_file(char *filename, int colonne, int ligne, char* liste, int dim);

//inverse une matrice (effet miroir droite gauche), utilisé pour le train 
char *** invert_mat(char *** mat, int colonne, int ligne);


//GARE//////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct gare * GARE;

struct gare {

	char *** mat_gare;
	char *** mat_fgcolor;
	char *** mat_bgcolor;
	int colonne;
	int ligne;
};

//initialise la structure gare
GARE init_gare(char * file_gare, char * file_fg, char * file_bg, char * liste);

//affiche la gare avec des couleurs
void printf_gare(GARE magare);



//TRAIN////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct train * TRAIN;

struct train {

	char direction; //'O' for ouest and 'E' for east
	char voie; //voie A, B, C, D;


	char *** mat_train; //destiné à être initialisé avec la fonction stock_file
	char *** mat_fgtrain;
	char *** mat_bgtrain;
	
	int compteur;
	int vitesse;
	int vitesseinit; //vitesse initiale (constante)
	char porte; //'o' for open and 'c' for close
	char etat; //sortie, stationné, entrant...
	int phase;

	int colonne;
	int ligne;

	int posx;
	int posxinit;//position x initiale (constante)
	int posy;

	int temps1_affichage_x;
	int temps2_affichage_x;
	int temps_affichage_y;

	time_t temps_1_init; //temps 0 au moment de la génération du temps d'attente
	time_t temps_2_init;
	int temps_1_actuel; //minute écoulé depuis temps_init
	int temps_2_actuel;
	int temps_1; //minutes restantes 
	int temps_2;

	int temps_zero; //temps ecoulé d'attente avant l'entrée en gare (pendant le zero clignotant)
	int temps_zero_totale; //temps d'attente totale avant l'entrée en gare (pendant le zero clignotant)
};

//initialise le train 
TRAIN init_train(char * file_train, char * file_fg, char * file_bg, char direction, char voie, char * list);


//affiche les portes du train (portes ouvertes)
void printf_porte(TRAIN montrain, GARE magare);

//affiche le train quand celui ci ne dépasse pas de la fenetre
void printf_train(TRAIN montrain, GARE magare);

//affiche le train quand celui-ci dépasse de la fenetre par la droite (x > 120)
void printf_train_droite(TRAIN montrain, GARE magare);

//affiche le train quand celui-ci dépasse de la fenetre par la gauche (x < 0)
void printf_train_gauche(TRAIN montrain, GARE magare);

//affiche le train correctement independament de sa position
void printf_TRAIN(TRAIN montrain, GARE magare);

//affiche les portes du train (portes ouvertes)
void deplacement_train(TRAIN montrain, GARE magare, LISTE * maliste, int vitesse, int vitesse_temps);

//fait attendre le train un petit temps aléatoire avant que celui-ci n'entre en gare
//return 1 si le train doit arrivé, 0 sinon
int pre_arrive_en_gare(TRAIN montrain, int vitesse_temps);

//fait arrivé le train en gare
//retourne 1 quand train est arrivé a quai, 0 sinon
int arrive_en_gare(TRAIN montrain, GARE magare, int vitesse);

//attend que les voyageur soit tous sorties et que ceux sur le quais soit entré dans le train
//renvoie 1 quand le train peut repartir, 0 sinon
int arret_en_gare(TRAIN montrain, GARE magare, LISTE * maliste, int vitesse);

//fait partir le train de la gare
//renvoie 1 quand le train n'est lus sur l'écran, 0 sinon
int depart_en_gare(TRAIN montrain, GARE magare, int vitesse);

//fonction qui gère quand un train doit arriver, s'arreter, repartire...
void deplacement_train(TRAIN montrain, GARE magare, LISTE * maliste, int vitesse,  int vitesse_temps);