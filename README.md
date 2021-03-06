# About
moon-earth-sun is an example LaTeX project that produces a quasi-scientific paper PDF with your name on it! This project is meant to be a pet example of how automation could be used to generate content-rich documents. 

# Contents
This project consists of:
- A makefile, which compiles all the sources to produce paper.pdf, the final product
- Some C source code, which contains the model of the Moon, Earth, Sun system
- A gnuplot script _plot.p_ which generates the plot of the Earth and Moon's path
- A python script, which generates the paper.tex source code used to create the paper.pdf file

# Dependencies 
moon-earth-sun requires the following software to be installed for the build process to complete
- make
- gcc
- python
- latex
- gnuplot

# Building
To create paper.pdf type _make_ and press ENTER.
You'll notice that a lot of extra files are produced, to delete everything that was generated from the make script run _make clean_

This project may be updated, to check for new updates, run _git pull_

# Support
This software has been tested to work on:
- Debian “Jessie” 8.5
- Mac OS X “El Capitan” 10.11.6

Although this software should compile on other operating systems without editing any files in this project, no guarantee will be made. 

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