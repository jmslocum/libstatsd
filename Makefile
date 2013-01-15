CC = gcc
CFLAGS = --std=gnu99 -Wall
OBJECTS = statsd.o batch.o
LIBRARY = libstatsd
LIB_VERSION = 1.0.0
OS = unix

ifdef DEBUG
CFLAGS += -ggdb
else
CFLAGS += -O3
endif

all : lib cli

ifeq ($(OS), unix)
CFLAGS += -fPIC

lib : $(OBJECTS)
	$(CC) -shared -W1,-soname,$(LIBRARY).so.1 -o $(LIBRARY).so.$(LIB_VERSION) $(OBJECTS)
	-ln -s $(LIBRARY).so.$(LIB_VERSION) $(LIBRARY).so

else
CFLAGS += -D ADD_EXPORTS

lib: $(OBJECTS)
	$(CC) -s -shared -mwindows -o $(LIBRARY).dll $(OBJECTS) -lWs2_32

endif

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean : 
	-rm *.o
	-rm *.gch
	-rm $(LIBRARY).so*
	-rm statsd-cli

cli : 
	$(CC) $(CFLAGS) statsd-cli.c -L./ -lstatsd -o statsd-cli

install : 

uninstall : 

.PHONY: clean install uninstall
