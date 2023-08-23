


/**
* Created on : 29-oct-2019, 16:51:26
* Author     : Antonio Gomez Gimenez
* Modificado: 29-oct, 01-nov, 05-nov, 09-nov, 18-nov
* Descripcion: controlar los formularios y la subida de imagen y logo al crear un nuevo proyecto
* Uso: su utilidad es realizar las validaciones de formulario de la pagina Busqueda, NuevoProyecto y ModificaDatos
  y el control de la subida de imagenes comprobando si es una imagen y el tamaÃ±o de la misma, si el tamano es excesivo se  avisara al usuario, 
  si se puede subir la imagen, la muestra dando el nombre y el tamano de la misma

*/
//temp
function extraerPagina(cadena){
	pos = cadena.lastIndexOf("/");
	pos2 = cadena.lastIndexOf(".");
	pos3 = pos2 - pos -1;	
	cad = cadena.substr(pos+1,pos3);
	return cad;
}

////////////////////////////Funcion Onload////////////////////////////

//variables usadas para la funcion onload
var paginas = ["Busqueda","CategoriasView","MisProyectos","NewProjectView","Detalle_Proyecto","Donar","Contactar","Faq"];
var pag, nuevo;

var ver_emails = /^[_a-z0-9-]+(.[_a-z0-9-]+)*@[a-z0-9-]+(.[a-z0-9-]+)*(.[a-z]{2,4})$/;
var num_movil = /^([6]|[7]|[9])[0-9]{8}$/;

/*
  * La funcion onload permite evitar poner codigo javascript en el propio html, por tanto aquí se albergan las llamadas a todas las funciones usada
  * para ello se extrae la pagina en la que estamos y tras obtenerla ya se llaman a las funciones de cada página
  */
window.onload = function(){
  
  //extraccion de la pagina
  pag = String(window.location);
  console.log("pag " + pag);
  nuevo = extraerPagina(pag);
  console.log("nuevo " + nuevo);
  
	if(isLogin() == false){
		if(!addButton(nuevo,paginas)){
			document.getElementById("titulo").style.width = "55%";
			var remover = document.getElementsByClassName("cab-der");
			document.getElementById("cabecera").removeChild(remover[0]);
		}
	}

  //pagina de busqueda
  if(nuevo=="Busqueda"){
    document.getElementById("Prueba_boton").addEventListener("click",function(){//se activa al hacer click en el formulario de busqueda
     functionvalidarform_Busqueda();
    });
  }

  //pagina de Nuevo_Proyecto
  if(nuevo=="NewProjectView"){

    //elimino el hecho de poder ver el archivo subido, ya que lo muestro de otra forma
     input = document.getElementById("logo_proyecto");
     input.style.opacity = 0;
     input2 = document.getElementById("img_proyecto");
     input2.style.opacity = 0;

    document.getElementById("img_proyecto").addEventListener("click",function(){//se activa al hacer click en Subir imagen proyecto
     imagen_proyecto();
    });
    document.getElementById("logo_proyecto").addEventListener("click",function(){//se activa al hacer click en Subir logo proyecto
     imagen_logo();
    });

    //estas funciones soluciona un problema que ocurria al borrar cuestionario ya que no borraba la imagen ni el logo
    document.getElementById("boton_form2").addEventListener("click",function(){//elimino el html de la imagen y añado el nuevo al hacer click en borrar formulario
     document.getElementsByClassName("img_der_sup")[0].innerHTML="";
     var texto = document.createElement("p");
     texto.innerHTML = "No hay imagen de proyecto subida";
     document.getElementsByClassName("img_der_sup")[0].appendChild(texto);
    });

    document.getElementById("boton_form2").addEventListener("click",function(){//elimino el html de la imagen y añado el nuevo al hacer click en borrar formulario
     document.getElementsByClassName("img_der_inf")[0].innerHTML="";
     var texto = document.createElement("p");
     texto.innerHTML = "No hay imagen de logo subida";
     document.getElementsByClassName("img_der_inf")[0].appendChild(texto);
    });

    document.getElementById("boton_form1").addEventListener("click",function(){//se activa al hacer click en el formulario del proyecto
     functionvalidarform_Nuevo_Proyecto();//reformas
    });
  }
  
  //pagina de Modificar_Datos
  if(nuevo=="updateDataView"){
	  
	  var profesion = document.getElementById("profHidden").value;
	  console.log("profesion " + profesion);
	  selectProfession(profesion);
	  
    document.getElementById("nombre").focus();
    document.getElementById("nombre").addEventListener("keypress",validarNombre);//funcion reciclada de javascrip de Oscar
    document.getElementById("apellido").addEventListener("keypress",validarNombre);//funcion reciclada de javascrip de Oscar
    document.getElementById("movil").addEventListener("keydown",validarTelefono);//funcion reciclada de javascrip de Oscar

    document.getElementsByName("envio")[0].addEventListener("submit",function(evt){
      correo = document.getElementById("email").value;
      movil = document.getElementById("movil").value;

      if(!num_movil.test(movil)){
        document.getElementById("movil").style.border = "1px solid red";
        document.getElementById("sp_mo").innerHTML = "Numero incorrecto";
        evt.preventDefault();
      }
      if(!ver_emails.test(correo)){
        document.getElementsByClassName("email")[0].style.border = "1px solid red";
        evt.preventDefault();
      }
    });
    showSlides(slideIndex);
  }
};



