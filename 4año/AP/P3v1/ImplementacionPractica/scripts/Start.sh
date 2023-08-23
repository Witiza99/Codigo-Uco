NHilos=(2 4 8 16)

rm EjercicioCompleto.txt
rm datos_ijk.txt
rm datos_jki.txt
rm datos_ikj.txt

gcc OMP_ijk_bucle_externo.c -fopenmp -o OMP_ijk_bucle_externo.exe
gcc OMP_ijk_bucle_interno.c -fopenmp -o OMP_ijk_bucle_interno.exe
gcc OMP_jki_bucle_externo.c -fopenmp -o OMP_jki_bucle_externo.exe
gcc OMP_jki_bucle_interno.c -fopenmp -o OMP_jki_bucle_interno.exe
gcc OMP_ikj_bucle_externo.c -fopenmp -o OMP_ikj_bucle_externo.exe
gcc OMP_ikj_bucle_interno.c -fopenmp -o OMP_ikj_bucle_interno.exe

echo "Ejercicio Completo:" >> EjercicioCompleto.txt

###ijk
echo "OMP_ijk_bucle_externo:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_ijk_bucle_externo"
variable1=$(echo "$(./OMP_ijk_bucle_externo.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable1:" >> EjercicioCompleto.txt
echo "OMP_ijk_bucle_interno:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_ijk_bucle_interno"
variable2=$(echo "$(./OMP_ijk_bucle_externo.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable2:" >> EjercicioCompleto.txt

echo "Realizando el ijk"
if (( $(echo "$variable1 < $variable2" |bc -l) )); then
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_ijk_bucle_externo.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_ijk.txt
	done
else
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_ijk_bucle_interno.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_ijk.txt
	done
fi

###jki
echo "OMP_jki_bucle_externo:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_jki_bucle_externo"
variable1=$(echo "$(./OMP_jki_bucle_externo.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable1:" >> EjercicioCompleto.txt
echo "OMP_jki_bucle_interno:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_jki_bucle_interno"
variable2=$(echo "$(./OMP_jki_bucle_interno.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable2:" >> EjercicioCompleto.txt

echo "Realizando el jki"
if (( $(echo "$variable1 < $variable2" |bc -l) )); then
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_jki_bucle_externo.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_jki.txt
	done
else
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_jki_bucle_interno.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_jki.txt
	done
fi

###ikj
echo "OMP_ikj_bucle_externo:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_ikj_bucle_externo"
variable1=$(echo "$(./OMP_ikj_bucle_externo.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable1:" >> EjercicioCompleto.txt
echo "OMP_ikj_bucle_interno:" >> EjercicioCompleto.txt
echo "Realizando general de OMP_ikj_bucle_interno"
variable2=$(echo "$(./OMP_ikj_bucle_interno.exe 0| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
echo "$variable2:" >> EjercicioCompleto.txt

echo "Realizando el ikj"
if (( $(echo "$variable1 < $variable2" |bc -l) )); then
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_ikj_bucle_externo.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_ikj.txt
	done
else
	for (( i=0; i<4; i++ )) do
		echo "Realizando el ${NHilos[i]}"
	    variable3=$(echo "$(./OMP_ikj_bucle_interno.exe 1 ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')")
	    echo "${NHilos[i]}	$variable3:" >> EjercicioCompleto.txt
	    echo "${NHilos[i]}	$variable3:" >> datos_ikj.txt
	done
fi
