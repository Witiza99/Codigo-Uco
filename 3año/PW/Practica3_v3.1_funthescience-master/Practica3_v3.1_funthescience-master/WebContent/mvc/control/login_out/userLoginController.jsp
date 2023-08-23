<%@page language="java" pageEncoding="ISO-8859-1"%>

<%@page import="es.uco.pw.data.dao.UserDAO"%>
<%@page import="java.util.Properties" %>

<%-- coge el bean de la session --%>
<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<%
	/* si ya esta logueado, devuelve a la pagina de inicio*/
	if (customerBean.getEmail() != "") {
		response.sendRedirect("../../../index.jsp");
	}

	String email = request.getParameter("email");
	
	/* si el campo email esta vacio, no viene de la vista userLoginView.jsp */
	if(email == "") {
		response.sendRedirect("../../view/userLoginView.jsp");
	}

	String pass = request.getParameter("password");
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	UserDAO user = new UserDAO(prop);

	/* si status es true almacenara en customerBean */
	boolean status = user.userLogin(email, pass);
	
	if(status){
		customerBean = user.getCustomer();
		session.setAttribute("customerBean",customerBean);
		response.sendRedirect("../../../index.jsp");
	}else{
		session.invalidate();

		response.sendRedirect("../../view/userLoginFail.jsp");
	}
%>
