if [ $# -ge 1 ] #compruebo que haya minimo un argumento
then
	if [ -d $(pwd)/copia/ ] #compruebo si existe y si no existe lo creo
	then
		find $(pwd)/copia/ -type f | while read x #compruebo la antiguedad de cada archivo
		do
			seg=$(date +"%s")
			ulmod=$(stat -c "%Y" $x)
			diferencia=$(($seg - $ulmod))
			if [ $diferencia -ge 200 ]
			then
				echo "Borrando $x de $diferencia segundos..."
				rm -Rf $x
			fi
		done
	else
		mkdir copia
	fi
	for x in $*
	do
		nametime=$(date +"%s") #asi evito quese me pueda cambiar el nombre al cambiarlo a la carpeta copia
		tar -czf copia-$(whoami)-$nametime.tar.gz $x
		mv copia-$(whoami)-$nametime.tar.gz $(pwd)/copia/
	done
	echo "La copia de seguridad se ha creado correctamente."
else
	echo "No se han introducido argumentos."
fi