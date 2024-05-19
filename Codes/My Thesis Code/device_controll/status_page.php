
<!DOCTYPE html>
<html lang="en">
    <head>
		<meta charset="UTF-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1"> 
		<meta name="viewport" content="width=device-width, initial-scale=1.0"> 
        <title>Controlling Page</title>
 
        <link rel="stylesheet" type="text/css" href="css/style.css" />

    </head>
    <body>
    
    <?php
    include_once('server.php');
    
    
    
    
    if(isset($_GET['device_status']))
    {
       
       $status  =   $_GET['device_status'];
       if($status==1)
       {
        $update_status  =   0;
       }
       elseif($status==0)
       {
        $update_status  =   1;
       }
       $query   =   "UPDATE devices_status SET device_status='$update_status' WHERE device_name='home_sensor'";
       $conn->query($query);
    }

    
    
    
    
    $get_status_sql            =   "SELECT device_status FROM devices_status WHERE device_name='home_sensor'";
    $result         =   $conn->query($get_status_sql);
    
    if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc())
    {
        $current_status = $row['device_status'];
        
        if($current_status == 1)
        {
            $checked    =   'checked';
        }
        else
        {
            $checked    =   '';
        }
    }
    }
    
    ?>
    
    
    
        <div class="container">
		
			
			<section class="main">
				<h1 style="text-align: center; padding: 30px; font-size: 35px; font-family: fantasy;">Control Sensor Data with PHP and MySQL</h1>
				
                <div class="switch demo3">
					
                    <input onClick="location.href='<?php echo $_SERVER['PHP_SELF']; ?>?device_status=<?php echo $current_status; ?>'" type="checkbox" value="<?php echo $current_status;?>" <?php echo $checked;?> />
                               
			
					<label><i></i></label>
                    
				</div>
<h4 style="text-align: center;">&copyAll rights reserved by &nbsp<a href="http://mte.ruet.ac.bd/" target="_blank">Dept. of Mechatronics Engineering, RUET</a></h4>
				
			</section>
			
        </div>

    </body>
</html>