<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>
<%@page import="es.uco.pw.data.dao.ProjectDAO" %>
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>
    
<%
	String busqueda = request.getParameter("miBusqueda");

	if(busqueda == null){
%>
	<jsp:forward page="../view/SearchView.jsp" />
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
	ProjectDAO projects = new ProjectDAO(prop);

	ArrayList<ProjectBean> tituloProject = projects.getProjectsByProp("nombre", busqueda);
	ArrayList<ProjectBean> AllProject = tituloProject;
	Integer contador=0;
	String valor = "si";
	String author;
	if(request.getParameter("autor") != null){
		author = request.getParameter("autor");
	}else{
		author="";
	}
	if(author.equals(valor)){

		ArrayList<ProjectBean> authorProject = projects.getProjectsByProp("nombreAutor", busqueda);
		
		for(int i=0; i<authorProject.size(); i++){
			contador=0;
			for(int j=0; j<AllProject.size(); j++){
				if(authorProject.get(i).getId()==AllProject.get(j).getId()){
					contador=1;
				}
			}
			if(contador==0){
				AllProject.add(authorProject.get(i));
			}
		}
	}
	String date;
	if(request.getParameter("fecha") != null){
		date = request.getParameter("fecha");
	}else{
		date="";
	}
	if(date.equals(valor)){
		ArrayList<ProjectBean> dateProject = projects.getProjectsByProp("date", busqueda);
		
		for(int i=0; i<dateProject.size(); i++){
			contador=0;
			for(int j=0; j<AllProject.size(); j++){
				if(dateProject.get(i).getId()==AllProject.get(j).getId()){
					contador=1;
				}
			}
			if(contador==0){
				AllProject.add(dateProject.get(i));
			}
		}
	}
	
	String emailAuthor;
	if(request.getParameter("correoAutor") != null){
		emailAuthor = request.getParameter("correoAutor");
	}else{
		emailAuthor="";
	}
	if(emailAuthor.equals(valor)){
		ArrayList<ProjectBean> emailAuthorProject = projects.getProjectsByProp("correoAutor", busqueda);
		
		for(int i=0; i<emailAuthorProject.size(); i++){
			contador=0;
			for(int j=0; j<AllProject.size(); j++){
				if(emailAuthorProject.get(i).getId()==AllProject.get(j).getId()){
					contador=1;
				}
			}
			if(contador==0){
				AllProject.add(emailAuthorProject.get(i));
			}
		}
	}
	
	String category;
	//comprobar campo
	if(request.getParameter("categoria") != null){
		category = request.getParameter("categoria");
	}else{
		category="";
	}
	if(category.equals(valor)){
		
		ArrayList<ProjectBean> categoryProject = projects.getProjectsByProp("categoria", busqueda);
		
		for(int i=0; i<categoryProject.size(); i++){
			contador=0;
			for(int j=0; j<AllProject.size(); j++){
				if(categoryProject.get(i).getId()==AllProject.get(j).getId()){
					contador=1;
				}
			}
			if(contador==0){
				AllProject.add(categoryProject.get(i));
			}
		}
	}
	
	String objetiveDonation;
	if(request.getParameter("objetivosDonaciones") != null){
		objetiveDonation = request.getParameter("objetivosDonaciones");
	}else{
		objetiveDonation="";
	}
	//comprobar si es numero
	try {
		Integer comprobacion=Integer.parseInt(busqueda);
    } catch (NumberFormatException excepcion) {
    	objetiveDonation="";
    }
	if(objetiveDonation.equals(valor)){
		ArrayList<ProjectBean> objetiveDonationProject = projects.getProjectsByProp("objetivo_donaciones", busqueda);
		
		for(int i=0; i<objetiveDonationProject.size(); i++){
			contador=0;
			for(int j=0; j<AllProject.size(); j++){
				if(objetiveDonationProject.get(i).getId()==AllProject.get(j).getId()){
					contador=1;
				}
			}
			if(contador==0){
				AllProject.add(objetiveDonationProject.get(i));
			}
		}
	}
	
	request.setAttribute("AllProject", AllProject);


	
%>
	
	<jsp:forward page="../view/SearchView.jsp" />