set term svg
set output 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=16\BETA 0,42\hist_magnetization.svg'

set term svg size 1280, 720

b = 1
a = -1

set xtics font ",16" 
set ytics font ",16"

set yrange[0:1]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",18"
set xlabel "Magnetización" font",18"
plot 'C:\Users\joelg\OneDrive\Escritorio\Computacional\Trabajo Modelo de Ising\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=16\BETA 0,42\hist_magnetization.txt' u 1:2 w boxes notitle

