#include <time.h>

/*int ligne = 45;

int colonne = 185;*/

char *** matrice_init(int colonne, int ligne);



//alloue un tableau contenant le contenu du fichier filename
char *** stock_file(char *filename, int colonne, int ligne, char* liste);



//GARE //////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct gare GARE;

struct gare {

	char *** mat_gare;
	char *** mat_fgcolor;
	char *** mat_bgcolor;
	int colonne;
	int ligne;
};

//initialise la gare
GARE init_gare(GARE magare, char * file_gare, char * file_fg, char * file_bg, char * liste);
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
	
	int compteur;
	int vitesse;
	char porte; //'o' for open and 'c' for close
	char etat; //sortie, stationné, entrant...

	int colonne;
	int ligne;

	int posx;
	int posy;

	time_t temps_1_init; //temps 0 au moment de la génération du temps d'attente
	time_t temps_2_init;
	int temps_1_actuel; //minute écoulé depuis temps_init
	int temps_2_actuel;
	int temps_1; //minutes restantes 
	int temps_2;
};

//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(char * file_train, char * file_fg, char * file_bg, char direction, char voie, char * list);


void printf_train(TRAIN montrain, GARE magare);
void printf_train_droite(TRAIN montrain, GARE magare);
void printf_train_gauche(TRAIN montrain, GARE magare);
void printf_TRAIN(TRAIN montrain, GARE magare);


void deplacement_train(TRAIN montrain, GARE magare);
int arrive_en_gare(TRAIN montrain, GARE magare);
int depart_en_gare(TRAIN montrain, GARE magare);
