function generahtml(){
	echo "<ul>" >> $archivo
	for x in $(find $1 -maxdepth 1) #permito así contorlar el flujo del programa y que no me lo haga recusivo usando así mi recursividad
	do
		if [ -d $x ] && [ $1 != $x ]
		then  
			echo "<li><strong>$x</strong></li>" >> $archivo
			generahtml $x
		elif [ $1 != $x ]
		then  
			echo "<li>$x</li>" >> $archivo
		fi
	done
	echo "</ul>" >> $archivo
}

if [ -z $1 ] #compruebo que pase un directorio
then
	echo "Debe introducir un directorio"
	exit 1
elif [ -d $1 ]
then
	if [ -f $1.html ] #comprueba si existe un fichero html para borrar para evitar fallos
	then
		rm -f $1.html
	fi
	archivo=$1.html #así evito problemas al pasar los argumentos
	echo "Generando el listado de la carpeta $(pwd)/$1 sobre el fichero $1.html..."
	echo "<html>
<head>
<title>Listado del directorio $1/</title>
</head>
<body>
<style type="text/css">body { font-family: sans-serif;}</style>
<h1>Listado del directorio $1/</h1>" >> $archivo

	generahtml $1
	
	echo "</body>
</html>" >> $archivo
	echo "Terminado!"
else
	echo "No se ha introducido un directorio valido."
	exit 1
fi