#include <Arduino.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

#include "Server_Config.h"
#include "SPIFFS_Config.h"
#include "sta.h"
#include "ap.h"

String selectMode; /* 选择ESP32的工作模式 */

void setup()
{
  Serial.begin(115200);
  Serial.printf("\r\nWeb配网 \r\n");
  pinMode(LED, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);
  MY_SPIFFS_Init(0); /* 初始化SPIFFS */

  if (SPIFFS.exists(path_mode)) /* 判断文件是否存在 */
  {
  }
  else /* 如果不存在创造这个文件,并且写入"AP",第一次进入配网模式 */
  {
    MY_SPIFFS_Write(path_mode, "AP");
  }

  delay(10);

  selectMode = MY_SPIFFS_Read(path_mode); /* 读取mode文件中保存的消息 */

  if (selectMode == "AP\r\n" || selectMode == "AP")
  {
    Serial.printf("进入AP模式\r\n");
    MY_WIFI_AP_Config(WiFi_SOFT_SSD, WiFi_SOFT_PASSWORD, WIFI_MODE_AP); /* 配置WiFi热点参数 */
    MY_Server_Config();                                                 /* 配置服务器 很重要 */
  }
  else if (selectMode == "STA\r\n" || selectMode == "STA")
  {
    Serial.printf("进入STA模式\r\n\r\n");
    String get_ssid = MY_SPIFFS_Read(path_ssid);
    String get_password = MY_SPIFFS_Read(path_password);

    Serial.printf("从闪存文件中获取的内容如下:\r\n");
    Serial.printf("%s\r\n", get_ssid.c_str());
    Serial.printf("%s\r\n\r\n", get_password.c_str());

    WIFI_STA_Conncet(get_ssid.c_str(), get_password.c_str(), WIFI_MODE_STA);  /* 在这个函数中添加了超时判断,如果连续60s都没连接上目标WiFi就会重新进入AP模式 */
  }
}

void loop()
{
  if (selectMode == "AP\r\n" || selectMode == "AP")
  {
    Serial.printf("main in AP\r\n");
    while (1)
    {
      if (WiFi.softAPgetStationNum() > 0)
      {
        webserver.handleClient(); // 处理http服务器访问
        digitalWrite(LED, HIGH);
      }
      else
      {
        digitalWrite(LED, LOW);
      }
    }
  }
  else if (selectMode == "STA\r\n" || selectMode == "STA")
  {
    static uint32_t key_time = 0;

    Serial.printf("main in STA \r\n");
    while (1)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        if (digitalRead(KEY) == 0)
        {
          key_time++;
          if (key_time == 1000000)
          {
            Serial.printf("即将进入配网模式\r\n");
          }
          if (key_time == 2000000)
          {
            Serial.printf("配网模式\r\n");
            delay(1000);
            MY_SPIFFS_Write(path_mode, "AP");
            esp_restart();
          }
        }
        else
        {
          key_time = 0;
        }
        digitalWrite(LED, HIGH);
      }
      else
      {
        digitalWrite(LED, LOW);
      }
    }
  }
  else
  {
    Serial.printf("%s\r\n", selectMode.c_str());
  }
}