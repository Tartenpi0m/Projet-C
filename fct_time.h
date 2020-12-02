

typedef struct train * TRAIN;

//initialise une variable au temps actuelle
time_t init_time();

//retourne le temps écouler depuis init_time en seconde
int get_time_s(time_t time_init);

//retourne le temps écouler depuis init_time en minute, moduler par la varibale vitesse
int get_time_min(time_t time_init, int vitesse);

//affiche les chiffres de 0 à 9 contenu dans des fichiers
void printf_chiffre(char* filename, int x);

//affiche le cadran autour des chiffres
void printf_time(int time, int x, int y);

//affiche un chiffre à partir d'un temps (minute)
void printf_cadran(TRAIN montrain);

//initialise l'aléatoire
void init_alea(); 

//genere un temps aléatoire entre 1 et 9 min et trasnfert le temps du prochain prochain train au temps du prochain train quand celui-ci est arrivé en gare
void pass_and_init_time(TRAIN montrain);

//compte les minute qui passe et affiche le temps en conséquences
void decompte_and_print_time(TRAIN montrain, int vitesse);

