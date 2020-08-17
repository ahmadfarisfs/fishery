#include "Arduino.h"
#include "ADCMux.h"

void ADCMux::init(uint8_t ADCpin, void (*callback)(char), uint16_t debounceTimeMs)
{
    m_pin = ADCpin;
    pinMode(m_pin, INPUT);
    //make sure safe for comparison if not used
    for (uint8_t i = 0; i < 5; i++)
    {
        m_minValue[i] = 1024;
        m_maxValue[i] = 0;
    }
    m_debounceTimeMs = debounceTimeMs;
    m_onButtonPressedCallback = callback;
}

bool ADCMux::setThreshold(uint8_t id, char btnLabel, uint16_t minValue, uint16_t maxValue)
{
    if (id > 4)
    {
        return false;
    }
    m_buttonLabel[id] = btnLabel;
    m_minValue[id] = minValue;
    m_maxValue[id] = maxValue;
    return true;
}

char ADCMux::getActiveLabel()
{
    uint16_t adcVal = (uint16_t)analogRead(m_pin);
    for (uint8_t i = 0; i < 5; i++)
    {
        //if detected adc value is inside predefined value, then button is pressed
        if (adcVal > m_minValue[i] && adcVal < m_maxValue[i])
        {
            return m_buttonState[i];
        }
    }
    return ' ';
}

void ADCMux::pollState()
{
    uint16_t adcVal = (uint16_t)analogRead(m_pin);
    for (uint8_t i = 0; i < 5; i++)
    {
        m_buttonState[i] = false;
        //if detected adc value is inside predefined value, then button is pressed
        if (adcVal > m_minValue[i] && adcVal < m_maxValue[i])
        {
            m_buttonState[i] = true;
        }

        //button changed state
        if (m_buttonState[i] != m_buttonPrevState[i])
        {
            //pushed and outside debounce time
            if (m_buttonState[i] == true && (millis() - m_lastChangeTime[i]) > m_debounceTimeMs)
            {
                m_onButtonPressedCallback(m_buttonLabel[i]);
            }

            m_lastChangeTime[i] = millis();
        }

        m_buttonPrevState[i] = m_buttonState[i];
    }
}