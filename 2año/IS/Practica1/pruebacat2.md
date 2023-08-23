**Contenidos**

1.1. Git.

	1.1.1. Introducción.
	1.1.2. Instalación y configuración.
	1.1.3. Uso básico.
	1.1.4. Github.

1.2. Markdown.

	1.2.1. Introducción.
	1.2.2. Código.

1.3. Eclipse.

	1.3.1. Introducción.
	1.3.2. Instalación.

1.4. Recursos

**Evaluación**

* Las entregas en moodle se realizarán por medio del representante o líder de cada grupo.
* Se debe entregar en moodle la dirección del repositorio de Github.
* Se evaluará la realización de un pequeño tutorial de Github con los contenidos aprendidos durante las dos primeras sesiones prácticas. El lenguaje de formateado será Markdown.
* El repositorio de Github contendrá tanto el tutorial como el historial de cambios realizados por los integrantes del grupo.

# **0. Git**

## **0.1. Introducción**

### **Motivación**

* Código efímero.
* Necesidad de mantener todas las versiones del código fuente.
* Problemas en organizaciones para mantener el código actualizado.
* Coherencia de versiones.
* Conocimiento del cambio que ha provocado que el sistema no funcione.
* Fallos en el disco duro que suponen riesgo de información desactualizada.
* Satisfacer el compromiso de entrega.

**Git y GitHub**

**Git**

![Logo de Git](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e0/Git-logo.svg/512px-Git-logo.svg.png)

*Git*: sistema para el control distribuido de versiones de código. Fundamentalmente permite:

* Dar seguimiento a los cambios realizados sobre un archivo.
* Almacenar una copia de los cambios.

**GitHub**

![Logo de GitHub](https://i1.wp.com/geeksroom.com/wp-content/uploads/2014/05/github-gde.png?w=580&ssl=1)

*GitHub*: sitio web dónde podemos subir una copia de nuestro repositorio Git.

**Ventajas**

**Git**

* Habilidad de deshacer cambios.
* Historial y documentación de cambios.
* Múltiples versiones de código.
* Habilidad de resolver conflictos entre versiones de distintos programadores.
* Copias independientes.

**GitHub**

* Documentación de requerimientos.
* Ver el avance del desarrollo.


## **0.2. Instalación y configuración**

### **Instalación**

* Para instalar Git: https://git-scm.com.
* En el curso se utilizará Git a través de líneas de comandos.
* Para eclipse existen *plugins* integrados: https://www.eclipse.org/egit
### **Configuración básica**
Nombre del administrador:
`git config --global user.name "Antonio M. Durán Rosal`

Correo electrónico:
`git config --global user.email aduran@uco.es`

Editor de texto:
`git config --global core.editor "gedit"`

Color de la interfaz:
`git config --global color.ui true`

Listado de la configuración:
`git config --list`

## **0.3 Uso básico**

### **Los tres estados de Git**

![Local Operations](https://image.slidesharecdn.com/git-intro-091215075529-phpapp01/95/git-and-github-13-728.jpg?cb=1260938801)

### **Comandos básicos I**

Iniciar repositorio en un directorio:
`git init`

Agregar cambios al area de *staging*:
`git add`

Validar cambios en el repositorio:
`git commit -m *"Mensaje"*`

Hacer los dos pasos anteriores en uno:
`git commit -am "Mensaje"`

Historial de commits:
`git log`


### **Comandos básicos II**

Ayuda del listado anterior:
`git help log`

Listar los 5 commits más recientes:
`git log -n 5`

Listar los commits desde una fecha:
`git log --author="Antonio"`

Ver cambios en el directorio:
`git status`


### **Comandos básicos III**

Ver diferencia entre ficheros en el directorio y el repositorio git:
`git diff`

Ver diferencia entre ficheros en el *staging* y el repositorio:
`git diff --staged`

Eliminar archivos:
~~~
git rm archivo
git commit -m "Mensaje"
~~~

Mover o renmbrar archivos:
~~~
git mv antiguo nuevo
git commit -m "Mensaje"
~~~


### **Comandos básicos IV**

Deshacer cambios con git:
`git checkout --nombre-fichero`

Retirar archivos del *staging*:
`git reset HEAD nombre_fichero`

Complementar último commit:
