#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2

#define     WiFi_SSD            "ESP32_WiFi"          /* �����ȵ����� */
#define     WiFi_PASSWORD       "123456789"           /* �����ȵ����� */
#define     LocalPort           2001


IPAddress   ESP_IP(192, 168, 1, 2);                   /* �ȵ�IP */
IPAddress   ESP_GETWAY(192, 168, 1, 1);               /* �ȵ����� */
IPAddress   ESP_SUBNET(255,255,255,0);                /* �ȵ����� */

WiFiUDP udp;

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  Serial.printf("\r\nAP������\r\n");  
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(ESP_IP, ESP_GETWAY, ESP_SUBNET);  
  while(!WiFi.softAP(WiFi_SSD, WiFi_PASSWORD))
  {
    delay(100);
    Serial.printf(".");
  }
  Serial.printf("\r\nAP�����ɹ�!!!\r\n");
  Serial.printf("�ȵ�����: %s\r\n",WiFi.softAPSSID());
  Serial.printf("�ȵ�IP: %s\r\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("UDP Port: %d\r\n", LocalPort);


}


void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n������������\r\n");
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

    /* �߼��ж� */
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