////////////////////////////Fin Funcion Onload////////////////////////////
function selectProfession(profesion){
	  if(profesion == "U"){
		  document.getElementById("U").selected = "true";
	  }else if(profesion == "GS"){
		  document.getElementById("GS").selected = "true";
	  }else if(profesion == "GM"){
		  document.getElementById("GM").selected = "true";
	  }else if(profesion == "B"){
		  document.getElementById("B").selected = "true";
	  }else{
		  document.getElementById("E").selected = "true";
	  }
}

////////////////////////////Funcion para anadir imagen a nuevo proyecto////////////////////////////

/** Funcion para subir logo donde se extraen las variables necesarias para el mismo. Se llama la funcion subir imagen cuando el input cambia */
function imagen_logo(){
  input = document.getElementById("logo_proyecto");
  preview = document.querySelector(".img_der_inf");
  console.log("preview" + input);

  input.style.opacity = 0;

  input.addEventListener("change", subir_logo);
}

/** funcion para subir imagen donde se extraen las variables necesarias para el mismo. Se llama la funcion subir imagen cuando el input cambia */
function imagen_proyecto(){
  input = document.getElementById("img_proyecto");
  preview = document.querySelector(".img_der_sup");

  input.style.opacity = 0;

  input.addEventListener("change", subir_imagen);
}

/** 
  * Funcion utilizada para subir la imagen del logo, modifica el DOM borrando parte del mismo y en su lugar muestra la imagen(en el caso de que se pueda)
  * con el nombre del archivo y el tamaño de la misma. Si no se puede subir el archivo por el tipo o el tamaño se muestra eso en lugar de la imagen.
  */
function subir_logo(){

  //borro todo lo que hay en preview, todos los hijos
  while(preview.firstChild) {
    preview.removeChild(preview.firstChild);
  }

  archivo =  input.files;//cojo el elemento
  var texto = document.createElement("p");

  if(archivo[0] == null){//en el caso de no haber archivo
    texto.innerHTML = "No hay imagen de logo subida";
    preview.appendChild(texto);
  }else{
    if(archivoValido(archivo[0])){//compruebo archivo
      if(archivo[0].size<(1048576*3)){//compruebo tamaño
        img=document.createElement("img");
        img.src=window.URL.createObjectURL(archivo[0]);
        texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", de tamaño: " + tamanoArchivo(archivo[0].size) + ".";

        //aniado tanto texto como imagen
        preview.appendChild(img);
        preview.appendChild(texto);

      }else {
        texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", el archivo es demasiado grande.";//advierto tamanio
        preview.appendChild(texto);
      }
    }else {
      texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", no es un archivo válido.";//advierto tipo
      preview.appendChild(texto);
    }
  }
}

