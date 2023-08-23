#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "ErroresEj6.eps"
set key right bottom
set xlabel "Bases de Datos"
set ylabel "CCR"
plot 'Errores2.txt' using 2:3 t "Datos columna 2(Bases de datos) frente a 3(Error SVM)" w l, 'Errores2.txt' using 2:4 t "Datos columna 2(Bases de datos) frente a 4(ErrorK-vecinos)" w l
_end_
