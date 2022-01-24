#ifndef ledHPP
#define ledHPP

#include"Component.hpp"

class Led: public Component
{
private:
    bool m_SwitchedOn;
    uint32_t m_PortNumber;
public:

//Constructeurs
    Led(uint32_t thePortNumber, const char* theName, bool debug = false):
        Led(thePortNumber, false, theName, debug) {}

    Led(uint32_t thePortNumber, bool switchOn, const char* theName, bool debug = false):
        m_PortNumber(thePortNumber), m_SwitchedOn(switchOn), Component(theName, debug)
    {
        pinMode(m_PortNumber, OUTPUT);
        if(m_SwitchedOn)
            digitalWrite(m_PortNumber, HIGH);
    }

//Accesseurs
    uint32_t GetPortNumber() const { return m_PortNumber; }
    bool IsSwitchedOn() const { return m_SwitchedOn; }

//Actions
    
    void SwitchOn() 
    { 
        if(!m_SwitchedOn)
        {
            m_SwitchedOn = true;
            digitalWrite(m_PortNumber, HIGH);
            if(IsDebug())
              Serial << name() << ": switched on\n";
        }
    }
    void SwitchOff() 
    { 
        if(m_SwitchedOn)
        {
            m_SwitchedOn = false;
            digitalWrite(m_PortNumber, LOW);
            if(IsDebug())
              Serial << name() << ": switched off\n";
        }
    }
};

#endif
