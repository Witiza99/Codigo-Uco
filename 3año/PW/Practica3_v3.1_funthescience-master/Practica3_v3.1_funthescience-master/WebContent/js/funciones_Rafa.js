/*
*
*   Created on : 10-nov-2019, 23:08:02
*   Author     : Rafael Hormigo
* Modificado: 10-nov, 15-nov
* Descripcion: Aplicar las funciones en acceder.html para el control del formulario
* Uso:comprobar en pagina acceder.html que contraseña
*/

var paginas = ["Categorias","MisProyectos","Nuevo_Proyecto","Detalle_Proyecto","Donar","Contactar","Faq","profileViewSuccess","ProfileController"];

var nuevo,nueva_pagina;
window.onload = function(){
	
	pag = String(window.location);// se queda
	nuevo = extraerPagina(pag);
	nueva_pagina = extraerNuevaPagina(pag);
	
	if(nuevo == "ProfileController"){
		window.history.pushState(null, '', 'http://localhost:8080/fundthescience/mvc/view/profileViewSuccess.jsp');    
	}
	
	
	if(isLogin() == false){
		if(!addButton(nuevo,paginas)){
			document.getElementById("titulo").style.width = "55%";
			var remover = document.getElementsByClassName("cab-der");
			document.getElementById("cabecera").removeChild(remover[0]);
		}
	}

		//* cambiar aqui para el login poner userLoginView en vez de userLogin*/
  if (nuevo == "userLoginView"){
    document.getElementById("formulario").addEventListener("submit",function(evt){
      contrasena = document.getElementById("ContrasenaAcceder").value;
      fallo=validarContrasena(contrasena);
      if (fallo != "") {
        alert(fallo);
        evt.preventDefault();
      }
    });
  }
}

/**
* comprueba que la contraseña tenga entre 8 y 50 caracteres
* @param {string} - recibe el string de contraseña
*/
function validarContrasena(input){
  if (input.length==0) {
    return "Debe introducir una contraseña\n"
  }else if (input.length<8) return "Contraseña demasidado corta\n";
  else if(input.length>50) return "Contraseña demasiado larga\n";
  else return "";
}

/**
* extrae de la URL el nombre de la pagina actual que se le pasa informacion por GET
* @param {string} cadena - url para extraer una parte de la cadena
*/
function extraerNuevaPagina(cadena){
	var pos1 = cadena.lastIndexOf("?");
	console.log("pag1 " + pos1)
	var pos2 = cadena.lastIndexOf("/");
	console.log("pos2 " + pos2)
	pos3 = pos2 - pos1 - 1;
	console.log("pos3 " + pos3)
	cad = cadena.substr(pos1+1,pos3);
	console.log("cade -> " + cad)
	return cad;
}
