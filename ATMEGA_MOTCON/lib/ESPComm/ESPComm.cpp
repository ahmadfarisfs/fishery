#include "Arduino.h"
#include "ESPComm.h"

void ESPComm::init(Stream *serialDevice, uint16_t timeoutMs)
{
    m_timeoutMs = timeoutMs;
    m_serial = serialDevice;
}

void ESPComm::sendDeviceState(char button, int8_t motorSpeed)
{
    //put to wire, motor speed as char
    char buffer[5];
    sprintf(buffer, "%c%d\n",  button,motorSpeed);
    m_serial->print(buffer);
}

bool ESPComm::waitSerialResponse()
{   
    //not implemented
    return true;
}

bool ESPComm::checkSerialResponse()
{
    //not implemented
    return true;
}