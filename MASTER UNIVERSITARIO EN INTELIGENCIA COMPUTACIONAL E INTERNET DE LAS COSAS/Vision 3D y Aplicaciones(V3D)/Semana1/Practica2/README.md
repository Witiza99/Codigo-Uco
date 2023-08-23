# Color balance

Equilibrado del color.


Los parametros de entrada para este ejercicio son:
La imagen de entrada
El nombre de la imagen de salida
El modo de funcionamiento siendo p
	si p=0 se aplica white patch
	si p=100 se aplica gray world

./color_balance ../data/manos_sin_balance1.jpg salida.jpg -p=0
./color_balance ../data/manos_sin_balance1.jpg salida.jpg -p=100


*En principio se ha escogido el punto más luminoso, no se escoge un porcentaje de puntos para coger la media, ni se escoge un punto con el ratón.