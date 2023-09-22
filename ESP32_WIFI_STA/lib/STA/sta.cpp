#include "sta.h"

IPAddress LocalIP(192, 168, 21, 12);
IPAddress WIFI_GETWAY(192, 168, 21, 1);
IPAddress WIFI_SUBNET(255, 255, 255, 0);

/**
 * @description: STA模式连接互联网
 * @param {char} *ssd 需连接的WiFi名称
 * @param {char} *password  需连接的WiFi密码
 * @param {bool} staticIP 是否启用静态IP
 * @return {*}
 */
void WIFI_STA_Conncet(const char *ssd, const char *password, bool staticIP)
{
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssd, password);
  WiFi.getAutoConnect(); /* 开启自动重连 */
  WiFi.setSleep(false);  /* 关闭睡眠模式 */
  if (staticIP == true)
  {
    WiFi.config(LocalIP, WIFI_GETWAY, WIFI_SUBNET); /* 配置静态*/
  }
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接成功!!!\r\n");

  Serial.printf("连接的WiFi名称 : %s\r\n", WiFi.SSID().c_str());
  Serial.printf("ESP32_IP : %s\r\n", WiFi.localIP().toString().c_str());
}