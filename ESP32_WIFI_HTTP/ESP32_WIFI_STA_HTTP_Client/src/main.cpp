/*
 * 在使用时首先把 sta.cpp 和 sta.h 中的 网络参数填好. IP 掩码 网关 连接的WiFi名 WiFi密码
 * 此代码是客户端.
 * 通过按下按键向服务器发送GET请求同时带着几个参数,参数每次发送都会增加1.
 * HTTP网上说不会丢包,但是我测试了一下,如果网络不好还是会丢包.
 * 所以在服务器接收到客户端发送的代码后会发送一个OK给客户端代表我已接受你的数据.
 * 客户端也通过这个接收到的数据肯定这个数据传输有效.
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

#define host "192.168.21.10"
#define hostport 80

WiFiClient client;
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);
  Serial.begin(115200);
  WIFI_STA_Conncet(WiFi_SSD, WiFi_PASSWORD, WIFI_MODE_STA);
}

void WiFiClientRequest(void)
{
  /***************************** 向服务器发送消息 **********************************/
  static int send_int = 0;
  static float send_float = 0;
  static String send_str = "helloworld";

  send_int += 1;
  send_float += 0.01;
  /* update 与服务器监听的请求要相同 */
  String url = "/update?float=" + String(send_float) + "&int=" + String(send_int) + "&str=" + send_str;
  /* 使用GET要有个空格别忘记  */
  String httpRrquest = String("GET ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" +
                       "Connection: colse\r\n" +
                       "\r\n";

  if (client.connect(host, hostport)) /* 向服务器发起连接 */
  {
    Serial.println("服务器连接成功!!!\r\n");
  }
  client.print(httpRrquest); /* 发送http语句 */

  Serial.printf("send_float: %.2f\r\n", send_float);
  Serial.printf("send_int: %d\r\n", send_int);
  Serial.printf("send_str: %s\r\n", send_str);
  Serial.println(httpRrquest);

  /***************************** 等待服务器的响应消息 **********************************/
  while (client.connected() || client.available())
  {
    if (client.find("server_send:")) /* find()函数会把目标字符之前的字符删除 */
    {
      String rec = client.readString();
      Serial.printf("从服务器收到的数据:%s\r\n", rec.c_str());
    }
  }
  client.stop();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (digitalRead(KEY) == 0)
    {
      WiFiClientRequest();
      delay(500);
      digitalWrite(LED, !digitalRead(LED));
    }
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}