# Mostrar Alumnos

**ID:** 05

**Breve Descripción:** El sistema es capaz de mostrar la información de los alumnos registrados



**Actores principales:** Usuario.

**Actores secundarios:** Alumnos.

**Prioridad:** 07

### Precondiciones:

1. Deben existir alumnos

### Flujo principal:

1. Este empieza cuando el usuario indica que quiere visualizar alumnos.
2. El usuario indica si quiere visualizar a todos o un grupo acotado de estos.

2.1. Si el usuario indica que quiere visualizarlos a todos se muestran todos por pantalla.

2.2. Si el usuario indica que quiere visualizar solo a un grupo de alumnos se le preguntará el método para filtrar la busqueda y acto seguido se inicializará la función búsqueda, una vez encontrados los alumnos se muestran.

## Postcondiciones

* Los alumnos se muestran en la terminal

## Flujo alternativo 

2.2.a Si la búsqueda no obtiene resultados se muestra un mensaje de error.
