#practica 3
#arg1 la carpeta
#arg2 el umbral1 ej 10.000
#arg3 el umbral2 ej 100.000
if test -d $1
	then
	if [ -z $2 ]
		then
		umbral1=10000
		else
		umbral1=$2
	fi
	if [ -z $3 ]
		then
		umbral2=100000
		else
		umbral2=$3
	fi
	echo "Creando las carpetas pequenos, medianos y grandes..."
	rm -Rf grandes
	rm -Rf medianos
	rm -Rf pequenos
	mkdir grandes
	mkdir medianos
	mkdir pequenos
	echo "Copiando los archivos..."
	for x in $(find $1 -size -$umbral1'c' -type f) #pequeños
	do
		cp $x pequenos/
	done
	for x in $(find $1 -size +$umbral1'c' -type f | find $1 -size -$umbral2'c' -type f) #medianos
	do
		cp $x medianos/
	done
	for x in $(find $1 -size +$umbral2'c' -type f) #grandes
	do
		cp $x grandes/
	done
else
	echo "$1 no es un directorio."
fi