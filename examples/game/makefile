# Miry, May 1999

BASEDIR = ../../

game: game.o 
	gcc -o game game.o ${BASEDIR}lib/rice.a -lpc -lm
 
game.o: game.c 
	gcc -c -I${BASEDIR}include game.c 

clean:
	rm game.o
	rm game.exe
