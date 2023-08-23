# Introducir alumno

**ID:** 01

**Breve descripción:** El sistema permite introducir a un alumno.


**Actores principales:** Usuario.

**Actores secundarios:** Alumnos.

**Prioridad:** 01

### Precondiciones:

* No necesitara de ninguna precondición.

### Flujo principal:

1. El caso de uso empieza cuando el usuario desea introducir un alumno.
2. El sistema recoge los datos introducidos de cada alumno.

### Postcondiciones:

* Se almacenara el alumno introducido.

### Flujos alternativos

2.a. Si coincide algun DNI o algun email dara error.

2.b. Si se deja algun campo vacio (salvo el atributo equipo al que pertenece y el atributo de si es lider del equipo) el programa dara error.

2.c. El programa no permitira elegir un segundo lider dentro de un mismo grupo.
