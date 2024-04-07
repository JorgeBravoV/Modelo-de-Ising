set term svg
set output 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=128\BETA 0,46\hist_magnetization.svg'

set term svg size 1280, 720

b = -0.745
a = -0.875

set xtics font ",16" 
set ytics font ",16"

set yrange[0:27]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",18"
set xlabel "Magnetizacion" font",18"
plot 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA 0,46\hist_magnetization.txt' u 1:2 w boxes notitle

