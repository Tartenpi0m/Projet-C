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

//JE SUIS LA DERNIER VERSION DU PROGRAMME


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
    LISTE * listeA_sortant;
    listeA_sortant = init_liste();
   
    QUAI quaiB;
    quaiB = init_quai(gare1, 'B');

    LISTE * listeB;
    listeB = init_liste();
    LISTE * listeB_sortant;
    listeB_sortant = init_liste();



    QUAI quaiC;
    quaiC = init_quai(gare1, 'C');

    LISTE * listeC;
    listeC = init_liste();
    LISTE * listeC_sortant;
    listeC_sortant = init_liste();
    

    //JOUEUR

    VOYAGEUR * joueur;
    joueur = init_voyageur_joueur(1 ,1 , 'A');


    //BUFFER

    //buffer zqsd
    char * p_mini_buffer;
    char mini_buffer;
    p_mini_buffer = &mini_buffer;

    //buffer couleur
    char * p_couleur_buffer1;
    char couleur_buffer1;
    p_couleur_buffer1 = &couleur_buffer1;
    char * p_couleur_buffer2;
    char couleur_buffer2;
    p_couleur_buffer2= &couleur_buffer2;
    char * p_couleur_buffer3;
    char couleur_buffer3;
    p_couleur_buffer3 = &couleur_buffer3;

    //buffer exit
    char * p_exit_buffer;
    char exit_buffer;
    p_exit_buffer = &exit_buffer;

    char touche;
