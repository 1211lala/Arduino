#ifndef _AP_H_
#define _AP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

#define LED 2

#define WiFi_SSD "ESP32_WiFi"           /* 设置热点名称 */
#define WiFi_PASSWORD "123456789"       /* 设置热点密码 */

IPAddress ESP_IP(192, 168, 1, 1);       /* 热点IP */
IPAddress ESP_GETWAY(192, 168, 1, 1);   /* 热点网关 */
IPAddress ESP_SUBNET(255, 255, 255, 0); /* 热点掩码 */

void WIFI_Config(const char *ssd, const char *password, wifi_mode_t wifi_mode);

#endif