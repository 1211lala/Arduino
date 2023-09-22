#include <Arduino.h>
#include "ota.h"
#include "sta.h"


void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WIFI_STA_Conncet(WiFi_SSD, WiFi_PASSWORD, WIFI_MODE_STA);
  MY_OTA_Init("12345678", 3232);
}

void loop()
{

  ArduinoOTA.handle();  /* 在主程序中检测是不是需要OTA升级*/


  // static uint8_t time = 0;
  // if (time++ > 200)
  // {
  //   time = 0;
  //   digitalWrite(LED, !digitalRead(LED));
  // }
  // delay(1);
}