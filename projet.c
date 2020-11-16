#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "fct_cursor.h"
#include "fct_fichier.h"
#include "fct_time.h"
#include "fct_voyageur.h"

//VARIABLE GLOBALE

//int height =; 
//int width = ;


//COULEUR RACOURCI


int main() {

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

    QUAI quai1;
    quai1 = init_quai(gare1, 'A');


    LISTE * listeA;
    listeA = init_liste();
    add_liste(listeA, 'A', 1,10,20, 1,'m');
    add_liste(listeA,'A', 10,1,1,0,'m');
    
////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////
    clear_screen();

    menu(train_bas_ouest, gare1);



    clear_screen();
    printf_gare(gare1);


/////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE/////////AFFICHAGE///

    //INITIALISATION DU TEMPS 

//voué a disparaitre
   /*         //temps ecoulé de puis le début
    time_t THE_time_init = init_time();   
    int THE_minute_time = 0; //doit augmenter de 1 toute les minutes
    printf_time(THE_minute_time, 1, 10);
*/

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


   
   



 /////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE/////
    clock_t debut;
    clock_t fin;
    while (1) { //LA GRANDE BOUCLE

        debut = clock();

        gestion_voyageur(listeA, quai1);
        
        //gerer les temps
        decompte_and_print_time(train_haut_ouest);
        decompte_and_print_time(train_bas_ouest);
        decompte_and_print_time(train_haut_est);

        //gerer les train
        deplacement_train(train_haut_ouest, gare1);
        deplacement_train(train_haut_est, gare1);
        deplacement_train(train_bas_ouest, gare1);



        
        fin = clock();
        //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
        while(   (double)(fin - debut) / 10000  <  1 ) { //le petite while 

            //rajouter le keypressed

            fin = clock();
        } 
    }

/**/
 /////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN///////////FIN//////




    set_background_color(300);
    getchar();  
    clear_screen();
	return 0;
    

}
