<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<%
	String email = customerBean.getEmail();
	/* si no esta logueado, devuelve a la pagina de login*/
	if (email.equals("")) {
%>
	<jsp:forward page="../view/loginView.jsp" />
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

	ArrayList<ProjectBean> projects = new ArrayList<ProjectBean>();
	
	String button = request.getParameter("submit");
	if(button.equals("Eliminar")){
		String id = request.getParameter("id");
		projectC.EliminateProject(id);
	}else{
		String column = request.getParameter("selector");

		if(column.equals("PCreados")){
			projects = projectC.getProjectsByProp("correoAutor" , email);
		}else{
			projects = projectC.getProjectsWithParticipation(email);
		}
		
		request.setAttribute("projects", projects);
	}
	
%>

<jsp:forward page="../view/MyProjectsView.jsp" />
