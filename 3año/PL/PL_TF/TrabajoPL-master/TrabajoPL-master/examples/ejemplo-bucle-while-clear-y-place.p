@Esto es un ejemplo de un bucle while

writestring('Programa que calcula el factorial de un número. \n');
writestring('Pulse \'enter\' para continuar\n');
readstring(a);

clear;
PLACE(10,10);

writestring('Introduzca el número del que quiere calcular el factorial: \n');
PLACE(11,10);
writestring('-->');
read(a);

while(a < 0) do
    writestring('El número debe ser positivo \n Introdúzcalo de nuevo: ');
    read(a);
endwhile

i:= a;
res := 1;

while(i>0) do
  res := res * i;
  i := i - 1;
endwhile

clear;
Place(10,10);
writestring('El resultado es: \n');
Place(11,10);
write(res);
writestring('\n');

Place(12,10);
writestring('Fin del Programa. Pulse enter para finalizar.\n');
readstring(a);
