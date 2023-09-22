#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

extern WebServer webserver;

void MY_Server_Config(void);

void handleLEDHigh();
void handleUserRequest();
bool handleFileRead(String resource);
String getContentType(String filename);

#endif