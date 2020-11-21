#include <time.h>


typedef struct liste LISTE;

char *** matrice_init(int colonne, int ligne);



//alloue un tableau contenant le contenu du fichier filename
char *** stock_file(char *filename, int colonne, int ligne, char* liste, int dim);


char *** invert_mat(char *** mat, int colonne, int ligne);



//GARE //////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct gare * GARE;

struct gare {

	char *** mat_gare;
	char *** mat_fgcolor;
	char *** mat_bgcolor;
	int colonne;
	int ligne;
};

//initialise la gare
GARE init_gare(char * file_gare, char * file_fg, char * file_bg, char * liste);
//afiche sur le terminale le contenu de tab_caractere avec des couleurs
void printf_gare(GARE magare);

//TRAIN ////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct train * TRAIN;

struct train {

	char direction; //'O' for ouest and 'E' for east
	char voie; //voie A, B, C, D;


	char *** mat_train; //destiné à être initialisé avec la fonction stock_file
	char *** mat_fgtrain;
	char *** mat_bgtrain;
	
	int compteur; //utilisé pour toutes les focntion depart arrive etc..
	int vitesse; //vitesse du train
	int vitesseinit; //vitesse initiale (constante)
	char etat; //sortie, stationné, entrant...
	char phase; //phase = 1 : les voyageurs ne sont pas encore tous rentré dans le trai; phase = 2 : ...

	int colonne;
	int ligne;

	int posx; //position x actuelle
	int posxinit;//position x initiale (constante)
	int posy; //posistion y (constante)

	//TEMPS
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

//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(char * file_train, char * file_fg, char * file_bg, char direction, char voie, char * list);


void printf_train(TRAIN montrain, GARE magare);
void printf_train_droite(TRAIN montrain, GARE magare);
void printf_train_gauche(TRAIN montrain, GARE magare);
void printf_TRAIN(TRAIN montrain, GARE magare);


void deplacement_train(TRAIN montrain, GARE magare, LISTE * maliste);
int pre_arrive_en_gare(TRAIN montrain);
int arrive_en_gare(TRAIN montrain, GARE magare);
int depart_en_gare(TRAIN montrain, GARE magare);
int arret_en_gare(TRAIN montrain, GARE magare, LISTE * maliste);
