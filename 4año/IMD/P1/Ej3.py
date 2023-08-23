#Ejercicio 3
import numpy as np

print('Introduce número de filas: ');
filas= int(input());
print('Introduce número de columnas:');
columnas= int(input());

matrizDatos = np.zeros((filas, columnas), dtype=float);

for i in range(filas):
	for j in range(columnas):
		print('Introduce el número (%d, %d):' % (i, j));
		matrizDatos[i][j] = float(input());

print('La matriz quedaría así:');
print(matrizDatos);


print('Calculando los máximos de cada fila...');
VmaximosFilas = np.zeros(filas, dtype=float);
for i in range(filas):
	axiliar = matrizDatos[i,:]
	VmaximosFilas[i] = float(axiliar.max());

print('Calculando los máximos de cada columna...');
VmaximosColumnas = np.zeros(columnas, dtype=float);
for j in range(columnas):
	axiliar = matrizDatos[:,j]
	VmaximosColumnas[j] = float(axiliar.max());

print('Los máximos por filas son:');
for i in range(filas):
	print('--> %f:' % VmaximosFilas[i]);

print('Los máximos por columnas son:');
for j in range(columnas):
	print('--> %f:' % VmaximosColumnas[j]);

print('El determinante de la matriz es %f:' % np.linalg.det(matrizDatos));