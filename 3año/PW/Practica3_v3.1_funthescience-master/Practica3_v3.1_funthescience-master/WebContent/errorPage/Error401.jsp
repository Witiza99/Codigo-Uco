<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@ page isErrorPage="true" %>
<!DOCTYPE>
<html>
<head>
    <meta name= "keywords" content="HTML,CSS,XML,JavaScript">
<title>Error 401</title>
<link href="https://cdn.3up.dk/flexgrid.io@2.5.1/css/flexgrid.min.css" type="text/css" rel="stylesheet"/>
    <link href="./css/Error_style.css" type="text/css" rel="stylesheet" />
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://cdn.3up.dk/in-view@0.6.1"></script>
    <script src="./js/error_js.js"></script>
</head>
<body>

	<a href="./index.jsp">Ir a inicio </a>
	<div class="container">
    <div class="row">
        <div class="xs-12 md-6 mx-auto">
            <div id="countUp">	
            	<!-- <h1>Error 404</h1>
				<h3>Hay un problema! No se encuentra la pagina solicitada</h3> -->
                <div class="number" data-count="401">0</div>
                <div class="text">Page not found</div>
                <div class="text">This may not mean anything.</div>
                <div class="text">I'm probably working on something that has blown up.</div>
            </div>
        </div>
    </div>
</div>    
</body>
</html>