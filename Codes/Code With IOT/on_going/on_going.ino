#include "ThingSpeak.h" //include the thingspeak header file
#include <ESP8266WiFi.h> //include the esp generic header file
#include<dht.h> //DHT sensor header file for arduino
#include <Servo.h>
Servo servo;

/* Initial pot reading and servo position set the position to neutral */


dht DHT; //DHT type and name; here DHT-11 is used

//Replace your wifi credentials here
const char* ssid     = "asif bin karim"; //Wifi router user name
const char* password = "asdf1234"; //Wifi password

//change your channel number here
unsigned long mychannel = 764228;
const char * myWriteAPIKey = "B131NDKFA2V82KM1";
const char * myReadAPIKey = "7G7B4O6N0WF13JOC";

//define the inputs (Gas sensor and DHT-11)
#define MQ_PIN A0
#define DHT11_PIN D0
//#define LDR_PIN D8
//define the modules to be controlled, as many as needed
int relay_1;  
//int relay_2;  
//int relay_3; //uncomment if not used
//int relay_4; //uncomment if not used

//declare the thingspeak channel field names respectively; highest 8 fields can be created
int Temp; //Field-6
int Hum; //Field-7
float LPG; //Field-5
//int Light; //Field-8

WiFiClient  client; //declaring the Wifi function to connect with client module/router

//The setup function which will run at the very first for one time only if no errors takes place
void setup(){
  servo.attach(D4); //D4
  servo.write(0);
   Serial.begin(115200); //define the baud rate for data transferring; more the baud rate the more less time consume takes place. But for nodeMCU 115200 is a good one.   
   pinMode(MQ_PIN,INPUT); //input-1 in pin A0 (MQ-X gas sensor)
   pinMode(DHT11_PIN,INPUT); //input-2 in pin D0 (DHT-11 sensor)
   pinMode(D1,OUTPUT); //output-1 in pin D1 (relay_1)

  delay(2000);
   
   //pinMode(D3,HIGH);
   //pinMode(D4,OUTPUT); //output-2 in pin D2 (relay_2)
   //pinMode(D4,HIGH);
   //pinMode(LDR_PIN, INPUT); //input-3 in pin D8 (LDR light sensor)

//setting up WiFi network connection
   Serial.println();
   Serial.println();
   Serial.print("Connecting to Router: ");
   WiFi.begin(ssid, password);
   while(WiFi.status() != WL_CONNECTED){
       delay(500);
       Serial.print(".");
    }
   Serial.println("");
   Serial.println("WiFi connected"); //serial print msg when connected to WiFi
   Serial.println("IP Address: "); //serial print local IP Address 
   Serial.println(WiFi.localIP());
   Serial.print("Netmask: "); //Serial print Netmask
   Serial.println(WiFi.subnetMask());
   Serial.print("Gateway: "); //Serial print Gateway
   Serial.println(WiFi.gatewayIP());
  
   ThingSpeak.begin(client); //begin to connect with ThingSpeak Web Server
     }

//Starting to read and calibrate Sensors
//Starting the main loop
void loop(){
  //Loop used for DHT
  DHT.read11(DHT11_PIN);
  Hum = DHT.humidity;
  Serial.println(Hum);
  ThingSpeak.setField(7, Hum);
  
  Temp = DHT.temperature;
  Serial.println(Temp);   
  ThingSpeak.setField(6, Temp);
  
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
  Serial.println(ppm);
  ThingSpeak.setField(5, LPG);

 // int light = digitalRead(LDR_PIN);
 // Serial.print (light);
 // ThingSpeak.setField(8, light);
//  ThingSpeak.setField(1, relay_1);
  //  ThingSpeak.setField(2, relay_2);
//updating channel fields
  ThingSpeak.writeFields(mychannel, myWriteAPIKey);

//get the last data of relays
  int relay_1 = ThingSpeak.readIntField(mychannel, 1, myReadAPIKey);
  Serial.print("relay_1 = ");
  Serial.println(relay_1);
   if (relay_1 == 1){
    digitalWrite(D1, LOW);
    Serial.println("Relay 1 is On..!");
        }
   else {
    digitalWrite(D1, HIGH);
    servo.write(180);

delay(100);

servo.write(0);

delay(1000);
    Serial.println("Relay 1 is Off...!");
    }
    
 /* int relay_2 = ThingSpeak.readIntField(mychannel, 2, myReadAPIKey);
  Serial.print("relay_2 = ");
  Serial.println(relay_2);
   if (relay_2 == 1){
    digitalWrite(D4, LOW);
    Serial.println("Relay 2 is On...!");
        }
   else {
    digitalWrite(D4, HIGH);
    Serial.println("Relay 2 is off...!");
    }


  int relay_3 = ThingSpeak.readIntField(mychannel, 3, myReadAPIKey);
  Serial.print("relay_3 = ");
  Serial.println(relay_3);
   if (relay_3 == 1){
    digitalWrite(D3, LOW);
    Serial.println("Relay 2 is On...!");
        }
   else {
    digitalWrite(D3, HIGH);
    Serial.println("Relay 2 is off...!");      
   }   
*/
delay(15000);
   }
   
