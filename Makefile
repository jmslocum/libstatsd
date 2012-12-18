CC = gcc
CFLAGS = --std=gnu99 -Wall -ggdb -fPIC
OBJECTS = statsd.o batch.o
LIBRARY = libstatsd
LIB_VERSION = 1.0.0

all : lib

lib : $(OBJECTS)
	$(CC) -shared -W1,-soname,$(LIBRARY).so.1 -o $(LIBRARY).so.$(LIB_VERSION) $(OBJECTS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean : 
	-rm *.o
	-rm *.gch
	-rm $(LIBRARY).so*

install : 

uninstall : 

.PHONY: clean install uninstall
