/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-16 12:57:10
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-16 13:16:50
 * @FilePath: \ESP32_SPIFFS\lib\SPIFFS\SPIFFS_Config.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _SPIFFS_CFG_
#define _SPIFFS_CFG_

#include <Arduino.h>
#include "SPIFFS.h"



void MY_SPIFFS_Init(bool format);
void MY_SPIFFS_Write(const char *path, const char *databuf);
void MY_SPIFFS_Append(const char *path, const char *databuf);
String MY_SPIFFS_Read(const char *path);
void MY_SPIFFS_Remove(const char *path);
#endif