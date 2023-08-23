<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
    <%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
	<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
	<%@page import="java.util.ArrayList" %>
	<%@page import="es.uco.pw.display.bean.ProjectBean" %>
	<%@page import="es.uco.pw.data.dao.messageDAO" %>

	<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<%
	//primero hay que comprobar que esta logueado
	if (customerBean.getEmail().equals("")) {
		request.setAttribute("errorDonar", "Debe estar logueado para poder donar.");
		
	%>
		<jsp:forward page="../view/donateViewFail.jsp" />
	<%
	}
	
	String id = (String)request.getParameter("id");
//	System.out.println("idDonar: " + id);
	
	String cantidadDonar = request.getParameter("cantidadDonar");
	String metPago = request.getParameter("metPago");
	String msg = request.getParameter("comentarioP");
	
	boolean anonimo = true;
	if(request.getParameter("DAnonima") == null){
		anonimo = false;
	}
	boolean terminos = true;
	if(request.getParameter("Lterm") == null){
		terminos = false;
	}
	
	
	if(!terminos){
		request.setAttribute("errorDonar", "Debe aceptar los terminos y condiciones.");
		%>
		<jsp:forward page="../view/donateViewFail.jsp" />
		<%
	}

	if(cantidadDonar == ""){
		request.setAttribute("errorDonar", "Debe indicar una cantidad");
		%>
		<jsp:forward page="../view/donateViewFail.jsp?id=<% out.println(id); %>" />
		<%
	}
/*
	System.out.println("cantidad: " + cantidadDonar);
	System.out.println("metodo pago: " + metPago);
	System.out.println("Anonima: " + anonimo);
	System.out.println("Terminos: " + terminos);*/
	
	
	String pass = request.getParameter("password");
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));

	ProjectDAO projectC = new ProjectDAO(prop);
	messageDAO msgC = new messageDAO(prop);
	
	ArrayList<ProjectBean> projects = projectC.getProjectsByProp("indice", id);
//	System.out.println("dinero actual: " + projects.get(0).getCurrentDonation());
	
	Integer aux = Integer.valueOf(projects.get(0).getCurrentDonation()) + Integer.valueOf(cantidadDonar);
	

	Integer status = projectC.updateProjectByID(id, "donaciones_actuales", String.valueOf(aux));

	//Tratamiento de los mensajes
	if(msg != null && msg != ""){
		int statusMsg;
		if(anonimo){
			statusMsg = msgC.newMessage(Integer.valueOf(id), msg, "Anonimo");
		}
		else{
			statusMsg = msgC.newMessage(Integer.valueOf(id), msg, customerBean.getName());			
		}
		
		if(statusMsg == 0){
			System.out.println("Error al guardar el mensaje");
		}
	}

	if(status == 0){
		request.setAttribute("errorDonar", "Error al realizar el pago.");
		%>
		<jsp:forward page="../view/donateViewFail.jsp?id=<% out.println(id); %>" />
		<%
	}
	else{
		%>
		<jsp:forward page="../view/donateViewCorrect.jsp" />
		<%
	}
%>
