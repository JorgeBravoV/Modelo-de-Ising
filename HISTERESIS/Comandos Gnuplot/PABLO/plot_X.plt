set term svg
set output 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTERESIS\Graficas\L 16\histeresis1_X.svg'

set term svg size 1280, 480
set xlabel 'β' font ",18"
set ylabel 'Susceptibilidad' font ",18"


set xtics font ",16"
set ytics font ",16"

set xrange[0:1]

plot 'C:\Users\pgadm\Downloads\Modelo-de-Ising-main\Modelo-de-Ising\HISTERESIS\Ficheros de salida\L 16\X.txt' u 1:2 w l lc rgb "red" notitle,\