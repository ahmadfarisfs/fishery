#include "Arduino.h"
#include "Thingsboard.h"
#include <stdlib.h>
#include <SD.h>
#include <ESP8266HTTPClient.h>
void Thingsboard::init(ESP8266WiFiClass *wifiDevice,  String key, uint8_t csPin)
{
    m_wifi = wifiDevice;
  //  m_client = httpClient;
    m_key = key;
    if (!SD.begin(csPin))
    {
        Serial.println("initialization failed!");
        return;
    }
}

bool Thingsboard::postData(int8_t motorSpeed, char button)
{
    char motorSpeedChr[5];
    itoa(motorSpeed, motorSpeedChr, 10);
    String url = "http://34.101.89.17:8080/api/v1/" + m_key + "/telemetry";
    m_client.begin(url);
    //Serial.println(url);
    m_client.addHeader("Content-Type", "application/json");
    String payload = "{\"button\":  \"" + String(button) + "\", \"speed\": "+ String(motorSpeedChr) + " }";
    int httpResponseCode = m_client.POST(payload);
    Serial.println(payload);
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200)
    {
        return true;
    }
    return false;
}

bool Thingsboard::saveToSD(int8_t motorSpeed, char button)
{
    //if frame is complete and valid, log to sd card
    char motorSpeedChr[5];
    itoa(motorSpeed, motorSpeedChr, 10);
    m_file = SD.open("log.csv", FILE_WRITE);
    if (m_file)
    {
        m_file.println(String(button) + "," + String(motorSpeedChr));
        m_file.close();
        return true;
    }
    else
    {
        return false;
    }
}