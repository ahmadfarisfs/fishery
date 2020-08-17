#include "Arduino.h"
#include "ESPRecv.h"
#include <stdlib.h>
void ESPRecv::init(Stream *serialDevice, uint16_t timeoutMs)
{
    m_timeoutMs = timeoutMs;
    m_serial = serialDevice;
    m_serial->setTimeout(200);
}

bool ESPRecv::parsePayload(char *button, int8_t *motorSpeed)
{   
    if (!m_frameReady){
        return false;
    }
Serial.println(m_bufferString);
    //dereference and put value 
    *button = m_bufferString[0];
String speedStr = m_bufferString.substring(1,m_bufferString.length());
//    m_bufferString.
/*
    char bufferSpeed[5] = {
        m_buffer[1],m_buffer[2],m_buffer[3],m_buffer[4]
    };*/
   int speed =  speedStr.toInt();
   *motorSpeed = (int8_t)speed;
    m_frameReady = false;
    return true;
}

bool ESPRecv::checkSerialCommand()
{
   m_bufferString =  m_serial->readStringUntil('\n');
if (m_bufferString == ""){
    return false;
}
m_frameReady=true;
return true;
  /*  if (m_serial->available() > 0)
    {
        char incomingByte = m_serial->read();
        m_buffer[m_bufferPos] = incomingByte;
        m_bufferPos++;
        if (incomingByte == '\n'){
            m_bufferPos = 0;
            m_frameReady = true;
            return true;
        }
    }*/

    return true;

    // say what you got:
    //Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
    //}
    // return false;
}
