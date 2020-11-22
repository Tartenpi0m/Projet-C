
typedef struct quai * QUAI;

struct quai {

	char voie; // 'A', 'B' or 'C'

	int colonne;
	int ligne;

	//up-left corner
	int posx;
	int posy;

	int ** matrice;
	char ** mat_fgcolor;
	char ** mat_bgcolor;

};



//Initialise à 0 une matrice au dimension d'un quai
int **  matrice_init_quai(int colonne, int ligne);

//Alloue et initialise une matrice au dimensiond'un quai, destiné à la couleur de premier plan des voyageur en fonction de l'éclairage
char ** matrice_init_quai_fgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy);
char ** matrice_init_quai_bgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy);

QUAI init_quai(GARE magare, char voie);



typedef struct voyageur VOYAGEUR;

struct voyageur {

	int posx;
	int posy;

	char etat; //à sa place 'w' (waiting) , en déplacement 'm' (moving)

	int destx; //posx de la destination, à initialiser partiellement aléatoirement sur le quai
	int desty;

	char quai;
	char couleur;

	int compteur; //utilisé uniquement pour le joueur

	//pointeur pour liste chainé

	VOYAGEUR * suivant;
};

/////LISTE_CHAINEE/////
typedef struct liste LISTE;
struct liste {

	VOYAGEUR * premier;

	//gestion de voyageur
	int compteur;
	char etat; //indique si les voyageurs attende le train ou doivent y monter



	//generation de voyageur
	int nbrvoyageur;
	int nbrvoyageur_max;
	int compteur_generation;
	int frequence_generation;//(compteur_generation_max)

};

LISTE * init_liste();

void print_voyageur(VOYAGEUR * monvoyageur, QUAI monquai);
void add_liste(LISTE * maliste, char quai, int a, int b, int aa, int bb, char etat);
void init_voyageur(LISTE * maliste, QUAI monquai);
void efface_voyageur(LISTE * maliste, VOYAGEUR * monvoyageur_precedent, VOYAGEUR * monvoyageur, VOYAGEUR * monvoyageur_suivant);
void genere_voyageur(LISTE * maliste, QUAI monquai, int frequence_generation);
void gestion_voyageur(LISTE * maliste, QUAI monquai, TRAIN montrain);

void attribution_porte(LISTE * maliste, QUAI monquai, TRAIN montrain);
void deplacement_voyageur(LISTE * maliste, QUAI monquai);



////////voyagageur joueur///////////

VOYAGEUR * init_voyageur_joueur(int a, int b, char quai);
void deplacement_joueur(VOYAGEUR * monvoyageur, QUAI monquai, char *p_mini_buffer);
void add_mini_buffer(char * p_mini_buffer, char touche);
void pull_mini_buffer(char * p_mini_buffer);