#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


#define     LED                 2
// #define     WIFI_SSD            "realme GT Neo5"
// #define     WIFI_PASSWORD       "12111211"

#define     WIFI_SSD            "TP-LINK 505"
#define     WIFI_PASSWORD       "tplink505"


#define     localPort           2002
IPAddress Local_IP(192,168,1,102);                 /* ���ؾ�̬IP */
IPAddress WIFI_GETWAY(192,168,1,1);                /* ���������� */
IPAddress WIFI_SUBNET(255,255,255,0);              /* ���������� */
WiFiUDP udp;

char readUDP[255];

void WIFI_Conncet(wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(WIFI_SSD, WIFI_PASSWORD);
  Serial.printf("��ʼ����WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi���ӳɹ�!!!\r\n");
  Serial.printf("ESP32 IP : %s\r\n",WiFi.localIP().toString().c_str());
  Serial.printf("WiFiǿ��: %d\r\n",WiFi.RSSI());


  WiFi.config(Local_IP, WIFI_GETWAY, WIFI_SUBNET);   /* ���� ������ַ �� ���� �� ����*/
  if(udp.begin(localPort))
  {
    Serial.printf("��ʼ���� IP:%s �˿�:%d ������\r\n",WiFi.localIP().toString().c_str(), localPort);
  }
  WiFi.setSleep(false);                           /* �ر�˯��ģʽ */
}


void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.printf("\r\nʵ������ESP32��ΪUDP�ķ�����,���յ��ͻ��˵���Ϣ��,���ں�UDP����ӡ�յ�����Ϣ\r\n");
    WIFI_Conncet(WIFI_MODE_STA);
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)       /* �鿴�Ƿ����������� -- LED������ʾ */
  {
    int pack;
    pack = udp.parsePacket();             /* ��ѯ�鿴UDP�˿��Ƿ���յ����� */
    if(pack > 0)
    {
      udp.read(readUDP, pack);
      readUDP[pack] = '\0';

      /* ���ڴ�ӡ��UDP���� */
      Serial.printf("�յ����� %s �˿�: %2d ��%d�ֽ����� :  %s\r\n", udp.remoteIP().toString().c_str(),udp.remotePort(), pack, readUDP);
      
      /* UDP��Ŀ��˷��ͽ��յ����� */
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.printf("�յ����� %s �˿�: %2d ��%d�ֽ����� :  %s\r\n", udp.remoteIP().toString().c_str(),udp.remotePort(), pack, readUDP);

      udp.endPacket();
    }
    pack = 0;
    digitalWrite(LED, HIGH);
  }
  else  /* û�н��յ����� */
  {
    WIFI_Conncet(WIFI_MODE_STA);
    digitalWrite(LED, LOW);
  }
}

