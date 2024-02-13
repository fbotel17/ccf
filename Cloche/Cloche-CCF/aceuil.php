<?php
require "session.php";
require "classe/user.php";
require "classe/histo.php";
$user = new user($BDD);
$histo = new hisorique($BDD);
if (!isset($_SESSION['id'])) {
    header("Location: index.php");
} else {
    $user->giveUser($_SESSION['id']);
    $role = $user->getRole();
}


if (isset($_GET['deco'])) {
    $user->deconnection();
}
if (isset($_GET['cloche'])) {
    if ($user->getStatue() == 1) {
        $histo->ajouthisto($_SESSION['id'], $_GET['cloche']);
        header("Location: aceuil.php");
    } else {
        header("Location: aceuil.php");
    }
}


?>

<!DOCTYPE html>
<html>

<head>
    <title>Cloche en redstone</title>
    <link rel="stylesheet" href="Messagerie.css">
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <link rel="stylesheet" href="Style/manu.css">


</head>

<body>
    <nav role="navigation">
        <div id="menuToggle">
            <input type="checkbox"/>
            <span></span>
            <span></span>
            <span></span>
            <ul id="menu">
                <a href="aceuil.php">
                    <li>Acceuil</li>
                </a>
                <?php if($role == 1){ ?>
                <a href="admin.php">
                    <li>Panel User</li>
                </a>
                <a href="panelHistorique.php">
                    <li>Panel Log</li>
                </a>
            <?php } ?>
                <a href="?deco" target="_blank">
                    <li>Déconnection</li>
                </a>
            </ul>
        </div>
    </nav>

    <div class="grand">
        <div class="head">
            <h2>Cloches en RedStone</h2>
        </div>
        <!--<div class="deco">
            <form action="" method="post">
                <button type="submit" value="déconnexion" name="déconnexion" class="monzgeg">Déconnexion</button>
            </form>
        </div> -->
    </div>

    <div class="NormalListeCloche">

        <h1>Cloche Solo</h1>

        <?php if ($user->getStatue() == 1) { ?>
            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Cloche1()">
                <h5 class="h5">Cloche 1</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Cloche2()">
                <h5 class="h5">Cloche 2</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Cloche3()">
                <h5 class="h5">Cloche 3</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Cloche4()">
                <h5 class="h5">Cloche 4</h5>
            </div>
        <?php } else { ?>
            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                <h5 class="h5">Cloche 1</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                <h5 class="h5">Cloche 2</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                <h5 class="h5">Cloche 3</h5>
            </div>

            <div class="NormalCloche">
                <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                <h5 class="h5">Cloche 4</h5>
            </div>
        <?php } ?>
    </div>

    <div class="Melodie">

        <div class="ListeCloche">

            <h1>Création de mélodie</h1>
            <?php if ($user->getStatue() == 1) { ?>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="MelodieCloche1()">
                    <h5 class="h5">Cloche 1</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="MelodieCloche2()">
                    <h5 class="h5">Cloche 2</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="MelodieCloche3()">
                    <h5 class="h5">Cloche 3</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="MelodieCloche4()">
                    <h5 class="h5">Cloche 4</h5>
                </div>
                <div class="Delay">

                    <input placeholder="Delay" id="delay" class="input"></input>
                    <button onclick="Delay()">J'ai choisie mon rythme</button>
                    <button id="send" onclick="Sonnerie(Tableau)" class="input"> DJ Balance le son</button>

                </div>
            <?php } else { ?>
                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                    <h5 class="h5">Cloche 1</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                    <h5 class="h5">Cloche 2</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                    <h5 class="h5">Cloche 3</h5>
                </div>

                <div class="Cloche">
                    <input type="image" src="Cloche_dorée_ombrée.png" class="ImageCloche" onclick="Noauto()">
                    <h5 class="h5">Cloche 4</h5>
                </div>

                <div class="Delay">

                    <input placeholder="Delay" id="delay" class="input"></input>
                    <button onclick="Noauto()">J'ai choisie mon rythme</button>
                    <button id="send" onclick="Noauto()" class="input"> DJ Balance le son</button>

                </div>
            <?php } ?>
        </div>

        <div>
            <table id="Liste" class="Liste">

                <thead class="Liste">
                    <th>Cloche</th>
                    <th>Ordre
                    <th>
                </thead>

            </table>
        </div>

    </div>

</body>

<script>
    const socket = new WebSocket('ws://192.168.65.86:168');
    let Tableau = [];
    let i = 1;
</script>

<script>
    function Cloche1() {

        var cloche = "1";

        socket.send(cloche);
        console.log(cloche);
        window.location.href = '?cloche=1';
        //location.reload();
    }

    function Cloche2() {

        var cloche = "2";
        socket.send(cloche);
        console.log(cloche);
        window.location.href = '?cloche=2';
        //location.reload();
    }

    function Cloche3() {

        var cloche = "3";

        socket.send(cloche);
        console.log(cloche);
        window.location.href = '?cloche=3';
        //location.reload();

    }

    function Cloche4() {

        var cloche = "4";

        socket.send(cloche);
        console.log(cloche);
        window.location.href = '?cloche=4';
        //location.reload();

    }

    function Noauto() {
        alert('vous devais etre autoriser par les administrateur du site pour pouvoir faire sonner les cloche !!');
    }

    function Delay() {

        TempsAttente = document.getElementById("delay").value;
        var Delay = "Attendre " + document.getElementById("delay").value + "ms";
        TableauHtml(Delay, i);
        let newLength = Tableau.push(TempsAttente);
        document.getElementById('send').value = '';

    }

    function JsTableau(cloche) {

        let newLength = Tableau.push(cloche)
        console.log(Tableau)

    }

    function TableauHtml(NomCloche, OrdreNuméro) {
        var TableauListe = document.getElementById('Liste').innerHTML += "<th>" + NomCloche + "<th> <th>" + OrdreNuméro + "<th>"

        i++;
    }

    function Sonnerie(Tableau) {

        document.getElementById("send").disabled = true;


        if (Tableau[0] == undefined) {
            console.log("Le tableau est vide")
            document.getElementById("send").disabled = false;
        } else {

            for (n = 0; n < Tableau.length; n++) {
                console.log(Tableau[n]);
                socket.send(Tableau[n]);
            }

            document.getElementById("send").disabled = false;
            Tableau.length = 0;

            var Ligne = document.querySelector("tbody");
            Ligne.remove();

        }
    }

    function MelodieCloche1() {

        var cloche = "cloche1";

        JsTableau(cloche)
        TableauHtml("Cloche 1", i)

    }

    function MelodieCloche2() {

        var cloche = "cloche2";

        JsTableau(cloche)
        TableauHtml("Cloche 2", i)
    }

    function MelodieCloche3() {

        var cloche = "cloche3";

        JsTableau(cloche);
        TableauHtml("Cloche 3", i)
    }

    function MelodieCloche4() {

        var cloche = "cloche4";

        JsTableau(cloche);
        TableauHtml("Cloche 4", i)
    }
</script>

</html>
