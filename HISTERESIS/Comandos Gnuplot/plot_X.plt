set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_energia_media.svg'

set term svg size 1280, 480
set xlabel 'beta'
set ylabel 'energia media'

set key outside right center

set xrange[0:1]
set yrange[-1.2:0.1]
plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Ficheros de salida\e_medio.txt' u 1:2 w l lc rgb "#008000" t'ENERGIA MEDIA',\