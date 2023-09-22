#include "sta.h"
#include "SPIFFS_Config.h"

void WIFI_STA_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  WiFi.getAutoConnect(); /* 开启自动重连 */
  WiFi.setSleep(false);  /* 关闭睡眠模式 */
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    static uint32_t count_time = 0;

    count_time += 1;
    if (count_time > 600) /* 一分钟还没连上网说明从SPIFFS得到的数据有问题，重新进入配网模式 */
    {
      MY_SPIFFS_Write(path_mode, "AP");
      Serial.printf("\r\n即将重新进入配网模式!!!\r\n");
      delay(2000);
      esp_restart();
    }

    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接成功!!!\r\n");

  Serial.printf("连接的WiFi名称 : %s\r\n", WiFi.SSID().c_str());
  Serial.printf("ESP32_IP : %s\r\n", WiFi.localIP().toString().c_str());
}