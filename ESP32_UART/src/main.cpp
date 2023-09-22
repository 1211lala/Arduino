/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-01 08:51:29
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-17 12:11:03
 * @FilePath: \ESP32_UART\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "my_uart.h"

#define LED 2 /* 板载LED在IO2 */
void setup()
{

  MY_UART0_Init(115200);
  MY_UART2_Init(115200);
  pinMode(LED, OUTPUT);
}

void loop()
{
  uint32_t size0 = Serial.available();
  char str0[255];
  if (size0)
  {
    MY_UART0_Receive_Buf(str0, size0);
    Serial.printf("%s\r\n", str0);
  }

  uint32_t size2 = Serial2.available();
  char str2[255];
  if (size2)
  {
    MY_UART2_Receive_Buf(str2, size2);
    Serial2.printf("%s\r\n", str2);
  }
}
