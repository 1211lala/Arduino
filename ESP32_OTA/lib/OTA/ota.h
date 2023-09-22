#ifndef _OTA_H_
#define _OTA_H_


#include <Arduino.h>
#include "ArduinoOTA.h"

void MY_OTA_Init(const char *passwoed, uint32_t port);



/*
;设置下载方式
upload_protocol = espota
;写入esp32现在的IP地址
upload_port = 192.168.21.11
upload_flags =
        ;设置下载需要的密码
        --auth=12345678
        ;设置下载端口
        --port=3232 
 */

#endif