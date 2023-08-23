<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO,es.uco.pw.data.dao.UserDAO,es.uco.pw.data.dao.ResumeDAO" %>

<%-- bean perfil para que tanto usuarios como invitados puedan tener acceso a los datos de autor de proyecto --%>
<jsp:useBean id="perfil" class="es.uco.pw.display.bean.CustomerBean" scope="request"/>
<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>
<jsp:useBean id="resume" class="es.uco.pw.display.bean.ResumeBean" scope="request"/>

<%-- Si no se encuentra el atributo indexProfile, redirecciona a profileViewFail a modo de control --%>
<%	

/*if(session.getAttribute("indexProfile") == null && request.getParameter("id") == null){*/
	if(customerBean.getIndex() == 0 && (request.getParameter("id") == null)){ %>

	<jsp:forward page="../view/profileViewFail.jsp" />		
	
<%
	}

	int index=0;

	if(request.getParameter("id") != null){
		index = Integer.parseInt(request.getParameter("id"));
	}else{
		/*if(session.getAttribute("indexProfile") != null){*/
		if(customerBean.getIndex() != 0){
			index = customerBean.getIndex();
		}
	}
		
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	/** Carga de los datos del perfil del autor del proyecto */
	UserDAO user = new UserDAO(prop);
	boolean status = user.queryUserProfile(index);
	
	/** Para carga de PDF */
	ResumeDAO rs = new ResumeDAO(prop);
	int number[] = {0,0};
	number = rs.getPhoneCV(index);
	resume.setPhone(number[0]);
	resume.setShow_cv(number[1]);
	
	if(status){
		perfil = user.getCustomer();
		request.setAttribute("perfil",perfil);
		request.setAttribute("resume",resume);
%>
		<jsp:forward page="../view/profileViewSuccess.jsp"/>
<%		
	}else{
%>
		<jsp:forward page="../view/profileViewFail.jsp"/>
<%		
	}
%>
