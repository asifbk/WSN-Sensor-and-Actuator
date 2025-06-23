#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <dht.h>
#define MQ_PIN A0
#define dht_apin D4 // Analog Pin sensor is connected to
#define LED D7 
dht DHT;
float get_temperature,get_humidity; // Setting up variables
int delay_time  = 3000; // Its mean 3 seconds wait to enter first record
float get_lpg;
 
//Access point credentials
const char* ssid        = "Asif";
const char* pwd         = "18273645";
String get_status_url   = "http://192.168.43.207/device_controll/get_status.php";
String add_data_url     = "http://192.168.43.207/device_controll/add_data.php";
WiFiServer server(80);  // open port 80 for server connection
 
void setup() 
{
  Serial.begin(115200); //initialise the serial communication
  delay(20);
  WiFi.begin(ssid, pwd);
 
   
    //starting the server
    server.begin();
    pinMode(LED,OUTPUT); 
 
}
 
void loop()
{
    String device_status  = get_device_status("home_sensor");
    delay(2000);
    WiFiClient client = server.available();
    DHT.read11(dht_apin);
    get_temperature =   DHT.temperature;
    get_humidity    =   DHT.humidity;
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

  double get_lpg = ppm;
 
    
    if(device_status=="1")
    {
     add_device_data(get_temperature, get_humidity, get_lpg); //add sensor
     if(get_lpg>550){
    digitalWrite(LED,LOW);}
    else{
       digitalWrite(LED,HIGH);}
       }
    else
    {
      Serial.println("Device Status is going OFF");
      
      }
    
    delay(delay_time);
      
      
}
 
 
///This is the function that will get status of device that is On or Off
void add_device_data(float get_temperature, float get_humidity,float get_lpg) // add sensor
  {
    
        WiFiClient client = server.available();
 
        HTTPClient http;
        String url = add_data_url+"?temp="+get_temperature+"&humidity="+get_humidity+"&lpg="+get_lpg; //add sensors
        http.begin(url);
        //GET method
        int httpCode = http.GET();
        String payload = http.getString();
        Serial.println(url);
        Serial.println(payload);
        http.end();
        
  
  }
 
 
String get_device_status(String device_name)
  {
    
        WiFiClient client = server.available();
 
        HTTPClient http;
        String url = get_status_url+"?device_name="+device_name;
        http.begin(url);
        int httpCode = http.GET();
        String payload = http.getString();
        Serial.println(url);
        Serial.println(payload);
        return payload;
        
  
  }
