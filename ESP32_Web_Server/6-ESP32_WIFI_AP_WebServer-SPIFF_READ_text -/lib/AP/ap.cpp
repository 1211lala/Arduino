#include "ap.h"



/* 建立WiFi热点 */
void WIFI_Config(const char *ssd, const char *password, wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(ESP_IP, ESP_GETWAY, ESP_SUBNET);
  Serial.printf("开启WiFi...");
  while (!WiFi.softAP(ssd, password))
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }

  Serial.printf("\nWiFi名称: %s\r\n", WiFi.softAPSSID().c_str());
  Serial.printf("ESP32IP: %s\r\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("WiFi强度: %d\r\n", WiFi.RSSI());
}