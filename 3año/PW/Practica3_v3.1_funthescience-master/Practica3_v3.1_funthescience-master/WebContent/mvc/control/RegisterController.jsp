<%@page language="java" pageEncoding="ISO-8859-1"%>

<%@page import="es.uco.pw.data.dao.UserDAO"%>
<%@page import="es.uco.pw.display.bean.CustomerBean"%>
<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<%
	/* si ya esta logueado, devuelve a la pagina de inicio*/
	if (customerBean.getEmail() != "") {
		
%>
	<jsp:forward page="../../index.jsp" />
	
<%
	}

	String email = request.getParameter("email");
	
	/* si el campo email esta vacio, no viene de la vista RegisterView.jsp */
	if(email == "") {
%>
	<jsp:forward page="../view/registerView.jsp"></jsp:forward>
	
<% 
	}
	
	String driver = application.getInitParameter("driver");
	String dbconn = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver);
	prop.put("dbconn",dbconn);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	UserDAO user = new UserDAO(prop);
	
	CustomerBean cb = new CustomerBean();
	cb.setEmail(request.getParameter("email"));
	cb.setName(request.getParameter("nombre"));
	cb.setLastName(request.getParameter("apellido"));
	cb.setPassword(request.getParameter("contrasena"));
	cb.setPhone(Integer.parseInt(request.getParameter("movil")));
	cb.setAddress(request.getParameter("direccion"));
	cb.setProvince(request.getParameter("provincia"));
	cb.setLocation(request.getParameter("localidad"));
	cb.setCountry(request.getParameter("pais"));
	cb.setDNI(request.getParameter("dni"));
	cb.setProfession(request.getParameter("grados"));
	cb.setAdditional_paragraph(request.getParameter("descripcion_reg"));
	
	boolean status = user.register(cb);

	if(status){
		response.sendRedirect("../../index.jsp");
	}else{
		response.sendRedirect("../view/registerFail.jsp");
	}

	
%>