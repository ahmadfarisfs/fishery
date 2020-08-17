#include "Arduino.h"
#include "BTN7960.h"

void BTN7960::init(uint8_t pinPwmA, uint8_t pinPwmB, bool invertDir = false)
{
    m_invert = invertDir;
    m_pinA = pinPwmA;
    m_pinB = pinPwmB;
    pinMode(m_pinB, OUTPUT);
    pinMode(m_pinA, OUTPUT);
}

int8_t BTN7960::setSpeed(int8_t speed)
{
    uint8_t pinA = m_pinA;
    uint8_t pinB = m_pinB;
    if (m_invert)
    {
        pinB = m_pinA;
        pinA = m_pinB;
    }
    if (speed > 100)
    {
        speed = 100;
    }
    if (speed < -100)
    {
        speed = -100;
    }

    if (speed == 0)
    {
        //stop
        analogWrite(m_pinA, 0);
        analogWrite(m_pinB, 0);
    }
    else if (speed > 0)
    {
        //map speed (0,100) to pwm (0,255)
        analogWrite(pinA, map(speed, 0, 100, 0, 255));
        analogWrite(pinB, 0);
    }
    else
    {
        //lower than 0, backwards
        analogWrite(pinA, 0);
        analogWrite(pinB, map(speed, 0, 100, 0, 255));
    }
    m_currentSpeed = speed;
    return m_currentSpeed;
}

int8_t BTN7960::setDeltaSpeed(int8_t deltaSpeed)
{
    return setSpeed(m_currentSpeed + deltaSpeed);
}

void BTN7960::stop()
{
    setSpeed(0);
}

int8_t BTN7960::getSpeed()
{
    return m_currentSpeed;
}