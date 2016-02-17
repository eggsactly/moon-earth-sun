CC=gcc
CFLAGS=-c -Wall
IFLAGS=-I.
LFLAGS=-lm

EXECUTABLE=moon-earth-sun

moon-earth-sun.svg: output.txt
	gnuplot plot.p

output.txt: $(EXECUTABLE)
	echo "Running simulation, please wait, this will take a minute."
	./$(EXECUTABLE) -o output.txt -s 1.0 -t 31536000 -m 3600

$(EXECUTABLE): moon-earth-sun.o n-body.o
	$(CC) -o $(EXECUTABLE) moon-earth-sun.o n-body.o $(IFLAGS) $(LFLAGS)

moon-earth-sun.o: moon-earth-sun.c n-body.h
	$(CC) $(CFLAGS) -o moon-earth-sun.o moon-earth-sun.c $(IFLAGS) $(LFLAGS)

n-body.o: n-body.c n-body.h
	$(CC) $(CFLAGS) -o n-body.o n-body.c $(IFLAGS) $(LFLAGS)

clean:
	rm -rf *o $(EXECUTABLE) output.txt *.svg *.pdf

