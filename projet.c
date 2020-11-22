#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "fct_cursor.h"
#include "fct_fichier.h"
#include "fct_time.h"
#include "fct_voyageur.h"
#include "fct_menu.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {

    //desactive l'affichage de stdin(clavier) sur stdout
    system("stty -echo");

    //desactive l'affichage du curseur
   printf("\033[?25l"); 
 


////CHARGEMENT////////CHARGEMENT////////CHARGEMENT////////CHARGEMENT////////CHARGEMENT////////CHARGEMENT////
    
    //INITIALISATION ALEATOIRE
    init_alea();
    srand(time(NULL));


    //CHARGER ET AFFICHER LA GARE
    char * liste = "azertyuiopqsdfghjklmwxcvbn0123456789 ";
    GARE gare1;
    gare1 = init_gare("objet/gare/gare.txt", "objet/gare/fgcolor.txt", "objet/gare/bgcolor.txt", liste); 
    
    //INITIALISER UN TRAIN
    TRAIN train_haut_ouest; 
    train_haut_ouest =  init_train("objet/train/train.txt", "objet/train/train_fgcolor.txt", "objet/train/train_bgcolor.txt", 'O', 'A', liste);
    

    //INITIALISER UN AUTRE TRAIN :D
    TRAIN train_haut_est; 
    train_haut_est = init_train("objet/train/train.txt", "objet/train/train_fgcolor.txt", "objet/train/train_bgcolor.txt", 'E', 'B', liste);
  
    //INITIALISER ENCORE UN AUTRE TRAIN :D :D

    TRAIN train_bas_ouest;   
    train_bas_ouest =  init_train("objet/train/train.txt", "objet/train/train_fgcolor.txt", "objet/train/train_bgcolor.txt", 'O', 'C', liste);







    //VOYAGEUR ET QUAI

    QUAI quaiA;
    quaiA = init_quai(gare1, 'A');

    LISTE * listeA;
    listeA = init_liste();
   
    QUAI quaiB;
    quaiB = init_quai(gare1, 'B');

    LISTE * listeB;
    listeB = init_liste();


    QUAI quaiC;
    quaiC = init_quai(gare1, 'C');

    LISTE * listeC;
    listeC = init_liste();
    

    //JOUEUR

    VOYAGEUR * joueur;
    joueur = init_voyageur_joueur(1 ,1 , 'A');







//VOUE A DISPARAITRE

    //add_liste(listeA,'A', 10,5,20,5,'m');
   
 
    for(int i = 2; i < 10 ; i++) {

          add_liste(listeA,'A', 1+i*8, 5, 1+i*4, 5,'m');
    }







////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////
    clear_screen();

    menu(train_bas_ouest, gare1);

    int frequence_voyageur =  1000;

    clear_screen();
    printf_gare(gare1);

    

/////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE///

    //INITIALISATION DU TEMPS 

         //temps restant train_haut_ouest
    printf_cadran(train_haut_ouest);
    printf_time(train_haut_ouest->temps_1, train_haut_ouest->temps1_affichage_x, train_haut_ouest->temps_affichage_y);
    printf_time(train_haut_ouest->temps_2, train_haut_ouest->temps2_affichage_x, train_haut_ouest->temps_affichage_y);

        //temps restant train_haut_est
    printf_cadran(train_haut_est);
    printf_time(train_haut_est->temps_1, train_haut_est->temps1_affichage_x,  train_haut_est->temps_affichage_y);
    printf_time(train_haut_est->temps_2, train_haut_est->temps2_affichage_x,  train_haut_est->temps_affichage_y);

        //temps restant train_bas_ouest
    printf_cadran(train_bas_ouest);
    printf_time(train_bas_ouest->temps_1, train_bas_ouest->temps1_affichage_x, train_bas_ouest->temps_affichage_y);
    printf_time(train_bas_ouest->temps_2, train_bas_ouest->temps2_affichage_x, train_bas_ouest->temps_affichage_y);


   char * p_mini_buffer;
   char mini_buffer;
   p_mini_buffer = &mini_buffer;


 /////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE/////
    char touche;
    clock_t debut;
    clock_t fin;
    while (1) { //LA GRANDE BOUCLE

        debut = clock();

        fflush(stdout);
        
        //gerer les temps
        decompte_and_print_time(train_haut_ouest);
        decompte_and_print_time(train_haut_est);
        decompte_and_print_time(train_bas_ouest);

        //gerer les train
        deplacement_train(train_haut_ouest, gare1,listeA);
        deplacement_train(train_haut_est, gare1, listeB);
        deplacement_train(train_bas_ouest, gare1, listeC);

        //deplacement joueur
        deplacement_joueur(joueur, quaiA, p_mini_buffer);

        //deplacement voyageur IA

     
        deplacement_voyageur(listeA, quaiA);
        //genere_voyageur(listeA, quaiA, frequence_voyageur);
        gestion_voyageur(listeA, quaiA, train_haut_ouest);

        deplacement_voyageur(listeB, quaiB);
       // genere_voyageur(listeB, quaiB, frequence_voyageur);
        gestion_voyageur(listeB, quaiB, train_haut_est);

        deplacement_voyageur(listeC, quaiC);
       // genere_voyageur(listeC, quaiC, frequence_voyageur);
        gestion_voyageur(listeC, quaiC, train_bas_ouest);



        
        fin = clock();
        //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
        while(   (double)(fin - debut) / 10000  <  1 ) { //le petite while 

            //rajouter le keypressed
        touche = key_pressed();
        add_mini_buffer(p_mini_buffer, touche);
        

            fin = clock();
        } 
    }

/**/
 /////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN//////

    
    printf("\033[?25h"); 


    set_background_color(300);
    getchar();  
    clear_screen();
	return 0;
    

}



