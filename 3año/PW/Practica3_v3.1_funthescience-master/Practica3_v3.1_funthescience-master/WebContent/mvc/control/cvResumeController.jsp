<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>

<%@page import="es.uco.pw.data.dao.ResumeDAO" %>
<%@page import="java.util.Properties,java.io.File" %>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session" />
<jsp:useBean id="resumeBean" class="es.uco.pw.display.bean.ResumeBean" scope="request"/>

<%-- si la propiedad name de customerBean esta vacia, lo enviara a hacer login --%>
<%	if(customerBean.getName().equals("")){ %>
		<jsp:forward page="../view/userLoginView.jsp"/>
<%	}
	
	String driver2 = application.getInitParameter("driver");
	String dbconn2 = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver2);
	prop.put("dbconn",dbconn2);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	ResumeDAO resume = new ResumeDAO(prop);
	
	/* Si llega dato de profileViewSuccess para realizar la carga de datos del curriculum de la persona */
	if(request.getParameter("consulta") != null){
		
		if(resume.dataForPDF(customerBean.getIndex(), "")){
			resumeBean = resume.getCVResume();
		}
		request.setAttribute("resumeBean",resumeBean);
%>
	<jsp:forward page="../view/cvResumeView.jsp" />
<%	
	}
	
	/************************************************/
	/************************************************/
	boolean showCV = true;
	int seleccion = 0;
	if(request.getParameter("mostrarCV") != null){

			if(request.getParameterValues("showCV") != null){
				seleccion = 1;
			}

		
		showCV = resume.showCVUsers(seleccion,customerBean.getIndex());
		
		if(!showCV){
			%>
			<jsp:forward page="../view/cvResume/cvResumeViewFail.jsp"/>
			<%
		}else{
			%>
			<jsp:forward page="../view/cvResume/cvResumeViewSuccess.jsp"/>
			<%
		}
	}
	/************************************************/
	/************************************************/
	
	/** Si llegan datos de la pagina cvResumeView para ser actualizados o insertados por primera vez **/
	String fullName = request.getParameter("fullName");
	String brief_intro = request.getParameter("brief_intro");
	String address = request.getParameter("address");
	String email = request.getParameter("email");
	String phone = request.getParameter("phone");
	String experience_professional = request.getParameter("experience_professional");
	String languages[] = request.getParameterValues("languages");
	String programming[] = request.getParameterValues("programming");
	String studies = request.getParameter("studies");
	String referer = request.getParameter("referer");
	String id_user = Integer.toString(customerBean.getIndex());
	//String aceptar[] = request.getParameterValues("showCV");
	int aceptar = 0;
	
	if(request.getParameterValues("showCV") != null){
		aceptar = 1;
	}

	String lista[] = {fullName,brief_intro,address,email,phone,experience_professional,studies,referer,id_user};

	boolean status = resume.cvUser(lista,languages,programming,aceptar);
	
	/** Generar el PDF */
	String path = config.getServletContext().getRealPath(".");
	path += "/pdf/";
	boolean state = resume.dataForPDF(customerBean.getIndex(),path);
	
	if(status && !state){
%>
	<jsp:forward page="../view/cvResume/cvResumeViewFailPDF.jsp"/>
<%
	}
	
	if(status){
%>
	<jsp:forward page="../view/cvResume/cvResumeViewSuccess.jsp"/>
<% } else { %>
	<jsp:forward page="../view/cvResume/cvResumeViewFail.jsp"/>
<% } %>