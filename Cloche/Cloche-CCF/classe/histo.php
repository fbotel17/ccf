<?php
class hisorique
{

    private $_BDD;
    private $id;
    private $_id_user;
    private $_cloche;

    /**
     * Constructeur de la classe.
     *
     * @param $BDD la connection a la base de donner
     *
     */
    public function __construct($BDD)
    {
        $this->_BDD = $BDD;
    }


    /**
     * fonction qui ajoute la personne qui a fait sonner une cloche en base de donner
     *
     * @param $id_user l'id de l'utilisateur qui a fait sonner la cloche
     * @param $cloche  et la cloche qui a etais sonner par l'utilisateur
     *
     */
    public function ajouthisto($id_user, $cloche)
    {
        $requetprepar = $this->_BDD->prepare("INSERT INTO `HistoCloche`(`User`, `Date`, `Cloche`) VALUES (?, ?, ?)");
        $dates = date('Y-m-d H:i:s');
        $requetprepar->execute(array($id_user, $dates, $cloche));
    }

    /**
     * function qui permet de récuper les log dans la base de donner est les inserer dans un tableau
     * 
     */
    public function getLog(){
        $requetprepar = $this->_BDD->prepare("SELECT HistoCloche.id, HistoCloche.User, HistoCloche.Date, HistoCloche.Cloche, user.idUser, user.Nom FROM HistoCloche, user WHERE HistoCloche.`User` = user.idUser");
        $requetprepar->execute();
        while ($data = $requetprepar->fetch()) { ?>
            <tr>
                <th scope="row">
                    <label class="custom-control custom-checkbox m-0 p-0">
                        <input type="checkbox" class="custom-control-input table-select-row">
                        <span class="custom-control-indicator"></span>
                    </label>
                </th>
                <td><?= $data['Nom'] ?></td>
                <td><?= $data['Date'] ?></td>
                <td><?= $data['Cloche'] ?></td>
                <td>
                    <button onclick="window.location.href='?suppr=<?= $data['id'] ?>'" class="btn btn-sm btn-danger">Delete</button>
                </td>
            </tr>
<?php }
    }


    /**
     * function qui permet de supprimer des Log en base de donner
     * 
     * @param $id est l'id du log en base de donner que on ve supprimer
     * 
     */
    public function supprLog($id){
        $requetprepar = $this->_BDD->prepare("DELETE FROM `HistoCloche` WHERE `id` = ?");
        $requetprepar->execute(array($id));
    }
}
