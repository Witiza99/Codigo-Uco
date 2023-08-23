<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@page errorPage="../../errorPage/error.jsp" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>
<jsp:useBean id="resumeBean" class="es.uco.pw.display.bean.ResumeBean" scope="request"/>


<% if(customerBean.getName().equals("")){ %>
	<jsp:forward page="./userLoginView.jsp" />
<% }else{ %>

<jsp:setProperty property="*" name="resumeBean"/>

<!DOCTYPE html>
<html>
	<head>
		<title>Curriculum</title>
		<meta charset="UTF-8">
		<meta name= "description" content="Curriculum de usuario">
		<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
		<meta name= "author" content="Oscar Godoy Calderon">
		<meta name= "viewport" content="width=device-width, initial-scale=1.0">
		<link rel="icon" href="../../img/logo.ico">
		<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
		<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
		<link href="../../css/estilos.css" rel="stylesheet" type="text/css"/>
		<script src="../../js/functionheader.js" type="text/javascript"></script>
		<script src="../../js/funcionesFormReg.js" type="text/javascript"></script>
		<script src="../../js/funcionesJS.js" type="text/javascript"></script>
	</head>
	<body>
		<div id="cuerpo">
		 
			<!-- ******************* Inicio Cabecera ********************************   -->
			<jsp:include page="../../include/header.jsp"/>
			<!-- ******************* Fin Cabecera ********************************   -->
			
			
			<div id="contenido-curr">
				<div id="crear-curriculum">
					<form id="form-curriculum" name="formcurriculum" method="POST" action="../control/cvResumeController.jsp">
						<div>
							<fieldset>
								<legend>DATOS PERSONALES</legend>
								<div class="camp-cur">
									<input type="text" id="nombre" name="fullName" placeholder="Nombres y Apellidos" required="required" value="<jsp:getProperty property="fullName" name="resumeBean"/>" />
								</div>
								<div class="sec-row-cur">
									<div class="col-izq-cur">
										<p>Redacta una breve introduccion:</p>
										<textarea id="text-cur" name="brief_intro" rows="5" cols="20" required="required"><jsp:getProperty property="brief_intro" name="resumeBean"/></textarea>
									</div>
									<div class="col-der-cur">
										<input type="text" id="direccion" name="address" placeholder="Direccion" required="required" value="<jsp:getProperty property="address" name="resumeBean"/>" />
										<input type="email" id="email" name="email" placeholder="Correo electronico" required="required" value="<jsp:getProperty property="email" name="resumeBean"/>"/>
										<span id="sp_mo"></span>
										<% if(resumeBean.getPhone() == 0){ %>
										<input type="text" id="movil" name="phone" placeholder="Numero de telefono" maxlength="9" required="required" />
										<%}else{ %>
										<input type="text" id="movil" name="phone" placeholder="Numero de telefono" maxlength="9" required="required" value="<jsp:getProperty property="phone" name="resumeBean"/>"/>
										<% } %>
									</div>
								</div>
							</fieldset>
						</div>
						<div class="div-cur"></div>
						<div>
							<fieldset>
								<legend>EXPERIENCIA PROFESIONAL</legend>
								<div class="exp-laboral">
									<textarea rows="5" name="experience_professional" required="required"><jsp:getProperty property="experience_professional" name="resumeBean"/></textarea>
								</div>
								
								<div class="thi-row-cur">
									<div class="col-izq-cur">
										<p>IDIOMAS</p>
										
										<input type="checkbox" name="languages" value="Castellano"/> Castellano<br>
										<input type="checkbox" name="languages" value="Ingles"/> Ingles<br>
										<input type="checkbox" name="languages" value="Frances" /> Frances<br>
										<input type="checkbox" name="languages" value="Aleman"/> Aleman<br>
										<input type="checkbox" name="languages" value="Otros" /> Otros<br>
										<span id="errIdiomas" class="sp_mo"></span>

									</div>
									<div class="col-der-cur">
										<p>FORMACION ACADEMICA</p>
										<div class="exp-laboral">
											<textarea rows="5" name="studies" required="required"><jsp:getProperty property="studies" name="resumeBean"/></textarea>
										</div>
									</div>
								</div>
								<div class="four-row-cur">
									<div class="col-izq-cur">									
										<p>LENGUAJES</p>
										<input type="checkbox" name="programming" value="C/C++"/> C/C++<br>
										<input type="checkbox" name="programming" value="Fortran"/> Fortran<br>
										<input type="checkbox" name="programming" value="MatLab"/> MatLab<br>
										<input type="checkbox" name="programming" value="SQL"/> SQL<br>
										<input type="checkbox" name="programming" value="Otros"/> Otros<br>
										<span id="errProgramacion" class="sp_mo"></span>
									</div>
									<div class="col-der-cur">
										<p>REFERENCIAS</p>
										<div class="exp-laboral">
											<textarea rows="5" name="referer" required="required"><jsp:getProperty property="referer" name="resumeBean"/></textarea>
										</div>
									</div>
								</div>
								<div class="check-accept">
									<% if(resumeBean.getShow_cv() == 0){ %>
									 <input type="checkbox" name="showCV" value="Acepto"/>Acepto poner mi Curriculum disponible para todo el p&uacute;blico.
									 <% } else { %>
									 <input type="checkbox" name="showCV" value="Acepto" checked="true"/>Acepto poner mi Curriculum disponible para todo el p&uacute;blico.
									 <% } %>
								</div>
							</fieldset>
						</div>
						<div class="">
							<input type="submit" class="form-button" name="envio" value="Enviar"/>
							<input type="reset" class="form-button" name="cancelar" value="Cancelar"/>
						</div>
					</form>
				</div>
			</div>
			
			<!-- ******************* Inicio Footer *****************************   -->
			<jsp:include page="../../include/footer.html"/>
			<!-- ******************* Fin Footer ********************************   -->
		</div>
	</body>
</html>
<% 
	resumeBean = null; 
}	
%>
