set term png
set output 'energy.png'

set term png size 1280, 480
set xlabel 't'
set ylabel 'x'

set key outside right center

set xrange[0:500]
set yrange[-1000:10]
plot 'energy.txt' u 1:2 w l t'E(t)',\