/** 
  * Función utilizada para subir la imagen del proyecto, modifica el DOM borrando parte del mismo y en su lugar muestra la imagen(en el caso de que se pueda)
  * con el nombre del archivo y el tamaño de la misma. Si no se puede subir el archivo por el tipo o el tamaño se muestra eso en lugar de la imagen.
  */
function subir_imagen(){

  //borro todo lo que hay en preview, todos los hijos
  while(preview.firstChild) {
    preview.removeChild(preview.firstChild);
  }

  archivo =  input.files;
  console.log("archivo"+archivo);
  var texto = document.createElement("p");

  if(archivo == null){
    texto.innerHTML = "No hay imagen de proyecto subida";
    preview.appendChild(texto);
  }else{
    if(archivoValido(archivo[0])){
      if(archivo[0].size<(1048576*3)){
        img=document.createElement("img");
        img.src=window.URL.createObjectURL(archivo[0]);
        texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", de tamaño: " + tamanoArchivo(archivo[0].size) + ".";

        preview.appendChild(img);
        preview.appendChild(texto);

      }else {
        texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", el archivo es demasiado grande.";
        preview.appendChild(texto);
      }
    }else {
      texto.innerHTML="Nombre del archivo: " + archivo[0].name + ", no es un archivo válido.";
      preview.appendChild(texto);
    }
  }
}


/** 
  * Variables y funcion para validar un archivo que haya recibido, devolverá true si este es valido y false en caso contrario 
  * @param {string} file - String que contiene el archivo pasado
  */
var tiposArchivo = ['image/jpeg','image/pjpeg','image/png','image/jpg'];

function archivoValido(file) {
  for(var i = 0; i < tiposArchivo.length; i++) {
    if(file.type === tiposArchivo[i]) {
      return true;
    }
  }
  return false;
}

/** Funcion que tras recibir un numero en bytes lo devuelve en KB o MB, dependiendo de su tamanio*/
function tamanoArchivo(numero) {
  if(numero < 1024) {
    return numero + 'bytes';
  } else if(numero >= 1024 && numero < 1048576) {
    return (numero/1024).toFixed(1) + 'KB';
  } else if(numero >= 1048576) {
    return (numero/1048576).toFixed(1) + 'MB';
  }
}
//////////////////////////// Fin funcion para añadir imagen a nuevo proyecto////////////////////////////


////////////////////////////funciones para formularios busqueda y nuevo proyecto////////////////////////////

/** Funcion que va llamando a las funciones de validacion y posteriormente mostrara estos errores, en el caso de que los haya, a los usuario con un alert */
function functionvalidarform_Nuevo_Proyecto(){
  Titulo = document.getElementById("Titulo").value;
  fallo = validarTitulo(Titulo);
  Descripcion_breve = document.getElementById("Descripcion_breve").value;
  fallo+=validarDescripcion_breve(Descripcion_breve);
  Descripcion_completa = document.getElementById("Descripcion_completa").value;
  fallo+=validarDescripcion_completa(Descripcion_completa);
  Participantes = document.getElementById("Participantes").value;
  fallo+=validarParticipantes(Participantes);
  Categoria= document.getElementById("Categorias").value;
  fallo+=validarCategoria(Categoria);
  Pagina_Web = document.getElementById("Pagina_Web").value;
  fallo+=validarPagina_Web(Pagina_Web);
  Objetivo_Donaciones = document.getElementById("Objetivo_Donaciones").value;
  fallo+=validarObjetivoDonaciones(Objetivo_Donaciones);

  if(fallo=="") return true;
  else{
	fallo+="Redireccionando ...";
    alert(fallo);
    //redireccionar a misma pagina 
    setTimeout ("redireccionar()", 1); //tiempo expresado en milisegundos
    return false;
  } 
}

