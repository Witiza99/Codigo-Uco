#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoquicksort.eps"
set key right bottom
set xlabel "Valores de N"
set ylabel "Tiempo"
plot 'valores.txt' using 1:2 t "Datos columna 1(N) frente a 2(tiempos reales)", 'valores.txt' using 1:3 t "Datos columna 1(N) frente a 3(tiempos estimados)" w l
_end_
