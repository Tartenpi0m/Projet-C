
typedef struct train * TRAIN;
typedef struct gare * GARE;
typedef struct quai * QUAI;
typedef struct Liste LISTE;

char key_pressed();

//affiche les voyageurs dans le menu
void affichage_voyageur(int a, QUAI monquai);

//cette fonction efface la zone de texte
void clear_zone_texte();

//fonction de selection du mode, d'animation et d'affichage du menu
int menu(TRAIN montrain, GARE magare, QUAI monquai, LISTE * maliste);

//affiche le cadre du menu
void printf_decoration2();

//affiche la fleche gauche du menu, en couleur
void printf_fleche_gauche(int fg, int bg);

//affiche la fleche droite du menu, en couleur
void printf_fleche_droite(int fg, int bg);

//active le mode d'affichage gras
void set_gras(int i);

//affiche l'écran de fermeture du simulateur et ferme le simulateur
void bye(int colonne, int ligne);