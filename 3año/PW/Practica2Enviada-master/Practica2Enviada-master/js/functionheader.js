/**
*
*   Created on : 03-nov-2019, 09:24:36
*   Author     : Oscar Godoy
*	Modificado: 03-nov
*	Descripcion: Funciones aplicables a todas las paginas del sitio
*	Uso: obtener la url para crear elementos segun el nombre de pagina
*/

/**
* Añadira un boton en el encabezado de la pagina para iniciar sesion o registrarse
* @constructor
* @param {string} nuevo - recibe el nombre de la pagina donde aplicar
* @param {array} pagina - array con lista de paginas donde se añadira el boton
*/
function addButton(nuevo,pagina){
	var found = false;
	
	var contenido = document.createTextNode("Mi cuenta / Registrarse");
	var a_element = document.createElement("a");
	a_element.appendChild(contenido);
	var h_ref = document.createAttribute("href");
	h_ref.value = "acceder.html";
	var id_a = document.createAttribute("id");
	id_a.value = "acceso";
	a_element.setAttributeNode(id_a);
	a_element.setAttributeNode(h_ref);
	var div_element = document.createElement("div");
	div_element.appendChild(a_element);

	for (var i = 0; i < pagina.length && !found; i++) {
		if(nuevo === pagina[i]){
			document.getElementsByClassName("cab-der")[0].appendChild(div_element);
			found = true;
		}
	}
	return found;
}

/**
* extrae de la URL el nombre de la pagina actual
* @param {string} caddena - url para extraer una parte de la cadena
*/
function extraerPagina(cadena){
	pos = cadena.lastIndexOf("/");
	pos2 = cadena.lastIndexOf(".");
	pos3 = pos2 - pos -1;	
	cad = cadena.substr(pos+1,pos3);
	return cad;
}
