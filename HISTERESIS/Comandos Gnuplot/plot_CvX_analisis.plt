set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_X_analisis.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Calor especifico' font ",18"

set xtics font ",16"
set ytics font ",16"

set xrange[0:1]
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\X1.txt' u 1:2 w l lc rgb "blue" t'configuracion 1', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\X2.txt' u 1:2 w l lc rgb "dark-green" t'configuracion 2', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\X3.txt' u 1:2 w l lc rgb "pink" t'configuracion 3', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\X4.txt' u 1:2 w l lc rgb "red" t'configuracion 4', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\X5.txt' u 1:2 w l lc rgb "purple" t'configuracion 5',


