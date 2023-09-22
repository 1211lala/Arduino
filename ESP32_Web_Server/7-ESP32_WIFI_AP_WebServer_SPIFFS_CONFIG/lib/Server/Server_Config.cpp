#include "Server_Config.h"
#include "SPIFFS_Config.h"

WebServer webserver(80); /* 设置网络服务器对象 端口80 */



void MY_Server_Config(void)
{
  webserver.on("/LED-Control", handleLEDHigh); /* 告知系统如何处理/LED-Control请求 */
  webserver.onNotFound(handleUserRequest);     /* 告知系统如何处理其它用户请求 */
  webserver.begin();                           /* 启动网站服务 */
  Serial.println("HTTP 服务器启动成功 ");
}


/* 处理/LED-Control请求 */
void handleLEDHigh(void)
{
  /*
    在html语句中 定义了一个类型为text的""变量"
    在浏览器中输入ok时，会一起被浏览器发送过来
    我们在程序中读取这个函数的变量
  */
  String ssid_str = webserver.arg("ssid");
  String password_str = webserver.arg("password");
  String other_str = webserver.arg("other");

  Serial.printf("ssid: %s\r\n", ssid_str.c_str());
  Serial.printf("password: %s\r\n", password_str.c_str());
  // Serial.printf("other: %s\r\n", other_str.c_str());

  String httpBody = "Please wait until the led light is on! <p><a href=\"/LED.html\"><-LED Page</a></p>";

  webserver.send(200, "text/html", httpBody);

  MY_SPIFFS_Write(path_ssid, ssid_str.c_str());
  MY_SPIFFS_Write(path_password, password_str.c_str());
  MY_SPIFFS_Write(path_mode, "STA");
  Serial.printf("数据已经写入SPIFFS,系统即将重启!!!\r\n");

  delay(1000);
  esp_restart();
}

// 处理用户浏览器的HTTP访问
void handleUserRequest(void)
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

/* 获取文件类型 */
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