<%@page language="java" pageEncoding="ISO-8859-1"%>

<%@page import="es.uco.pw.data.dao.ProjectDAO"%>
<%@page import="es.uco.pw.display.bean.ProjectBean"%>
<%@page import="es.uco.pw.data.dao.UserDAO"%>
<%@page import="es.uco.pw.display.bean.CustomerBean"%>
<%@page import="java.util.Properties,es.uco.pw.data.dao.ConexionDAO" %>

<%@ page import="java.util.List" %>
<%@ page import="java.util.Calendar" %>

<%@ page import="org.apache.commons.io.*" %>
<%@page import="org.apache.commons.fileupload.FileItem"%>
<%@page import="org.apache.commons.fileupload.FileUploadException"%>
<%@page import="org.apache.commons.fileupload.servlet.ServletFileUpload"%>
<%@page import="java.io.File"%>
<%@page import="org.apache.commons.fileupload.disk.DiskFileItemFactory"%> 
<%@ page import="org.apache.commons.fileupload.disk.DiskFileItemFactory"%>

<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>
<%	

	/* si no esta logueado, le lleva a la pagina de registro*/
	if (customerBean.getEmail().equals("")) {
		
%>
	<jsp:forward page="../view/registerView.jsp" />
	
<%
	}
	
	/* si el campo Titulo esta vacio, no viene de la vista RegisterView.jsp */
	String Titulo = request.getParameter("titulo");
	if(Titulo == "") {
%>
	<jsp:forward page="../view/NewProjectView.jsp"></jsp:forward>
	
<% 
	}
	
	String driver = application.getInitParameter("driver");
	String dbconn = application.getInitParameter("dbconn");
	Properties prop = new Properties();
	prop.put("driver",driver);
	prop.put("dbconn",dbconn);
	prop.put("user",application.getInitParameter("dbuser"));
	prop.put("password",application.getInitParameter("dbpassword"));
	
	ProjectDAO CreateProject = new ProjectDAO(prop);
	
	ProjectBean cb = new ProjectBean();
	
	//String ubicacion=getServletContext().getRealPath("/")+"/WebContent/img/img_project/";
	//String ubicacion=getServletContext().getRealPath("/")+"WebContent/img/img_project/";
    	
    DiskFileItemFactory factory = new DiskFileItemFactory();
    //factory.setSizeThreshold(0);
    //factory.setRepository(yourTempDirectory);
	ServletFileUpload upload = new ServletFileUpload(factory);
    
    //upload.setSizeMax(1024*1024*5);
		
	try{ 
		
		// Parse the request
		List<FileItem> items = upload.parseRequest(request);
		
		// Process the uploaded items
		for (int i = 0; i < items.size(); i++) {
	
			FileItem item = (FileItem) items.get(i);
		
	   		if (! item.isFormField()) {
	        
		    	if(item.getSize()>0){
			    	if(item.getFieldName().equals("img_proyecto")) {
			    		
		    			File file = new File(config.getServletContext().getRealPath("/")+"img/img_project/"+item.getName());
                        if(file.exists()){
                        	file.delete();
                        }
                        System.out.println(file.getPath());
                        item.write(file);
				    	cb.setImageProject("../../img/img_project/"+item.getName());
				    	
			    	}else if(item.getFieldName().equals("logo_proyecto")) {
			    		
			    		File file = new File(config.getServletContext().getRealPath("/")+"img/img_logo/"+item.getName());
                        if(file.exists()){
                        	file.delete();
                        }
                        System.out.println(file.getPath());
                        item.write(file);
				    	cb.setLogoProject("../../img/img_logo/"+item.getName());
			    		
			    	}
		    	}
        
		    } else if(item.getFieldName().equals("Titulo")) {
		    	String TituloProyecto=item.getString();
		    	cb.setTitle(TituloProyecto);    	
		    } else if(item.getFieldName().equals("Objetivo_Donaciones")){  	
		    	try {
		    		Integer ObjetivoDonaciones=Integer.parseInt(item.getString());
			    	cb.setObjectiveDonation(ObjetivoDonaciones);
		        } catch (NumberFormatException excepcion) {
		        	cb.setObjectiveDonation(0);
		        }
		    } else if(item.getFieldName().equals("Descripcion_breve")){
		    	String DescripcionBreve=item.getString();
		    	cb.setDescriptionbrief(DescripcionBreve);
		    } else if(item.getFieldName().equals("Descripcion_completa")){
		    	String DescripcionCompleta=item.getString();
		    	cb.setDescriptionComplete(DescripcionCompleta);
		    } else if(item.getFieldName().equals("Participantes")){
		    	String Participantes=item.getString();
		    	cb.setParticipantes(Participantes);
		    } else if(item.getFieldName().equals("Pagina_Web")){
		    	String PaginaWeb=item.getString();
		    	cb.setWebPages(PaginaWeb);
		    } else if(item.getFieldName().equals("Categorias")){
		    	String Categorias=item.getString();
		    	cb.setCategory(Categorias);
		    }
	    
		}
	    
	}catch(FileUploadException e){
        out.println("#error al subir archivo" + e);
    } 
	
	
	
	cb.setAuthor(customerBean.getName()+" "+customerBean.getLastName());
	cb.setAuthorMail(customerBean.getEmail());
	cb.setAuthorIndex(customerBean.getIndex());
	
	Calendar c = Calendar.getInstance();
    String dia = Integer.toString(c.get(Calendar.DATE));
    String mes = Integer.toString(c.get(Calendar.MONTH));
    String ano = Integer.toString(c.get(Calendar.YEAR));
	String Date=dia+" de "+mes+" de "+ano;
	cb.setDate(Date);
	
	boolean status = CreateProject.newProject(cb);

	if(status){
		//System.out.println("true");
		/* si es corrector se redirecciona a detalle_proyecto CAMBIAR */
		response.sendRedirect("../control/ProjectDetailController.jsp?id="+cb.getId());
	}else{
		//System.out.println("false");
		/* si no se mantiene en la misma pagina */
		response.sendRedirect("../view/NewProjectView.jsp");
	}
%>
