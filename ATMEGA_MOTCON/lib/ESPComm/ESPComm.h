#ifndef ESPCOMM_H
#define ESPCOMM_H
#include "Arduino.h"

class ESPComm{
    public:
    void init(Stream *serialDevice,uint16_t timeoutMs);
    //this function is not wait for response
    void sendDeviceState(char button, int8_t motorSpeed);
    //block until reponse arrived, false if response malformed or timeout reached
    bool waitSerialResponse();

    //only check for incoming response, not blocking
    bool checkSerialResponse();

    //blocking until device state 
//    bool waitDeviceState()
    private:
    Stream *m_serial;
    uint16_t m_timeoutMs;
};

#endif