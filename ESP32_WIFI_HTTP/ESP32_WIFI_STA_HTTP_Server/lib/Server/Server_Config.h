#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

extern WebServer Server;

void MY_Server_Config(void);

void handleNotfind(void);
void handleUpdate(void);

#endif