
#include "ota.h"

/**
 * @description:
 * @param {char} *passwoed OTA升级的连接密码
 * @param {uint32_t} port   OTA升级的连接端口
 * @return {*}
 */
void MY_OTA_Init(const char *passwoed, uint32_t port)
{
    ArduinoOTA.setHostname("ESP32"); /* 可写可不写 */
    ArduinoOTA.setPassword(passwoed);
    ArduinoOTA.setPort(port);
    ArduinoOTA.begin();
    Serial.printf("ESP32 OTA 已启动\r\n");
}