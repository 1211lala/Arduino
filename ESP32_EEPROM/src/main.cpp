
#include <Arduino.h>
#include "my_eeprom.h"

#define SSD "realme_GT_Neo_5"
#define PASSWORD "12111211"

#define EEPROM_START_ADDRESS 1


void setup()
{
  uint8_t reveive[30];
  uint16_t ssd_ardess;
  uint16_t password_ardess;

  Serial.begin(115200);
  Serial.println();

  MY_EEPROM_Init(4095);

  // /* 写入 SSD*/
  ssd_ardess = EEPROM_START_ADDRESS; /* 确定 SSD的地址 */
  // MY_EEPROM_Write_Buf(ssd_ardess, (uint8_t *)SSD, sizeof(SSD));

  // /* 写入 PASSWORD */
  password_ardess = EEPROM_START_ADDRESS + sizeof(SSD); /* 确定 PASSWORD的地址 */
  // MY_EEPROM_Write_Buf(password_ardess, (uint8_t *)PASSWORD, sizeof(PASSWORD));

  /* 读出 SSD */
  MY_EEPROM_Read_Buf(ssd_ardess, reveive, sizeof(SSD));
  Serial.printf("读取%d字节:%s\r\n", strlen((char *)reveive), (char *)reveive);

  /* 读出 PASSWORD */
  MY_EEPROM_Read_Buf(password_ardess, reveive, sizeof(PASSWORD));
  Serial.printf("读取%d字节:%s\r\n", strlen((char *)reveive), (char *)reveive);

}

void loop()
{
}
