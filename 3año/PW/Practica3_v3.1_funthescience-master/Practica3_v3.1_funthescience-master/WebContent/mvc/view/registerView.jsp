<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
	<head>
		<title>Registro</title>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta name= "description" content="Registro de usuarios">
		<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
		<meta name= "author" content="Oscar Godoy Calderón">
		<link rel="icon" href="img/logo.ico">
		<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
		<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
		<link href="../../css/estilos.css" rel="stylesheet" type="text/css"/>
		<script src="../../js/functionheader.js" type="text/javascript"></script>
		<script src="../../js/funcionesFormReg.js" type="text/javascript"></script>
		<script src="../../js/funcionesJS.js" type="text/javascript"></script>
	</head>
	<body>
		<div id="cuerpo">
			<%@include file="../../include/header.jsp" %>
			
			
			<article id="contenido-reg">
				<section class="izq-registro">
					<div class="form-registro">
						<form id="form-registro" name="formregistro" method="POST" action="../control/RegisterController.jsp">
							<input type="text" id="nombre" name="nombre" placeholder="Nombre" required="required" /><span class="ast-form">*</span><br>
							<input type="text" id="apellido" name="apellido" placeholder="Apellidos"  required="required" /><span class="ast-form">*</span><br>
							<input type="email" id="email" name="email" placeholder="Correo Electronico"  required="required" /><span class="ast-form">*</span><br>
							<span id="sp_mo"></span>
							<input type="password" id="contrasena" name="contrasena" placeholder="Contraseña" minlength="8" maxlength="30" required="required"/><span class="ast-form">*</span><br>
							<input type="text" id="movil" name="movil" placeholder="Telefono de contacto"  required="required" maxlength="9" /><span class="ast-form">*</span><br>
							<input type="text" id="direccion" name="direccion" placeholder="Direccion" /><span class="ast-form-white">*</span><br>
							<input type="text" id="provincia" name="provincia" placeholder="Provincia" /><span class="ast-form-white">*</span><br>
							<input type="text" id="localidad" name="localidad" placeholder="Localidad" /><span class="ast-form-white">*</span><br>
							<input type="text" id="pais" name="pais" placeholder="Pais" /><span class="ast-form-white">*</span><br>
							<input type="text" id="dni" name="dni" placeholder="DNI" /><span class="ast-form-white">*</span><br>
							<select name="grados" id="grados">
								<option>--selecciona una opcion--</option>
								<option value="Fisica">F&iacute;sica</option>
								<option value="Quimica">Qu&iacute;mica</option>
								<option value="Medicina">Medicina</option>
								<option value="Arquitectura">Arquitectura</option>
								<option value="Astronomia">Astronom&iacute;a</option>
								<option value="Ingenieria">Ingenier&iacute;a</option>
							</select>
							<br>
							<span class="form_camp_oblig">(*) Campos obligatorios</span>
							<br>
							<textarea name="descripcion_reg" rows="5" cols="30" >Envia un comentario</textarea>
							<br>
							<input class="form-button" type="submit" name="envio" value="Enviar"/>
							<input class="form-button" type="reset" name="cancelar" value="Cancelar"/>
						</form>
					</div>
				</section>
				<section class="der-registro">	
					<div id="carrusel-reg">
						<div class="slideshow-container">

						  <!-- Se generaran tantos bloques con imagenes para el carrusel de acuerdo a la cantidad limite 
						  a mostrar de los proyectos en los que se involucra mas la gente. -->
							<div class="mySlides fade">
								<div class="numbertext">1 / 3</div>
									<img src="../../img/image1.jpg" alt="" style="width:100%"/>
									<!--<div class="text">Caption Text</div>-->
									<div>Imagen de nuestra empresa
									</div>
							</div>
							<!-- FIN DE COMENTARIO -->
							<!-- ***************** -->
							
							<!-- A modo de relleno para hacer una muestra de la pagina -->
							<div class="mySlides fade">
								<div class="numbertext">2 / 3</div>
									<img src="../../img/image2.jpg" alt="" style="width:100%"/>
									<!--<div class="text">Caption Text</div>-->
									<div>Imagen de nuestra empresa
									</div>
							</div>

							<div class="mySlides fade">
								<div class="numbertext">3 / 3</div>
									<img src="../../img/image3.jpg" alt="" style="width:100%"/>
									<!--<div class="text">Caption Text</div>-->
									<div>Imagen de nuestra empresa
									</div>
							</div>

						  <!-- Next and previous buttons -->
						  <a class="prev" onclick="plusSlides(-1)">&#10094;</a>
						  <a class="next" onclick="plusSlides(1)">&#10095;</a>
						</div>
					</div>
				</section>
			</article>
			

			<%@ include file="../../include/footer.html" %>
			
		</div>
	</body>
</html>
