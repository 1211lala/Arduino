#include "my_eeprom.h"

/**
 * @description:
 * @param {uint16_t} size EEPROM初始化大小
 * @return {*}
 */
void MY_EEPROM_Init(uint16_t size)
{
    EEPROM.begin(size); /* 开启4095个字节EEPROM */
}

/**
 * @description: 向指定地址写入固定长度的字符串
 * @param {uint16_t} WriteAddr 写入地址
 * @param {uint8_t} *pBuffer  将写入字符
 * @param {uint16_t} NumToWrite  写入字符长度
 * @return {*}
 */
void MY_EEPROM_Write_Buf(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite)
{
    while (NumToWrite--)
    {
        EEPROM.write(WriteAddr, *pBuffer);
        WriteAddr++;
        pBuffer++;
    }
    EEPROM.commit();    /* EEPEOM实际写入函数 */
}

/**
 * @description: 从固定地址读取固定长度字符
 * @param {uint8_t} ReadAddr    读取地址
 * @param {uint8_t} *pBuffer    字符串
 * @param {uint8_t} NumToRead   读取长度
 * @return {*}
 */
void MY_EEPROM_Read_Buf(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead)
{
    while (NumToRead)
    {
        *pBuffer++ = EEPROM.read(ReadAddr++);
        NumToRead--;
    }
}