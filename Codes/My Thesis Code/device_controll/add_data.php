<?php
    include_once('server.php');
    
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    date_default_timezone_set("Asia/Karachi");
    $val = $_GET['temp'];
    $humd = $_GET['humidity'];
    $lpg = $_GET['lpg'];
    
    
    
    $date = date('Y-m-d');
    $time = date('H:i:s');
    $sql = "INSERT INTO temps(temp,humidity,lpg,dated,time) VALUES ($val,$humd,$lpg,'$date','$time');";
    
    if ($conn->query($sql) === TRUE) {
        echo "Saved Successfully!";
    } else {
        echo "Error:" . $sql . "<br>" . $conn->error;
    }
    
    $conn->close();
?>