#ifndef ESPRECV_H
#define ESPRECV_H
#include "Arduino.h"

class ESPRecv{
    public:
    void init(Stream *serialDevice,uint16_t timeoutMs);
    
    //block until reponse arrived, false if response malformed or timeout reached
    bool waitSerialCommand();

    //only check for incoming response, not blocking
    bool checkSerialCommand();

    bool parsePayload(char *button, int8_t *motorSpeed);

    private:
    Stream *m_serial;
    String m_bufferString;
    char m_buffer[6];
    uint16_t m_bufferPos;
    uint16_t m_timeoutMs;
    bool m_frameReady;
};

#endif