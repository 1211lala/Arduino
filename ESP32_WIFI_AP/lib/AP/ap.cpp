/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-17 12:59:49
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-17 13:04:05
 * @FilePath: \ESP32_WIFI_AP\lib\AP\ap.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ap.h"

IPAddress ESP_SOFT_IP(192, 168, 1, 1);       /* 热点IP */
IPAddress ESP_SOFT_GETWAY(192, 168, 1, 1);   /* 热点网关 */
IPAddress ESP_SOFT_SUBNET(255, 255, 255, 0); /* 热点掩码 */



/**
 * @description: 
 * @param {char} *ssd ESP32建立的WFIFI名称
 * @param {char} *password  ESP32建立的WFIFI密码
 * @return {*}
 */
void MY_WIFI_AP_Config(const char *ssd, const char *password)
{
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAPConfig(ESP_SOFT_IP, ESP_SOFT_GETWAY, ESP_SOFT_SUBNET);
  Serial.printf("\n开启WiFi...");
  while (!WiFi.softAP(ssd, password))
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\nWiFi名称: %s\r\n", WiFi.softAPSSID().c_str());
  Serial.printf("ESP32IP: %s\r\n", WiFi.softAPIP().toString().c_str());
}