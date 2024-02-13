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
    <section class="inscription">
        <form id="Inscription" method="POST">

            <h1>Inscription</h1>

            <div class="inputs">
                <input type="text" id="usernameInscription" name="usernameInscription" placeholder="Pseudo" />
                <input type="password" id="passwordInscription" name="passwordInscription" placeholder="Mot de passe">
                <input type="password" id="ConfirmpasswordInscription" name="ConfirmpasswordInscription" placeholder="Confirmer votre mot de passe">
            </div>
            <div align="center">
                <a class="changement_page" href="index.php">Je possède un compte.</p>
                    <button type="submit" onclick="inscription()" name="inscription">S'inscrire</button>
            </div>

        </form>
        <?php
        if (isset($_POST['inscription'])) {
            $error = $user->inscription($_POST['usernameInscription'], $_POST['passwordInscription'], $_POST['ConfirmpasswordInscription']);
        }
        ?>
    </section>

</body>

</html>