<?php
session_start();

try{
    $BDD = new PDO('mysql:host=192.168.64.70;dbname=Cloche; charset=utf8', 'admin', 'admin');
    $BDD->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}catch(Exception $e){
    die('Erreur : '. $e->getMessage());
}

?>