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
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

set term epslatex
set output "moon-earth-sun.tex"
plot "output.txt" using 2:3 title 'Lunar Path' w lines,\
"output.txt" using 4:5 title 'Earth Path' w lines