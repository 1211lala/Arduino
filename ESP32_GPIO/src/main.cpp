#include <Arduino.h>

uint8_t Get_key_status(void);

#define   LED   2       /* 板载LED在IO2 */
#define   KEY   0

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);
}

void loop()
{
  // uint8_t key_status = Get_key_status();
  // if(key_status == 1)
  // {
  //   static uint8_t flag = 0;
  //   if(flag == 0)
  //   {
  //     flag = 1;
  //     digitalWrite(LED, HIGH);
  //   }
  //   else 
  //   {
  //     flag = 0;
  //     digitalWrite(LED, LOW);
  //   }
    

  // }


  digitalWrite(LED, HIGH);
  delay(10);
    digitalWrite(LED, LOW);
  delay(10);
}

uint8_t Get_key_status(void)
{
  static uint8_t flag = 0;
  if(digitalRead(KEY) == LOW && flag == 0) 
  {
    delay(20);
    flag = 1;
    return 1;
  }
  if(digitalRead(KEY) == HIGH && flag == 1)
  {
    flag = 0;
  }
  return 0;
}
