/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-01 08:51:30
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-16 13:56:08
 * @FilePath: \ESP32_WIFI_STA\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
  http://www.taichi-maker.com/homepage/iot-development/iot-dev-reference/esp8266-c-plus-plus-reference/esp8266wifista/
*/
#include <Arduino.h>
#include "sta.h"

#define LED 2

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n\r\n");
  WIFI_STA_Conncet(WiFi_SSD, WiFi_PASSWORD, false);
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("WiFi的子网掩码:");
    Serial.println(WiFi.subnetMask());
    Serial.print("WiFi的网关地址:");
    Serial.println(WiFi.gatewayIP());
    Serial.print("DNS地址:");
    Serial.println(WiFi.dnsIP());
    Serial.print("WiFi强度:");
    Serial.println(WiFi.RSSI());
    Serial.print("主机名:");
    Serial.println(WiFi.getHostname());
    Serial.printf("\r\n\r\n");
    delay(1000);
    digitalWrite(LED, HIGH);
  }
  else
  {
    delay(1000);
    Serial.printf("网络已断开\r\n\r\n");
    digitalWrite(LED, LOW);
  }
}
