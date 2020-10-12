all : compile exec


fct_cursor.o : fct_cursor.c fct_cursor.h
	gcc -Wall -c fct_cursor.c

fct_fichier.o : fct_fichier.c fct_fichier.h
	gcc -Wall -c  fct_fichier.c



testechappement.o : testechappement.c fct_cursor.h fct_fichier.h
	gcc -Wall -c testechappement.c



compile : fct_fichier.o fct_cursor.o testechappement.o
	gcc -Wall -o testechappement.exe fct_fichier.o fct_cursor.o testechappement.o


exec :
	./testechappement.exe

clean : 	
	rm *.o -v