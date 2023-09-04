CC=gcc
LDFLAGS=-lxcb -lxcb-util -lxcb-ewmh
PREFIX=/usr/local
INC=-I include/

default: puppy

puppy: puppy.c
	$(CC) $(INC) -g puppy.c util.c -o puppy $(LDFLAGS)

install: puppy 
	cp puppy $(PREFIX)/bin/

clean: puppy
	rm -f puppy
