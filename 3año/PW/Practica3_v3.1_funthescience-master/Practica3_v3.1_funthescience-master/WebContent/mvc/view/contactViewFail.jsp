<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Mensaje Fallido</title>
</head>
<body>
	<h1>Mensaje Fallido</h1>
	<p><% out.println(request.getAttribute("errorMsg")); %></p>
	<a href="../../index.jsp">Ir al home</a>
</body>
</html>