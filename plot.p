set term svg
set output "moon-earth-sun.svg"
plot "output.txt" using 2:3 title 'Lunar Path' w lines,\
"output.txt" using 4:5 title 'Earth Path' w lines