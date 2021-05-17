<?php
session_start();
require_once("bdd.php");
require("class/classUser.php");
require("class/classClasse.php");
$requete = 'SELECT * FROM classe_tbl';
$resultat = $bdd->prepare($requete);
$resultat->execute();
if(isset($_POST['subInscription'])){
    if(!empty($_POST['nomInscription']) && !empty($_POST['prenomInscription']) && !empty($_POST['listeClasseInscription']) && !empty($_POST['mailInscription']) && !empty($_POST['passwordInscription']) && !empty($_POST['confirmPasswordInscription'])){
        if($_POST['passwordInscription'] == $_POST['confirmPasswordInscription']){
            $user = new User($bdd);
            $classe = new Classe($bdd);
            $classe->setIdClasse($_POST['listeClasseInscription']);
            $classe->initById();
            $user->setNom($_POST['nomInscription']);
            $user->setPrenom($_POST['prenomInscription']);
            $user->setClasse($classe);
            $user->setMail($_POST['mailInscription']);
            $user->setPassword($_POST['passwordInscription']);
            $user->inscriptionUser();
            $message = "Inscription réussie";
        } else {
            $message = "Les mots de passe ne correspondent pas";
        }
    } else {
        echo $_POST['nomInscription']."<br>";
        echo $_POST['prenomInscription']."<br>";
        echo $_POST['listeClasseInscription']."<br>";
        echo $_POST['mailInscription']."<br>";
        echo $_POST['passwordInscription']."<br>";
        echo $_POST['confirmPasswordInscription']."<br>";
        $message = "Des champs ne sont pas remplis";
    }
}
?>
<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css/style.css">
    <title>Index</title>
</head>

<body>
    <div class="login-box">
        <h2>Inscription</h2>
        <form id="inscription" action="" method="POST">
            <div>
                <input type="text" name="nomInscription" placeholder="Nom" required>
            </div>
            <div>
                <input type="text" name="prenomInscription" placeholder="Prenom" required>
            </div>
                <select name="listeClasseInscription">
                    <?php
                    while ($ligne = $resultat->fetch()) {
                        echo "<option value='" . $ligne['cl_id'] . "'>" . $ligne['cl_nom'] . "</option>";
                    }
                    ?>
                </select>
            <div>
                <input type="mail" name="mailInscription" placeholder="Adresse mail" required>
            </div>
            <div>
                <input type="password" name="passwordInscription" placeholder="Mot de passe" required>
            </div>
            <div>
                <input type="password" name="confirmPasswordInscription" placeholder="Confirmation mot de passe" required>
            </div>
            <button name="subInscription" type="submit">Confirmer</button>
            <h4><?php if(!empty($message)){
                echo $message;
            } ?></h4>
        </form>
    </div>
    <div class="login-box">
        <h2>Connexion</h2>
        <form id="connexion" action="" method="POST">
            <div>
                <input type="mail" name="emailConnexion" placeholder="Adresse mail" required>
            </div>
            <div>
                <input type="password" name="passwordConnexion" placeholder="Mot de passe" required>
            </div>

            <button type="submit">Confirmer</button>
        </form>
    </div>
    <!--Bas de page-->
    <div>
    </div>
</body>

</html>
<?php
/*if (!empty($_POST['password'])
    && !empty($_POST['Cpassword']) && !empty($_POST['nom'])
    && !empty($_POST['prenom']) && !empty($_POST['mail'])
    && !empty($_POST['classe'])) {

    $password  = $_POST['password'];
    $Cpassword = $_POST['Cpassword'];
    $mail      = $_POST['mail'];
    $nom       = $_POST['nom'];
    $prenom    = $_POST['prenom'];
    $idClasse    = $_POST['classe'];
    var_dump("MDRRRRRRRRRR");
    if ($password == $Cpassword) {
        $user = new User($bdd);
        $idClasse = $user->getIdClasse($classe);
        $user->inscriptionUser($password, $mail, $nom, $prenom, $idClasse);
    } else {
        echo "<div>Confirmation de mot de passe incorrect</div>";
    }
} elseif (!empty($_POST['email2']) && !empty($_POST['password2'])) {
    $email  = $_POST['email2'];
    $passwd = $_POST['password2'];

    $user = new User($bdd);
    $user->connexionUser($email, $passwd);
}*/
?>