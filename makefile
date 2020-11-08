all : compile exec


fct_cursor.o : fct_cursor.c fct_cursor.h
	gcc -Wall -c fct_cursor.c

fct_fichier.o : fct_fichier.c fct_fichier.h
	gcc -Wall -c  fct_fichier.c

fct_time.o : fct_time.c fct_time.h
	gcc -Wall -c fct_time.c

fct_voyageur.o : fct_voyageur.c fct_voyageur.h
	gcc -Wall -c fct_voyageur.c



projet.o : projet.c fct_cursor.h fct_fichier.h fct_time.h fct_voyageur.h
	gcc -Wall -c projet.c




compile : fct_fichier.o fct_cursor.o fct_time.o fct_voyageur.o projet.o
	gcc -Wall -o projet.exe fct_fichier.o fct_cursor.o fct_time.o fct_voyageur.o projet.o


exec :
	./projet.exe

clean : 	
	rm *.o -v
	rm *.exe -v