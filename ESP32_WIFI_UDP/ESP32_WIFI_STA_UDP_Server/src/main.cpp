#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2
// #define     WIFI_SSD            "realme GT Neo5"
// #define     WIFI_PASSWORD       "12111211"

#define     WIFI_SSD            "TP-LINK 505"
#define     WIFI_PASSWORD       "tplink505"


#define     localPort           2002
IPAddress Local_IP(192,168,1,102);                 /* 本地静态IP */
IPAddress WIFI_GETWAY(192,168,1,1);                /* 局域网网关 */
IPAddress WIFI_SUBNET(255,255,255,0);              /* 局域网掩码 */
WiFiUDP udp;

char readUDP[255];

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(WIFI_SSD, WIFI_PASSWORD);
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接成功!!!\r\n");
  Serial.printf("ESP32 IP : %s\r\n",WiFi.localIP().toString().c_str());
  Serial.printf("WiFi强度: %d\r\n",WiFi.RSSI());


  WiFi.config(Local_IP, WIFI_GETWAY, WIFI_SUBNET);   /* 设置 本机地址 与 网关 和 掩码*/
  if(udp.begin(localPort))
  {
    Serial.printf("开始监听 IP:%s 端口:%d 的数据\r\n",WiFi.localIP().toString().c_str(), localPort);
  }
  WiFi.setSleep(false);                           /* 关闭睡眠模式 */
}


void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.printf("\r\n实验内容ESP32作为UDP的服务器,接收到客户端的消息后,串口和UDP都打印收到的消息\r\n");
    WIFI_Conncet(WIFI_MODE_STA);
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)       /* 查看是否连接上网络 -- LED点亮提示 */
  {
    int pack;
    pack = udp.parsePacket();             /* 轮询查看UDP端口是否接收到数据 */
    if(pack > 0)
    {
      udp.read(readUDP, pack);
      readUDP[pack] = '\0';

      /* 串口打印出UDP数据 */
      Serial.printf("收到来自 %s 端口: %2d 的%d字节数据 :  %s\r\n", udp.remoteIP().toString().c_str(),udp.remotePort(), pack, readUDP);
      
      /* UDP向目标端发送接收到数据 */
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.printf("收到来自 %s 端口: %2d 的%d字节数据 :  %s\r\n", udp.remoteIP().toString().c_str(),udp.remotePort(), pack, readUDP);

      udp.endPacket();
    }
    pack = 0;
    digitalWrite(LED, HIGH);
  }
  else  /* 没有接收到数据 */
  {
    WIFI_Conncet(WIFI_MODE_STA);
    digitalWrite(LED, LOW);
  }
}

