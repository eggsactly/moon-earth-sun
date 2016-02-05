CC=gcc
CFLAGS=-c -Wall
IFLAGS=-I. -I/usr/include 
LFLAGS=-L/usr/lib -lm  

SOURCES=n-body.c
OBJECTS=n-body.o
HEADERS=n-body.h
EXECUTABLE=n-body

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(IFLAGS) $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< $(IFLAGS) $(LFLAGS)

clean:
	rm -rf *o $(EXECUTABLE)  

