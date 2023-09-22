/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-09-17 10:44:07
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-09-17 12:02:59
 * @FilePath: \ESP32_UART\lib\UART\my_uart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MY_UART_H_
#define _MY_UART_H_

#include "Arduino.h"


void MY_UART0_Init(uint32_t baud);
void MY_UART2_Init(uint32_t baud);
void MY_UART0_Receive_Buf(char* rec_buf, size_t size);
void MY_UART2_Receive_Buf(char* rec_buf, size_t size);

#endif // ! _MY_UART_H_