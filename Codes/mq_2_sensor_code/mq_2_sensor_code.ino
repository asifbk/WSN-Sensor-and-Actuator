#include <MQ2.h>

const int gasPin = A0;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(gasPin));
  delay(1000); 
}
