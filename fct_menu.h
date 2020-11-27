
typedef struct train * TRAIN;
typedef struct gare * GARE;
typedef struct quai * QUAI;
typedef struct Liste LISTE;

char key_pressed();

void affichage_voyageur(int a, QUAI monquai);
int menu(TRAIN montrain, GARE magare, QUAI monquai, LISTE * maliste);

void printf_decoration();
void printf_decoration2();

void printf_fleche_gauche(int fg, int bg);
void printf_fleche_droite(int fg, int bg);

void set_gras(int i);
void bye(GARE magare);