////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////////MENU////
    clear_screen();
    set_cursor(0,0);
    int choix = menu(train_bas_ouest, gare1, quaiC, listeC);
    set_cursor(0,0);
    printf("\e[49m"); //couleur d'arrière plan par défault
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

    clock_t debut;
    clock_t fin;






    
 /////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE//////////GRANDE BOUCLE/////

    //MODE SANS VOYAGEUR (RAPIDE)
    if(choix == 0) {

    //initialisation du mode
    int vitesse = 10; //mode rapide
    int vitesse_train = 300;

         while (1) { //LA GRANDE BOUCLE

            debut = clock();

            fflush(stdout);
            
            //gerer les temps
            decompte_and_print_time(train_haut_ouest, vitesse);
            decompte_and_print_time(train_haut_est, vitesse);
            decompte_and_print_time(train_bas_ouest, vitesse);

            //gerer les train
            deplacement_train(train_haut_ouest, gare1,listeA, vitesse_train, vitesse);
            deplacement_train(train_haut_est, gare1, listeB, vitesse_train, vitesse);
            deplacement_train(train_bas_ouest, gare1, listeC, vitesse_train, vitesse);
            
            if(*p_exit_buffer == 'p') {
                pull_mini_buffer(p_exit_buffer);
                bye(gare1);
            }

            fin = clock();


            //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
            while(   (double)(fin - debut) / 1000  <  1 ) { //le petite while 

                touche = key_pressed();
                if(touche == 'p') {
                    add_mini_buffer(p_exit_buffer, touche);
                }

                fin = clock();
            } 
        }
    }



    //MODE COMPLET RAPIDE

    if(choix == 1) {

        //initialisation du mode
        int frequence_voyageur = 15000;
        int vitesse_voyageur = 10; 
        int vitesse = 10;
        int vitesse_train = 300;
        int frequence_voyageur_sortant = 100;

        while (1) { //LA GRANDE BOUCLE

            debut = clock();

            fflush(stdout);
            
            //gerer les temps
            decompte_and_print_time(train_haut_ouest, vitesse);
            decompte_and_print_time(train_haut_est, vitesse);
            decompte_and_print_time(train_bas_ouest, vitesse);

            //gerer les train
            deplacement_train(train_haut_ouest, gare1,listeA, vitesse_train, vitesse);
            deplacement_train(train_haut_est, gare1, listeB, vitesse_train, vitesse);
            deplacement_train(train_bas_ouest, gare1, listeC, vitesse_train, vitesse);


            //deplacement voyageur IA       
            deplacement_voyageur(listeA, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur(listeB, quaiB, vitesse_voyageur, p_couleur_buffer2);
            deplacement_voyageur(listeC, quaiC, vitesse_voyageur, p_couleur_buffer3);
            deplacement_voyageur_sortant(listeA_sortant, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur_sortant(listeB_sortant, quaiB, vitesse_voyageur, p_couleur_buffer2);
            deplacement_voyageur_sortant(listeC_sortant, quaiC, vitesse_voyageur, p_couleur_buffer3);

            genere_voyageur(listeA, quaiA, frequence_voyageur);
            genere_voyageur(listeB, quaiB, frequence_voyageur);
            genere_voyageur(listeC, quaiC, frequence_voyageur);
            genere_voyageur_sortant(listeA_sortant, quaiA, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeB_sortant, quaiB, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeC_sortant, quaiC, frequence_voyageur_sortant);
            
            gestion_voyageur(listeA, listeA_sortant, quaiA, train_haut_ouest);
            gestion_voyageur(listeB, listeB_sortant, quaiB, train_haut_est);
            gestion_voyageur(listeC, listeC_sortant, quaiC, train_bas_ouest);

            if(*p_exit_buffer == 'p') {
                pull_mini_buffer(p_exit_buffer);
                bye(gare1);
            }
            
            fin = clock();
            //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
            while(   (double)(fin - debut) / 1000  <  1 ) { //le petite while 

                    //rajouter le keypressed
                touche = key_pressed();
                if (touche == 'q' || touche == 's' || touche == 'd' || touche == 'z' || touche == ' ') {
                    add_mini_buffer(p_mini_buffer, touche);
                }

                if(touche == 'i' || touche == 'o') {
                    add_mini_buffer(p_couleur_buffer1, touche);
                    add_mini_buffer(p_couleur_buffer2, touche);
                    add_mini_buffer(p_couleur_buffer3, touche);
                }
                 if(touche == 'p') {
                    add_mini_buffer(p_exit_buffer, touche);
                }
                 fin = clock();
            
            }    
        }
    }


    //MODE AJUSTEE

    if(choix == 2) {

        //initialisation du mode
        int frequence_voyageur = 5000;
        int vitesse_voyageur = 10; 
        int vitesse = 10;
        int vitesse_train = 300;
        int frequence_voyageur_sortant = 50;

        while (1) { //LA GRANDE BOUCLE

            debut = clock();

            fflush(stdout);
            
            //gerer les temps
            decompte_and_print_time(train_haut_ouest, vitesse);
            decompte_and_print_time(train_haut_est, vitesse);
            decompte_and_print_time(train_bas_ouest, vitesse);

            //gerer les train
            deplacement_train(train_haut_ouest, gare1,listeA, vitesse_train, vitesse);
            deplacement_train(train_haut_est, gare1, listeB, vitesse_train, vitesse);
            deplacement_train(train_bas_ouest, gare1, listeC, vitesse_train, vitesse);

            //deplacement joueur
            deplacement_joueur(joueur, quaiA, train_haut_ouest,  p_mini_buffer);

            //deplacement voyageur IA      
            deplacement_voyageur(listeA, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur(listeB, quaiB, vitesse_voyageur, p_couleur_buffer2);
            deplacement_voyageur(listeC, quaiC, vitesse_voyageur, p_couleur_buffer3);
            deplacement_voyageur_sortant(listeA_sortant, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur_sortant(listeB_sortant, quaiB, vitesse_voyageur, p_couleur_buffer2);
            deplacement_voyageur_sortant(listeC_sortant, quaiC, vitesse_voyageur, p_couleur_buffer3);

            genere_voyageur(listeA, quaiA, frequence_voyageur);
            genere_voyageur(listeB, quaiB, frequence_voyageur);
            genere_voyageur(listeC, quaiC, frequence_voyageur);
            genere_voyageur_sortant(listeA_sortant, quaiA, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeB_sortant, quaiB, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeC_sortant, quaiC, frequence_voyageur_sortant);
            
            gestion_voyageur(listeA, listeA_sortant, quaiA, train_haut_ouest);
            gestion_voyageur(listeB, listeB_sortant, quaiB, train_haut_est);
            gestion_voyageur(listeC, listeC_sortant, quaiC, train_bas_ouest);

            if(*p_exit_buffer == 'p') {
                pull_mini_buffer(p_exit_buffer);
                bye(gare1);
            }
            
            fin = clock();
            //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
            while(   (double)(fin - debut) / 10000  <  1 ) { //le petite while 

                //rajouter le keypressed
             touche = key_pressed();
                if (touche == 'q' || touche == 's' || touche == 'd' || touche == 'z' || touche == ' ') {
                    add_mini_buffer(p_mini_buffer, touche);
                }

                if(touche == 'i' || touche == 'o') {
                    add_mini_buffer(p_couleur_buffer1, touche);
                    add_mini_buffer(p_couleur_buffer2, touche);
                    add_mini_buffer(p_couleur_buffer3, touche);
                }
                 if(touche == 'p') {
                    add_mini_buffer(p_exit_buffer, touche);
                }
            

                fin = clock();
            } 
        }       
    }



    //MODE COMPLET NOMALE (LENT)

    if(choix == 3) {

        int vitesse_voyageur = 60;
        int vitesse = 60;
        int frequence_voyageur = 12000;
        int vitesse_train = 300;
        int frequence_voyageur_sortant = 50;



        while (1) { //LA GRANDE BOUCLE

            debut = clock();

            fflush(stdout);
            
            //gerer les temps
            decompte_and_print_time(train_haut_ouest, vitesse);
            decompte_and_print_time(train_haut_est, vitesse);
            decompte_and_print_time(train_bas_ouest, vitesse);

            //gerer les train
            deplacement_train(train_haut_ouest, gare1,listeA, vitesse_train, vitesse);
            deplacement_train(train_haut_est, gare1, listeB, vitesse_train, vitesse);
            deplacement_train(train_bas_ouest, gare1, listeC, vitesse_train, vitesse);

            //deplacement voyageur IA
            deplacement_voyageur(listeA, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur(listeB, quaiB, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur(listeC, quaiC, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur_sortant(listeA_sortant, quaiA, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur_sortant(listeB_sortant, quaiB, vitesse_voyageur, p_couleur_buffer1);
            deplacement_voyageur_sortant(listeC_sortant, quaiC, vitesse_voyageur, p_couleur_buffer1);
            //pull_mini_buffer(p_couleur_buffer);

            genere_voyageur(listeA, quaiA, frequence_voyageur);
            genere_voyageur(listeB, quaiB, frequence_voyageur);
            genere_voyageur(listeC, quaiC, frequence_voyageur);
            genere_voyageur_sortant(listeA_sortant, quaiA, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeB_sortant, quaiB, frequence_voyageur_sortant);
            genere_voyageur_sortant(listeC_sortant, quaiC, frequence_voyageur_sortant);
            
            gestion_voyageur(listeA, listeA_sortant, quaiA, train_haut_ouest);
            gestion_voyageur(listeB, listeB_sortant, quaiB, train_haut_est);
            gestion_voyageur(listeC, listeC_sortant, quaiC, train_bas_ouest);

            if(*p_exit_buffer == 'p') {
                pull_mini_buffer(p_exit_buffer);
                bye(gare1);
            }


            
            fin = clock();
            //il s'écoule 10 ms entre le debut de "LA GRANDE BOUCLE" et la fin du " le petit while"
            while(   (double)(fin - debut) / 10000  <  1 ) { //le petite while 

                //rajouter le keypressed
            touche = key_pressed();
             if (touche == 'q' || touche == 's' || touche == 'd' || touche == 'z' || touche == ' ') {
                    add_mini_buffer(p_mini_buffer, touche);
                }
             if(touche == 'p') {
                    add_mini_buffer(p_exit_buffer, touche);
                }
            

                fin = clock();
            } 
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



