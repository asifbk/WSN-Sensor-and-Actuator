<?php include('server.php') ?>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body class="body">

<div class="demo">
<h2><font color="green">Environment Condition Monitoring and long distance actuator controlling using WSN</font></h2><br>
<h3><font color="blue">Course No : 4200 <br>Course Title : Project & Thesis</font></h3><br>
<h3><font color="orange">Supervisor<br>Md. Manirul Islam ,Lecturer <br>Dept. of Mechatronics Engineering,
RUET</font></h3>
</div> 
    
	<div class="header">
        <h2>Log In</h2>
	</div>
	
	<form method="post" action="home.php">

		<?php include('errors.php'); ?>

		<div class="input-group">
			<label>Username</label>
			<input type="text" name="username" >
		</div>
		<div class="input-group">
			<label>Password</label>
			<input type="password" name="password">
		</div>
      
		<div class="input-group">
			<button type="submit" class="btn btn-success" name="login_user">Login</button>
		</div>
		<p>
			Don&#39;t have an account? <a href="register.php">Sign up</a>
		</p>
	</form>

<br>&copyAll rights reserved by &nbsp<a href="http://mte.ruet.ac.bd/" target="_blank">Dept. of Mechatronics Engineering, RUET</a>
</body>
</html>
