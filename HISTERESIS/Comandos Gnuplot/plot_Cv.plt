set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Graficas\histeresis_Cv.svg'

set term svg size 1280, 480
set xlabel 'β'
set ylabel 'Calor especifico'

set key outside right center


set xrange[0:1]
<<<<<<< HEAD

plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTERESIS\Ficheros de salida\Cv.txt' u 1:2 w l lc rgb "blue" t'CALOR ESPECIFICO',\
=======
set yrange[-100:20000]
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTERESIS\Ficheros de salida\Cv.txt' u 1:2 w l lc rgb "blue" t'CALOR ESPECIFICO',\
>>>>>>> 0a0ca7c4060d206879c1a4527fc8a70731572207
