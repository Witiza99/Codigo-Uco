@Ejemplo de operadores lógicos y de cadenas

writestring('Introduce la primera cadena: \n');
readstring(string1);

writestring('Introduce la segunda cadena: \n');
readstring(string2);

string3 := string1 || string2;

writestring('La cadena concatenada es: \'');
writestring(string3);
writestring('\'.\n');

writestring('Escribe un número: ');
read(a);
writestring('\n');

if ((a <= 0) and not (string3 <> 'sacacorchos')) then
    writestring('El número menor o igual a 0 es: ');
    write(a);
    writestring('\nHas escrito sacacorchos.\n');
else
    writestring('El número no es menor que 0 o la palabra compuesta no es sacacorchos. \n');
endif

if (a > 0 or string3 = 'rascacielos') then
  writestring('El número es mayor que cero o a palabra es rascacielos.\n');
endif
