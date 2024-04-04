set term png
set output 'histeresis_energia_media.png'

set term png size 1280, 480
set xlabel 'beta'
set ylabel 'energia media'

set key outside right center

set xrange[0:2]
set yrange[0:1.2]
plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Ficheros de salida\e_medio.txt' u 1:2 w l t'ENERGIA MEDIA',\