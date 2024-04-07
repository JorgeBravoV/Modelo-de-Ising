set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=128\BETA CRITICA\hist_energy.svg'

set term svg size 1280, 720

b = 0.77
a = 0.66

set xtics font ",16" 
set ytics font ",16"

set yrange[0:80]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",18"
set xlabel "β" font",18"
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA CRITICA\hist_energy.txt' u 1:2 w boxes lc rgb "#008000" notitle
