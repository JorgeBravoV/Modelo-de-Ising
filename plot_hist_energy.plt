set term png
set output 'hist_energy.png'

set term png size 1080, 720

b = 0.77
a = 0.66


set yrange[0:50]
set xrange[a:b]

set xtics font ",12"
set ytics font ",12"

set ylabel "Frecuencia"
set xlabel "β"
plot 'hist_energy.txt' u 1:2 w boxes lc rgb "#008000" notitle
