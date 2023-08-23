/*
*
*   Created on : 24-oct-2019, 23:08:02
*   Author     : Oscar Godoy
*	Modificado: 28-oct, 31-oct, 03-nov, 04-nov, 10-nov, 12-nov, 19-nov, 20-nov
*	Descripcion: Aplicar las funciones segun el nombre de pagina entre ellas Categorias, Registro y Curriculum
*	Uso: Controlar los formularios de Registro y Curriculum, Paginacion en Categorias.html dependiendo de la categoria seleccionada
*	se aplican las funciones y procesos dentro de window.onload 
*/

var pag,pos,pos2,correo,movil;

/**
* Array con lista de paginas donde no se creara el elemento boton de iniciar sesion
*/
var paginas = ["Categorias","MisProyectos","Nuevo_Proyecto","Detalle_Proyecto","Donar","Contactar","Faq"];

/**
* variables para paginacion 
*/
/** variable que obtendra los nodos hijos donde se insertara el contenido para la paginacion */
var items;
/** Se guarda en un array los nodos que recibe de 'items' */
var itemArray = [];
var i=0;
/** Numero de contenidos por pagina */
var div_por_pagina = 3;
/** se guarda el id dado con anterioridad y el actual en la paginacion */
var id,id_anterior;
var clase = document.createAttribute("class");
clase.value = "active";

/**
* variable utilizada para obtener el nombre de la pagina actual
*/
var nuevo;

/*
* Cuando se carga la pagina HTML para que comience js.
*/	
window.onload = function(){	
	pag = String(window.location);// se queda
	nuevo = extraerPagina(pag);

	if(!addButton(nuevo,paginas)){
		document.getElementById("titulo").style.width = "55%";
		var remover = document.getElementsByClassName("cab-der");
		document.getElementById("cabecera").removeChild(remover[0]);
	}
	
	if(nuevo === "Categorias"){		
		/** A partir de aqui es para la paginacion */
		paginacion();
		/** Fin de la paginacion */

		document.getElementById("seleccion_categoria").addEventListener("change",selectorCategorias);
	}
	
	if(nuevo === "Curriculum"){
		document.getElementById("nombre").focus();
		document.getElementById("nombre").addEventListener("keypress",validarNombre);
		document.getElementById("movil").addEventListener("keydown",validarTelefono);
		correo = document.getElementById("email").value;
		movil = document.getElementById("movil").value;
		
		document.getElementsByName("cancelar")[0].addEventListener("click",function(evt){
			document.formcurriculum.nombre.focus();
			document.getElementById("email").style.border = "1px solid #999";
			document.getElementById("movil").style.border = "1px solid #999";
			document.getElementById("errProgramacion").innerHTML = "";
			document.getElementById("errIdiomas").innerHTML = "";
		});

		document.getElementById("form-curriculum").addEventListener("submit",validarCurriculum);
	}

	if(nuevo === "Registro"){
		formularioRegistro();

		document.getElementsByTagName("textarea")[0].addEventListener("click",function(){
			var texto = document.getElementsByTagName("textarea")[0].innerHTML;
			if(texto === "Envia un comentario"){
				document.getElementsByTagName("textarea")[0].innerHTML = "";
				document.getElementsByTagName("textarea")[0].style.color = "gray";
			}
		});
		
		document.getElementsByTagName("textarea")[0].addEventListener("blur",function(){
			var texto = document.getElementsByTagName("textarea")[0].innerHTML;
			if(texto === ""){
				document.getElementsByTagName("textarea")[0].placeholder = "Envia un comentario";

			}
		});
	}
};

/**
 * Valida el formulario de curriculum
 * @param {object} evt - parametro que obtiene el evento que se ha invocado
 */
