<!DOCTYPE html>
<html>
<head>
<style type="text/css">
.table_titles {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}
.table_titles {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}
.header {
	width: 45%;
    height: 15px;
	margin: 10px auto 0px;
	color: white;
	background: #5F9EA0;
	text-align: center;
	border: 1px solid #B0C4DE;
	border-bottom: none;
	border-radius: 10px 10px 0px 0px;
	padding: 20px;
}
        .table_cells_odd{
          border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
        }
        .table_cells_even{
          border: 1px solid #dddddd;
            text-align: left;
            padding: 8px;
            background-color: #dddddd;
        }
table {
border: 1px solid #dddddd;
}
body { font-family: "Trebuchet MS", Courier; }
</style>
<body>
<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url"); // Refresh the webpage every 5 seconds
?>

<center>
    <a href="index.php">Go Back to Previous Page</a>
    <div class="header">
		<font size="5px">Data From Wireless Sensor Network</font>
	</div>
    
<table border="0" cellspacing="0" cellpadding="4">
<tr>
<td class="table_titles">ID</td>
<td class="table_titles">Temperature(in °C)</td>
<td class="table_titles">Humidity(in %)</td>
<td class="table_titles">LPG(in ppm)</td>
<td class="table_titles">Time</td>
<td class="table_titles">Date</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM temps ORDER BY id DESC');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow; 
    
echo "<tr>";
echo "<td '.$css_class.'>"  .$row['id'] . "</td>";
echo "<td '.$css_class.'>"  .$row['temp'] . "</td>";
echo "<td '.$css_class.'>"  .$row['humidity'] . "</td>";
echo "<td '.$css_class.'>"  .$row['lpg'] . "</td>";
echo "<td '.$css_class.'>"  .$row['time'] . "</td>";
echo "<td '.$css_class.'>"  .$row['dated'] . "</td>";
echo "</tr>"; 
}
    
 
// Close the connection
mysqli_close($con);
?>
</table></center>
</body>
</html>