#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2

#define     WIFI_SSD            "ESP32_WiFi"
#define     WIFI_PASSWORD       "123456789"

#define   localPort             2002                /* 本机UDP端口号*/
IPAddress Local_IP(192,168,1,102);                  /* 本机IP*/
IPAddress WIFI_GETWAY(192,168,1,1);                 /* 局域网网关*/
IPAddress WIFI_SUBNET(255,255,255,0);               /* 局域网掩码*/

WiFiUDP udp;



char readUDP[255];                                 /* UDP数据缓存块*/

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  Serial.printf("\r\n\r\nAP开启中");
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(Local_IP, WIFI_GETWAY, WIFI_SUBNET);         
  if(WiFi.softAP(WIFI_SSD, WIFI_PASSWORD) != 1)
  {
    Serial.printf(".");
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nAP已开启!!!\r\n");
  Serial.printf("本机热点: %s\r\n",WiFi.softAPSSID().c_str());
  Serial.printf("本机IP %s UDP端口: %d\r\n",WiFi.softAPIP().toString().c_str(), localPort);
}


void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.printf("\r\n\r\n本机做UDP通讯服务端\r\n");
    WIFI_Conncet(WIFI_MODE_AP);
    udp.begin(localPort);                                     /* 开始侦听本地端口 */
}

void loop() 
{
  uint8_t rec_buf[255];
  uint8_t rec_num  = udp.parsePacket();             /* 轮询查看UDP端口是否接收到数据 */
  if(rec_num > 0)
  {
    udp.read(rec_buf, rec_num);
    readUDP[rec_num] = '\0';

    if(rec_num == 4)
    {
      if(rec_buf[3] == (rec_buf[0] + rec_buf[1] + rec_buf[2]))
      {
        if(rec_buf[2] == 0x01)
        {
          digitalWrite(LED, HIGH);
        }
        else if(rec_buf[2] == 0x00)
        {
          digitalWrite(LED, LOW);
        }
      }
    }
  }
}

