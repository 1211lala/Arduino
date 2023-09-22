#include <Arduino.h>
#include <WiFi.h>

#define     LED              2
#define     WIFI_SSD        "realme GT Neo5"
#define     WIFI_PASSWORD   "12111211"


#define     LocalPort       2001
#define     RemotePort      2002

IPAddress   RemoteIP(192, 168, 2, 19);

WiFiClient  client;     /*定义一个客户端*/

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
  Serial.printf("ESP32_IP : %s\r\n", WiFi.localIP().toString().c_str());

  Serial.printf("需要连接的远端IP : %s, Port : %d", RemoteIP.toString().c_str(), RemotePort);
  
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
    Serial.println("尝试访问服务器");
    if(client.connect(RemoteIP, RemotePort))
    {
      Serial.println("访问成功");
      while(client.connected())       /* 连接上网络 连接上服务器  LED 常亮  但是在http请求时这个while不是死循环 */
      {
        Serial.printf("22222\r\n");
        uint16_t rec_num =  client.available();       /* 注意堵塞获取当前未接收的字节数 ,不能发太快 300ms一次比较合适，不然数据会堵塞在一起 */
        if(rec_num)
        {
          uint8_t rec_buf[255];             
          client.readBytes(rec_buf, rec_num);
          rec_buf[rec_num] = '\0';                    /* 库里函数默认没有加'\0' */
          client.printf("接收到%d字节数据\r\n",strlen((char*)rec_buf));
          client.printf("接收到的数据为 : %s\r\n",(char*)rec_buf);
        }
        digitalWrite(LED, HIGH);
      }

      Serial.printf("111111\r\n");
    }
    else    /* 连接上网络 未有客户端连接  LED 500ms闪烁*/
    {
      client.stop();
      delay(500);
      Serial.printf("未连接上服务器!!!\r\n");
      digitalWrite(LED, !digitalRead(LED));
    }
  }
  else      /* 未连接上网络 LED熄灭 */
  {
    WIFI_Conncet(WIFI_MODE_STA);
    digitalWrite(LED, LOW);
  }
}
