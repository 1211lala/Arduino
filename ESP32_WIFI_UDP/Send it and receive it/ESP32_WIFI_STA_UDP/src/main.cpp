#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2

#define     WiFi_SSD            "ESP32_WiFi"          /* �����ȵ����� */
#define     WiFi_PASSWORD       "123456789"           /* �����ȵ����� */ 

// #define     WiFi_SSD            "realme GT Neo5"          /* �����ȵ����� */
// #define     WiFi_PASSWORD       "12111211"           /* �����ȵ����� */

IPAddress   ESP_GETWAY(192, 168, 1, 1);               /* �ȵ����� */
IPAddress   ESP_SUBNET(255,255,255,0);                /* �ȵ����� */

IPAddress   ESP_IP(192, 168, 1, 5);                   /* ����IP */
#define     LocalPort           2002                  /* ���ض˿� */

IPAddress   Server_IP(192, 168, 1, 2);                /* Զ��IP */
#define     ServerPort           2001                 /* Զ�˶˿� */

WiFiUDP udp;

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  Serial.printf("\r\nWiFi������\r\n");  
  WiFi.mode(wifi_mode);
  WiFi.setSleep(false);
  WiFi.getAutoConnect();
  WiFi.begin(WiFi_SSD, WiFi_PASSWORD);
  WiFi.config(ESP_IP, ESP_GETWAY, ESP_SUBNET);  
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi���ӳɹ�!!!\r\n");
  Serial.printf("������: %s\r\n",WiFi.SSID().c_str());
  Serial.printf("����IP: %s  ", WiFi.localIP().toString().c_str());
  Serial.printf("UDP Port: %d\r\n", LocalPort);
}


void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n\r\n");
  WIFI_Conncet(WIFI_MODE_STA);
  udp.begin(LocalPort);
}
uint8_t ON_buf[] ={0x01, 0x02, 0x01, 0x04};
uint8_t OFF_buf[] ={0x01, 0x02, 0x00, 0x03};

void loop() 
{

  if(WiFi.status() == WL_CONNECTED)
  {
    udp.beginPacket(Server_IP, ServerPort);
    udp.write(ON_buf, 4);
    Serial.write(ON_buf, 4);
    udp.endPacket();
    delay(2000);


    udp.beginPacket(Server_IP, ServerPort);
    udp.write(OFF_buf,4);
    Serial.write(OFF_buf,4);
    udp.endPacket();
    delay(2000);
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}
