/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-16 12:57:10
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-16 13:21:30
 * @FilePath: \ESP32_SPIFFS\lib\SPIFFS\SPIFFS_cfg.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "SPIFFS_CFG.h"

/**
 * @description:
 * @param {bool} format 1格式化 0不格式化
 * @return {*}
 */
void MY_SPIFFS_Init(bool format)
{
    if (format)
    {
        Serial.println("SPIFFS 开始格式化....\r\n");
        SPIFFS.format(); /* 格式化SPIFFS 时间很长 5s左右 */
        Serial.println("SPIFFS 格式化完成.\r\n");
    }
    if (SPIFFS.begin())
    {
        Serial.println("SPIFFS 初始化成功.\r\n");
    }
    //   Serial.printf("SPIFFS的总空间为 %dK\r\n", SPIFFS.totalBytes() / 1024);
    //   Serial.printf("SPIFFS已使用空间为 %dK\r\n", SPIFFS.usedBytes() / 1024);
}

/**
 * @description:
 * @param {char} *path  文件路径
 * @param {char} *databuf 需写入内容
 * @return {*}
 */
void MY_SPIFFS_Write(const char *path, const char *databuf)
{
    File dataFile = SPIFFS.open(path, "w");
    dataFile.printf(databuf);
    dataFile.close();
}

/**
 * @description:
 * @param {char} *path  文件路径
 * @param {char} *databuf   需添加内容
 * @return {*}
 */
void MY_SPIFFS_Append(const char *path, const char *databuf)
{
    if (SPIFFS.exists(path))
    {
        File dataFile = SPIFFS.open(path, "a");
        dataFile.printf(databuf);
        dataFile.close();
    }
    else
    {
        Serial.printf("%s 文件不存在,无法添加.\r\n", path);
    }
}

/**
 * @description:
 * @param {char} *path  文件读取路径
 * @return {*}
 */
String MY_SPIFFS_Read(const char *path)
{
    String readstr;
    if (SPIFFS.exists(path)) /* 判断文件是否存在 */
    {
        File readFile = SPIFFS.open(path, "r");
        readstr = readFile.readString();
        readFile.close();
        return readstr;
    }
    else
    {
        Serial.printf("%s 文件不存在,无法读取.\r\n", path);
    }
    readstr = "FF"; /* 读取失败返回 FF */
    return readstr;
}
/**
 * @description:
 * @param {char} *path  文件删除路径
 * @return {*}
 */
void MY_SPIFFS_Remove(const char *path)
{
    if (SPIFFS.exists(path)) /* 判断文件是否存在 */
    {
        SPIFFS.remove(path);      
    }
    else
    {
        Serial.printf("%s 文件不存在,无法删除.\r\n", path);
    }
}