#include <Arduino.h>
#include "ADCMux.h"
#include "ESPComm.h"
#include "BTN7960.h"

//#define BREADBOARD

const int builtinLed = 13;

//static allocation to prevent mem leak
ADCMux buttonPoller;
ESPComm commChannel;
BTN7960 motorControl;



void buttonPressedCallback(char buttonLabel){
  if (buttonLabel != ' ')
  {
    switch (buttonLabel)
    {
    case 'A':
      motorControl.setDeltaSpeed(10);
      break;
    case 'B':
      motorControl.setDeltaSpeed(-10);
      break;
    case 'C':
      motorControl.stop();
      break;
    case 'D':
      motorControl.setSpeed(100);
      break;
    }
    commChannel.sendDeviceState(buttonLabel,motorControl.getSpeed());
  }
}

void setup()
{
  //serial for debug and comm
  Serial.begin(9600);

  //setup comm channel to esp, use DI
  commChannel.init(&Serial, 500);

  //setup button mux poller
  buttonPoller.init(A0,buttonPressedCallback);
  buttonPoller.setThreshold(0, 'A', 190, 200);
  buttonPoller.setThreshold(1, 'B', 390, 395);
  buttonPoller.setThreshold(2, 'C', 585, 593);
  buttonPoller.setThreshold(3, 'D', 795, 800);
  
  //setup motor controller
  motorControl.init(5, 6);
}

void loop()
{
  //poll button and get state
  buttonPoller.pollState();
}