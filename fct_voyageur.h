typedef struct voyageur * VOYAGEUR;

struct voyageur {

	int posx;
	int posy;

	char etat; //à sa place 'w' (waiting) , en déplacement 'm' (moving)

	int destx; //posx de la destination, à initialiser partiellement aléatoirement sur le quai
	int desty;

	char quai;
	char couleur;
};




typedef struct quai * QUAI;

struct quai {

	char voie; // 'A', 'B' or 'C'

	int colonne;
	int ligne;

	//up-left corner
	int posx;
	int posy;

	VOYAGEUR ** matrice;
	char ** mat_fgcolor;

};



//Alloue et intialise a NULL une matrice au dimension d'un quai
VOYAGEUR ** matrice_init_quai(int colonne, int ligne);

//Alloue et initialise une matrice au dimensiond'un quai, destiné à la couleur de premier plan des voyageur en fonction de l'éclairage
char ** matrice_init_quai_fgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy);

QUAI init_quai(GARE magare, char voie);





VOYAGEUR init_voyageur(char quai, int a, int b, int aa, int bb, char e);

void print_voyageur(VOYAGEUR monvoyageur, QUAI monquai);

//acreer
void swap(VOYAGEUR ** matrice_quai, int x1, int y1, char nextpos);  //nextpos = zqsdaecw




void main_voyageur(VOYAGEUR ** matrice_quai);