function validarCurriculum(evt){
	correo = document.getElementById("email").value;
	movil = document.getElementById("movil").value;
	if(verificarIdiomas()){
		console.log("entras1")
		evt.preventDefault();
	}

	if(verificarProgramacion()){
		console.log("entras2")
		evt.preventDefault();
	}

	if(!num_movil.test(movil)){
		document.getElementById("sp_mo").innerHTML = "Numero incorrecto.";
		document.getElementById("movil").style.border = "1px solid rgba(255,55,61,1)";
		evt.preventDefault();
	}

	if(!mails.test(correo)){
		document.getElementById("email").style.border = "1px solid rgba(255,55,61,1)";
		evt.preventDefault();
	}
}

/**
 * Paginacion de Categorias.html
 * @constructor
 */
function paginacion(){
			/* A partir de aqui es para la paginacion */
	var tamano = document.getElementsByClassName("encapsula").length;
	
	var suma = 0;//suamara el ancho de cada bloque de la paginacion para obtener el ancho total y poder centrarlo respecto al nodo padre

	for (i = 0; i < (tamano/div_por_pagina); i++) {
		crearElemento(i,clase);
		suma += document.getElementsByClassName("pagination")[0].childNodes[i].offsetWidth;/**/
	}
	suma += 3;
	document.getElementsByClassName("pagination")[0].style.width = suma+"px";
	document.getElementsByClassName("pagination")[0].style.margin = "0 auto";
	
	items = document.getElementsByClassName("content-div-block")[0].children;

	for (i = 0; i < items.length-1; i++) {
		itemArray.push(items[i].cloneNode(true));
	} 
	
	removeryAnadir(0,div_por_pagina-1);
	
	id_anterior = "p1";//guarda el id del primer elemrnto con class="active"

	document.getElementsByClassName("pagination")[0].addEventListener("mouseover",function(evt){
		id = evt.target.id;
		document.getElementById(id).style.cursor = "pointer";
	});

	document.getElementsByClassName("pagination")[0].addEventListener("click",function(evt){

		document.getElementById(id_anterior).removeAttribute("class");
		id = evt.target.id;
		/**/
		var valor = document.getElementById(id).innerHTML;
		/**/
		id_anterior = id;

		document.getElementById(id).setAttributeNode(clase);
		
		var pagina = id.substring(1);
		var num_pagina = parseInt(pagina);

		var hasta = num_pagina*div_por_pagina - 1;

		/**/
		var ultimo_hijo = document.getElementsByClassName("pagination")[0].lastChild;
		var atributo = ultimo_hijo.id;
		ultimo_hijo = document.getElementById(atributo).innerHTML;
		/**/

		if(num_pagina === parseInt(ultimo_hijo)){
			hasta = itemArray.length - 1;
		}
		var desde = div_por_pagina*(num_pagina - 1);

		removeryAnadir(desde,hasta);

	});
}

/**
* obtiene el valor de una de las categorias de la etiqueta select
* @param {object} evt - parametro que obtiene el evento que se ha invocado
*/
function selectorCategorias(evt){
	var op = this.selectedIndex;
	var valor = this.options[op].value;
	var categoria = document.getElementById("segun_cat");
	categoria.innerHTML = "";
	var texto;
	if(op > 1){
		texto = document.createTextNode(" de " + valor);
	}else{
		texto = document.createTextNode(valor);
	}
	categoria.appendChild(texto);
}

/**
 * Extrae el nombre de una pagina a partir de la url que se le pasa.
 * @param {string} cadena - busca una palabra en concreto de la cadena que se le pasa
 * devuelve, la pagina actual para realizar cambios.
 */
function extraerPagina(cadena){
	pos = cadena.lastIndexOf("/");
	pos2 = cadena.lastIndexOf(".");
	pos3 = pos2 - pos -1;	
	cad = cadena.substr(pos+1,pos3);
	return cad;
}

/**
 * verifica que al menos un campo del checkbox de idiomas haya sido seleccionado 
 * en la pagina Curriculum.html
 */
