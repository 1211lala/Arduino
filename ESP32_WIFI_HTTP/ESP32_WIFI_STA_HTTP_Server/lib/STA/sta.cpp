#include "sta.h"
#include "SPIFFS_Config.h"

IPAddress ESP_IP(192, 168, 21, 10);       /* 热点IP */
IPAddress ESP_GETWAY(192, 168, 21, 109); /* 热点网关 */
IPAddress ESP_SUBNET(255, 255, 255, 0);  /* 热点掩码 */

void WIFI_STA_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  WiFi.config(ESP_IP, ESP_GETWAY, ESP_SUBNET); /* 设置固定IP前三位要和路由器一致 */
  WiFi.getAutoConnect();                       /* 开启自动重连 */
  WiFi.setSleep(false);                        /* 关闭睡眠模式 */
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    static uint32_t count_time = 0;

    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接成功!!!\r\n");

  Serial.printf("连接的WiFi名称 : %s\r\n", WiFi.SSID().c_str());
  Serial.printf("ESP32_IP : %s\r\n", WiFi.localIP().toString().c_str());
}