#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "Grafica_todas.eps"
set key right bottom
set xlabel "Numero de hilos"
set ylabel "Tiempo"
set yrange [-500:3500]

plot 'datos_ijk.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ijk]" w l, 'datos_jki.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-jki]" w l, 'datos_ikj.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ikj]" w l
#plot 'datos_ijk.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ijk]" w l,
#plot 'datos_jki.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-jki]" w l,
#plot 'datos_ikj.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales) [4000-ikj]" w l,
_end_
xdg-open "Grafica_todas.eps"