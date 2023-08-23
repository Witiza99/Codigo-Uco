#Ejercicio 1

import numpy as np
import sys

print('Introduce el nombre del fichero: ');
fichero=input();
f=open(fichero, "r");
lineas = f.readlines();
print(lineas)
if len(lineas) < 3:
	print('Error en el fichero');
	f.close();
	sys.exit()
else:
	filas = int(lineas[0]);
	columnas = int(lineas[1]);
	matrizDatos = np.zeros((filas, columnas), dtype=float);
	if len(lineas)-2 != columnas*filas:
		print('Error en el fichero');
		f.close();
		sys.exit()
	else:
		for i in range(filas):
			for j in range(columnas):
				matrizDatos[i][j] = float(lineas[i*columnas+j+2]);

f.close();

print('La matriz es la siguiente:');
print(matrizDatos);

print('La matriz inversa es así:');
matrizDatosInversa = np.linalg.inv(matrizDatos);
print(matrizDatosInversa);

print('Comprobamos identidad:');
print(np.dot(matrizDatos, matrizDatosInversa));