#ifndef _SPIFFS_CONFIG_
#define _SPIFFS_CONFIG_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

#define path_test "/test.txt"
#define path_mode "/mode.txt"
#define path_ssid "/ssid.txt"
#define path_password "/password.txt"

void MY_SPIFFS_Init(bool format);
void MY_SPIFFS_Write(const char *path, const char *databuf);
String MY_SPIFFS_Read(const char *path);

#endif