const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div id="demo">
<h2><font color="green">Environment Condition Monitoring and long distance actuator controlling using WSN</font></h2><br>
<h3><font color="blue">Course No : MTE4210 <br>Course Title : Seminer</font></h3><br>
<h3><font color="orange">Supervisor<br> Md. Manirul Islam<br>Assistant Professor, Dept. of Mechatronics Engineering,
RUET</font></h3>
  <button type="button" onclick="sendData(1)">Actuator ON</button>
  <button type="button" onclick="sendData(0)">Actuator OFF</button><BR>
</div>

<div>
  ADC Value is : <span id="ADCValue">0</span><br>
    LED State is : <span id="LEDState">NA</span>
</div>
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
<br>&copyAll rights reserved by &nbsp<a href="http://mte.ruet.ac.bd/" target="_blank">Dept. of Mechatronics Engineering, RUET</a>
</body>
</html>
)=====";