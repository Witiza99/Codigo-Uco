# Modificar alumno

**ID:** 02

**Breve descripción:** El sistema permite modificar los datos de los alumnos.


**Actores principales:** Usuario.

**Actores secundarios:** Alumnos.

**Prioridad:** 05


### Precondiciones:

1. Debe existir una forma de buscar al alumno que se desea modificar
 

### Flujo principal:

1. El caso de uso comienza cuando el usuario quiere modificar la información de algun alumno.
2. El programa guarda los datos nuevos.

### Postcondiciones:

* Se almacenara al alumno con los datos modificados.

### Flujos alternativos

1.a. Se buscara al usuario por DNI para comprobar que ese alumno ya existe.

1.b. Si desea modificar el lider de un equipo se quita el lider anterior.

1.c. Si al modificar coincide el DNI o el email dara error.
