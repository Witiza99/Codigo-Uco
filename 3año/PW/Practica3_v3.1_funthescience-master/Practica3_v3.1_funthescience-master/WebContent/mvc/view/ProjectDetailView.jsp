<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>

<!DOCTYPE html>
<html>

	<head>
		<title>Detalle Proyecto</title>
		<author Antonio Gómez Giménez>
		<meta charset="UTF-8">
		<meta name="nombre" content="Página de Detalle Proyecto">
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
		
		<!-- ******************* Inicio Detalle_Proyecto ********************************   -->
		<div id="cuerpo_detalle_proyecto">
			<% ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("projects"); 
				ArrayList<String> msgs = (ArrayList<String>)request.getAttribute("messages");%>
			<div class="det_izquierda">
				<div class="titulo_proyecto">
					<h4><%= projects.get(0).getTitle() %></h4>
				</div>	
				<div class="img_proyecto">
					<img src=<%= projects.get(0).getImageProject() %> alt="Imagen del proyecto:"/>
				</div>
				<div class="descripcion_proyecto">
				<% 
					if(customerBean.getIndex()==projects.get(0).getAuthorIndex()) { 
						for(int i=1; i<msgs.size(); i+=2){%>
						<p class="comentario"><%= msgs.get(i) %>:<%= msgs.get(i-1) %><br>
						</p>
						<%}
					}else {%>
						<p><%= projects.get(0).getDescriptionComplete() %><br>	
						</p>
					<%} %>
				</div>	
			</div>
			<div class="det_derecha">
				<div class=botones_detalle>
					<button><a href="../view/donateView.jsp?id=<%= projects.get(0).getId() %>">Donar</a></button>
					<button><a href="../control/contactController.jsp?cat=<%= projects.get(0).getCategory() %>&id=<%= projects.get(0).getId() %>">Contactar</a></button>
				</div>
				<div class="descripcion_proyecto_corta">
					<p><%= projects.get(0).getDescriptionbrief() %></p>
				</div>
				<div class="encapsula">
					<p>
					Autor: <br>
					<a href="../control/ProfileController.jsp?id=<%= projects.get(0).getAuthorIndex() %>"><%= projects.get(0).getAuthor() %></a><br>
					Participantes:<br>
					<%= projects.get(0).getParticipantes() %><br>	
					</p>
				</div>		
			</div>
		</div>
		<!-- ******************* Fin Detalle_Proyecto ********************************   -->


		<%@ include file="../../include/footer.html" %>
	</body>
</html>
