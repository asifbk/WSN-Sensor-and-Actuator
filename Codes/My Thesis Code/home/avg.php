<div class="content">
<?php
require_once('connection.php');
$s = "select * from temps";
$result = mysqli_query($con,$s);
$count = mysqli_num_rows($result);
echo $count. " ";
    
$query="SELECT avg(humidity) as 'sumhum' FROM temps";
$res=mysqli_query($con, $query);
$data= mysqli_fetch_array($res);
    echo "Average of Humidity: " .$data['sumhum'];
$query="SELECT max(temp) as 'avgtemp' FROM temps";
$res=mysqli_query($con, $query);
$data= mysqli_fetch_array($res);
    echo "Average of Humidity: " .$data['avgtemp'];
?>
</div>

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
    </head>
<body>
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
echo "Total Number of Rows: " .$count. " " ;

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
                    <td> &nbsp $field1a</td>
                    <td>&nbsp $field2a</td>
                    <td>&nbsp $field3a</td>
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
                        <td> &nbsp $field1b</td>
                        <td>&nbsp $field2b</td>
                        <td>&nbsp $field3b</td>
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
                    <td> &nbsp $field1b</td>
                    <td>&nbsp $field2b</td>
                    <td>&nbsp $field3b</td>
                    </tr>";
    

?>
    </table>
</center> 
    </body>
</html>