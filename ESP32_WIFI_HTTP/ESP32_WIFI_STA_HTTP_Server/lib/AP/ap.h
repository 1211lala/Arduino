#ifndef _AP_H_
#define _AP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

#define LED 2
#define KEY 0

#define WiFi_SOFT_SSD "ESP32_WiFi"     /* 设置热点名称 */
#define WiFi_SOFT_PASSWORD "123456789" /* 设置热点密码 */

extern IPAddress ESP_SOFT_IP;     /* 热点IP */
extern IPAddress ESP_SOFT_GETWAY; /* 热点网关 */
extern IPAddress ESP_SOFT_SUBNET; /* 热点掩码 */

void MY_WIFI_AP_Config(const char *ssd, const char *password, wifi_mode_t wifi_mode);

#endif