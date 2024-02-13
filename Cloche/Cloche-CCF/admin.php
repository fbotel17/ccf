<?php
require "session.php";
require "classe/user.php";
$user = new user($BDD);
if (!isset($_SESSION['id'])) {
  header("Location: index.php");
} else {
  $user->giveUser($_SESSION['id']);
  $role = $user->getRole();
  if ($role == 0) {
    header("Location: index.php");
  }
}

if (isset($_GET['deco'])) {
  $user->deconnection();
}
if (isset($_GET['suppr'])) {
  $user->supprUser($_GET['suppr']);
  header("Location: admin.php");
}

if (isset($_GET['statue'])) {
  $user->changeStatus($_GET['statue']);
  header("Location: admin.php");
}


?>

<!DOCTYPE html>
<html lang="fr">

<head>
  <title>Cloche en redstone</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <link rel="stylesheet" href="Style/manu.css">
  <link rel="stylesheet" type="text/css" href="Style/admin.css" media="screen" />
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
  <div class="adminx-container">
    <!-- Main Content -->
    <div class="adminx-content">
      <div class="adminx-main-content">
        <div class="container-fluid">
          <!-- BreadCrumb -->

          <div class="pb-3">
            <h1>Panel Des Utilisateur :</h1>
          </div>
          <div class="row">
            <div class="col">
              <div class="card mb-grid">
                <div class="table-responsive-md">
                  <table class="table table-actions table-striped table-hover mb-0" data-table>
                    <thead>
                      <tr>
                        <th scope="col">
                          <label class="custom-control custom-checkbox m-0 p-0">
                            <input type="checkbox" class="custom-control-input table-select-all">
                            <span class="custom-control-indicator"></span>
                          </label>
                        </th>
                        <th scope="col">Identifiant</th>
                        <th scope="col">Mots De Passe</th>
                        <th scope="col">Status</th>
                        <th scope="col">Roles</th>
                        <th scope="col">Actions</th>
                      </tr>
                    </thead>
                    <tbody>
                      <?php $user->getUserPanelAdmin(); ?>
                    </tbody>
                  </table>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <!-- // Main Content -->
  </div>

  <!-- If you prefer jQuery these are the required scripts -->
  <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.3/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/js/bootstrap.min.js"></script>
  <script src="js/vendor.js"></script>
  <script src="js/adminx.js"></script>

  <script src="https://cdn.datatables.net/1.10.16/js/jquery.dataTables.min.js"></script>
  <script src="https://cdn.datatables.net/1.10.16/js/dataTables.bootstrap4.min.js"></script>
</body>

</html>