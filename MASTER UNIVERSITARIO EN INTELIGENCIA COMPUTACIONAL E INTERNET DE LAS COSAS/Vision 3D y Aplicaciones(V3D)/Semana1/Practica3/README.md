# Realce usando máscara de desenfoque (Unsharp Mask).

Los parametros de entrada para este ejercicio son:
La imagen de entrada
El nombre de la imagen de salida
El radio usado con r
El gamma usado con g
El tipo de filtro usado siendo f
	si f=0 se aplica filtro caja
	si f=1 se aplica filtro gaussiano

./usm_enhance ../data/radiografia.png salida.jpg -r=60 -g=1.5 -f=0
./usm_enhance ../data/ciclista_original.jpg salida2.jpg -r=7 -g=2 -f=1