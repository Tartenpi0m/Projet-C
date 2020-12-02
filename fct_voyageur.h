
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

//Alloue et initialise une matrice au dimension d'un quai, destiné à la couleur d'arrière plan des voyageur
char ** matrice_init_quai_bgcolor(char *** matrice_bgcolor, int colonne, int ligne, int posx, int posy);

//initialise un quai
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
typedef struct Liste LISTE;
struct Liste {

	VOYAGEUR * premier;

	//gestion de voyageur
	int compteur_before_porte;
	int compteur;
	char etat; //indique si les voyageurs attende le train ou doivent y monter
	int couleur;



	//generation de voyageur
	int nbrvoyageur;
	int nbrvoyageur_max;
	int nbrvoyageur_max_sortant;
	int compteur_generation; //compteur dedié a la focntion generation
	int frequence_generation;//(compteur_generation_max)
	int frequence_generation_sortant;

};

//affiche un voyageur à la position precisé
void print_voyageur(VOYAGEUR * monvoyageur, QUAI monquai);

//initialise une liste de voyageur
LISTE * init_liste();

//ajoute un voyageur à la liste
void add_liste(LISTE * maliste, QUAI monquai, int a, int b, int aa, int bb, char etat);


//initialise un voyageur et l'ajoute à une liste
void init_voyageur(LISTE * maliste, QUAI monquai);
void init_voyageur_sortant(LISTE * maliste, QUAI monquai);

//initialise un voyageur à intervalle de temps plus ou moins régulier
void genere_voyageur(LISTE * maliste, QUAI monquai, int frequence_generation);
void genere_voyageur_sortant(LISTE * maliste, QUAI monquai, int frequence_generation);

//Attribue les coordoonées de la position des porte aux position de destination de chaque voyageur
void attribution_porte(LISTE * maliste, QUAI monquai, TRAIN montrain);
void deplacement_voyageur(LISTE * maliste, QUAI monquai, int vitesse_voyageur, char * p_couleur_buffer);

//enleve le voyageur de sa liste
void efface_voyageur(LISTE * maliste, VOYAGEUR * monvoyageur_precedent, VOYAGEUR * monvoyageur, VOYAGEUR * monvoyageur_suivant);

//parcours la liste chainé de voyageurs et les déplacent un à un
void deplacement_voyageur(LISTE * maliste, QUAI monquai, int vitesse_voyageur, char * p_couleur_buffer);
void deplacement_voyageur_sortant(LISTE * maliste, QUAI monquai, int vitesse_voyageur, char * p_couleur_buffer);


//fonction qui coordoone les flux de voyageurs entrant et sortant
void gestion_voyageur(LISTE * maliste, LISTE * maliste_sortant, QUAI monquai, TRAIN montrain);


////////voyagageur joueur///////////

//initialise le voyageur qui sera utilisé comme joueur
VOYAGEUR * init_voyageur_joueur(int a, int b, char quai);

//déplace le jouer en fonction de stdin
void deplacement_joueur(VOYAGEUR * monvoyageur, QUAI monquai, TRAIN montrain, char *p_mini_buffer);

//ajoute dans un buffer l'entrée clavier
void add_mini_buffer(char * p_mini_buffer, char touche);

//vide le buffer
void pull_mini_buffer(char * p_mini_buffer);