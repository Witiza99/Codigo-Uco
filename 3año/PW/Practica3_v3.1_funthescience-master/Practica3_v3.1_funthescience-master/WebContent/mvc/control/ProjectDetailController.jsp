<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>

<%
	String id = request.getParameter("id");

	if(id == null){
%>
	<jsp:forward page="../view/ProjectDetailView.jsp" />
<%	
	}
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));

//Creo el conector al projectDao
	ProjectDAO projectC = new ProjectDAO(prop);

	
	ArrayList<ProjectBean> projects = projectC.getProjectsByProp("indice", id);
	ArrayList<String> msgs = projectC.getMessages(id);
	
	
	request.setAttribute("projects", projects);
	request.setAttribute("messages", msgs);
%>

<jsp:forward page="../view/ProjectDetailView.jsp" />