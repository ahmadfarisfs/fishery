#ifndef BTN7960_H
#define BTN7960_H
#include "Arduino.h"

class BTN7960{
    public:
    void init(uint8_t pinPwmA, uint8_t pinPwmB, bool invertDir = false);
    int8_t setSpeed(int8_t speed);
    int8_t setDeltaSpeed(int8_t deltaSpeed);
    void stop();
    int8_t getSpeed();
    private:
    uint8_t m_pinA,m_pinB;
    int8_t m_currentSpeed;
    bool m_invert;
};

#endif