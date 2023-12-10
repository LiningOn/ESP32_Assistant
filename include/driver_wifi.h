#ifndef _DRIVER_WIFI_
#define _DRIVER_WIFI_

#include <includes.h>

/**
 * WIFI 配置参数
*/
#define WIFI_SSID "Xiaomi_974C"   // 需要连接到的WiFi名
#define WIFI_PASSWORD "17827657635" // 连接的WiFi密码
#define UTC_OFFSET_IN_SECONDS 28800 // Beijing: UTC +8  -- 获取东八区时间
#define NTP_SERVER "pool.ntp.org"

void init_wifi(void);

#endif