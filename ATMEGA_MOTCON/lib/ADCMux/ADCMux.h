#ifndef ADCMUX_H
#define ADCMUX_H
#include "Arduino.h"

//ADCMux onlright now configured for maximum 5 button, can be extended if desired
class ADCMux{
    
    public:
    void init(uint8_t ADCpin,void (*callback)(char), uint16_t debounceTimeMs=100);
    //Maximum 5 button, id = 0 - 4 
    bool setThreshold(uint8_t id,char btnLabel, uint16_t minValue, uint16_t maxValue);
    void pollState();
    char getActiveLabel();

    private:
    uint8_t m_pin;
    uint16_t m_minValue[5];
    uint16_t m_maxValue[5];  
    char m_buttonLabel[5];  
    bool m_buttonState[5];  
    bool m_buttonPrevState[5];  
    unsigned long m_lastChangeTime[5];
    void (*m_onButtonPressedCallback)(char);
     uint16_t m_debounceTimeMs;
};

#endif