#!/bin/bash
for (( i = 1; i < 26; i++ )); do
  cat << _end_ | gnuplot
  set terminal png
  set output "./grafics/grafica$i.png"
  set key right bottom
  set xlabel "iteracion"
  set ylabel "fitness"
  plot './results/testFunc$i.txt' using 0:1 t "currentfirst" w l, './results/testFunc$i.txt' using 0:2 t "bestfirst" w l, './results/testFunc$i.txt' using 0:3 t "currentbest" w l, './results/testFunc$i.txt' using 0:4 t "bestbest" w l
_end_
done
