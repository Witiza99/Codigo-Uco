@Ejemplo del bucle for

writestring('Programa que calcula la sucesión de fibonacci de un número. \n');
writestring('Pulse \'enter\' para continuar\n');
readstring(n);

clear;
PLACE(10,10);

writestring('Introduzca el número del que quiere calcular su sucesión de fibonacci: \n');
PLACE(11,10);
writestring('-->');
read(n);

if (n = 0)then
  t := 0;
else
  i := 0;
  j := 1;

  for k from 1 to n-1 do
    t := i + j;
    i := j;
    j := t;
  endfor
endif

clear;
Place(10,10);
writestring('El resultado es: \n');
Place(11,10);
write(t);
writestring('\n');

Place(13,10);
writestring('Fin del Programa. Pulse enter para finalizar.\n');
readstring(n);
