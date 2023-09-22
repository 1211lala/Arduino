https://github.com/espressif/arduino-esp32/tree/master/libraries/Ticker
https://blog.csdn.net/Naisu_kun/article/details/86764221?ops_request_misc=&request_id=c0d9811977ea43189836efcd0c6fea29&biz_id=&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~koosearch~default-26-86764221-null-null.268^v1^control&utm_term=esp32&spm=1018.2226.3001.4450


unsigned long micros(); //返回微秒为单位系统时间
unsigned long millis(); //返回毫秒为单位系统时间

void delay(uint32_t); //设置毫秒级延时
void delayMicroseconds(uint32_t us); //设置微秒级延时
