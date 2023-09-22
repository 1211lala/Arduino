#include "ap.h"

IPAddress ESP_SOFT_IP(192, 168, 1, 1);       /* 热点IP */
IPAddress ESP_SOFT_GETWAY(192, 168, 1, 1);   /* 热点网关 */
IPAddress ESP_SOFT_SUBNET(255, 255, 255, 0); /* 热点掩码 */


/* 建立WiFi热点 */
void MY_WIFI_AP_Config(const char *ssd, const char *password, wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.softAPConfig(ESP_SOFT_IP, ESP_SOFT_GETWAY, ESP_SOFT_SUBNET);
  Serial.printf("\n开启WiFi...");
  while (!WiFi.softAP(ssd, password))
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\nWiFi名称: %s\r\n", WiFi.softAPSSID().c_str());
  Serial.printf("ESP32IP: %s\r\n", WiFi.softAPIP().toString().c_str());
}