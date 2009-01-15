# Miry, May 1999

BASEDIR = ../../

simplepp: simplepp.o 
	gxx -o simplepp simplepp.o ${BASEDIR}lib/rice.a -lpc -lm 

simplepp.o: simplepp.cpp
	gcc -c -I${BASEDIR}include simplepp.cpp

clean:
	rm simplepp.o
	rm simplepp.exe
