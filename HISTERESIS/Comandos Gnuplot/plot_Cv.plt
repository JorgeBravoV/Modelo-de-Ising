set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_Cv.svg

set term svg size 1280, 480
set xlabel 'β'
set ylabel 'Calor especifico'

set key outside right center


set xrange[0:1]
set yrange[-100:20000]
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Ficheros de salida\Cv.txt' u 1:2 w l lc rgb "blue" t'CALOR ESPECIFICO',\