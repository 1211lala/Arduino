#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define     LED                 2
#define     KEY                 0

#define     WIFI_SSD            "realme GT Neo5"        /* ��Ҫ���ӵ��ȵ����� */
#define     WIFI_PASSWORD       "12111211"              /* ��Ҫ���ӵ��ȵ����� */

WebServer   webserver(80);


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
  WiFi.setSleep(false);                                 /* �ر�˯��ģʽ,��Ӧ���� */
  WiFi.getAutoReconnect();                              /* �����Զ����� */
  Serial.printf("\r\nWiFi������: %s\r\n",WiFi.SSID().c_str());
  Serial.printf("WiFiǿ��: %d\r\n",WiFi.RSSI());
  Serial.printf("ESP32IP: %s\r\n",WiFi.localIP().toString().c_str());

}


void handleRoot(void)
{
  webserver.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

void handleNotFound(void)
{
  webserver.send(404, "text/plain", "404: Not found");  
}

void handleled(void)
{
  digitalWrite(LED,!digitalRead(LED));
  webserver.sendHeader("Location","/");
  webserver.send(303); 
  delay(20);
}

void Web_Server_Init(void)
{
  webserver.begin();
  /*
    "/" ��ESP32�ĸ�Ŀ¼    
    HTTP_GET ������ʽ
    handleRoot  ��ESP32���ʸ�Ŀ¼Ҫִ�еĺ���
  */
  webserver.on("/",HTTP_GET , handleRoot);
  webserver.on("/LED", HTTP_POST, handleled);
  webserver.onNotFound(handleNotFound);
  Serial.printf("��������������ɹ�\r\n!!!");
}


void setup() 
{
    pinMode(LED, OUTPUT);
    pinMode(KEY, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.printf("\r\nʵ��������ͬһ����������,�������½ESP32��IP,����LED\r\n");
    WIFI_Conncet(WIFI_SSD, WIFI_PASSWORD, WIFI_MODE_STA);
    Web_Server_Init();
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)
  {
    webserver.handleClient();     // ����http����������
  }
  else
  {
    delay(1000);
    Serial.printf("�����ѶϿ�\r\n\r\n");
  }
}

