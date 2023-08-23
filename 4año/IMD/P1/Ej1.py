#Ejercicio 1

import numpy as np
import sys

opcion = -1;
numeroPartidos = 0;
numeroEscanos = 0;

#compruebo modo de introduccion de datos
while True:
	print('Elige método de introducción de datos: ');
	print('0 -> Introducción de datos manual');
	print('1 -> Introducción de datos por fichero');
	opcion= int(input());
	if opcion >= 0: 
		if opcion <= 1:
			break;
		else:
			print('Opcion incorrecta');	
	else:
		print('Opcion incorrecta');	

#modo 0 directamente por teclado
if opcion == 0:
	print('Introduce número de partidos: ');
	numeroPartidos= int(input());
	print('Introduce número de escaños:');
	numeroEscanos= int(input());

	vectorVotos = np.zeros(numeroPartidos, dtype=int);
	for i in range(numeroPartidos):
		print('Introduce los votos del patido %d: ' % i);
		vectorVotos[i] = int(input());
#modo 1 datos introducidos por fichero
else:
	print('Introduce el nombre del fichero: ');
	fichero=input();
	#if 
	f=open(fichero, "r");
	lineas = f.readlines();
	if len(lineas) < 3:
		print('Error en el fichero');
		f.close();
		sys.exit()
	else:
		numeroPartidos = int(lineas[0]);
		numeroEscanos = int(lineas[1]);
		vectorVotos = np.zeros(numeroPartidos, dtype=int);
		if len(lineas)-2 != numeroPartidos:
			print('Error en el fichero');
			f.close();
			sys.exit()
		else:
			for i in range(numeroPartidos):
				vectorVotos[i] = int(lineas[i+2]);
	#else:
		#print('Error en el fichero al abrir el fichero o no existe un fichero con ese nombre');
		#sys.exit()

	f.close();

vectorEscanos = np.zeros(numeroPartidos, dtype=int);
vectorEscanos.fill(1);
matrizDatos = np.zeros((numeroEscanos+1, numeroPartidos), dtype=int);
#calculo la matriz de escaños y partidos
for i in range(numeroEscanos):
	for j in range(numeroPartidos):
		matrizDatos[i][j] = vectorVotos[j]/vectorEscanos[j];
	axiliar = matrizDatos[i,:]
	ganador=axiliar.argmax(axis=0);
	vectorEscanos[ganador]+=1;
	matrizDatos[numeroEscanos][ganador]+=1;
print('La matriz resultante es:');
print(matrizDatos);

print('Pudiendo ver que los resultados para cada partidos son:');
for j in range(numeroPartidos):
	print('Partido %d tiene %d escaños' % (j, matrizDatos[numeroEscanos][j]));