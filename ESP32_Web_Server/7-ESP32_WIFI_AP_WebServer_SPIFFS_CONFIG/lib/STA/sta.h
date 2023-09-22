#ifndef _STA_H_
#define _STA_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include "ap.h"


void WIFI_STA_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode);

#endif