#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "datos_p2_ijk_4096_paralelo.eps"
set key right bottom
set xlabel "Numero de hilos"
set ylabel "Tiempo"
plot 'datos_p2_ijk_4096_paralelo.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales)" w l
_end_
xdg-open "datos_p2_ijk_4096_paralelo.eps"