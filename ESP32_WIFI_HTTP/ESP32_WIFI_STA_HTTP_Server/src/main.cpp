/*
 * 在使用时首先把 sta.cpp 和 sta.h 中的 网络参数填好. IP 掩码 网关 连接的WiFi名 WiFi密码
 * 此代码是服务器端.
 * 监听HTTP端口80,如果有 "/update请求执行 "SPIFFS_Config.cpp"中的handleUpdate()函数
 * 从客户端的http语句中读取三个变量的值分别为 int float String 类型
 * 在接收完数据后向客户端返回"OK"表示服务器已接收数据
 *
 *
 * ps:这个代码实现的HTTP传输延迟很高单次通讯网络好的情况在2s左右(从客户端发送到客户端接收)
 *    使用的手机开热点(不知道和这个有没有问题)
 */

#include <Arduino.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

#include "Server_Config.h"
#include "SPIFFS_Config.h"
#include "sta.h"
#include "ap.h"

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  WIFI_STA_Conncet(WiFi_SSD, WiFi_PASSWORD, WIFI_MODE_STA);
  MY_Server_Config();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Server.handleClient();
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}