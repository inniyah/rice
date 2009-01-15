NAME=rice
MAJOR=0
MINOR=0d1

all: lib$(NAME).so lib$(NAME).a

SOURCES = $(shell find src -name '*.c')
SHARED_OBJS = $(SOURCES:.c=.shared.o)
STATIC_OBJS = $(SOURCES:.c=.static.o)

CFLAGS=-O2 -g -Wall
EXTRA_CFLAGS=
STATIC_CFLAGS= $(CFLAGS) $(EXTRA_CFLAGS)
SHARED_CFLAGS= $(CFLAGS) $(EXTRA_CFLAGS) -fPIC
LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined

lib$(NAME).so.$(MAJOR).$(MINOR): $(SHARED_OBJS)
	g++ $(LDFLAGS) -shared \
		-Wl,-soname,lib$(NAME).so.$(MAJOR) \
		-o lib$(NAME).so.$(MAJOR).$(MINOR) \
		$+ -o $@ $(LIBS)

lib$(NAME).so: lib$(NAME).so.$(MAJOR).$(MINOR)
	rm -f $@.$(MAJOR)
	ln -s $@.$(MAJOR).$(MINOR) $@.$(MAJOR)
	rm -f $@
	ln -s $@.$(MAJOR) $@

lib$(NAME).a: $(STATIC_OBJS)
	ar cru $@ $+

%.o: %.cpp
	g++ -o $@ -c $+ $(CFLAGS)

%.o: %.c
	gcc -o $@ -c $+ $(CFLAGS)

%.so : %.o
	g++ $(LDFLAGS) -shared $^ -o $@

%.shared.o: %.cpp
	g++ -o $@ -c $+ $(SHARED_CFLAGS)

%.shared.o: %.c
	gcc -o $@ -c $+ $(SHARED_CFLAGS)

%.static.o: %.cpp
	g++ -o $@ -c $+ $(STATIC_CFLAGS)

%.static.o: %.c
	gcc -o $@ -c $+ $(STATIC_CFLAGS)

clean:
	rm -f $(SHARED_OBJS)
	rm -f $(STATIC_OBJS)
	rm -f $(FIXED_OBJS)
	rm -f $(STATIC_FIXED_OBJS)
	rm -f *.so *.so* *.a

DESTDIR=

install:
	mkdir -p "$(DESTDIR)/usr/lib/"
	cp -a *.a "$(DESTDIR)/usr/lib/"
	cp -a *.so* "$(DESTDIR)/usr/lib/"
	mkdir -p "$(DESTDIR)/usr/include/"
	cp -a include/* "$(DESTDIR)/usr/include/"
