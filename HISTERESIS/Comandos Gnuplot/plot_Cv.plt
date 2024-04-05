set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_Cv.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Calor especifico' font ",18"

set xtics font ",16"
set ytics font ",16"

set xrange[0:1]
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Ficheros de salida\Cv.txt' u 1:2 w l lc rgb "blue" t'CALOR ESPECIFICO',\