function redireccionar(){
	window.locationf="../mvc/view/NewProjectView.jsp";
}

/**
  *Funcion que llamara a la funcion validar busqueda y en el caso de ocurrir error en la validacion mostrara dicho error con un alert
  * @param {string} inp - Variable a comprobar
  */
function functionvalidarform_Busqueda(){
  busqueda = document.getElementById("miBusqueda").value;
  console.log("busqueda"+busqueda);
  fallo = validarBusqueda(busqueda);
  if(fallo=="") 
    return true;
  else{
    alert(fallo); 
    return false;
  }
}

/**
  * Funcion para validar el titulo, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarTitulo(inp){
  if(inp=== "")return "No se introdujo Título\n";
  else if(inp.length< 5)return "Título demasiado corto\n";
  else if(inp.length> 30)return "Título demasiado largo\n";
  else if(/[^a-zA-Z0-9_ -]/.test(inp))return "Carácteres inválidos en Título\n";
  else return "";
}

/**
  * Funcion para validar la descripcion breve, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarDescripcion_breve(inp){
  if(inp=== "")return "No se introdujo Descripción breve\n";
  else if(inp.length> 150)return "Descripción breve demasiado larga\n";
  else if(/[^a-zA-Z0-9_ -][\n]/.test(inp))return "Carácteres inválidos en Descripción breve\n";
  else return "";

}

/**
  * Funcion para validar la Descripcion completa, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarDescripcion_completa(inp){
  if(inp=== "")return "No se introdujo Descripción completa\n";
  else if(inp.length> 700)return "Descripción completa demasiado larga\n";
  else if(/[^a-zA-Z0-9_ -][\n]/.test(inp))return "Carácteres inválidos en Descripción completa\n";
  else return "";
}

/**
  * Funcion para validar la los participantes, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarParticipantes(inp){
  if(inp=== "")return "No se introdujeron participantes\n";
  else if(inp.length>300)return "Se ha excedido en el número de carácteres\n";
  else if(/[^a-zA-Z0-9_ -][\n]/.test(inp))return "Carácteres inválidos usados en los participantes\n";
  else return "";
}

/**
  * Funcion para validar la página web introducida por el usuario, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarPagina_Web(inp){
  if(inp=== "")return "No se introdujo página web\n";
  else if(inp.length>150)return "Se ha excedido en el número de carácteres\n";
  else if(/[^a-zA-Z0-9\.\@\_\/\-]/.test(inp))return "Carácteres inválidos para dirección de página web\n";
  else return "";
}

/**
  * Funcion para validar la busqueda, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarBusqueda(inp){
  if(/[^a-zA-Z0-9 \.\_\/\-]/.test(inp))return "Carácteres inválidos para buscar\n";
  else return "";
}

/**
  * Funcion para validar la categoría, recibe valor y devuelve fallo en caso de que asi sea
  * @param {string} inp - Variable a comprobar
  */
function validarCategoria(inp){
  //var elemento = document.getElementById("Categorias");
  //console.log(elemento);
  //var hijo = elemento.firstChild();
  //console.log("hijo " + hijo.innerHTML);
  if(inp==="--Selecionar--")return "No has selecionado categoría\n";
  else return "";
}

/**
 * Funcion para validar la cantidad
 * @param {string} inp - Variable a comprobar
 */
function validarObjetivoDonaciones(inp){
	  if(inp=== "")return "No se introdujo Objetivo Donaciones\n";
	  else if(inp<0)return "Número no válido\n";
	  else if(/[^0-9]/.test(inp))return "Carácteres inválidos Objetivo Donaciones\n";
	  else return "";
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

////////////////////////////Fin funciones para nuevo proyecto y busqueda////////////////////////////