#ifndef buttonHPP
#define buttonHPP

#include"Component.hpp"



template<int portNumber>
class Button: public Component
{
private:
    static Button<portNumber>* mButton;
    static bool m_Pressed;
    static uint32_t m_StartPress;
    
    static void Pressed() 
    { 
      noInterrupts();
      if(!m_Pressed)
      {
        uint32_t currentTime = millis();
        if(currentTime - m_StartPress > 50)
        {
          m_Pressed = true;
          attachInterrupt(portNumber, Released, RISING);
          mButton->OnButtonPressed(currentTime);
          m_StartPress = currentTime; 
        }
      }
      interrupts();
    }
    static void Released() 
    { 
      noInterrupts();
      uint32_t currentTime = millis();
      if(m_Pressed)
      {
        m_Pressed = false;
       // Serial << currentTime - m_StartPress << "\n"; //Commande pour afficher le temps entre pressed et released
        if(currentTime - m_StartPress > 50)
          mButton->OnButtonReleased(currentTime);
          attachInterrupt(portNumber, Pressed, FALLING);
      }
      m_StartPress = currentTime;
      interrupts();
    }

    uint32_t m_LastPressTime = 0;

public:
    Button(const char* theButtonName, bool debug = false):
      Component(theButtonName, debug)
    {
      pinMode(portNumber, INPUT);
      mButton = this;
      m_Pressed = false;
    }

    void StartMonitorEvents()
    {
        attachInterrupt(portNumber, Pressed, LOW);
    }

    bool IsPressed() { return digitalRead(portNumber) == LOW; }

    virtual void OnButtonPressed(uint32_t theStartTime)
    {      
      m_LastPressTime = theStartTime;
      //if(IsDebug())
          //Serial << name() << ": Button is pressed (" << theStartTime << ").\n";
    }
    virtual void OnButtonReleased(uint32_t theEndTime)
    {
      //if(IsDebug())
        //Serial << name() << ": Button is released(" << theEndTime << ").\n";
      if(theEndTime - m_LastPressTime > 1500)
        OnVeryLongButtonClick();
      else if(theEndTime - m_LastPressTime > 700)
        OnLongButtonClick();
      else
        OnShortButtonClick();
    }

    virtual void OnShortButtonClick()
    {
      if(IsDebug())
        Serial << name() << ": Short Click\n";
    }
    virtual void OnLongButtonClick()
    {
      if(IsDebug())
        Serial << name() << ": Long Click\n";
    }
    virtual void OnVeryLongButtonClick()
    {
      if(IsDebug())
        Serial << name() << ": Very Long Click\n";
    }
};

template<int portNumber>
Button<portNumber>* Button<portNumber>::mButton = NULL;

template<int portNumber>
bool Button<portNumber>::m_Pressed = false;
template<int portNumber>
uint32_t Button<portNumber>::m_StartPress = 0;

#endif
