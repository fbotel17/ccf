<?php
require "session.php";
require "classe/user.php";
$admin = new user($BDD);
$user = new user($BDD);
$user->giveUser($_GET['modif']);
if (!isset($_SESSION['id'])) {
    header("Location: index.php");
} else {
    $admin->giveUser($_SESSION['id']);
    $role = $admin->getRole();
    if ($role == 0) {
        header("Location: index.php");
    }
}

if (isset($_GET['deco'])) {
    $user->deconnection();
}

?>
<!DOCTYPE html>
<html>

<head>
    <title>Cloche en redstone</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="Messagerie.css">
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <link rel="stylesheet" href="Style/manu.css">
</head>

<body>
    <nav role="navigation">
        <div id="menuToggle">
            <input type="checkbox" />
            <span></span>
            <span></span>
            <span></span>
            <ul id="menu">
                <a href="aceuil.php">
                    <li>Acceuil</li>
                </a>
                <a href="admin.php">
                    <li>Panel User</li>
                </a>
                <a href="panelHistorique.php">
                    <li>Panel Log</li>
                </a>
                <a href="?deco" target="_blank">
                    <li>Déconnection</li>
                </a>
            </ul>
        </div>
    </nav>

    <section class="inscription">
        <form id="Inscription" method="POST">

            <h1>Modif User</h1>

            <div class="inputs">
                <input type="text" id="usernameInscription" name="usernameModif" placeholder="Pseudo" value="<?= $user->getNom() ?>" />
                <input type="password" id="passwordModif" name="passwordModif" placeholder="Mot de passe" value="<?= $user->getMdp() ?>">
                <input type="password" id="Confirmpasswordmodif" name="Confirmpasswordmodif" placeholder="Confirmer votre mot de passe" value="<?= $user->getMdp() ?>">
            </div>
            <div class="form-check form-switch">
                <div id="center">
                    <?php if ($user->getRole() == 1) { ?>
                        <input class="form-check-input" type="checkbox" id="flexSwitchCheckChecked" name="admin" checked>
                    <?php } else { ?>
                        <input class="form-check-input" type="checkbox" id="flexSwitchCheckChecked" name="admin">
                    <?php } ?>

                    <label class="form-check-label" for="flexSwitchCheckChecked">Administrateur</label>
                </div>
            </div>
            <div align='center'>
                <button type="submit" name="modif">Modifier</button>
            </div>

        </form>
        <?php
        if (isset($_POST['modif'])) {
            if (isset($_POST['admin'])) {
                $roleAdmin = 1;
            } else {
                $roleAdmin = 0;
            }

            $user->modifUser($_POST['usernameModif'], $_POST['passwordModif'], $_POST['Confirmpasswordmodif'], $roleAdmin);
        }
        ?>
    </section>

</body>

</html>