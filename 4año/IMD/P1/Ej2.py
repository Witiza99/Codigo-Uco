#Ejercicio 2

import numpy as np
import random

print('Introduce número de filas: ');
filas= int(input());
print('Introduce número de columnas:');
columnas= int(input());
print('Introduce valor máximo aleatorio: ');
almax= float(input());
print('Introduce valor mínimo aleatorio:');
almin= float(input());
matrizDatos = np.zeros((filas, columnas), dtype=float);

for i in range(filas):
	for j in range(columnas):
		matrizDatos[i][j] = random.uniform(almin, almax);

maximo = float(matrizDatos.max());
minimo = float(matrizDatos.min());

print(matrizDatos);

print('El máximo es: %f' % maximo);
print('El mínimo es: %f' % minimo);

PrimerValor = 0;
SegundoValor = 0;

while True:
	print('Cálculo del ángulo de dos vectores fila o columna: ');
	print('0 ->: Modo Filas');
	print('1 ->: Modo Columnas');
	opcion= int(input());
	if opcion >= 0: 
		if opcion <= 1:
			break;
		else:
			print('Opcion incorrecta');	
	else:
		print('Opcion incorrecta');	

if opcion == 0:

	while True:
		print('Introduce la primera fila:');
		PrimerValor = int(input());
		if PrimerValor >= 0: 
			if PrimerValor < filas:
				break;
			else:
				print('Valor incorrecta');	
		else:
			print('Valor incorrecta');	
	
	while True:
		print('Introduce la segunda fila:');
		SegundoValor = int(input());
		if SegundoValor >= 0: 
			if SegundoValor < filas:
				break;
			else:
				print('Valor incorrecta');	
		else:
			print('Valor incorrecta');	

	axiliarPrimero = matrizDatos[PrimerValor,:];
	axiliarSegundo = matrizDatos[SegundoValor,:];

	Grados = np.inner(axiliarPrimero, axiliarSegundo);



else: 

	while True:
		print('Introduce la primera columna:');
		PrimerValor = int(input());
		if PrimerValor >= 0: 
			if PrimerValor < columnas:
				break;
			else:
				print('Valor incorrecta');	
		else:
			print('Valor incorrecta');

	while True:
		print('Introduce la segunda columna:');
		SegundoValor = int(input());
		if SegundoValor >= 0: 
			if SegundoValor < columnas:
				break;
			else:
				print('Valor incorrecta');	
		else:
			print('Valor incorrecta');
	
	axiliarPrimero = matrizDatos[:, PrimerValor];
	axiliarSegundo = matrizDatos[:, SegundoValor];

	Grados = np.inner(axiliarPrimero, axiliarSegundo);

print('El ángulo formado por dos vectores usando el producto escalar es %f' % Grados);