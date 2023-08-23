<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@ page isErrorPage="true" %>
<html>
<head>
    <meta charset="utf-8">
    <meta name="description" content="Pagina para loguearte">
    <meta name= "keywords" content="HTML,CSS,XML,JavaScript">
    <meta name= "author" content="Oscar Godoy">
    <link rel="icon" href="../img/logo.ico">
    <link href="../css/Error_style.css" type="text/css" rel="stylesheet" />
    <script>
    	window.history.pushState(null, '', 'http://localhost:8080/Practica3_v2/errorPage/error.jsp');  
    </script>
</head>
<body>

	<div class="noise"></div>
	<div class="overlay"></div>
	<div class="terminal">
	  <h1>Error Interno <span class="errorcode">Java</span></h1>
	  	<h3>Lamentamos el error!</h3>
		Ha ocurrido el siguiente error:<br/>
		
		<%=exception%>
		
	  <p class="output">The page you are looking for might have been removed, had its name changed or is temporarily unavailable.</p>
	  <p class="output">Please try to go back on the browser or <a href="../index.jsp">return to the homepage</a>.</p>
	  <p class="output">Good luck.</p>
	</div>
</body>
</html>