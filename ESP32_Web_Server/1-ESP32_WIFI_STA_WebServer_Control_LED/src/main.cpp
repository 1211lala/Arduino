#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define     LED                 2
#define     KEY                 0

#define     WIFI_SSD            "realme GT Neo5"        /* 需要连接的热点名称 */
#define     WIFI_PASSWORD       "12111211"              /* 需要连接的热点密码 */

WebServer   webserver(80);


void WIFI_Conncet(const char *ssd, const char *password ,wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print('.');
      delay(100);
      digitalWrite(LED, !digitalRead(LED));
  }
  WiFi.setSleep(false);                                 /* 关闭睡眠模式,响应更快 */
  WiFi.getAutoReconnect();                              /* 开启自动重连 */
  Serial.printf("\r\nWiFi连接至: %s\r\n",WiFi.SSID().c_str());
  Serial.printf("WiFi强度: %d\r\n",WiFi.RSSI());
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
    "/" 是ESP32的根目录    
    HTTP_GET 是请求方式
    handleRoot  是ESP32访问根目录要执行的函数
  */
  webserver.on("/",HTTP_GET , handleRoot);
  webserver.on("/LED", HTTP_POST, handleled);
  webserver.onNotFound(handleNotFound);
  Serial.printf("网络服务器启动成功\r\n!!!");
}


void setup() 
{
    pinMode(LED, OUTPUT);
    pinMode(KEY, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.printf("\r\n实验内容在同一个局域网下,浏览器登陆ESP32的IP,控制LED\r\n");
    WIFI_Conncet(WIFI_SSD, WIFI_PASSWORD, WIFI_MODE_STA);
    Web_Server_Init();
}

void loop() 
{
  if(WiFi.status() == WL_CONNECTED)
  {
    webserver.handleClient();     // 处理http服务器访问
  }
  else
  {
    delay(1000);
    Serial.printf("网络已断开\r\n\r\n");
  }
}

