#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2

#define     WIFI_SSD            "ESP32_WiFi"
#define     WIFI_PASSWORD       "123456789"

#define   localPort             2002                /* ����UDP�˿ں�*/
IPAddress Local_IP(192,168,1,102);                  /* ����IP*/
IPAddress WIFI_GETWAY(192,168,1,1);                 /* ����������*/
IPAddress WIFI_SUBNET(255,255,255,0);               /* ����������*/

WiFiUDP udp;



char readUDP[255];                                 /* UDP���ݻ����*/

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  Serial.printf("\r\n\r\nAP������");
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(Local_IP, WIFI_GETWAY, WIFI_SUBNET);         
  if(WiFi.softAP(WIFI_SSD, WIFI_PASSWORD) != 1)
  {
    Serial.printf(".");
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nAP�ѿ���!!!\r\n");
  Serial.printf("�����ȵ�: %s\r\n",WiFi.softAPSSID().c_str());
  Serial.printf("����IP %s UDP�˿�: %d\r\n",WiFi.softAPIP().toString().c_str(), localPort);
}


void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.printf("\r\n\r\n������UDPͨѶ�����\r\n");
    WIFI_Conncet(WIFI_MODE_AP);
    udp.begin(localPort);                                     /* ��ʼ�������ض˿� */
}

void loop() 
{
  uint8_t rec_buf[255];
  uint8_t rec_num  = udp.parsePacket();             /* ��ѯ�鿴UDP�˿��Ƿ���յ����� */
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

