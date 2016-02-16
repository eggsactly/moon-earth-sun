CC=gcc
CFLAGS=-c -Wall
IFLAGS=-I.
LFLAGS=-lm

SOURCES=moon-earth-sun.c n-body.c
OBJECTS=moon-earth-sun.o n-body.o
HEADERS=n-body.h
EXECUTABLE=moon-earth-sun

$(EXECUTABLE): $(OBJECTS)
	$(CC) -g -o $(EXECUTABLE) $(OBJECTS) $(IFLAGS) $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -g $(CFLAGS) -o $@ $< $(IFLAGS) $(LFLAGS)

clean:
	rm -rf *o $(EXECUTABLE)  

