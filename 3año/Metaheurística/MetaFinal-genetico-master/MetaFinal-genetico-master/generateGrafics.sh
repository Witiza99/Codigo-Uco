#!/bin/bash
for (( i = 1; i < 26; i++ )); do
  cat << _end_ | gnuplot
  set terminal png
  set output "./grafics/grafica$i.png"
  set key right bottom
  set xlabel "iteracion"
  set ylabel "fitness"
  plot './results/testFunc$i.txt' using 0:1 t "currentGA" w l, './results/testFunc$i.txt' using 0:2 t "bestGA" w l
_end_
done
