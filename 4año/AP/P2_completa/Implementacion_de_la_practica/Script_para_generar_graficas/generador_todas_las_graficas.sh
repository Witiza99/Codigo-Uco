#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "Todas_las_graficas.eps"
set key right bottom
set xlabel "Numero de hilos"
set ylabel "Tiempo"
plot 'datos_p2_ijk_4000_paralelo.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ijk]" w l, 'datos_p2_ijk_4096_paralelo.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4096-ijk]" w l, 'datos_p2_ikj_4000_paralelo.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ikj]" w l, 'datos_p2_ikj_4096_paralelo.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4096-ikj]" w l
_end_
xdg-open "Todas_las_graficas.eps"