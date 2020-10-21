
/*int ligne = 45;

int colonne = 185;*/

char *** matrice_init(int colonne, int ligne);



//alloue un tableau contenant le contenu du fichier filename
char *** stock_file(char *filename, int colonne, int ligne, char* liste);




//afiche sur le terminale le contenu de tab_caractere avec des couleurs
void printf_gare(char *** mat_gare, char *** mat_fgcolor, char *** mat_bgcolor, int colonne, int ligne);





typedef struct train TRAIN;

struct train {

	char direction; //'O' for ouest and 'E' for east
	char voie; //voie A, B, C, D;
	int posx;
	int posy;
	char *** mat_train; //destiné à être initialisé avec la fonction stock_file
	char *** mat_fgtrain;
	char *** mat_bgtrain;
	int colonne;
	int ligne;
	char porte; //'o' for open and 'c' for close
	char etat[10]; //sortie, stationné, entrant...
	int vitesse;


};

//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char *** mat_train, char *** mat_fgtrain, char *** mat_bgtrain, char direction, char voie );


void printf_train(TRAIN montrain);
void printf_train_droite(TRAIN montrain);
void printf_train_gauche(TRAIN montrain);
void printf_TRAIN(TRAIN montrain);



//int deplacement_train(TRAIN montrain, char *** mat_bgcolor, int compteur);
int deplacement_train2(TRAIN montrain, int compteur);

