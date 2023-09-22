#include "Server_Config.h"
#include "SPIFFS_Config.h"

WebServer Server(80); /* 设置网络服务器对象 端口80 */

void MY_Server_Config(void)
{
  /* 要和客户端发送的请求相对应 update*/
  Server.on("/update", handleUpdate);
  Server.onNotFound(handleNotfind); /* 告知系统如何处理其它用户请求 */
  Server.begin();                   /* 启动网站服务 */
  Serial.println("HTTP 服务器启动成功!!!\r\n");
}

void handleUpdate(void)
{
  /*****************处理接收到的数据*********************/
  float rec_float = Server.arg("float").toFloat();
  int rec_int = Server.arg("int").toInt();
  String rec_str = Server.arg("str");

  Serial.printf(" rec_float: %.2f\r\n", rec_float);
  Serial.printf(" rec_int: %d\r\n", rec_int);
  Serial.printf(" rec_str: %s\r\n", rec_str);

  /*****************发送返回消息*********************/
  // 带参数
  //  String send = "OK";
  //  Server.send(200, "text/html", "server_send:" + send);

  Server.send(200, "text/html", "OK");
}

void handleNotfind(void)
{
  Server.send(200, "text/plain", "Error");
}
