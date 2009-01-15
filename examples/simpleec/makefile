# Miry, May 1999

BASEDIR = ../../

simpleec: simpleec.o 
	gcc -o simpleec simpleec.o ${BASEDIR}lib/rice.a -lpc -lm 
 
simpleec.o: simpleec.c 
	gcc -c -I${BASEDIR}include simpleec.c 

clean:
	rm simpleec.o
	rm simpleec.exe
