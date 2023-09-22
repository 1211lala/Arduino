/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-11 16:34:35
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-16 13:30:22
 * @FilePath: \ESP32_SPIFFS\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "spiffs_cfg.h"

String file_test = "/esp32/test.txt";

#define ssid "esp wifi"
#define password "12111211"

void setup()
{
  Serial.begin(115200);
  Serial.println("");

  MY_SPIFFS_Init(0);
  MY_SPIFFS_Write(file_test.c_str(), ssid);

  String readStr = MY_SPIFFS_Read(file_test.c_str());
  Serial.printf("读取到:%s\r\n", readStr.c_str());

  MY_SPIFFS_Append(file_test.c_str(), password);
  readStr = MY_SPIFFS_Read(file_test.c_str());
  Serial.printf("读取到:%s\r\n", readStr.c_str());

  MY_SPIFFS_Remove(file_test.c_str());

  if (SPIFFS.exists(file_test.c_str()))
  {
  }
  else
  {
    Serial.printf("%s已删除\r\n", file_test.c_str());
  }

  /***************************************** 文件夹未写 *********************************************/
}

void loop()
{
  delay(1000);
}