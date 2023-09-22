/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-16 13:35:20
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-16 13:48:27
 * @FilePath: \ESP32_WIFI_STA\lib\STA\sta.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _STA_H_
#define _STA_H_

#include <Arduino.h>
#include <WiFi.h>

#define LED 2

// #define WiFi_SSD "realme GT Neo5" /* 设置热点名称 */
// #define WiFi_PASSWORD "12111211"  /* 设置热点密码 */

#define WiFi_SSD "TP-LINK 505" /* 设置热点名称 */
#define WiFi_PASSWORD "tplink505"  /* 设置热点密码 */

extern IPAddress LocalIP;
extern IPAddress WIFI_GETWAY;
extern IPAddress WIFI_SUBNET;

void WIFI_STA_Conncet(const char *ssd, const char *password, bool staticIP);

#endif