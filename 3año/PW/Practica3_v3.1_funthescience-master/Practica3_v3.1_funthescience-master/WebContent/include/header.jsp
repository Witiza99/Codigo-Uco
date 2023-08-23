<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>	
<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>
	<header id="cabecera">
		<div class="cab-izq">
			<figure id="logo"> 
				<a href="../../index.jsp"><img src="../../img/logo.png" alt="logo_pagina"/></a>
			</figure>
		</div>
		<div class="cab-cent">
			<section id="seleccion_idioma" name="seleccion_idioma">
				<select>
					<option value="ES">ES</option>
					<option value="EN">EN</option>
				</select>
			</section>
		</div>
		<section class="titulo">
			<h2 id="titulo">Fund the Science</h2>
		</section> 
		<!-- ************************************************************** -->
		<!-- Se controla la muestra del boton con javascript, dependiendo de la pagina que
			necesite mostrar alguna informacion para el usuario -->
			
		<%-- controlar el boton de login/registro --%>
	    <% if(!customerBean.getName().equals("")){ %>
        	<input type="hidden" id="botonLogin" value="ok"/>
        <% } else{ %>
        	<input type="hidden" id="botonLogin" value="not"/>
        <% } %>
        <%-- fin de control --%>
			

		<div class="cab-der">
			<!-- <section>
				<a href="./acceder.jsp" id="acceso">Mi cuenta / Registrarse</a>
			</section> -->
		</div>

		<div class="relleno-cab"></div>
		<!-- ********************* FIN DE COMENTARIO ********************** -->
		<!-- ************************************************************** -->
	</header>