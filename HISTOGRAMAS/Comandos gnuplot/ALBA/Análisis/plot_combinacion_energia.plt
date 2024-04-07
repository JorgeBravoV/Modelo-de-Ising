set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=128\histogramas_analisis_energia.svg'

set term svg size 1280, 720

b = 1
a = 0

set xtics font ",16" 
set ytics font ",16"

set yrange[0:50]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Energia" font",18"


plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA 0,42\hist_energy.txt' u 1:2 w l lc rgb "blue" t'β 0,42', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA CRITICA\hist_energy.txt' u 1:2 w l lc rgb "dark-green" t'β CRITICA', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA 0,46\hist_energy.txt' u 1:2 w l lc rgb "magenta" t'β 0,46', \
