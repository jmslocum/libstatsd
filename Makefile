CC = gcc
CFLAGS = --std=gnu99 -Wall
OBJECTS = statsd.o
LIBRARY = libstatsd
LIB_VERSION = 0.0.1
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

cli : 
	$(CC) $(CFLAGS) statsd-cli.c -L./ -lstatsd -o statsd-cli

clean : 
	-rm *.o
	-rm *.gch
	-rm $(LIBRARY).so*
	-rm statsd-cli

install : 
	install $(LIBRARY).so.$(LIB_VERSION) /usr/local/lib
	cp -d $(LIBRARY).so /usr/local/lib
	cp statsd.h /usr/local/include
	install statsd-cli /usr/local/bin
	ldconfig

uninstall : 
	rm /usr/local/lib/$(LIBRARY).so*
	rm /usr/local/bin/statsd-cli
	rm /usr/local/include/statsd.h
	ldconfig -n /usr/local/lib

.PHONY: clean install uninstall
