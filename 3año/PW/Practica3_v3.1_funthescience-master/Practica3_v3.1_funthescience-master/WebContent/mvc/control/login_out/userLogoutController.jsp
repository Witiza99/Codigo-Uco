<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session" />

<%
	if(customerBean.getName().equals("")){
		response.sendRedirect("../../../index.jsp");
	}
	customerBean = null;
	session.invalidate();
	response.sendRedirect("../../../index.jsp");
%>