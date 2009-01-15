PROGRAM=minimal
CFLAGS=-O2 -g -Wall
LDFLAGS=
INCLUDES=-I../../include
LIBS=-L../.. -lrice -lm
SOURCES = $(shell find . -name '*.c')
CC=gcc

$(PROGRAM): $(SOURCES)
	$(CC) $+ -o $@ $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(PROGRAM) *~
