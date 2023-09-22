#include "SPIFFS_Config.h"



void MY_SPIFFS_Init(bool format)
{
    if (format)
    {
        Serial.println("SPIFFS 开始格式化....\r\n");
        SPIFFS.format();
        Serial.println("SPIFFS 格式化完成.\r\n");
    }
    if (SPIFFS.begin())
    {
        Serial.println("SPIFFS 初始化成功.\r\n");
    }
}


void MY_SPIFFS_Write(const char *path, const char *databuf)
{
    File dataFile = SPIFFS.open(path,"w");
    dataFile.printf(databuf);
    dataFile.close();
}


String MY_SPIFFS_Read(const char *path)
{
    String readstr;
    if (SPIFFS.exists(path)) /* 判断文件是否存在 */
    {
        File readFile = SPIFFS.open(path,"r");
        readstr = readFile.readString();
        // for (int i = 0; i < readFile.size(); i++)
        // {
        //     readstr += readFile.read(); /* 按字节读取 */
        // }
        readFile.close();
        return readstr;
    }
    else
    {
        Serial.printf("%s 不存在.\r\n", path);
    }
    readstr = "FF"; /* 读取失败返回 FF */
    return readstr;
}