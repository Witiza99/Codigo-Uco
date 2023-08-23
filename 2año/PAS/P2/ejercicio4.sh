#practica 4
#who|awk para saber usuarios conectados awk filtra en columnas
#por ejemplo awk se usaria wc -l ej.txt da 14 ej.txt habria cque poner who|awk {print $1} y nos quedariamos con las filas solo
#se usa basename que da nombre sin ruta y grep $c -o|wc -l ver que significa -o

cant1=$(find . -maxdepth 1 -type f | wc -l ) #cuenta solo ficheros
echo "El número actual de archivos en el fichero es $cant1"
who | awk '{ print $1 }' | sort | uniq #muetra el nombre de las personas conectadas y elimina las repetidas
echo "¿Qué carácter quieres contar? "; read -t 5 c
if [ -z $c ]
then
	c=a
fi
for x in $(find .) 
	do
		echo "$(basename $x)"
	done | grep "$c" -o | wc -l > fichero.temp
echo "El carácter $c aparece $(cat fichero.temp) en nombres de ficheros o carpetas contenidos en la carpeta actual"
rm -f fichero.temp