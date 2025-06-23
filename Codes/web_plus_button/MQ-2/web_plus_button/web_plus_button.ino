#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include "Asif.h" //Our HTML webpage contents with javascripts
#define MQ_PIN A0

#define LED D4  //On board LED
//const int trigPin = 2;
//const int echoPin = 0;
//long distance;
//int duration;
//SSID and Password of your WiFi router
const char* ssid = "Asif";
const char* password = "18273645";
 
ESP8266WebServer server(80); //Server on port 80
 
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleADC() {
  //digitalWrite(trigPin, LOW);
//delayMicroseconds(200);

// Sets the trigPin on HIGH state for 10 micro seconds
//digitalWrite(trigPin, HIGH);
//delayMicroseconds(200);
//digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
//duration = pulseIn(echoPin, HIGH);

// Calculating the distance

  //distance= duration*0.034/2;
  //delay(1000);
  //Serial.print("distance");
  //Serial.print(distance);
  //Serial.print(" ");
  
  float MQ = analogRead(A0);
  String LPG = String(MQ);
 float sensor_volt; //Define variable for sensor voltage 
  float RS_gas; //Define variable for sensor resistance  
  float ratio; //Define variable for ratio
  float sensorValue = analogRead(MQ_PIN); //Read analog values of sensor  
  float m = -0.423; //Slope 
  float b = 1.276; //Y-Intercept 
  float R0 = 5.62; //Sensor Resistance in fresh air from previous code
  
  sensor_volt = sensorValue*(5.0/1023.0); //Convert analog values to voltage 
  RS_gas = ((5.0*10.0)/sensor_volt)-10.0; //Get value of RS in a gas
  ratio = RS_gas/R0;  // Get ratio RS_gas/RS_air

  double ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale 
  double percentage = ppm/10000; //Convert to percentage 

  LPG = ppm;
 
 server.send(200, "text/plane", LPG); //Send ADC value only to client ajax request
}
 
void handleLED() {
 String LEDState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,HIGH); //LED ON
  LEDState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(LED,LOW); //LED OFF
  LEDState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", LEDState); //Send web page
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();          //Handle client requests
}
