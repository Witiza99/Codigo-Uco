#arg1 carpeta
#arg2 numero bytes
if [ $# -ge 1 ]; then #compruebo que haya minimo un argumento
	if test -d $1
		then
		if [ -z $2 ]
			then
			n1=0
			else
			n1=$2
		fi
		echo "Nombre, LongitudUsuario, FechaModificación, FechaAcceso, Tamaño, Bloques, Permisos, Ejecutable"
		for x in $(find $1 -size +$n1'c' -type f) 
		do
			if [ -x $x ];  
			then  
				ejecutable=1  
			else  
				ejecutable=0  
			fi
			echo "$(basename $x); $(stat -c "%U" $x | wc -m); $(stat -c "%y" $x); $(stat -c "%x" $x); $(stat -c "%s" $x); $(stat -c "%b" $x); $(stat -c "%A" $x); $ejecutable"
		done | sort -n -k5 -t ";"
		else
			echo "$1 no es un directorio."
	fi
else 
	echo "No ha introducido argumentos"
fi