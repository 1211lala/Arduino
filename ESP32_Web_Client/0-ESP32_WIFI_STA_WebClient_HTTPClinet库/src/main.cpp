#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define     LED                 2
#define     WIFI_SSD            "realme GT Neo5"        /* 需要连接的热点名称 */
#define     WIFI_PASSWORD       "12111211"              /* 需要连接的热点密码 */
#define     URL                 "http://www.example.com"/* 请求连接的URL */


void WIFI_Conncet(const char *ssd, const char *password ,wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  WiFi.setSleep(false);                              
  WiFi.getAutoReconnect();                             
  Serial.printf("\r\nWiFi连接至: %s\r\n",WiFi.SSID().c_str());
  Serial.printf("ESP32IP: %s\r\n",WiFi.localIP().toString().c_str());
}


void HTTP_Client_Request(String url)
{
  /*创建 HTTPClient 对象 */
  HTTPClient httpClient;
  /*向 begin 设置URL地址  */
  httpClient.begin(url);
  /* 通过GET 方式请求*/
  uint8_t httpCode = httpClient.GET();
  Serial.printf("已向 URL = %s 发送请求 With GET 请求\r\n", URL);
  if(httpCode == HTTP_CODE_OK)
  {
    Serial.printf("HTTP请求成功\r\n");
    String rec_httpclient = httpClient.getString();
    Serial.printf("返回内容\r\n%s\r\n\r\n",rec_httpclient.c_str());
  }
  else
  {
    Serial.printf("HTTP请求失败\r\n");
  }
  /* 关闭ESP32与服务器连接 */
  httpClient.end();
}

void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n实验内容在互联网下连接外网并返回消息\r\n");
  WIFI_Conncet(WIFI_SSD, WIFI_PASSWORD, WIFI_MODE_STA);
  
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)
  {
    delay(3000);
    HTTP_Client_Request(URL);
    digitalWrite(LED,!digitalRead(LED));
  }
  else
  {
    delay(1000);
    Serial.printf("网络已断开\r\n\r\n");
  }
}

