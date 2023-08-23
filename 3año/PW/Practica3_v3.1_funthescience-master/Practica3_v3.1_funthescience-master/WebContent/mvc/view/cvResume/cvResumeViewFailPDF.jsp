<%@page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<% if(customerBean.getName().equals("")){
		response.sendRedirect("../../../index.jsp");
}else{
%>

<!DOCTYPE html>
<html>
	<head>
		<title>CvResumeSuccess</title>
		<meta name= "author" content="Oscar Godoy Calderon">
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0"> 
		<meta name="nombre" content="Pagina de Modificar Datos">
		<meta name="palabras_clave" content="HTML,CSS,JavaScript">
		<link rel="icon" href="../../img/logo.ico">
		<link href="../../css/estilos.css" rel="stylesheet" type="text/css"/>
		<link href="../../css/estilos_HF.css" rel="stylesheet" type="text/css"/>
		<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
		<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
		<script src="../../js/functionheader.js" type="text/javascript"></script>
		<script>
			window.history.pushState(null, '', 'http://localhost:8080/fundthescience/mvc/view/cvResume/cvResumeViewFail.jsp');    
		</script>
	</head>
	<body>
		<div id="cuerpo">
			
			<jsp:include page="../../../include/header_desk.jsp"/>
						
			<div style="padding: 100px;background:white;">
				<h3>Ooooppppssss!! Hubo un error.</h3>
				<h4>Se guardo correctamente los datos pero no se pudo crear el PDF</h4>
				<a href="../../index.jsp">volver al Home</a>
			</div>
			
			<%@include file="../../../include/footer.html"%>
		</div>
	</body>
</html>
<%}%>