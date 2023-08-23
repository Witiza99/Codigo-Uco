for (( i = 1; i < 26; i++ )); do
  ./prueba ../Github/cec2005benchmark-master/inst/extdata/ $i > ./results/testFunc$i.txt
done
