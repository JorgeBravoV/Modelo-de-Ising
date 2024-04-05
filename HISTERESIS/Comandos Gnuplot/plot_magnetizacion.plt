set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_magnetizacion_media_absoluta.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Magnetizacion media absoluta' font ",18"


set xtics font ",16"
set ytics font ",16"

set xrange[0:1]

plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Ficheros de salida\m_medio_absoluto.txt' u 1:2 w l lc rgb "purple" notitle ,\