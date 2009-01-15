PROGRAM=ricefuzzy
CFLAGS=-O2 -g -Wall
LDFLAGS=
INCLUDES=-I../../include
LIBS=-L../.. -lrice -lm
SOURCES = $(shell find . -name '*.c')
CC=gcc

$(PROGRAM): $(SOURCES)
	$(CC) $+ -o $@ $(CFLAGS) -DTEST_FUZZY $(INCLUDES) $(LDFLAGS) $(LIBS)

test: $(PROGRAM)
	LD_LIBRARY_PATH="../..:$$LD_LIBRARY_PATH" ./$(PROGRAM)

clean:
	rm -f *.o $(PROGRAM) *~
