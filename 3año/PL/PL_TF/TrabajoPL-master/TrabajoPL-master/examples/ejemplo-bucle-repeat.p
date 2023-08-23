@Ejemplo del bucle repeat


clear;
PLACE(10,10);
writestring('Intente adivinar la palabra secreta. ');
PLACE(11,10);
writestring('Introduzca su nombre:');
PLACE(12,10);
readstring(nombre);
PLACE(13,10);
writestring('Pulse \'enter\' para continuar\n');
readstring(respuesta);

clear;
PLACE(10,10);

writestring('Primera pista: ¡tiene que ver con la informática!\n');
place(15,10);
writestring('Introduzca la respuesta: ');
place(16,10);
readstring(respuesta);

clear;

resuelta := false;
intentos := 0;

repeat
  if(respuesta = 'intérprete') then
    resuelta := true;
  else
    if(intentos = 3) then
      place(10,10);
      writestring('¿Qué tal una segunda pista?');
      place(11,10);
      writestring('Tiene que ver con esta asignatura.');
      place(12,10);
      writestring('Pulse \'enter\' para continuar\n');
      readstring(respuesta);
      clear;
    endif

    if(intentos = 6) then
      place(10,10);
      writestring('¿Aún no lo tienes? ¡Tranquilo! Aquí tienes otra pista.');
      place(11,10);
      writestring('Es lo que hemos desarrollado en esta práctica.');
      place(12,10);
      writestring('Pulse \'enter\' para continuar\n');
      readstring(respuesta);
      clear;
    endif

    place(10,10);
    writestring('Respuesta incorrecta, siguiente intento: ');
    place(11,10);
    readstring(respuesta);
    clear;
  endif
  intentos := intentos + 1;
until(resuelta = true or intentos >= 12);

if (resuelta = true) then
  place(10,10);
  writestring('¡Enhorabuena ');
  writestring(nombre);
  writeString(', has acertado!');
else
  place(10,10);
  writestring('Te quedaste sin intentos! La respuesta es \'intérprete\'');
endif

Place(11,10);
writestring('Pulse \'enter\' para salir del programa\n');
readstring(respuesta);
clear;
