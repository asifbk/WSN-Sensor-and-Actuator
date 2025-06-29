/*
   wia.io
   Get IP Address of ESP8266 in Arduino IDE
*/

#include <ESP8266WiFi.h>

const char* ssid     = "Asif"; // Your WiFi ssid
const char* password = "18273645"; // Your Wifi password;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);

  // Attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP  network:
    // Wait 5 seconds for connection:
    delay(5000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
}

// the loop function runs over and over again forever
void loop() {
}
