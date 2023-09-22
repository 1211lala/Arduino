#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

void WIFI_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode);
String getContentType(String filename);
bool handleFileRead(String path);
void handleUserRequet();

#define LED 2

#define WIFI_SSD "realme GT Neo5" /* 需要连接的热点名称 */
#define WIFI_PASSWORD "12111211"  /* 需要连接的热点密码 */

WebServer webserver(80); /* 设置网络服务器对象 端口80 */

/* 连接网络 */
void WIFI_Conncet(const char *ssd, const char *password, wifi_mode_t wifi_mode)
{
  WiFi.mode(wifi_mode);
  WiFi.begin(ssd, password);
  WiFi.setSleep(false);    /* 关闭睡眠模式,响应更快 */
  WiFi.getAutoReconnect(); /* 开启自动重连 */
  Serial.printf("开始连接WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(100);
    digitalWrite(LED, !digitalRead(LED));
  }
  Serial.printf("\r\nWiFi连接至: %s\r\n", WiFi.SSID().c_str());
  Serial.printf("ESP32IP: %s\r\n", WiFi.localIP().toString().c_str());
  Serial.printf("WiFi强度: %d\r\n", WiFi.RSSI());
}

// 获取文件类型
String getContentType(String filename)
{
  if (filename.endsWith(".htm"))
    return "text/html";
  else if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".png"))
    return "image/png";
  else if (filename.endsWith(".gif"))
    return "image/gif";
  else if (filename.endsWith(".jpg"))
    return "image/jpeg";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".xml"))
    return "text/xml";
  else if (filename.endsWith(".pdf"))
    return "application/x-pdf";
  else if (filename.endsWith(".zip"))
    return "application/x-zip";
  else if (filename.endsWith(".gz"))
    return "application/x-gzip";
  return "text/plain";
}

/* 处理浏览器HTTP访问 */
bool handleFileRead(String path)
{
  if (path.endsWith("/"))
  {                       /* 如果访问地址以"/"为结尾 */
    path = "/index.html"; /* 则将访问地址修改为/index.html便于SPIFFS访问 */
  }

  String contentType = getContentType(path); /* 获取文件类型 */

  if (SPIFFS.exists(path))
  {                                          /* 如果访问的文件可以在SPIFFS中找到 */
    File file = SPIFFS.open(path, "r");      /* 则尝试打开该文件 */
    webserver.streamFile(file, contentType); /* 并且将该文件返回给浏览器 */
    file.close();                            /* 并且关闭文件 */
    return true;                             /* 返回true */
  }
  return false; /* 如果文件未找到，则返回false */
}

void handleUserRequet()
{
  /* 获取用户请求网址信息 */
  String reqResource = webserver.uri();
  /* 通过handleFileRead函数处处理用户访问 */
  bool fileReadOK = handleFileRead(reqResource);
  Serial.printf("用户请求是：%s \r\n", reqResource.c_str());
  /* 如果在SPIFFS无法找到用户访问的资源，则回复404 (Not Found) */
  if (!fileReadOK)
  {
    webserver.send(404, "text/plain", "404 Not Found");
  }
}

void handleNotFound(void)
{
  webserver.send(404, "text/plain", "404: Not found");
}
void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n实验内容在同一个局域网下,浏览器访问ESP32的IP发起请求, ESP32通过请求从SPIFFS中读取消息并发送到浏览器\r\n");
  WIFI_Conncet(WIFI_SSD, WIFI_PASSWORD, WIFI_MODE_STA);

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS 初始化失败.\r\n");
  }

  /* 这里没有定义 webserver.on() 函数 所以webserver.onNotFound() 函数处理用户的所有请求 */
  webserver.onNotFound(handleUserRequet);

  // webserver.on("/", handleUserRequet);                     /* 告知系统如何处理用户请求 */
  // webserver.on("/main.css", handleUserRequet);             /* 告知系统如何处理用户请求 */
  // webserver.on("/clock.js", handleUserRequet);             /* 告知系统如何处理用户请求 */
  // webserver.on("/img/taichi-maker.jpg", handleUserRequet); /* 告知系统如何处理用户请求 */
  // webserver.onNotFound(handleNotFound);                    /* 告知系统如何处理用户请求 */

  webserver.begin(); /* 启动网站服务 */
  Serial.println("HTTP 服务器启动成功 ");
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    webserver.handleClient(); // 处理http服务器访问
    digitalWrite(LED, HIGH);
  }
  else
  {
    delay(1000);
    Serial.printf("网络已断开\r\n\r\n");
    digitalWrite(LED, LOW);
  }
}
