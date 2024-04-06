set term svg
set output 'E:\USUARIO (NO TOCAR)\Desktop\UNIVERSIDAD\SEGUNDO\COMPUTACIONAL\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=16\hist_magnetization.svg'

set term svg size 1280, 720

b = 1
a = -1

set xtics font ",16" 
set ytics font ",16"

set yrange[0:3]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",18"
set xlabel "Magnetización" font",18"
plot 'E:\USUARIO (NO TOCAR)\Desktop\UNIVERSIDAD\SEGUNDO\COMPUTACIONAL\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=16\hist_magnetization.txt' u 1:2 w boxes notitle

