<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<% if(customerBean.getEmail().equals("")){ %>
	<jsp:forward page="./userLoginView.jsp" />
<% }else{ %>
<!Doctype html>
<html>

	<head>
	<title>Nuevo Proyecto</title>
	<author Antonio Gómez Giménez>
	<meta charset="UTF-8">
	<meta name="nombre" content="Página de Nuevo Proyecto">
	<meta name="palabras_clave" content="HTML,CSS,JavaScript">
	<link rel="icon" href="../../img/logo.ico">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
	<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
	<link href="../../css/estilos_HF.css" rel="stylesheet" type="text/css"/>
	<link href="../../css/estilos_Antonio.css" rel="stylesheet" type="text/css"/>
	<script src="../../js/functionheader.js" type="text/javascript"></script>
	<script src="../../js/funciones_Antoniov2.js" type="text/javascript"></script>
	
	</head>

	<body>

		<jsp:include page="../../include/header.jsp"/>
		<div id="cuerpo">

			<div id="formulario_nuevo_proyecto">
				<form id="form1" action="../control/NewProjectController.jsp" method="POST" name="form1" enctype="multipart/form-data">
				    <div class= "lineas">
				        <label for="Titulo">T&iacutetulo:</label>
				        <input type="text" id="Titulo" name="Titulo" />
				    </div>
				    <div class= "parrafos">
				        <label for="Descripcion_breve">Descripci&oacuten breve:</label>
				        <textarea class= "estiloarea" id="Descripcion_breve" name="Descripcion_breve"></textarea>
				    </div>
				    <div class= "parrafos">
				        <label for="Descripcion_completa">Descripci&oacuten completa:</label>
				        <textarea class= "estiloarea" id="Descripcion_completa" name="Descripcion_completa"></textarea>
				    </div>
				    <div class= "parrafos">
				        <label for="Participantes">Participantes:</label>
				        <textarea class= "estiloarea" id="Participantes" name="Participantes"></textarea>
				    </div>
				    <div class="lineas">
					    <select name="Categorias" id="Categorias">
					    	<option>--Selecionar--</option>
							<option value="Fisica">F&iacute;sica</option>
							<option value="Quimica">Qu&iacute;mica</option>
							<option value="Medicina">Medicina</option>
							<option value="Arquitectura">Arquitectura</option>
							<option value="Astronomia">Astronom&iacute;a</option>
							<option value="Ingenieria">Ingenier&iacute;a</option>
					    </select>
				    </div>
				    <div class="lineas">
				        <label for="Pagina_Web">P&aacutegina Web:</label>
				        <input type="text" id="Pagina_Web" name="Pagina_Web" />
				    </div>
				    <div class= "lineas">
				        <label for="Objetivo_Donaciones">Objetivo Donaciones:</label>
				        <input type="text" id="Objetivo_Donaciones" name="Objetivo_Donaciones" required/>
				    </div>
				    <div class="lineas_img">
				    	<label for="img_proyecto">Imagen del proyecto:</label>
						<input type="file" id="img_proyecto" name="img_proyecto" accept="image/png, image/jpeg, image/jpg">
					</div>
				    <div class="lineas_img2">
				    	<label for="logo_proyecto">Logo del proyecto:</label>
						<input type="file" id="logo_proyecto" name="logo_proyecto" accept="image/png, image/jpeg, image/jpg">
					</div>
				    <div class="button1">
				        <input id="boton_form2" type="reset" value="Borrar información">
				    </div>
				    <div class="button2">
				        <input id="boton_form1" type="submit" value="Aceptar">
			   		</div>
				</form>
			</div>

			<div id="mostrar_imagenes_derecha">
				<figure class="img_der_sup"> 
					<p>No hay imagen de proyecto subida</p>
				</figure>
				<figure class="img_der_inf"> 
					<p>No hay imagen de logo subida</p>
				</figure>
			</div>
		</div>
	
		<%@ include file="../../include/footer.html" %>

	</body>

</html>
<%} %>
