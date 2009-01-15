# Miry, May 1999

BASEDIR = ../../

minimal: minimal.o 
	gcc -o minimal minimal.o ${BASEDIR}lib/rice.a -lpc -lm 
 
minimal.o: minimal.c 
	gcc -c -I${BASEDIR}include minimal.c 

clean:
	rm minimal.o
	rm minimal.exe
