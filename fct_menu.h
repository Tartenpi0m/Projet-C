
typedef struct train * TRAIN;
typedef struct gare * GARE;

char key_pressed();
int menu(TRAIN montrain, GARE magare);

void printf_decoration();
void printf_decoration2();

void printf_fleche_gauche(int fg, int bg);
void printf_fleche_droite(int fg, int bg);

void set_gras(int i);
