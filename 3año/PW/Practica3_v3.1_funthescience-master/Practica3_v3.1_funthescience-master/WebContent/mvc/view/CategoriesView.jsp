<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>


<%--
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>  

<%@page import="java.util.ArrayList"%>   
<%@page import="java.util.List"%>
--%>
 
<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
	<head>
		<title>Categorias</title>
		<meta charset="UTF-8">
		<meta name= "description" content="Categorias">
		<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
		<meta name= "author" content="Oscar Godoy Calderón">
		<meta name= "viewport" content="width=device-width, initial-scale=1.0">
		<link rel="icon" href="../../img/logo.ico">
		<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
		<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
		<link href="../../css/estilos.css" rel="stylesheet" type="text/css"/>
		<script>
			window.history.pushState(null, '', 'http://localhost:8080/fundthescience/mvc/view/CategoriesView.jsp');    
		</script>
		<script src="../../js/functionheader.js" type="text/javascript"></script>
		<script src="../../js/funcionesJS.js" type="text/javascript"></script>

	</head>
	<body>
		<div id="prueba"></div>
		<div id="cuerpo">
				
		
		<jsp:include page="../../include/header.jsp" />	
		
			<section id="contenido">
				<div class="izquierda">
					<h5>Selecciona categor&iacute;a:</h5>
					<form id="sel_cat" method="post" action="../control/CategoriesController.jsp">
						<select name="seleccion_categoria" id="seleccion_categoria">
							<option>selecciona una opcion</option>
							<option value="Fisica">F&iacute;sica</option>
							<option value="Quimica">Qu&iacute;mica</option>
							<option value="Medicina">Medicina</option>
							<option value="Arquitectura">Arquitectura</option>
							<option value="Astronomia">Astronom&iacute;a</option>
							<option value="Ingenieria">Ingenier&iacute;a</option>
							<!-- <option value="Categoria7">Categoria7</option> -->
						</select>
						<input type="submit" value="Submit">
					</form>
				</div>
				<div class="derecha">
					<section id="tit_cat">
					<%
						ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("projects");
						if(projects == null){
							%>
							<h2>Seleccione una categor&iacutea</h2>
							<%
						}
						else if(projects.size() == 0){
							%>
							<h2>No hay proyectos de la categor&iacutea seleccionada</h2>
							<%	
						}
						else{
							%>
							<h2>Proyectos</h2>
							<%	
						}
					
					%>
					</section>
					<div class="content-div-block">
						<!-- ************************************************************** -->
						<!-- se generaran tantas div para mostrar las categorias necesarias -->
						
						<!--						
						<article class="encapsula">
							<section class="descripcion_detalle_proyecto">
								<h3><a href="Detalle_Proyecto.html?id=proyecto=1">Titular del proyecto</a></h3>
								<p>Fecha de creacion: <span>29-10-2019</span></p>
								<p>Estado del proyecto: <span>Abierto1</span></p>
								<p>Creador o representate: <span>Mariano Rajoy</span></p>
							</section>
							<figure class="imagen_detalle_proyecto">
								<img src="img/open_graph_logo.png" alt=""/>
							</figure>
						</article>
						-->
						<%
						if(projects != null){
							for(int i=0; i<projects.size(); i++){
							%>
							<article class="encapsula">
								<section class="descripcion_detalle_proyecto">
									<h3><a href="../control/ProjectDetailController.jsp?id=<% out.println(projects.get(i).getId()); %>"><% out.println(projects.get(i).getTitle()); %></a></h3>
									<p>Fecha de creacion: <span><%out.println(projects.get(i).getDate()); %></span></p>
									<p>Estado del proyecto: <span><% out.println(projects.get(i).getStatus()); %></span></p>
									<p>Creador o representate: <span><%out.println(projects.get(i).getAuthor()); %></span></p>
								</section>
								<figure class="imagen_detalle_proyecto">
									<img src="../../img/open_graph_logo.png" alt=""/>
								</figure>
							</article>
							<%
							}
						}
						%>
						
						
						<!-- Fin de comentario de carga de proyectos por categoria -->
						<!-- ************************************************************** -->
						
						<!-- A modo de relleno para demostrar la paginacion de proyectos segun categoria -->
				
						<!-- Fin de comentario sobre el relleno -->					
						<div class="pagination1"><div class="pagination"></div></div>
					</div>
				</div>
			</section>
			
			<%@ include file="../../include/footer.html" %>
		</div>
	</body>
</html>
