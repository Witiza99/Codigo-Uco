variablep=$(echo "$(./OMP_ijk_bucle_externo.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variablep"
variablep2=$(echo "2")
echo "$variablep2"

if (( $(echo "$variablep < $variablep2" |bc -l) )); then
	echo "hila"
else
	echo "holo"
fi