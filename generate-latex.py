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

import subprocess
import getpass
import sys

username = getpass.getuser()
# Get the user's full name
task = subprocess.Popen("finger $(whoami) | grep \"Name\" | awk '{split($0,a,\"Name:\"); print a[2]}' | sed -e 's/^[ \t]*//'", shell=True, stdout=subprocess.PIPE)
data = task.stdout.read()
assert task.wait() == 0

# Write the paper (in LaTeX format) with the current data and the users name
f = open('paper.tex', 'w')

f.write("\\documentclass{article}");
f.write("\\usepackage{graphicx}");
f.write("\\begin{document}\\title{Using N-Body Systems to Model the Solar System}\\date{\\today}");
f.write("\\author{");
f.write(data.rstrip());
f.write("}");
f.write("\\maketitle");
f.write("");
f.write("\\section{Abstract}");
f.write("In this experiment the path of the moon and earth were shown to move around each other as they orbited the sun.");
f.write("");
f.write("\\section{Introduction}");
f.write("N-Body systems are use to model the gravitational effects bodies of mass have on each other. In a simulation the forces on a body, due to every other body in the system, are calculated for each body in the system. For each step of the simulation the speed and position of each body is updated. The forces on a body \\emph{i} can be modeled by the following equation:");
f.write("\\begin{equation}");
f.write("   \\label{eq:nbodyforces}");
f.write("    \\vec{F}_i = \\sum_{n} G \\cdot \\frac{m_i \\cdot m_n}{\\vec{d}_{n-i}}");
f.write("\end{equation}");
f.write("");
f.write("\\section{Procedure}");
f.write("A model was created in the C programming language, which followed the formula in equation \\ref{eq:nbodyforces}, to calculate the forces acting on each body. Masses and velocity vectors of the Moon, Earth and Sun, from the NASA Space Science Data Coordinate Archive, were programmed into the model.");
f.write("");
f.write("\\newpage");
f.write("\\section{Results}");
f.write("The result of the simulation were plotted and below is the result. Purple is the path of the Moon, teal is the path of the Earth.\\\\");
f.write("\\begin{figure}[h!]");
f.write("  \\centering");
f.write("    \\includegraphics[width=\\textwidth]{moon-earth-sun}");
f.write("    \\caption{Paths of the Earth and Moon around the Sun}");
f.write("\\end{figure}");
f.write("");
f.write("\\section{Conclusion}");
f.write("Experimenting with N-Body systems shows that the moon does not rigorously orbit the Earth as the Earth orbits the Sun, rather the Moon and Earth interweave around each other as both orbit the sun. Instead of calling the Moon a satellite of the Earth it is more accurate to call the Moon and Earth a double-planet system.");
f.write("");
f.write("\\end{document}");

f.closed;