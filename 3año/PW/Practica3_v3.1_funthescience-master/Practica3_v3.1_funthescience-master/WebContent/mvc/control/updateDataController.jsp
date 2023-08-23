<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<%@page import="es.uco.pw.data.dao.ConexionDAO,es.uco.pw.data.dao.UserDAO,es.uco.pw.data.dao.ProjectDAO,es.uco.pw.display.bean.ProjectBean" %>
<%@page import="java.util.Properties,java.util.ArrayList" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session" />
<jsp:useBean id="perfil" class="es.uco.pw.display.bean.CustomerBean" scope="request" />
<jsp:useBean id="projectsBean" class="es.uco.pw.display.bean.ProjectBean" scope="request" />

<%-- en caso pretenda acceder a la pagina sin haber hecho login --%>
<% if(customerBean.getName().equals("")){ %>

		<jsp:forward page="../view/userLoginView.jsp"/>		
<%
	}
	
	/*En caso pretenda cambiar un perfil que no le corresponde */
	if(customerBean.getIndex() != (Integer)session.getAttribute("indexProfile")){
%>
	<jsp:forward page="../view/updateData/updateDataFail.jsp"/>
<%	
	}
	
	/* Para realizar la carga de las imagenes segun el autor y posterioremente la actualizacion de datos en la pagina updateDataView */
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	String cad1 = (String)request.getParameter("modificar");
	if(cad1 != null){
		/*****/
		ProjectDAO projects_author = new ProjectDAO(prop);
		
		String index = Integer.toString(customerBean.getIndex());
		ArrayList<ProjectBean> projects = projects_author.getProjectsByProp("indiceAutor", index);
		
		request.setAttribute("projects_author",projects);
		/*******/
%>
		<jsp:forward page="../view/updateDataView.jsp"/>
<%
	}
	
	UserDAO user = new UserDAO(prop);
	
	String name = (String)request.getParameter("nombre");
	String lastName = (String)request.getParameter("apellido");
	String phone = (String)request.getParameter("movil");
	String email = (String)request.getParameter("email");
	String address = (String)request.getParameter("direccion");
	String province = (String)request.getParameter("provincia");
	String location = (String)request.getParameter("localidad");
	String country = (String)request.getParameter("pais");
	String password = (String)request.getParameter("contrasena");
	String profession = (String)request.getParameter("grados");
	String parrafo = (String)request.getParameter("descripcion_reg");
	
	String lista[] = {email,name,lastName,phone,address,province,location,country,profession,password,parrafo};
	
	boolean status = user.updateDataUser(lista,customerBean.getIndex());

	if(status){
%>
	<jsp:forward page="../view/updateData/updateDataViewSuccess.jsp"/>
<%
	}else{
%>
	<jsp:forward page="../view/updateData/updateDataViewFail.jsp"/>
<%
	}
%>
