
#include "my_uart.h"

/**
 * @description:    UART0初始化
 * @param {uint32_t} baud   设置波特率
 * @return {*}
 */
void MY_UART0_Init(uint32_t baud)
{
    Serial.begin(baud);
    Serial.println("0初始化完成\r\n");
}

/**
 * @description:    UART2初始化
 * @param {uint32_t} baud   设置波特率
 * @return {*}
 */
void MY_UART2_Init(uint32_t baud)
{
    Serial2.begin(baud, SERIAL_8N1, 18, 17);
    Serial2.println("2初始化完成\r\n");
}

/**
 * @description:    UART0 接收字符串函数
 * @param {char} *rec_buf   接收字符串
 * @param {size_t}  size 接收大小
 * @return {*}
 */
void MY_UART0_Receive_Buf(char *rec_buf, size_t size)
{
    Serial.readBytes(rec_buf, size);
    rec_buf[size] = '\0';
}
/**
 * @description: UART2 接收字符串函数
 * @param {char} *rec_buf   接收字符串
 * @param {size_t}  size 接收大小
 * @return {*}
 */
void MY_UART2_Receive_Buf(char *rec_buf, size_t size)
{
    Serial2.readBytes(rec_buf, size);
    rec_buf[size] = '\0';
}