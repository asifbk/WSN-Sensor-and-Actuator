<?php
$username = "root";
$pass = "";
$host = "localhost";
$db_name = "temperature";
$con = mysqli_connect ($host, $username, $pass);
$db = mysqli_select_db ( $con, $db_name );
?>