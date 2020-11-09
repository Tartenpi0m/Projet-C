

typedef struct train * TRAIN;


time_t init_time();
int get_time_s(time_t time_init);
int get_time_min(time_t time_init);

void printf_chiffre(char* filename, int x);
void printf_time(int time, int x, int y);
void printf_cadran(TRAIN montrain);

void init_alea(); 
void pass_and_init_time(TRAIN montrain);
void decompte_and_print_time(TRAIN montrain);

