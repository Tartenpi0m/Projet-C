
//alloue un tableau contenant le contenu du fichier filename
char *** stock_file(char *filename, int colonne, int ligne, char* liste);

//afiche sur le terminale le contenu de tab_caractere avec des couleurs
void printf_gare(char *** mat_gare, char *** mat_fgcolor, char *** mat_bgcolor, int colonne, int ligne);

char *** matrice_init(int colonne, int ligne);



typedef struct train TRAIN;

struct train {

	char direction; //'O' for ouest and 'E' for east
	char voie; //voie A, B, C, D;
	int posx;
	int posy;
	char* tab_train; //destiné à être initialisé avec la fonction stock_file
	int taille_tab_train;
	int taille_ligne_train;
	char porte; //'o' for open and 'c' for close
	char etat[10]; //sortie, stationné, entrant...


};

//initialise le train et en particulier sa position verticale par rapport à sa voie.
TRAIN init_train(TRAIN montrain, char direction, char voie );

