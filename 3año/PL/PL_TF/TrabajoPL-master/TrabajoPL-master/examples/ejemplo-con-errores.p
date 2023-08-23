@Este ejemplo contiene errores

@Aquí hay una asignación mal hecha
a = 0;

@Aquí unos identificadores no válido
_id := 'hola';
id__1 := 243;
2a := true;


@Aquí ejemplos de números incorrectos
a := 2,3;
b := 2.;
c := 2.3.2;
d := 2E;
e := 2.E-;

@Aquí un while usando una variable indefinida

while (indef < 0) do
  write(indef);
endwhile


@Advertencia de un if con la condición constante

if(true) then
  writestring('hola que tal');
endif

@Un if con la condición de tipo distinto a lógico

if(2 + 3) then
  write(2+3);
endif


@ejemplos de for infinitos

for a from 0 to -1 do
  write(a);
endfor

for a from 0 to 5 step -1 do
  write(a);
endfor

for a from 0 to 5 step 0 do
  write(a);
endfor

@Ejemplo de falta de punto y coma

writestring('Me falta el semicolon al final')

@Ejemplos de tipos incompatibles

write('hola');

num := 5;

writestring(num);

@aunque introduzcas un número no puedes mostrarlo con write porque está guardado como cadena
writestring('Introduce un número que se guardara como cadena para ver el error al intentar mostrarlo con write \n');
readstring(cadena);
write(cadena);

a := 1 + '5';

b := 1 || '5';

c := 5 and true;
