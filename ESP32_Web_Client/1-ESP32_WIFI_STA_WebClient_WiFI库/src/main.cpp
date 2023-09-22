#include <Arduino.h>
#include <WiFi.h>

#define     LED                 2
#define     WIFI_SSD            "realme GT Neo5"        /* 需要连接的热点名称 */
#define     WIFI_PASSWORD       "12111211"              /* 需要连接的热点密码 */
#define     HOST                "www.example.com"
#define     HTTPPORT            80

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


void HTTP_Client_Request(void)
{
  /*创建 Client 对象 */
  WiFiClient Client;

  String httpRequest = String("GET /") + " HTTP/1.1\r\n" + "Host: " + HOST + "\r\n" + "Connection: close\r\n" + "\r\n";

  if(Client.connect(HOST, HTTPPORT))
  {
    Serial.println("连接上网站服务器");
    /* 发送请求消息 */
    Client.print(httpRequest);
    while(Client.connected() || Client.available())       /* 不是死循环会退出 */
    {
      if(Client.available())
      {
        String line = Client.readStringUntil('\n');
        Serial.printf("connected %d\r\n",Client.connected());
        Serial.printf("available %d\r\n",Client.available());
      }
    }
    Client.stop();        
    Serial.printf("2 %d\r\n",Client.connected());              
    Serial.printf("2 %d\r\n",Client.available());
  }
  else
  {
    Serial.println("未连接上目标网址");
  }
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
    HTTP_Client_Request();
    digitalWrite(LED,!digitalRead(LED));

    
  }
  else
  {
    delay(1000);
    Serial.printf("网络已断开\r\n\r\n");
  }
}

