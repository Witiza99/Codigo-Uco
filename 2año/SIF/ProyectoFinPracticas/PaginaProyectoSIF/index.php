<?php
	session_start();
	if (isset($_SESSION['estado'])){
	unset($_SESSION['estado']);}
?>

<!DOCTYPE html>
<html>

<head>

  <meta charset="UTF-8">

  <title>AllFood - Log-in</title>

  <link rel='stylesheet' href='http://codepen.io/assets/libs/fullpage/jquery-ui.css'>

    <link rel="stylesheet" href="css/style.css" media="screen" type="text/css" />

</head>

<body>

<div class="login-card">
  <img width="273" ;height="125";align="center"; src="allfood2.jpeg">
  <br>
  <form method="post" action="index1.php">
    <input type="text" name="ID" placeholder="Usuario">
    <input type="password" name="Contrasena" placeholder="Contraseña">
	<input type="submit" name="login" class="login login-submit" value="Iniciar sesión">
	<input type="hidden" name="opcion" id="opcion" value="<?php echo $_POST["opcion"] ?>" >
  </form>
  <br>
</div>

<!-- <div id="error"><img src="https://dl.dropboxusercontent.com/u/23299152/Delete-icon.png" /> Your caps-lock is on.</div> -->

  <script src='http://codepen.io/assets/libs/fullpage/jquery_and_jqueryui.js'></script>

</body>

</html>
