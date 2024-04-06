set term svg
set output 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTERESIS\Graficas\L 128\histeresis1_magnetizacion_media_absoluta_termalizado.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Magnetizacion media absoluta' font ",18"


set xtics font ",16"
set ytics font ",16"

set xrange[0:1]

plot 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTERESIS\Ficheros de salida\L 128\Error_magnetizacion.txt' u 1:2 w l lc rgb "purple" notitle ,\
'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTERESIS\Ficheros de salida\L 128\Error_magnetizacion.txt' u 1:2:3 w errorbars pt 7 lc rgb "red" ps 0.4 notitle