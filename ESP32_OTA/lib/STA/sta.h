#ifndef _STA_H_
#define _STA_H_

#include <Arduino.h>
#include <WiFi.h>

#define LED 2
#define WiFi_SSD "realme GT Neo5" /* 设置热点名称 */
#define WiFi_PASSWORD "12111211"  /* 设置热点密码 */

extern IPAddress LocalIP;
extern IPAddress WIFI_GETWAY;
extern IPAddress WIFI_SUBNET;

void WIFI_STA_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode);

#endif