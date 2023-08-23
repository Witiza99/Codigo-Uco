<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@page errorPage="errorPage/error.jsp" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>
<jsp:useBean id="perfil" class="es.uco.pw.display.bean.CustomerBean" scope="request" />

<!DOCTYPE html>
<html>
<head>
	<title>Home</title>
	<meta charset ="UTF-8">
	<meta name= "description" content="Pagina principal">
	<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
	<meta name= "author" content="Andrés López Cárdenas">
	<meta name= "viewport" content="width=device-width, initial-scale=1.0">
	<link rel="icon" href="img/logo.ico">
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.11.2/css/all.min.css">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
	<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
	<link href="./css/estilos_HF.css" type="text/css" rel="stylesheet" />
	<link href="./css/estilos_home.css" type="text/css" rel="stylesheet" />
	<script src="./js/home.js" type="text/javascript"></script>
</head>
<body>
	<!-- ******************* Inicio Cabecera ********************************   -->
	
	<header id="cabecera">
		<div class="cab-izq">
			<figure id="logo"> 
				<img src="img/logo.png"/>
			</figure>
		</div>
		<section class="titulo">
				<h2 id="titulo">Fund the Science</h2>
		</section> 
		<div class="cab-lang-home">
			<section id="seleccion_idioma">
				<select>
					<option label="ES">ES</option>
					<option label="EN">EN</option>
				</select>
			</section>
			<div class="home-buscar">
				<input type="search" placeholder="Buscar" /><a href="./mvc/view/SearchView.jsp"><i class="fas fa-search"></i></a>
			</div>
			<div class="welcome">

				<% if(!customerBean.getName().equals("")){ %>
				<span><i class="fa fa-dice"></i> Bienvenido <%= customerBean.getName() %></span>
				<% } %>
			</div>
		</div>
		<div class="relleno-cab"></div>
	</header>
	<!-- ******************* Fin Cabecera ********************************   -->
	<div id="cuerpo">

		<nav>
			<div class="navbar">

			  <a href="./mvc/view/MyProjectsView.jsp" class="anchura"><i class="fa fa-fw fa-code"></i> Mis Proyectos</a>
			  <a href="./mvc/view/NewProjectView.jsp" class="anchura"><i class="fa fa-fw fa-cogs"></i> Nuevo Proyecto</a>
			  <a href="./mvc/view/CategoriesView.jsp" class="anchura"><i class="fa fa-fw fa-layer-group"></i>Categor&iacuteas</a>

			  <% 
			  	if(!customerBean.getName().equals("")){
			  		int index = customerBean.getIndex();
			  		session.setAttribute("indexProfile",index);
			  %>
			  
			  	<a href="./mvc/control/ProfileController.jsp"><i class="fa fa-graduation-cap"></i> Mi perfil</a>
			   	<a href="./mvc/control/login_out/userLogoutController.jsp"><i class="fa fa-fw fa-sign-out-alt"></i>Logout</a>
			  <% }else{ %>
			  	<a href="./mvc/view/userLoginView.jsp" class="anchura"><i class="fa fa-fw fa-user"></i>Login</a>
			  <% } %>
			  
			</div>
		</nav>

		<% ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("projects");
		%>
		<!-- los proyectos se obtienen de la base de datos -->
		<div id="PrDestacado">
			<section>
				<h1><strong>PROYECTO DESTACADO</strong></h1>
			</section>
			<div class="proyecto">
				<aside>
					<h3><strong>Titulo:</strong><a href="./mvc/control/ProjectDetailController.jsp?id=<%= projects.get(0).getId() %>"> <%= projects.get(0).getTitle() %></a></h3>
					<p><%= projects.get(0).getDescriptionbrief() %></p>
				</aside>
				<%
					String imagen = projects.get(0).getLogoProject();
					imagen = imagen.substring(4);
				%>
				<img src="<%= imagen %>" alt="logo" >
			</div>
		</div>
		<!-- los proyectos se obtienen de la base de datos -->
		
		<div id="SDestacado">
			<section>
				<h1><strong>SEGUNDO PROYECTO DESTACADO</strong></h1>
			</section>
			<div class="proyecto">
				<aside>
					<h3><strong>Titulo:</strong><a href="./mvc/control/ProjectDetailController.jsp?id=<%= projects.get(1).getId() %>"> <%= projects.get(1).getTitle() %></a></h3>
					<p><%= projects.get(1).getDescriptionbrief() %></p>
				</aside>
				<%
					imagen = projects.get(1).getLogoProject();
					imagen = imagen.substring(4);
				%>
				<%-- <img src=<%= projects.get(1).getLogoProject() - alt="logo" > --%>
				<img src="<%=imagen%>" alt="logo" >
			</div>
		</div>

		<div id="TDestacado">
			<section>
				<h1><strong>TERCER PROYECTO DESTACADO</strong></h1>
			</section>
			<div class="proyecto">
				<aside>
					<h3><strong>Titulo:</strong><a href="./mvc/control/ProjectDetailController.jsp?id=<%= projects.get(2).getId() %>"> <%= projects.get(2).getTitle() %></a></h3>
					<p><%= projects.get(2).getDescriptionbrief() %></p>
				</aside>
				<%
					imagen = projects.get(2).getLogoProject();
					imagen = imagen.substring(4);
				%>
				<img src="<%= imagen %>" alt="logo" >
			</div>
		</div>

	</div>

	<footer id="footer">			
		<div class="boton_footer esp"><a href="./faq.html">FAQ</a></div>
		<div class="boton_footer"><a href="./faq.html#Sobre_nosotros">Contacta con nosotros</a></div>
		<div class="boton_footer"><a href="./faq.html#Contacto">¿Quienes somos?</a></div>
	</footer>
	
</body>
</html>
