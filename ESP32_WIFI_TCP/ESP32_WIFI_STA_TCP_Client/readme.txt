wl_status_t begin(const char* ssid, const char *passphrase = NULL, int32_t channel = 0, const uint8_t* bssid = NULL, bool connect = true)
该方法用来接入网络；

bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000)
设置网络地址；

bool disconnect(bool wifioff = false, bool eraseap = false)
断开网络连接，若wifioff为true则还将还原网络设置，若eraseap为true则将清除保存于flash中的网络参数；

bool isConnected()
返回是否已接入网络；

bool setAutoReconnect(bool autoReconnect)
设置断网自动重连接；

bool getAutoReconnect()
返回是否自动重连接；

IPAddress localIP()
返回模块地址；

IPAddress subnetMask()
返回子网掩码；

IPAddress gatewayIP()
返回网关地址；

IPAddress dnsIP(uint8_t dns_no = 0)
返回DNS地址；

uint8_t * macAddress(uint8_t* mac)
String macAddress()
返回MAC地址；

const char * getHostname()
返回主机名字；

bool setHostname(const char * hostname)
设置主机名字；

wl_status_t status()
返回联网状态，状态如下：

255：WL_NO_SHIELD不用在意（兼容WiFi Shield而设计）
0：WL_IDLE_STATUS正在WiFi工作模式间切换；
1：WL_NO_SSID_AVAIL无法访问设置的SSID网络；
2：WL_SCAN_COMPLETED扫描完成；
3：WL_CONNECTED连接成功；
4：WL_CONNECT_FAILED连接失败；
5：WL_CONNECTION_LOST丢失连接；
6：WL_DISCONNECTED断开连接；


int32_t channel()
返回当前信道；

void persistent(bool persistent)
设置是否将WiFi模式、SSID、密码、自动重连等信息存储于flash中，默认为true；

bool mode(wifi_mode_t)
设置WiFi工作模式，参数可选WIFI_OFF WIFI_STA WIFI_AP WIFI_AP_STA；

wifi_mode_t getMode()
返回WiFi工作模式；

bool enableSTA(bool enable)
使能/失能STA模式；

bool enableAP(bool enable)
使能/失能AP模式；

bool setSleep(bool enable)
使能/失能休眠（仅STA模式，默认开启休眠；如果对实时响应要求较高的话需要关闭休眠）；

bool getSleep()
返回是否开启休眠；

bool setTxPower(wifi_power_t power)
设置WiFi发射功率，默认为WIFI_POWER_19_5dBm（最大值）；

wifi_power_t getTxPower()
返回WiFi发射功率；








int connect(IPAddress ip, uint16_t port)
int connect(IPAddress ip, uint16_t port, int32_t timeout)
int connect(const char *host, uint16_t port)
int connect(const char *host, uint16_t port, int32_t timeout)
用于和服务器建立连接，可以连接指定IP地址或是指定域名，连接成功返回1，失败返回0；

size_t write(uint8_t data)
size_t write(const uint8_t *buf, size_t size)
size_t write_P(PGM_P buf, size_t size)
size_t write(Stream &stream)
发送数据，发送成功返回发送字节数，失败返回0；
除了用write()方法外也可以用print()等方法发送数据；

int available()
返回可读取数据长度，如果没有数据可读取则返回0；

int read()
int read(uint8_t *buf, size_t size)
从接收缓存读取数据并返回读取到的数据字节数，如果返回-1则表示读取失败，读取过的数据会从接收缓存删除；

int peek()
读取首字节数据，但并不从接收缓存中删除它；

void flush()
清空当前接收缓存；

void stop()
关闭客户端，释放资源；

uint8_t connected()
返回当前客户端是否与服务器建立连接；

IPAddress remoteIP() const
IPAddress remoteIP(int fd) const
返回服务器IP地址；

uint16_t remotePort() const
uint16_t remotePort(int fd) const
返回服务器端口号；

IPAddress localIP() const
IPAddress localIP(int fd) const
返回本地IP地址；

uint16_t localPort() const
uint16_t localPort(int fd) const
返回本地端口号；

版权声明：本文为CSDN博主「Naisu Xu」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Naisu_kun/article/details/87125845