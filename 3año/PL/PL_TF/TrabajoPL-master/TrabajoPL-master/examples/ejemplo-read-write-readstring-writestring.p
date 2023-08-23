@Ejemplo de los métodos read, write, readstring y writestring

#
leemos un dato
#

writestring('Introduce un dato numérico \n');

read(dato);

writestring('El dato es: ');
write(dato);
writestring('\n');
@Ahora le cambiamos el tipo a string

writestring('Introduce una cadena \n');

readstring(dato);

writestring('La cadena es \t\'');
writestring(dato);
writestring('\'\n');
