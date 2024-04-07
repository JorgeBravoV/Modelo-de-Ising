set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=16\BETA 0,46\hist_energy.svg'

set term svg size 1280, 720

b = 0.94
a = 0.62

set xtics font ",16" 
set ytics font ",16"

set yrange[0:13]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",18"
set xlabel "β" font",18"
plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=16\BETA 0,46\hist_energy.txt' u 1:2 w boxes lc rgb "#008000" notitle
