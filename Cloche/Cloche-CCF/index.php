<?php
require "session.php";
require "classe/user.php";
$user = new user($BDD);
if(isset($_SESSION['id'])){
  header("Location: aceuil.php");
}
?>
<!DOCTYPE html>
<html>

<head>
  <title>Cloche en redstone</title>
  <link rel="stylesheet" href="Messagerie.css">
  <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
</head>

<body>

  <section class="login">
    <form id="Connexion" method="POST">

      <h1>Se connecter</h1>

      <div class="inputs">
        <input type="text" id="usernameConnexion" name="usernameConnexion" placeholder="Pseudo" />
        <input type="password" id="passwordConnexion" name="passwordConnexion" placeholder="Mot de passe">
      </div>


      <div align="center">
        <a class="changement_page" href="inscription.php">Je n'ai pas de compte.</p>
          <button type="submit" onclick="connexion()" name="connexion">Se connecter</button>
      </div>

    </form>
    <?php
    if (isset($_POST['connexion'])) {
      $error = $user->conection($_POST['usernameConnexion'], $_POST['passwordConnexion']);
    }
    ?>
  </section>

</body>

</html>