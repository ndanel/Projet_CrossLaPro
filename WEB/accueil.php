<?php
include "header.php";

require_once("bdd.php");
require("class/classUser.php");

?>
<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="utf-8">
    <title>Accueil</title>
</head>

<body class="bg-blue-300 h-screen">
    <div class="mb-8 text-center">
        <p class="text-black text-opacity-100 text-xl">Où souhaitez-vous aller ?</p>
    </div>
    <div class="container mx-auto flex justify-center grid justify-items-start m-56">

        <ul>
            <div class="text-center">
                <button class="bg-blue-800 hover:bg-yellow-300 text-white hover:text-black font-bold py-2 px-4 rounded m-2">
                    <a href="course.php">Page course
                </button>
            </div>
            <div class="text-center">
                <button class="bg-blue-800 hover:bg-yellow-300 text-white hover:text-black font-bold py-2 px-4 rounded m-2">
                    <a href="classement.php">Page classement</a>
                </button>
            </div>
    </div>
</body>

</html>