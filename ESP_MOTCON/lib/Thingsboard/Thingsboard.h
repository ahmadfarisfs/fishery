#ifndef THINGSBOARD_H
#define THINGSBOARD_H
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Thingsboard{
    public:
    void init(ESP8266WiFiClass *wifiDevice, String key, uint8_t csPin);
    bool postData(int8_t motorSpeed, char button);
    bool saveToSD(int8_t motorSpeed, char button); 
    private:
    String m_key;
    ESP8266WiFiClass *m_wifi;
    HTTPClient m_client;
    File m_file;
};

#endif