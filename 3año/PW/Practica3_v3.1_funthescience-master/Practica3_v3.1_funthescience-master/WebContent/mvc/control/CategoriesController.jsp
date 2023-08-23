<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>
    
<%
	String categoria = request.getParameter("seleccion_categoria");
//	System.out.println("categoria: " + categoria);

	if(categoria == null){
%>
	<jsp:forward page="../view/CategoriesView.jsp" />
<%	
	}
	
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
	
	ArrayList<ProjectBean> projects = projectC.getProjectsByProp("categoria", categoria);
//	System.out.println("Tamaño controller: " + projects.size());
	
	for(int i=0; i<projects.size(); i++){
		if(projects.get(i).getObjectiveDonation() > projects.get(i).getCurrentDonation()){
			projects.get(i).setStatus("En progreso");
		}
		else{
			projects.get(i).setStatus("Objetivo alcanzado");
		}
		
	}

	request.setAttribute("projects", projects);
%>
	
	<jsp:forward page="../view/CategoriesView.jsp" />
