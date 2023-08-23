# Calibración de la cámara con OpenCV.

Se ha realizado la practica entera, en principio las funciones realizadas pasan todos los test. Cabe destacar que no se ha usado la función fsiv_undistort_video_stream, ya que se cogia cada frame del video introducido, y sobre dicho frame se le aplicaba la funcion fsiv_undistort_image.

Cabe destacar que el formato de carga y guardado de los datos intrinsecos de la camara se encuentran en formato yml.

Algunos ejemplos de entradas que se han probado para la comprobación del correcto funcionamiento de undistort y calibrate son los siguientes:
./calibrate -verbose -size=0.04 -rows=5 -cols=6 ../data/salida.yml ../data/logitech_000_000.png ../data/logitech_000_001.png ../data/logitech_000_002.png ../data/logitech_000_003.png ../data/logitech_000_004.png ../data/logitech_000_005.png ../data/logitech_000_006.png ../data/logitech_000_007.png ../data/logitech_000_008.png ../data/logitech_000_009.png
En el caso anterior se prueba como se veria dibujado el eje xyz sin rvec y tvec, logicamente no se puede realizar el dibujo correctamente ya que faltan los parametros extrinsecos.
./calibrate -verbose -i -size=0.04 -rows=5 -cols=6 ../data/salida.yml ../data/logitech_000_000.png ../data/logitech_000_001.png ../data/logitech_000_002.png ../data/logitech_000_003.png ../data/logitech_000_004.png ../data/logitech_000_005.png ../data/logitech_000_006.png ../data/logitech_000_007.png ../data/logitech_000_008.png ../data/logitech_000_009.png
En el caso anterior si se puede ver el dibujo de los ejes correctamente representado para distintas imagenes
./undistort ../data/salida.yml ../data/logitech_000_000.png salida
Con la salida anterior se puede comprobar el undistort para una imagen, pero es dificil comprobar si funciona correctamente.
./undistort -v ../data/salida.yml ../data/tablero_000_000.avi salida
Similar al caso anterior pero probando con un video