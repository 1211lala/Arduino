#include <Arduino.h>
#include <WiFi.h>

#define     LED              2
#define     WIFI_SSD        "realme GT Neo5"
#define     WIFI_PASSWORD   "12111211"


#define     LocalPort       2001
IPAddress   LocalIP(192, 168, 2, 11);
IPAddress   WIFI_GETWAY(192, 168, 2, 1);
IPAddress   WIFI_SUBNET(255, 255, 255, 0);

WiFiServer  server;     /* 定义一个服务端 */

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(WIFI_SSD, WIFI_PASSWORD);
  WiFi.getAutoConnect();                              /* 开启自动重连 */
  WiFi.setSleep(false);                               /* 关闭睡眠模式 */
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接成功!!!\r\n");

  WiFi.config(LocalIP, WIFI_GETWAY, WIFI_SUBNET);
  server.begin(LocalPort);
  Serial.printf("ESP32_IP : %s\r\n", WiFi.localIP().toString().c_str());
  
  Serial.printf("服务器IP : %s,  Port : %d", WiFi.localIP().toString().c_str(), LocalPort);
  
}



void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.printf("\r\n\r\n");
    WIFI_Conncet(WIFI_MODE_STA);
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client = server.available();
    if(client)
    {
      printf("已连接客户端\r\n");
      while(client.connected())
      {
        uint8_t rec_buf[255];
        uint8_t rec_num = client.available();
        if(rec_num)
        {
          client.readBytes(rec_buf, rec_num);
          rec_buf[rec_num] = '\0';

          Serial.printf("接收到 %d 字节 --> %s\r\n",strlen((char*)rec_buf), rec_buf);

          client.printf("接收到 %d 字节 --> %s\r\n",strlen((char*)rec_buf), rec_buf);

          digitalWrite(LED, HIGH);
        }
      }
    }
    else    /* 连接上网络 未有客户端连接  LED 500ms闪烁*/
    {
      client.stop();
      delay(500);
      Serial.printf("未有客户端连接!!!\r\n");
      digitalWrite(LED, !digitalRead(LED));
    }
  }
  else      /* 未连接上网络 LED熄灭 */
  {
    WIFI_Conncet(WIFI_MODE_STA);
    digitalWrite(LED, LOW);
  }
}
