set term png
set output 'hist_energy.png'

set term png size 1280, 480

b = 1
a = 0

set yrange[0:1]

plot 'hist_energy.txt' u 1:2 w boxes, 1.0/(b-a)