# Estimación de la Pose para Realidad Aumentada

Se ha realizado la practica entera, en principio las funciones realizadas pasan todos los test excepto la ultima, ya que no entendia que pedia dicha funcion y la he realizado de mi forma entendiendola. Si se lanza la aplicacion funciona perfectamente.

Cabe destacar que para la carga de los datos intrinsecos de la camara se utiliza un fichero en formato yml. (se adjunta el archivo)

Algunos ejemplos de entradas que se han probado:
Para la comprobación del dibujo de la piramide:
./aug_real 5 6 0.04 ../data/salida.yml ../data/tablero_000_000.avi -m
Ejemplo para el dibujo de los ejes:
./aug_real 5 6 0.04 ../data/salida.yml ../data/tablero_000_000.avi
Un ejemplo de una imagen:
./aug_real 5 6 0.04 ../data/salida.yml ../data/tablero_000_000.avi -i=../data/computer-vision.jpg
Un ejemplo de un video:
./aug_real 5 6 0.04 ../data/salida.yml ../data/tablero_000_000.avi -v=../data/tablero_000_000.avi