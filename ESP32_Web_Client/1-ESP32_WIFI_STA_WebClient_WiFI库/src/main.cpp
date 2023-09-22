#include <Arduino.h>
#include <WiFi.h>

#define     LED                 2
#define     WIFI_SSD            "realme GT Neo5"        /* ��Ҫ���ӵ��ȵ����� */
#define     WIFI_PASSWORD       "12111211"              /* ��Ҫ���ӵ��ȵ����� */
#define     HOST                "www.example.com"
#define     HTTPPORT            80

void WIFI_Conncet(const char *ssd, const char *password ,wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  Serial.printf("��ʼ����WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  WiFi.setSleep(false);                              
  WiFi.getAutoReconnect();                             
  Serial.printf("\r\nWiFi������: %s\r\n",WiFi.SSID().c_str());
  Serial.printf("ESP32IP: %s\r\n",WiFi.localIP().toString().c_str());
}


void HTTP_Client_Request(void)
{
  /*���� Client ���� */
  WiFiClient Client;

  String httpRequest = String("GET /") + " HTTP/1.1\r\n" + "Host: " + HOST + "\r\n" + "Connection: close\r\n" + "\r\n";

  if(Client.connect(HOST, HTTPPORT))
  {
    Serial.println("��������վ������");
    /* ����������Ϣ */
    Client.print(httpRequest);
    while(Client.connected() || Client.available())       /* ������ѭ�����˳� */
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
    Serial.println("δ������Ŀ����ַ");
  }
}

void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\nʵ�������ڻ�����������������������Ϣ\r\n");
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
    Serial.printf("�����ѶϿ�\r\n\r\n");
  }
}

