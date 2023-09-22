#ifndef _MY_EEPROM_H_
#define _MY_EEPROM_H_

#include <Arduino.h>
#include <EEPROM.h>

void MY_EEPROM_Init(uint16_t size);
void MY_EEPROM_Write_Buf(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
void MY_EEPROM_Read_Buf(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);

#endif