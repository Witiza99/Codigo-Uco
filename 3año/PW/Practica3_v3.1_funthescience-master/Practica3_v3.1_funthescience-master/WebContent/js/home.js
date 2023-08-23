/**
 * 
 */

window.onload = function(){
	var children = document.getElementsByClassName("navbar")[0].children.length;
	var selectores = document.getElementsByClassName("navbar")[0];
	if(children == 4){
		for(i=0;i< children;i++){
			document.getElementsByClassName("anchura")[i].style.width = "22.7%";
		}
	}
}