bool softAP(const char* ssid, const char* passphrase = NULL, int channel = 1, int ssid_hidden = 0, int max_connection = 4)
该方法用来启动AP，在成功启动后返回true，各项参数如下：
ssid所建立AP网络的名称，至少需一个字节，最大一般不超过32字节;
passphrase所建立AP网络的密码，可以为NULL（无密码）或不小于8字节且不大于63字节的密码;
channelWiFi网络信道，可选值1~13;
ssid_hidden是否对外隐藏SSID，0-不隐藏，1-隐藏;
max_connection最大可接入数，可选值1~4;


bool softAPConfig(IPAddress local_ip, IPAddress gateway, IPAddress subnet)
设置本地地址、网关地址和子网掩码，默认分别为192.168.4.1 192.168.4.1 255.255.255.0;


bool softAPdisconnect(bool wifioff = false)
关闭当前AP，若wifioff为true则还将还原网络设置;


uint8_t softAPgetStationNum()
返回连接到AP的客户端数量;


IPAddress softAPIP()
返回当前模块IP


const char * softAPgetHostname()
返回主机名字


bool softAPsetHostname(const char * hostname)
设置主机名字


String softAPmacAddress(void)
返回mac地址