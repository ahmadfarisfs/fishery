#include <Arduino.h>
#include "ESPRecv.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SD.h>
#include <Thingsboard.h>
#include <SoftwareSerial.h>

//#define BREADBOARD

ESPRecv serialCmd;
Thingsboard tb;
int8_t motorSpeed;
char buttonPressed;
unsigned long lastWiFiCheckMS;

#ifndef BREADBOARD
SoftwareSerial mSerial(D1, D2, false); //rx = io5 (D1), tx = io4 (D2)
#endif

void setup()
{
  Serial.begin(9600);
  String tbKey = String("z5NvbcpglGAMB0bTaKer");

  #ifdef BREADBOARD
  //my breadboard use this to test
  serialCmd.init(&Serial, 500); 
  #else
  //real board use this config so uart wont collide
  mSerial.begin(9600);
  serialCmd.init(&mSerial, 500);
  #endif

  WiFi.begin("AFFS-Redmi", "ahmadfaris");
  tb.init(&WiFi,tbKey,4);
}


void loop()
{
  //command parser, get data from atmega
  if (serialCmd.checkSerialCommand())
  {
    if (serialCmd.parsePayload(&buttonPressed, &motorSpeed))
    {
      Serial.println(motorSpeed);
      Serial.println(buttonPressed);
      tb.saveToSD(motorSpeed,buttonPressed);
    }
  }

  //auto connect to wifi if available
  //check wifi every 5 seconds and do log and push to thingsboard
  if (millis() > lastWiFiCheckMS + 5000)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      tb.postData(motorSpeed,buttonPressed);
    }
    lastWiFiCheckMS = millis();
  }
}