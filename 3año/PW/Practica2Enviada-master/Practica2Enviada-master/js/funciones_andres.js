/*
*
*   Created on : 01-nov-2019, 18:59:45
*   Author     : Andrés Lopez
* Modificado: 01-nov, 05-nov, 12-nov, 15-nov
* Descripcion: Paginacion en MisProyectos.html
* Uso: Paginado de proyectos segun su actividad
*/


var nProy = 4;
var arrayList;
var lista = [];

var paginas = ["Categorias","MisProyectos","Nuevo_Proyecto","Detalle_Proyecto","Donar","Contactar","Faq"];
var pag, nuevo;
window.onload = function(){
	//Esta parte es necesaria para el header
	pag = String(window.location);
	nuevo = extraerPagina(pag);
	console.log("nuevo " + nuevo);
	if(!addButton(nuevo,paginas)){
		document.getElementById("titulo").style.width = "55%";
	}
	
	//Guardo todos los elemetos que habia en el div que almacena los proyectos
	arrayList = document.getElementById("proyectos").children;

	//Guardo todos los proyectos en un vector
	for(i=1;i < arrayList.length; i++){
		lista.push(arrayList[i].cloneNode(true));
	}

	
	//Borro todos los proyectos del documento, para despues poder mostrar tan solo los que me interesan
	borrarHijos();
	
	//Como la cantidad de paginas depende de la cantidad de proyectos hay que crear los botones
	CrearBotones();
	
	//Por defecto se mostraran los n primeros elementos, es decir la primera pagina
	let j=0;
	while(j<nProy && j<lista.length){
		document.getElementById("proyectos").insertBefore(lista[j], arrayList[arrayList.length]);
		j++;
	}

	//Cuando haga click en uno de los botones mostrare la parte del vector que le corresponda
	document.getElementById("botPag").addEventListener("click", function(evt){
		id = evt.target.id;
		
		//Muestro la parte que me interesa del vector de proyectos que me interesa
		let parte = nProy * (id[id.length -1] -1);
		
		borrarHijos();
		let i = parte;
		while(i<nProy+parte && i<lista.length){
			document.getElementById("proyectos").insertBefore(lista[i], arrayList[arrayList.length]);
			i++;
		}
	});
	
	document.getElementById("proyectos").addEventListener("click", function(evt){

		document.getElementById("imgPrSelect").removeChild(document.getElementById("imgPrSelect").firstChild);
		
		id = evt.target.id;

		//Ahora teniendo el id del proyecto habria que cargar su imagen

		let div_img = document.getElementById("imgPrSelect");
		let imagen = document.createElement("img");

		//Le asigno un sorce a la imagen
		let src_attribute = document.createAttribute("src");
		//Despues habra que actualizar el path de la imagen de cada proyecto obteniendolo de una base de datos
		if(id == "proy2"){
			src_attribute.value = "./img/Logo_UGR.jpeg";
		}
		else{
			src_attribute.value = "./img/Logo_UCO.png";
		}
		///////////////////////////////////////////
		imagen.setAttributeNode(src_attribute);

		//Y un alt
		let alt_attribute = document.createAttribute("alt");
		alt_attribute.value = id;
		imagen.setAttributeNode(alt_attribute);
		
		div_img.appendChild(imagen);
	});
}

function borrarHijos(){
	var oldproy = document.getElementsByClassName("proyecto");
	for(i=oldproy.length-1; i>=0; i--){
		document.getElementById("proyectos").removeChild(oldproy[i]);
	}

}

function CrearBotones(){
	for(i=0; i<lista.length/nProy; i++){
		let Bname = i+1;
		let boton = document.createElement("button");
		boton.innerText = Bname;
		let div_bot = document.getElementById("botPag");
		
		//Le asigno un name a los botones
		let name_attribute = document.createAttribute("name");
		name_attribute.value = "Bpaginado_"+Bname;
		boton.setAttributeNode(name_attribute);

		//Y un id
		let id_attribute = document.createAttribute("id");
		id_attribute.value = "Bpaginado_"+Bname;
		boton.setAttributeNode(id_attribute);

/*		let valor_attribute = document.createAttribute("valor");
		valor_attribute.value = ""+Bname+"";
		boton.setAttributeNode(valor_attribute);*/

		div_bot.appendChild(boton);
	}	
}