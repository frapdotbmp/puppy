CC=gcc
LDFLAGS=-lxcb -lxcb-keysyms -lxcb-ewmh -lxcb-util
PREFIX=/usr/local
INC=-I include/

default: puppy

puppy: puppy.c
	$(CC) $(INC) -g puppy.c func.c ewmh.c cursor.c -o puppy $(LDFLAGS)

install: puppy 
	cp puppy $(PREFIX)/bin/

clean: puppy
	rm -f puppy
