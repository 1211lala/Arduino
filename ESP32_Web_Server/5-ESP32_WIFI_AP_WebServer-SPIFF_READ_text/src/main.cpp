#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

String getContentType(String filename);
bool handleFileRead(String resource);
void handleUserRequest();
void handleLEDHigh();
void handleLEDLow();

#define LED 2

#define WiFi_SSD "ESP32_WiFi"           /* 设置热点名称 */
#define WiFi_PASSWORD "123456789"       /* 设置热点密码 */
IPAddress ESP_IP(192, 168, 1, 1);       /* 热点IP */
IPAddress ESP_GETWAY(192, 168, 1, 1);   /* 热点网关 */
IPAddress ESP_SUBNET(255, 255, 255, 0); /* 热点掩码 */


WebServer webserver(80); /* 设置网络服务器对象 端口80 */

/* 连接网络 */
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


void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.printf("\r\n实验内容在同一个局域网下,浏览器访问ESP32的IP发起请求, ESP32通过请求从SPIFFS中读取消息并发送到浏览器\r\n");
  WIFI_Config(WiFi_SSD, WiFi_PASSWORD, WIFI_MODE_AP);
  // SPIFFS.format();
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS 初始化失败.\r\n");
  }
  webserver.on("/LED-Control", handleLEDHigh); // 告知系统如何处理/LED-Control请求
  
  webserver.onNotFound(handleUserRequest);     // 告知系统如何处理其它用户请求

  webserver.begin(); /* 启动网站服务 */
  Serial.println("HTTP 服务器启动成功 ");
}

void loop()
{
  if (WiFi.softAPgetStationNum() > 0)
  {
    webserver.handleClient(); // 处理http服务器访问
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}

// 处理/LED-Control请求
void handleLEDHigh()
{
  

  /*
    在html语句中 定义了一个类型为text名称为ledPwm的""变量"
    我们在浏览器中输入ok时，会一起被浏览器发送过来
    我们在程序中读取这个函数的变量
  */

  String str = webserver.arg("ledPwm");
  Serial.printf("Web rec : %s  %d.\r\n", str.c_str(), str.toInt());

  int ledPwm = str.toInt();
  String httpBody = "Led PWM: " + str + "<p><a href=\"/LED.html\"><-LED Page</a></p>";

  webserver.send(200, "text/html", httpBody);
}

// void handleLEDLow()
// {
//   digitalWrite(LED, LOW);
//   webserver.sendHeader("Location", "/LED.html");
//   webserver.send(303);
// }


// 处理用户浏览器的HTTP访问
void handleUserRequest()
{
  // 获取用户请求资源(Request Resource）
  String reqResource = webserver.uri();
  Serial.print("reqResource: ");
  Serial.println(reqResource);

  // 通过handleFileRead函数处处理用户请求资源
  bool fileReadOK = handleFileRead(reqResource);

  // 如果在SPIFFS无法找到用户访问的资源，则回复404 (Not Found)
  if (!fileReadOK)
  {
    webserver.send(404, "text/plain", "404 Not Found");
  }
}

bool handleFileRead(String resource)
{ // 处理浏览器HTTP访问

  if (resource.endsWith("/"))
  {                           // 如果访问地址以"/"为结尾
    resource = "/index.html"; // 则将访问地址修改为/index.html便于SPIFFS访问
  }

  String contentType = getContentType(resource); // 获取文件类型

  if (SPIFFS.exists(resource))
  {                                          // 如果访问的文件可以在SPIFFS中找到
    File file = SPIFFS.open(resource, "r");  // 则尝试打开该文件
    webserver.streamFile(file, contentType); // 并且将该文件返回给浏览器
    file.close();                            // 并且关闭文件
    return true;                             // 返回true
  }
  return false; // 如果文件未找到，则返回false
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