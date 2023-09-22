#include <Arduino.h>

#define   LED   2       /* 板载LED在IO2 */

void setup() 
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}


unsigned long uwtick;
unsigned long previoustick = 1000;

void loop()
{
  uwtick = millis();
  Serial.printf("uwtick : %d\r\n",uwtick);
  if((uwtick - previoustick) > 1000)
  {
    previoustick = uwtick;
    digitalWrite(LED, !digitalRead(LED));
  }
}

