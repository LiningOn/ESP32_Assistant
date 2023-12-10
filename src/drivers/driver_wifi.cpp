#include "driver_wifi.h"

void init_wifi()
{
    Serial.println("---------- WIFI START INIT ----------");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nWiFi connected!");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    // 获取时间
    configTime(UTC_OFFSET_IN_SECONDS, 0, NTP_SERVER);

    while (!time(nullptr))
    {
        delay(1000);
        Serial.println("Waiting for time sync...");
    }
    Serial.println("Time synced successfully");
    Serial.println("---------- WIFI END INIT ----------");
}