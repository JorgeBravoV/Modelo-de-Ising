set term png
set output 'hist_energy.png'

set term png size 1280, 480

b = 0.80
a = 0.60

set yrange[0:0.5]

plot 'hist_energy.txt' u 1:2 w boxes, 1.0/(b-a)