


//efface l'écran et poistionne le curseur à 0,0
void clear_screen();

//positionne le curesur à la positio x,y
void set_cursor(int x, int y);

//déplace le curseur du nombre de y ligne et de x colonne
void move_cursor(int x, int y);

//modifie le couleur de l'arrière plan (choisir x > 256 pour la couleur par défaut du terminale)
void set_background_color(int x);


//modifie le couleur du premier plan (choisir x > 256 pour la couleur par défaut du terminale)
void set_foreground_color(int x);