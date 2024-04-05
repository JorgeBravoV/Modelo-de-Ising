set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_Cv_analisis.svg'

set term svg size 1280, 480

set xtics font ",24"
set ytics font ",26"

set key left top font ",24"

set xrange[0:0.8]
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\Cv1.txt' u 1:2 w l lc rgb "blue" t'conf. 1', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\Cv2.txt' u 1:2 w l lc rgb "dark-green" t'conf. 2', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\Cv3.txt' u 1:2 w l lc rgb "magenta" t'conf. 3', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\Cv4.txt' u 1:2 w l lc rgb "red" t'conf. 4', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Analisis\Cv5.txt' u 1:2 w l lc rgb "orange" t'conf. 5',