function verificarIdiomas(){
    var errIdiomas = false;
    for (var i = 0; i < document.formcurriculum.curcheckidioma.length; i++) {
        if(document.formcurriculum.curcheckidioma[i].checked){
            errIdiomas = true;
            i=document.formcurriculum.curcheckidioma.length;
        }
    }
    if(!errIdiomas){
        document.getElementById("errIdiomas").innerHTML = "Dato requerido";
        return true;
    }
    else{
        document.getElementById("errIdiomas").innerHTML = "";
        return false;
    }
}

/**
 * verifica que al menos un campo del checkbox de lenguajes de programacion
 * haya sido seleccionado n la pagina Curriculum.html
 */
function verificarProgramacion(){
    var errProgramacion = false;
    for (var i = 0; i < document.formcurriculum.curchecklanguage.length; i++) {
        if(document.formcurriculum.curchecklanguage[i].checked){
            errProgramacion = true;
            i=document.formcurriculum.curchecklanguage.length;
        }
    }
    if(!errProgramacion){
        document.getElementById("errProgramacion").innerHTML = "Dato requerido";
        return true;
    }
    else{
        document.getElementById("errProgramacion").innerHTML = "";
        return false;
    }
}

/**
 * Crea un nuevo elemento HTML para la paginacion en Categorias.html
 * @constructor
 * @param {number} i - utilizado para el atributo id.
 * @param {string} clase - atributo class que tendra el nuevo elemento.
 */
function crearElemento(i,clase){
	var a_tag = document.createElement("a");
	var contenido = document.createTextNode(i+1);
	a_tag.appendChild(contenido);
	//var a_attr = document.createAttribute("href");
	//a_attr.value = "#";
	var id_a = document.createAttribute("id");
	var valor = "p"+(i+1);
	id_a.value= valor;
	a_tag.setAttributeNode(id_a);
	//a_tag.setAttributeNode(a_attr);
	if(i === 0){
		a_tag.setAttributeNode(clase);
	}
	document.getElementsByClassName("pagination")[0].appendChild(a_tag);
}

/**
 * remueve y añade elementos dependiendo del numero de pagina en Categorias.html
 * @constructor
 * @param {number} desde - desde que elemento del array coge elementos
 * @param {number} hasta - hasta qué punto donde cogera los elementos
 */
function removeryAnadir(desde,hasta){
	//se obtienen todos los elementos con la clase encapsula
	var elementos = document.getElementsByClassName("encapsula");
	//se eliminan todos los elementos con la clase encapsula contenidos en bloque div
	for (i = elementos.length-1; i >= 0 ; i--) {
		document.getElementsByClassName("content-div-block")[0].removeChild(elementos[i]);
	}
	
	//se obtiene el primer elemento con la clase pagination1
	var pag = document.getElementsByClassName("pagination1")[0];
	//se inserta los nuevos elementos con la clase encapsula dentro del elemento padre content-div-block
	//justo antes del elemento con la clase pagination
	for (i = desde; i < (hasta+1); i++) {
		document.getElementsByClassName("content-div-block")[0].insertBefore(itemArray[i],pag);
	}
}

/**
 * validar el nombre en formulario, no permite la introduccion de numeros en el campo alfabetico
 * @param {number} e - parametro por defecto que actua junto al eveneto que realiza la llamada a la funcion
 */
function validarNombre(e){
    var evento = e||window.event;
    if(evento.which >= 48 && evento.which <= 57){
        evento.preventDefault();   //anula accion del evento
    }
}

/**
 * validar el telefono en formulario, no permite la introduccion de letras en el campo alfabetico
 * @param {number} e - parametro por defecto que actua junto al eveneto que realiza la llamada a la funcion
 */
function validarTelefono(e){
    var evento = e||window.event;
	if((evento.which >= 0 && evento.which < 8)|| (evento.which >= 9 && evento.which <= 34) || (evento.which == 38) || (evento.which >= 40 && evento.which <= 47) || (evento.which >= 58)){
		evento.preventDefault(); 
	}
	document.getElementById("sp_mo").innerHTML = "";
	document.getElementById("movil").style.border = "1px solid lightgray";
}