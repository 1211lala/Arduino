#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2

#define     WiFi_SSD            "ESP32_WiFi"          /* 设置热点名称 */
#define     WiFi_PASSWORD       "123456789"           /* 设置热点密码 */
#define     LocalPort           2001


IPAddress   ESP_IP(192, 168, 1, 2);                   /* 热点IP */
IPAddress   ESP_GETWAY(192, 168, 1, 1);               /* 热点网关 */
IPAddress   ESP_SUBNET(255,255,255,0);                /* 热点掩码 */

WiFiUDP udp;

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  Serial.printf("\r\nAP启动中\r\n");  
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(ESP_IP, ESP_GETWAY, ESP_SUBNET);  
  while(!WiFi.softAP(WiFi_SSD, WiFi_PASSWORD))
  {
    delay(100);
    Serial.printf(".");
  }
  Serial.printf("\r\nAP启动成功!!!\r\n");
  Serial.printf("热点名称: %s\r\n",WiFi.softAPSSID());
  Serial.printf("热点IP: %s\r\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("UDP Port: %d\r\n", LocalPort);


}


void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n本机做服务器\r\n");
  WIFI_Conncet(WIFI_MODE_AP);
  udp.begin(LocalPort);
}

void loop() 
{
  int rec_num = udp.parsePacket();
  if(rec_num)
  {
    Serial.printf("num :%d\r\n",rec_num);
    uint8_t rec_buf[255];
    udp.readBytes(rec_buf, rec_num);
    rec_buf[rec_num] = '\0';

    /* 逻辑判断 */
    if(rec_num == 4)
    {
      Serial.printf("1111\r\n");
      if(rec_buf[3] == (rec_buf[0] + rec_buf[1] +rec_buf[2]))
      {
        Serial.printf("2222\r\n");
        if(rec_buf[2] == 0X01)
        {

          Serial.printf("3333\r\n");
          digitalWrite(LED, HIGH);
          udp.beginPacket(udp.remoteIP(), udp.remotePort());
          udp.printf("LED ON!!\r\n");
          udp.endPacket();
        }
        else if(rec_buf[2] == 0X00)
        {
          Serial.printf("4444\r\n");
          digitalWrite(LED, LOW);
          udp.beginPacket(udp.remoteIP(), udp.remotePort());
          udp.printf("LED OFF!!\r\n");
          udp.endPacket();
        }
      }
    }
  }
}
