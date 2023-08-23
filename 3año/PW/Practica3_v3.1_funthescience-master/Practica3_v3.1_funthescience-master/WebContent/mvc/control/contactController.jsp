<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>
<%@page import="es.uco.pw.data.dao.messageDAO" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<%
	String msg = request.getParameter("mensaje");
	String categoria = (String)request.getParameter("cat");
	String id = (String)request.getParameter("id");

	if (customerBean.getEmail().equals("")){
		request.setAttribute("errorMsg", "Debe estar logueado");
		%>
		<jsp:forward page="../view/contactViewFail.jsp" />
		<%	
	}
	
	//Primero hay que comprobar de donde se viene
	
	//Y hacer la conexion para extraer los proyectos con la misma categoria
	
	String pass = request.getParameter("password");
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));

//Creo el conector al projectDao
	ProjectDAO projectC = new ProjectDAO(prop);
	messageDAO msgC = new messageDAO(prop);
	
	ArrayList<ProjectBean> projects = projectC.getProjectsByProp("categoria", categoria);
	request.setAttribute("projects", projects);
	
	if(msg == null || msg == ""){
		//Le paso la categoria para despues tenerla para el valver al hacer action para el email
		%>
		<jsp:forward page="../view/contactView.jsp?cat=<% out.println(categoria); %>" />
		<%	
	}
	else{
		int statusMsg = msgC.newMessage(Integer.valueOf(id), msg, customerBean.getName());			
		if(statusMsg == 0){
			System.out.println("Error al guardar el mensaje");
		}
		//Faltan las paginas de error y success de contactar
		%>
		<jsp:forward page="../view/contactViewSuccess.jsp" />
		<%	
	}




%>
