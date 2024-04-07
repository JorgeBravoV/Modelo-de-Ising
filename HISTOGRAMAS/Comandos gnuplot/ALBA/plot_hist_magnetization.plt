set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=64\BETA 0,46\hist_magnetization.svg'

set term svg size 1280, 720

b = 1
a = -1

set xtics font ",16" 
set ytics font ",16"

set yrange[0:14]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Magnetización" font",18"
set xlabel "β" font",18"
plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=64\BETA 0,46\hist_magnetization.txt' u 1:2 w boxes notitle

