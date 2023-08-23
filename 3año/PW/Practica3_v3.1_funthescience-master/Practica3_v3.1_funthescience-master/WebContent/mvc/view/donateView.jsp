<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
	<title>Donar</title>
	<meta charset ="UTF-8">
	<meta name= "description" content="Pagina para realizar donaciones">
	<meta name= "keywords" content="HTML,CSS,XML,JavaScript">
	<meta name= "author" content="Andrés López Cárdenas">
	<meta name= "viewport" content="width=device-width, initial-scale=1.0">
	<link rel="icon" href="img/logo.ico">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans&display=swap" rel="stylesheet"> 
	<link href="https://fonts.googleapis.com/css?family=Waiting+for+the+Sunrise&display=swap" rel="stylesheet">
	<link href="../../css/estilos_Donar.css" type="text/css" rel="stylesheet" />
	<link href="../../css/estilos_HF.css" type="text/css" rel="stylesheet" />
	<script src="../../js/functionheader.js" type="text/javascript"></script>
</head>
<body>
	<%@ include file="../../include/header.jsp" %>

	<div id="cuerpo">
		<div id="paybox" >
			<form id="form-donar" action="../control/donateController.jsp?id=<% out.println(request.getParameter("id")); %>"  name="donar" method="POST"> <!--action="../../Donar.js"-->
				<p>Indique la cantidad que desea donar.</p>
				<input type="number" id="cantidad_Donar" name="cantidadDonar" step="0.01">
				<div id="selectorPago">
					<div>
						<input type="radio" id="MP_Paypal" name="metPago" value="Paypal" checked>
						<label for="MP_Paypal">Paypal</label>
					</div>
					<div>
						<input type="radio" id="MP_Visa" name="metPago" value="Visa">
						<label for="MP_Visa">Visa</label>
					</div>
					<div>
						<input type="radio" id="MP_Mastercard" name="metPago" value="Mastercard">
						<label for="MP_Mastercard">Mastercard</label>
					</div>
				</div>

				<div class="check_box">
					<input type="checkbox" name="DAnonima" id="D_anonima" value="DAnonima">Deseo que esta donacion sea an&oacutenima
				</div>
				<textarea name="comentarioP" id="comentario_P" cols="50" rows="6"></textarea>
				<div class="check_box">
					<input type="checkbox" name="Lterm" id="L_term" value="Lterm">He le&iacutedo y acepto los t&eacuterminos y condiciones de servicio
				</div>
				<div id="buttons">
					<input class="form-button" type="submit" name="envio" value="Enviar" />
					<input class="form-button" type="reset" name="cancelar" value="Cancelar"/>
				</div>
			</form>
		</div>

		<div class="masInfo">
			<div>
				<p>Estas ayudando a: <span id="ayudandoaPr"></span></p>
			</div>
			<figure>
				<img src="../../img/Logo_UCO.png" alt="imagen relacionana">
			</figure>
		</div>
	</div>

	<%@ include file="../../include/footer.html" %>
</body>
</html>
