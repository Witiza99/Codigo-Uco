NHilos=(4 8 16)

rm datos_p2_ijk_4096_paralelo.txt
gcc p2_ijk.c -Wall -o p2_ijk.exe -lpthread #esta linea debe modificarse en el caso de que el ejecutable se encuentre en una carpeta, es necesario añadirle la ruta
echo "Datos de bucle ijk en paralelo para matrices de 4096 valores" >> datos_p2_ijk_4096_paralelo.txt

for (( i=0; i<3; i++ )) do
	echo "Realizando el ${NHilos[i]}"
    echo "${NHilos[i]}	$(./p2_ikj.exe ${NHilos[i]}| tail -n 1 | grep -o -E '[0-9]+(.[0-9]+(e-[0-9]+)?)?')" >> datos_p2_ijk_4096_paralelo.txt
done