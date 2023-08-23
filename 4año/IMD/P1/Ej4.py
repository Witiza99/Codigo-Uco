#Ejercicio 4
import numpy as np
#from scipy import stats

print('Introduce número de filas: ');
filas= int(input());
print('Introduce número de columnas:');
columnas= int(input());

matrizDatos = np.zeros((filas, columnas), dtype=int);

for i in range(filas):
	for j in range(columnas):
		print('Introduce el número (%d, %d):' % (i, j));
		matrizDatos[i][j] = int(input());

print('La matriz quedaría así:');
print(matrizDatos);

print('La moda de la matriz es la siguiente: ');
aux, contador = np.unique(matrizDatos, return_counts=True)
moda = np.where(contador == np.amax(contador))
print(aux[moda])


print('La media de toda la matriz es la siguiente: ');
print(matrizDatos.mean());