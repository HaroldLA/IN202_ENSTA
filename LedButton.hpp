#ifndef ledButtonHPP
#define ledButtonHPP

#include"Component.hpp"
#include"Led.hpp"
#include"DimmableLed.hpp"
#include"Button.hpp"



template<int portNumber>
class LedButton: public Button<portNumber>
{
private:
    DimmableLed& m_DimmableLed;               // Désigne la led à contrôler
    bool m_increasingOrDecreasing = false;    // Bit de contrôle de l'augmentation ou de la 
                                              // diminution de l'intensité luminuese de la led
                                              
public:

//Constructeur

    LedButton(DimmableLed& theDimmableLed): Button<portNumber>("LedButton", true),
      m_DimmableLed(theDimmableLed){
        pinMode(13,OUTPUT); //Declaration du pin 13 et de la LED_BUILTIN comme OUTPUT
      }

//Actions

    virtual void OnShortButtonClick(){
      if(m_DimmableLed.IsDebug()) 
        Serial  << " Intensity variation \n";
        
      if(!m_increasingOrDecreasing){ 
        m_DimmableLed.IncreaseLight();
      }
      else{
        m_DimmableLed.DecreaseLight();
      }
    }
    
    virtual void OnLongButtonClick(){
      if(m_DimmableLed.IsDebug())
        Serial  << " Increase/decrease variation \n";

      //Changement du bit de contrôle increase/decrease  
      m_increasingOrDecreasing = !(m_increasingOrDecreasing);

      //Signal d'indication du changement d'état par la LED_BUILTIN
      digitalWrite(13,m_increasingOrDecreasing);
    }
    virtual void OnVeryLongButtonClick(){
      if(m_DimmableLed.IsDebug())
        Serial << " Blinking mode change \n";

      //Changement d'état, mode de clignotement  
      m_DimmableLed.Blink();  
    }
};

#endif
