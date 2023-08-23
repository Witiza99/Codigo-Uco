#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "Ej4.eps"
set key right bottom
set xlabel "Bases de Datos"
set ylabel "Probabilidades y T"
set xrange[0:2]
set yrange[0:10]
plot 'datosfieldman.txt' using 2:3 t "Datos columna 2(Tipo de clasificador) frente a 3(T)" w l, 'datosfieldman.txt' using 2:4 t "Datos columna 2(Tipo de clasificador) frente a 4(Probabilidades)" w l
_end_
