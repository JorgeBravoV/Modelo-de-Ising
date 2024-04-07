set term svg
set output 'C:\Users\pablo\OneDrive\Escritorio\FISICA\Segundo Física\S2\Física computacional\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=64\BETA 0,46\hist_magnetization.svg'

set term svg size 1280, 720

b = 1
a = -1

set xtics font ",45" 
set ytics font ",45"

set yrange[0:3]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Frecuencia" font",45"
set xlabel "β" font",45"
plot 'C:\Users\pablo\OneDrive\Escritorio\FISICA\Segundo Física\S2\Física computacional\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=64\BETA 0,46\hist_magnetization.txt' u 1:2 w boxes notitle

