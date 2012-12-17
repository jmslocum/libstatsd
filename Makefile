CC = gcc
CFLAGS = --std=gnu99 -Wall -ggdb
OBJECTS = statsd.o

all : $(OBJECTS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean : 
	-rm *.o
	-rm *.gch

