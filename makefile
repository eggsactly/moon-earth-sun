# Copyright (c) 2014 - 2016 W.A. Garrett Weaver

# This file is part of moon-earth-sun.
    
# moon-earth-sun is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
    
# moon-earth-sun is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with moon-earth-sun.  If not, see <http://www.gnu.org/licenses/>.

CC=gcc
CFLAGS=-c -Wall
IFLAGS=-I.
LFLAGS=-lm

EXECUTABLE=moon-earth-sun

paper.pdf: paper.tex
	pdflatex paper.tex
	pdflatex paper.tex

paper.tex: moon-earth-sun.tex
	python generate-latex.py

moon-earth-sun.tex: output.txt
	gnuplot plot.p

output.txt: $(EXECUTABLE)
	@echo "Running simulation, please wait, this will take a minute."
	./$(EXECUTABLE) -o output.txt -s 1.0 -t 31536000 -m 3600

$(EXECUTABLE): moon-earth-sun.o n-body.o
	$(CC) -o $(EXECUTABLE) moon-earth-sun.o n-body.o $(IFLAGS) $(LFLAGS)

moon-earth-sun.o: moon-earth-sun.c n-body.h
	$(CC) $(CFLAGS) -o moon-earth-sun.o moon-earth-sun.c $(IFLAGS) $(LFLAGS)

n-body.o: n-body.c n-body.h
	$(CC) $(CFLAGS) -o n-body.o n-body.c $(IFLAGS) $(LFLAGS)

.PHONY: clean
clean:
	rm -rf *o $(EXECUTABLE) output.txt *.pdf *.eps *.aux *.log *.tex *.gz

