<?php 
	session_start(); 

	if (!isset($_SESSION['username'])) {
		$_SESSION['msg'] = "You must log in first";
		header('location:home.php');
	}
	if (isset($_GET['logout'])) {
		session_destroy();
		unset($_SESSION['username']);
		header("location: home.php");
	}

?>
<!DOCTYPE html>
<html>
<head>
	<title>Home</title>
	<link rel="stylesheet" type="text/css" href="style.css">

</head>
<body>
	<div class="header">
		<h2>Home Page</h2>
	</div>
    
    <!-- notification message -->
		<?php if (isset($_SESSION['success'])) : ?>
		<?php endif ?>

		<!-- logged in user information -->
		<?php  if (isset($_SESSION['username'])) : ?>
			<div class="content">
                <p>Welcome <strong><?php echo $_SESSION['username']; ?></strong></p>
			<p> <a href="index.php?logout='1'" style="color: red;">logout</a> </p>
		<?php endif ?>
    </div>
 <div class="content"> 
     <p style="color: black;">Now you can control your device status from <a href="http://localhost/device_controll/status_page.php" target="_blank" style="color: red;">here</a> to prevent auto collection of sensors data. If you turn it off, controller data will not be saved to the database.</p>
</div>

 <div class="content">               
<button type="button" onclick="sendData(1)">RELAY ON</button>
<button type="button" onclick="sendData(0)">RELAY OFF</button><BR>
  Sensor value is : <span id="ADCValue">0</span><br>
    LED State is : <span id="LEDState">NA</span>
<script>
function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
}

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
</script>
     </div>
     
<center>  <table border="0" cellspacing="0" cellpadding="4">
<tr>
<td class="table_titles">Name</td>
<td class="table_titles">Highest Value</td>
<td class="table_titles">Lowest Value</td>
<td class="table_titles">Average Value</td>
</tr>
     <?php
 
require_once('connection.php');
$s = "select * from temps";
$result = mysqli_query($con,$s);
$count = mysqli_num_rows($result);
echo "Total Number of Stored Data: " .$count. " " ;

     $query="SELECT max(temp) as 'hightemp' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field1a= $data["hightemp"];
        $query="SELECT min(temp) as 'lowtemp' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field2a= $data['lowtemp'];
        $query="SELECT avg(temp) as 'avgtemp' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field3a= $data['avgtemp'];
    
                echo "<tr>
                    <td>  Temperature </td>
                    <td> &nbsp&nbsp $field1a</td>
                    <td>&nbsp&nbsp $field2a</td>
                    <td>&nbsp&nbsp $field3a</td>
                    </tr>"; 
    
        $query="SELECT max(humidity) as 'highhum' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field1b= $data["highhum"];
        $query="SELECT min(humidity) as 'lowhum' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field2b= $data["lowhum"];
        $query="SELECT avg(humidity) as 'avghum' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field3b= $data["avghum"];
                echo "<tr>
                        <td>  Humidity </td>
                        <td>&nbsp&nbsp $field1b</td>
                        <td>&nbsp&nbsp $field2b</td>
                        <td>&nbsp&nbsp $field3b</td>
                        </tr>";

        $query="SELECT max(lpg) as 'highlpg' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field1c= $data["highlpg"];
        $query="SELECT min(lpg) as 'lowlpg' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field2c= $data["lowlpg"];
        $query="SELECT avg(lpg) as 'avglpg' FROM temps";
    $res=mysqli_query($con, $query);
    $data= mysqli_fetch_array($res);
    $field3c= $data["avglpg"];
                
                echo "<tr>
                    <td>  LPG </td>
                    <td>&nbsp&nbsp $field1c</td>
                    <td>&nbsp&nbsp $field2c</td>
                    <td>&nbsp&nbsp $field3c</td>
                    </tr>";
    

?>
    </table>
</center> 
<center><a href="livedata.php" style"color: blue;"> See Live Data Here</a></center>

<div id="header-content"><br><br><br><br> &copyAll rights reserved by &nbsp<a href="http://mte.ruet.ac.bd/" target="_blank">Dept. of Mechatronics Engineering, RUET</a>
     </div>
</body>
</html>