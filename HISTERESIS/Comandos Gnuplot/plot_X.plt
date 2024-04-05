set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_X.svg'

set term svg size 1280, 480
set xlabel 'β'
set ylabel 'Susceptibilidad'

set key outside right center

set xrange[0:1]

plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Ficheros de salida\X.txt' u 1:2 w l lc rgb "red" t'SUSCEPTIBILIDAD',\