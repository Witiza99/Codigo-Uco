<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Donaci&oacuten Fallida</title>
</head>
<body>
	<h1>Donaci&oacuten Fallida</h1>
	<p><% out.println(request.getAttribute("errorDonar")); %></p>
	<a href="../view/donateView.jsp?id=<% out.println(request.getParameter("id")); %>">Volver a intentar</a><br>
	<a href="../../index.jsp">Ir al home</a>
</body>
</html>