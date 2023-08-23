<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>
<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<% if(!customerBean.getEmail().equals("")){ %>
<!DOCTYPE html>
<html>	
<head>
	<title>Mis proyectos</title>
	<meta charset ="UTF-8">
	<meta name= "description" content="Todos mis proyectos">
	<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
	<meta name= "author" content="Andrés López Cárdenas">
	<meta name= "viewport" content="width=device-width, initial-scale=1.0">
	<link rel="icon" href="../../img/logo.ico">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
	<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
	<link href="../../css/estilos_MisProyectos.css" type="text/css" rel="stylesheet" />
	<link href="../../css/estilos_HF.css" type="text/css" rel="stylesheet" />
	<script src="../../js/functionheader.js" type="text/javascript"></script>
	<script src="../../js/funciones_andres.js" type="text/javascript"></script>
</head>
<body>
	<jsp:include page="../../include/header.jsp" />			
	<div id=cuerpo>
		<div id="selector">
			<form method="POST" action="../control/MyProjectsController.jsp">
				<input type="radio" id="ProyCreados" name="selector" value="PCreados" checked>
				<label for="ProyCreados">Proyectos creados</label>
		
				<input type="radio" id="ProyParticipo" name="selector" value="PParticipo">
				<label for="ProyParticipo">Proyectos en los que participo</label>
		
				<input type="submit" name="submit" value="Buscar">
			</form>
		</div>
		<% ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("projects");
		if(projects == null){
			%>
			<h2>Seleccione una categor&iacutea</h2>
			<%
		}else{
			%>
			<h2>Proyectos</h2>
			<%	
		}%>
		<div id="Cizquierda">
			<div id="proyectos">
				<div id="CProy">
					<button>
						<a href="../view/NewProjectView.jsp">Crear Proyecto</a>
					</button>
				</div>
				<%
				if(projects != null){
					for(int i=0; i<projects.size(); i++){
					%>
				<div class="proyecto" id="proy1">
					<div>
						<h3><strong>Titulo: </strong><a href="../control/ProjectDetailController.jsp?id=<%= projects.get(i).getId() %>"><%= projects.get(i).getTitle() %></a></h3>
						<p><%= projects.get(i).getDescriptionbrief() %></p>
					</div>
					<form method="POST" action="../control/MyProjectsController.jsp?id=<%= projects.get(i).getId() %>">

						<input type="submit" name="submit" value="Eliminar">
					</form>
					<img src="<%= projects.get(i).getLogoProject() %>" alt="logo" >
				</div>
				<%
					}
				}
				%>
				
				
			</div>
			<div id="botPag">	
			</div>
		</div>
		<div id="imgPrSelect">
		</div>
	</div>

			<%@ include file="../../include/footer.html" %>
</body>
</html>
<% } else { %>
 <jsp:forward page="./userLoginView.jsp" />
<% } %>
