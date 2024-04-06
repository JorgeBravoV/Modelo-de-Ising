set term svg
set output 'C:\Users\pablo\OneDrive\Escritorio\FISICA\Segundo Física\S2\Física computacional\Modelo-de-Ising\HISTERESIS\Graficas\L 128\histeresis_X.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Susceptibilidad' font ",18"


set xtics font ",16"
set ytics font ",16"

set xrange[0:1]

plot 'C:\Users\pablo\OneDrive\Escritorio\FISICA\Segundo Física\S2\Física computacional\Modelo-de-Ising\HISTERESIS\Ficheros de salida\L 128\X.txt' u 1:2 w l lc rgb "red" notitle,\