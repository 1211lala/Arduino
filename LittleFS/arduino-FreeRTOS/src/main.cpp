#include <Arduino.h>
#include "soc/rtc_wdt.h"
#include "LittleFS.h"
#include "littlefs_api.h"

#define LED 2
#define KEY 0

TaskHandle_t task1_handle;
TaskHandle_t task2_handle;
TaskHandle_t task3_handle;

void task1_littlefs(void *pt);
void task2_key(void *pt);
void task3_uart(void *pt);
void start_task(void);

uint8_t get_key_value(uint8_t waittime);

char buf[20];
void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    pinMode(KEY, INPUT_PULLUP);

    littlefs_start_get_info(LittleFS);

    start_task();
    vTaskSuspend(NULL);
}

void loop()
{
}

void start_task(void)
{
    xTaskCreate(task1_littlefs, "task1_littlefs", 1024 * 5, NULL, 2, &task1_handle);
    xTaskCreate(task2_key, "task2_key", 1024 * 5, NULL, 3, &task2_handle);
    xTaskCreate(task3_uart, "task3_uart", 1024 * 5, NULL, 4, &task3_handle);
}

/* 使用了FS多给内存 */
void task1_littlefs(void *pt)
{
    char buf[50];
    /******************************************************/
    littlefs_writeFile(LittleFS, "/configs.txt", "192.168.8.33");
    littlefs_scanFile(LittleFS, "/");
    littlefs_readFile(LittleFS, "/data.txt", buf);
    Serial.printf("%s\r\n",buf);
    while (1)
    {
        vTaskDelay(2000);
    }
}

void task2_key(void *pt)
{
    char buf[500];
    uint8_t flag = 0;
    while (1)
    {
        if (get_key_value(30) == 1)
        {
            int num = littlefs_readFile(LittleFS, "/configs.txt", buf);
            if (num > 0)
            {
                buf[num] = '\0';
                Serial.printf("read data is %s\r\n", buf);
            }

            if (flag == 0)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        vTaskDelay(5);
    }
}

void task3_uart(void *pt)
{

    while (1)
    {
        // Serial.printf("ESP32 Freq =%dMhz\r\n", getCpuFrequencyMhz());
        // Serial.printf("ESP.getHeapSize() = %dK\r\n", ESP.getHeapSize() / 1024);
        // Serial.printf("ESP.getFreeHeap() = %dK\r\n", ESP.getFreeHeap() / 1024);
        // Serial.printf("ESP.getFlashChipSize() = %dK\r\n", ESP.getFlashChipSize() / 1024);
        // Serial.printf("ESP.getFlashChipSpeed() = %dMhz\r\n", ESP.getFlashChipSpeed() / 1000000);
        // Serial.printf("ESP.getFlashChipMode() = %d\r\n", ESP.getFlashChipMode());

        // Serial.printf("task1 min free = %d word\r\n", uxTaskGetStackHighWaterMark(task1_handle));
        // Serial.printf("task2 min free = %d word\r\n", uxTaskGetStackHighWaterMark(task2_handle));
        // Serial.printf("task3 min free = %d word\r\n\r\n", uxTaskGetStackHighWaterMark(task3_handle));
        vTaskDelay(5000);
    }
}

uint8_t get_key_value(uint8_t waittime)
{
    static uint64_t tick = 0;
    static uint8_t flag = 0;

    uint8_t key_status = 0;

    key_status = digitalRead(KEY);
    if (flag == 0 && key_status == 0)
    {
        tick = millis();
        flag = 1;
    }
    if (flag == 1 && ((millis() - tick) > waittime))
    {
        if (key_status == 0)
        {
            flag = 2;
            return 1;
        }
    }
    if (key_status == 1)
    {
        flag = 0;
    }
    return 0;
}
