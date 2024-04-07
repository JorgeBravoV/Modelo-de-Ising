set term svg
set output 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Gráficas\L=128\histogramas_analisis_magnetizacion.svg'

set term svg size 1280, 720

b = 1
a = -1

set xtics font ",16" 
set ytics font ",16"

set yrange[0:30]
set xrange[a:b]

set style line 1 lw 2

set ylabel "Magnetización" font",18"


plot 'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA 0,42\hist_magnetization.txt' u 1:2 w l lc rgb "blue" t'β 0,42', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA CRITICA\hist_magnetization.txt' u 1:2 w l lc rgb "dark-green" t' β critica', \
'C:\Users\USUARIO\Documents\UNIZAR\Segundo\Segundo cuatri\Física Computacional\Nueva carpeta\Modelo-de-Ising\HISTOGRAMAS\Ficheros de salida\L=128\BETA 0,46\hist_magnetization.txt' u 1:2 w l lc rgb "magenta" t' β 0,46'
