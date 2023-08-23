<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<%@page import="java.util.ArrayList" %>
<%@page import="es.uco.pw.display.bean.ProjectBean" %>

<!DOCTYPE html>
<html>
  <head>
    <title>Contactar</title>
    <meta charset="utf-8">
    <meta name= "keywords" content="HTML,CSS,XML,JavaScript">
    <meta name= "author" content="Rafael Hormigo">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="img/logo.ico">
    <link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
    <link href="../../css/Estilo.css" type="text/css" rel="stylesheet" />
    <link href="../../css/estilos_HF.css" type="text/css" rel="stylesheet" />
    <script src="../../js/functionheader.js" type="text/javascript"> </script>
    <script src="../../js/funciones_Rafa.js" type="text/javascript"> </script>
  </head>
  <body>

    <div>
      <div id="cuerpo_contactar">
		
		<%@ include file="../../include/header.jsp" %>
		
        <div id="Contactar">
          <form id="formulario2" method="post" name="formContactar">
            <!--
            <p>
              <input id="asunto" class="input" type="text" name="asunto" placeholder="Asunto">
            </p>
            -->
            <p>
              <textarea id="texto" name="mensaje" placeholder="Mensaje" action="../control/contactController.jsp"></textarea>
              <br>
              <input class="button" type="submit" value="Enviar">
            </p>
          </form>
        </div>

 		<div id="proyectos">
 		<%
 		ArrayList<ProjectBean> projects = (ArrayList<ProjectBean>)request.getAttribute("projects");
		for(int i=0; i<projects.size() && i<4; i++){
		%>
          <div class="proyecto">
            <div>
              <h3><strong>Titulo:</strong> <% out.println(projects.get(i).getTitle()); %></h3>
              <p><% out.println(projects.get(i).getDescriptionbrief()); %></p>
            </div>
            <img src=<% out.println(projects.get(i).getLogoProject()); %> alt="logo" >
          </div>
		<%
		}
 		%>
       </div>

		<%@ include file="../../include/footer.html" %>
      </div>
    </div>
  </body>
</html>
