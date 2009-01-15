# Miry, May 1999

BASEDIR = ../../

simple: simple.o 
	gcc -o simple simple.o ${BASEDIR}lib/rice.a -lpc -lm 
 
simple.o: simple.c 
	gcc -c -I${BASEDIR}/include simple.c 

clean:
	rm simple.o
	rm simple.exe
