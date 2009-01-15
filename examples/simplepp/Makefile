PROGRAM=simplepp
CFLAGS=-O2 -g -Wall
LDFLAGS=
INCLUDES=-I../../include
LIBS=-L../.. -lrice -lm
SOURCES = $(shell find . -name '*.cpp')
CXX=g++

$(PROGRAM): $(SOURCES)
	$(CXX) $+ -o $@ $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(PROGRAM) *~
