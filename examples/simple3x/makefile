# Miry, May 1999

BASEDIR = ../../

simple3x: simple3x.o 
	gcc -o simple3x simple3x.o ${BASEDIR}lib/rice.a -lpc -lm 
 
simple3x.o: simple3x.c 
	copy simple3x.lnk rice.lnk 
	copy simple3x.cod rice.cod 
	gcc -c -I${BASEDIR}include -I${BASEDIR}upgrade -I. -DRICE_UPGRADE simple3x.c 
	del rice.lnk 
	del rice.cod 

clean:
	rm simple3x.o
	rm simple3x.exe
