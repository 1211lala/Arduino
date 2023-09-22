#include "Server_Config.h"
#include "SPIFFS_Config.h"

WebServer Server(80); /* 设置网络服务器对象 端口80 */

void MY_Server_Config(void)
{
  Server.on("/update", handleUpdate);
  Server.onNotFound(handleNotfind); /* 告知系统如何处理其它用户请求 */
  Server.begin();                   /* 启动网站服务 */
  Serial.println("HTTP 服务器启动成功!!!\r\n");
}

void handleUpdate(void)
{
  float rec_float = Server.arg("float").toFloat();
  int rec_int = Server.arg("int").toInt();
  String rec_str = Server.arg("str");

  Serial.printf(" %.2f\r\n", rec_float);
  Serial.printf(" %d\r\n", rec_int);
  Serial.printf(" %s\r\n", rec_str);

  Server.send(200, "text/plain", "Received");
}

void handleNotfind(void)
{
  Server.send(200, "text/plain", "Error");
}
