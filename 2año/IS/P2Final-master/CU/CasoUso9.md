# Cargar Información

**ID:** 09

**Breve descripción:** El sistema es capaz de cargar la información de un fichero.


**Actores principales:** Usuario.

**Actores secundarios:** Ninguno.

**Prioridad:** 03

### Precondiciones:

1. El fichero debe de existir.
2. Debe existir la función guardar información.

## Flujo principal:

1. El caso de uso empieza cuando es necesario el uso de información almacenada en el fichero.
2. El programa al iniciarse carga la información a un vector en el programa.


## Postcondiciones

* Se abre el fichero en modo escritura-lectura para su uso.

## Flujo alternativos:

2.a. Si ocurre algún problema en la apertura del fichero este informará de error.
