/*
*
*   Created on : 10-nov-2019, 23:08:02
*   Author     : Rafael Hormigo
* Modificado: 10-nov, 15-nov
* Descripcion: Aplicar las funciones en acceder.html para el control del formulario
* Uso:comprobar en pagina acceder.html que contraseña
*/

var paginas = ["Categorias","MisProyectos","Nuevo_Proyecto","Detalle_Proyecto","Donar","Contactar","Faq"];

var nuevo;
window.onload = function(){
  pag = String(window.location);// se queda
	nuevo = extraerPagina(pag);

	if(!addButton(nuevo,paginas)){
		document.getElementById("titulo").style.width = "55%";
		var remover = document.getElementsByClassName("cab-der");
		document.getElementById("cabecera").removeChild(remover[0]);
	}
  if (nuevo=="acceder"){
    document.getElementById("EnviarAcceder").addEventListener("click",function(){
      contrasena=document.getElementById("ContrasenaAcceder").value;
      fallo=validarContrasena(contrasena);
      if (fallo=="") {
        return true;
      }else{
        alert(fallo);
        return false;
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
