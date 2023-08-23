#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "ErroresEj3.eps"
set key right bottom
set xlabel "Bases de Datos"
set ylabel "CCR"
plot 'Errores.txt' using 2:3 t "Datos columna 2(Bases de datos) frente a 3(Error Arboles)" w l, 'Errores.txt' using 2:4 t "Datos columna 2(Bases de datos) frente a 4(ErrorSVM)" w l, 'Errores.txt' using 2:5 t "Datos columna 2(Bases de datos) frente a 5(K-vecinos)" w l
_end_
