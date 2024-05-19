<?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "temperature";
    // Create connection
     $conn	=	mysqli_connect($servername, $username,$password);
    $connection = mysqli_select_db($conn,$dbname);
?>