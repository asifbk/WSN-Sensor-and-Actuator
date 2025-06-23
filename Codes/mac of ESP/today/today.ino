
//include libraries
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <dht.h>
#define dht_apin D4 // Analog Pin sensor is connected to
dht DHT;
float get_temperature,get_humidity; // Setting up variables
int delay_time  = 3000; // Its mean 3 seconds wait to enter first record
 
//Access point credentials
const char* ssid        = "Asif";
const char* pwd         = "18273645";
String get_status_url   = "http://192.168.43.35/device_controll/get_status.php";
String add_data_url     = "http://192.168.43.35/device_controll/add_data.php";
WiFiServer server(80);  // open port 80 for server connection
 
void setup() 
{
  Serial.begin(115200); //initialise the serial communication
  delay(20);
  WiFi.begin(ssid, pwd);
 
   
    //starting the server
    server.begin();
 
}
 
void loop()
{
    String device_status  = get_device_status("home_sensor");
    delay(2000);
    WiFiClient client = server.available();
    DHT.read11(dht_apin);
    get_temperature =   DHT.temperature;
    get_humidity    =   DHT.humidity;
    
    if(device_status=="1")
    {
     add_device_data(get_temperature, get_humidity);
    }
    else
    {
      Serial.println("Device Status is going OFF");
      }
    
    delay(delay_time);
      
      
}
 
 
///This is the function that will get status of device that is On or Off
void add_device_data(float get_temperature, float get_humidity)
  {
    
        WiFiClient client = server.available();
 
        HTTPClient http;
        String url = add_data_url+"?temp="+get_temperature+"&humidity="+get_humidity;
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
