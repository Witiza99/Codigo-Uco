<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>



<!Doctype html>
<html>

	<head>
		<title>Busqueda</title>
		<author Antonio Gómez Giménez>
		<meta charset="UTF-8">
		<meta name="nombre" content="Página de Busqueda">
		<meta name="palabras_clave" content="HTML,CSS,JavaScript">
		<link rel="icon" href="img/logo.ico">
		<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
		<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
		<link href="../../css/estilos_Antonio.css" rel="stylesheet" type="text/css"/>
		<link href="../../css/estilos_HF.css" rel="stylesheet" type="text/css"/>
		<script src="../../js/functionheader.js" type="text/javascript"></script>
		<script src="../../js/funciones_Antonio.js" type="text/javascript"></script>
	</head>
	<body>

		<%@ include file="../../include/header.jsp" %>	

		<!-- ******************* Inicio Busqueda ********************************   -->
		<div id="cuerpo_busqueda">
			<div class="bus_izquierda">
				<form action="../control/SearchController.jsp" role="search" name="form_busq">
				 	<div class="buscador">
				  		<input type="search" id="miBusqueda" name="miBusqueda" placeholder="Buscar proyecto..." aria-label="Buscar en el contenido del sitio" size="15" required minlength="1" maxlength="35" >
				  		<button id="Prueba_boton">Buscar</button>
				  		<span class="validity"></span>
				 	</div>
				<!--</form>
				<form method="post">-->
					<div class="buscador_checkbox">
				  		<p>
				   		 	<input type="checkbox" name="autor" value="si"> Autor<br>
				   			<input type="checkbox" name="fecha" value="si"> Fecha<br>
				   			<input type="checkbox" name="correoAutor" value="si"> Correo Autor<br>
				   			<input type="checkbox" name="categoria" value="si"> Categoría<br>
				   			<input type="checkbox" name="objetivosDonaciones" value="si">Objetivos Donaciones<br>
				 			<!--<input type="submit" value="Realizar Busqueda"></p>-->
					</div>
				</form>
			</div>
			
		<div class="bus_derecha">
			<%
				ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("AllProject");
				if(projects == null){
					%>
					<h2>Realice una busqueda</h2>
					<%
				}
				else if(projects.size() == 0){
					%>
					<h2>No hay proyectos de la busqueda realizada</h2>
					<%	
				}
				else{
					%>
					<h2>Proyectos</h2>
					<%	
				}
			
			%>
			
			<%
					if(projects != null){
						for(int i=0; i<projects.size(); i++){
						%>
			<div class="bloques">	
			
				<!--  div class="bus_img_proyecto">
					<a href="Detalle_Proyecto.html"><img src="img/Logo_UCO.png" alt="Imagen del proyecto:"/></a>
				</div>
				<div class="bus_titulo_proyecto">
				<h4><a href="Detalle_Proyecto.html">T&iacutetulo del proyecto </a></h4>
				</div>
				<div class="bus_descripcion_proyecto">
					<p>Descripcion del proyecto</p>
				</div -->
				
				
						<div class="bus_img_proyecto">
							<a href="../control/ProjectDetailController.jsp?id=<% out.println(projects.get(i).getId()); %>"><img src="<% out.println(projects.get(i).getImageProject()); %>" /></a>
						</div>
						<div class="bus_titulo_proyecto">
							<h3><a href="../control/ProjectDetailController.jsp?id=<% out.println(projects.get(i).getId()); %>"><% out.println(projects.get(i).getTitle()); %></a></h3>
						</div>
						<div class="bus_descripcion_proyecto">
							<p><% out.println(projects.get(i).getDescriptionbrief()); %></p>
						</div>
									
			</div>
			<%
						}
					}
				%>	
		</div>
		<!-- ******************* Fin Busqueda ********************************   -->

		<%@ include file="../../include/footer.html" %>
		
	</body>
</html>
