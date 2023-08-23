#chmod u+x practicax.sh
#Ej1
if test -d $1
	then
		cant1=$(find $1 -type f -name "*.c" | wc -l)
		cant2=$(find $1 -type f -name "*.h" | wc -l)
		echo "Tenemos $cant1 Ficheros con extension.c y $cant2 ficheros con extension.h"

		#en el find se puede poner -o para que encuentre una cosa o otra
		for x in $(find $1 -type f -name "x.c" -o -type f -name "*.h")
		do
			echo "El fichero $x tiene $(cat $x|wc -l) lineas y $(cat $x|wc -m) caracteres"
		done | sort -nr -k 8
	else
		echo "$1 no es un directorio."
fi
#-nv(ordenar de forma inversa)
#se podria volcar en fichero >> Ficherotmp y luego hacer sort
