# About
moon-earth-sun is an example LaTeX project that produces a quasi-scientific paper PDF with your name on it! This project is meant to be a pet example of how automation could be used to generate content-rich documents. 

# Contents
This project consists of:
- A makefile, which compiles all the sources to produce paper.pdf, the final product
- Some C source code, which contains the model of the Moon, Earth Sun system
- A gnuplot script `plot.p' which generates the plot of the Earth and Moon's path
- A python script, which generates the paper.tex source code used to create the paper.pdf file

# Building
To create paper.pdf type `make' and press ENTER.
You'll notice a lot of extra files are produced, to delete everything that was generated from the make script run `make clean'

This project may be updated, to check for new updates, run `git pull'

# Support
This software has been tested to work on:
- Debian “Jessie” 8.5
- Mac OS X “El Capitan” 10.11.6

# License
moon-earth-sun is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

moon-earth-sun is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with moon-earth-sun.  If not, see <http://www.gnu.org/licenses/>.