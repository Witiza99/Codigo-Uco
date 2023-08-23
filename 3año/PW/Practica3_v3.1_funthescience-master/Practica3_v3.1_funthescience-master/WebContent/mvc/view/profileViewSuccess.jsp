<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<%@page errorPage="../../errorPage/error.jsp" %>

<%-- utilizado para la comunicacion entre las paginas para ver el perfil de un autor --%>
<jsp:useBean id="perfil" class="es.uco.pw.display.bean.CustomerBean" scope="request"/>
<jsp:useBean id="resume" class="es.uco.pw.display.bean.ResumeBean" scope="request"/>

<%-- utilizado por el propio autor logueado para mostrar su perfil y posible modificacion --%>
<jsp:useBean id="customerBean" class="es.uco.pw.display.bean.CustomerBean" scope="session"/>

<jsp:setProperty property="*" name="perfil"/>

<% if(perfil.getName().equals("")){ %>
	<jsp:forward page="./profileViewFail.jsp"/>
<% } else { %>

<!DOCTYPE html>
<html>
  <head>
    <title>Mi perfil</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name= "keywords" content="HTML,CSS,XML,JavaScript">
    <meta name= "author" content="Rafael Hormigo">
    <link rel="icon" href="../../img/logo.ico">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.11.2/css/all.min.css">
    <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
    <link href="../../css/Estilo.css" type="text/css" rel="stylesheet" />
    <link href="../../css/estilos_HF.css" type="text/css" rel="stylesheet" />
    <script src="../../js/functionheader.js" type="text/javascript"></script>
  <script src="../../js/funciones_Rafa.js" type="text/javascript"></script>
  </head>
  <body>
   		<%-- --%>
   		<jsp:include page="../../include/header.jsp" />
   		<%-- --%>
        
      <div id="cuerpo" style="float: left;width: 100%;">
        <div id="info">
          <!-- Esta informacion se traera de la base de datos -->
          <div id="info_personal">
          	<h4>Perfil del Autor <i class="fa fa-address-card" style="font-size:25px;color:blue;"></i>:</h4>
            <p class="parrafo"><jsp:getProperty property="name" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="lastName" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="email" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="phone" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="address" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="province" name="perfil"/></p>
            <p class="parrafo"><jsp:getProperty property="country" name="perfil"/></p>
            

            <p class="parrafo">Formaci&oacute;n Acad&eacute;mica: <jsp:getProperty property="profession" name="perfil"/></p>
            
            <%-- control de boton que aparecera en caso el usuario este logueado y quiera gestionar sus proyectos --%>
            <%-- if(!customerBean.getName().equals("")){--%>
            <%-- <a href="../control/MyProjectsController.jsp" style="text-decoration:none;">Ir a Mis proyectos <i class="fa fa-user-edit"></i></a> --%>
            <%-- } --%>
            
            <%-- se utilizara el indexProfile para las consultas de perfil de autor de proyecto desde otras paginas --%>
            <% session.setAttribute("indexProfile",perfil.getIndex()); %>
            
            <p class="parrafo">
              <jsp:getProperty property="additional_paragraph" name="perfil"/>
            </p>
            
          </div>
          
          <%-- control de boton que aparecera en caso el usuario este logueado y quiera modificar datos de perfil --%>
          <% if(!customerBean.getName().equals("") && (perfil.getIndex() == customerBean.getIndex()) ){%>
          <form action="../control/updateDataController.jsp" method="post" accept-charset="UTF-8">
          	<input type="hidden" name="modificar" value="modificar"/>
          	<input type="submit" name="boton" id="boton" class="button" value="Modificar Datos" style="cursor:pointer;"/>
          </form>
          	
          <% } %>
        </div>

        <div id="curriculum">
        
            <%-- control de la aceptacion de mostrar CV solo para el usuario autor y no se mostrara si no tiene cv editado --%>
            <%--             Inicio parte nueva 				 --%>
	      	<% if(!customerBean.getName().equals("") && resume.getPhone() != 0 && (customerBean.getIndex() == perfil.getIndex())){%>
        	<form action="../control/cvResumeController.jsp" method="post">
        		<input type="hidden" name="mostrarCV" value="mostrarCV"/>
        		<% if(resume.getShow_cv() == 0){ %>
				 	<input type="checkbox" name="showCV" value="Acepto"/>Acepto poner mi Curriculum disponible para todo el p&uacute;blico.
				 <% } else { %>
				 	<input type="checkbox" name="showCV" value="Acepto" checked />Acepto poner mi Curriculum disponible para todo el p&uacute;blico.
				 <% } %>
        		<input type="submit" value="Enviar"/>
        	</form>
        	<%} %>
        	<%--             Fin parte nueva 				 --%>
        	
        	
          <%-- Se mostrara el PDF en caso el autor no tenga un CV hecho aun --%>
          <% if(resume.getPhone() == 0 || (resume.getShow_cv() == 0 && !customerBean.getName().equals(perfil.getName())) ){ %>
           <%-- if(resume.getPhone() == 0 || resume.getShow_cv() == 0 ){ --%>
          <iframe  src="../../pdf/not_found.pdf"></iframe>
          
          <%-- caso contrario se muestra el CV del autor --%>
          <% } else {
        		String path = "../../pdf/";
        		String file = Integer.toString(resume.getPhone());
        		path = path + file + ".pdf";
       	   %>
          <iframe  src="<%= path %>"></iframe>
          <% } %>
          <br>
          
          <%-- control de boton que aparecera en caso el usuario este logueado y quiera modificar datos de Curriculum --%>
           <% if(!customerBean.getName().equals("") && (perfil.getIndex() == customerBean.getIndex())){ %>
          	<form action="../control/cvResumeController.jsp" method="post">
          		<input type="hidden" name="consulta" value="consulta"/>
          		<input type="submit" class="button" value="Modificar Curriculum" id="button2" style="cursor:pointer;"/>
          	</form>
          <% } %>
        </div>
      </div>

      <%-- ******************* Inicio Footer ******************************** --%>
      <%@include file="../../include/footer.html"%>
        <%-- ******************* Fin Footer ********************************   --%>
  </body>
</html>
<% 
	/** Borrado de beans */
	perfil = null;
	resume = null;
}
%>
