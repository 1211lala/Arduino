/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-01 08:51:29
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-17 13:10:55
 * @FilePath: \ESP32_WIFI_AP\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "ap.h"

#define LED 2

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n\r\n");
  MY_WIFI_AP_Config(WiFi_SOFT_SSD, WiFi_SOFT_PASSWORD);
}

void loop()
{
  Serial.printf("主机名字: %s\r\n", WiFi.softAPgetHostname());
  uint8_t macAddress[6];
  WiFi.softAPmacAddress(macAddress);
  Serial.printf("MAC地址为  %02x:%02x:%02x:%02x:%02x:%02x\n", macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
  Serial.printf("热点名称: %s\r\n", WiFi.softAPSSID());
  Serial.printf("热点IP: %s\r\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("热点设备数: %d\r\n\r\n", WiFi.softAPgetStationNum());

  delay(500);
}
