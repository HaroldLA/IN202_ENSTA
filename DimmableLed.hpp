#ifndef dimmableLedHPP
#define dimmableLedHPP

#include"Led.hpp"
#include"UART.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
// Cette classe hérite de la classe Led et autorise de contrôler la tension que nous   //
// délivrons à la classe diode. Plus la tension est élevée, plus l'intensité lumineuse //
// de la diode est importante.                                                         //
/////////////////////////////////////////////////////////////////////////////////////////

class DimmableLed: public Led
{
private:
    int m_Intensity;      //Paramètre d'intensité lumineuse de la LED
    bool m_IsBlinking;    //Bit du contrôle du mode de clignotement
    bool m_IsOn;          //Bit qui indique si la LED est allumé
    
public:

//Constructeurs
    DimmableLed(uint32_t thePortNumber, const char* theName, bool debug = false):
    DimmableLed(thePortNumber, false, theName, debug, false, 0){}
    
    DimmableLed(uint32_t thePortNumber, bool switchOn, const char* theName, bool debug = false, bool Blinking = false, int Intensity = 255):
    Led(thePortNumber, switchOn, theName, debug), m_IsBlinking(Blinking), m_Intensity(Intensity), m_IsOn(false){}

//Accesseurs
    int Get_Intensity() const { return m_Intensity; }
    bool GetIsBlinking() const { return m_IsBlinking; }


//Actions 

protected:

    /* Cette fonction met la led à une intensité spécifique 
       Si elle est éteint, la diode reste éteint sinon elle 
       prend la valeur de m_Intensity. */
    void DriveLed()
    {
      if(m_IsOn){
        analogWrite(GetPortNumber(), m_Intensity);
      }else{
        analogWrite(GetPortNumber(), 0);
      }
    }

public:

   /* Cette fonction diminue l'intensité lumineuse de la led et retourne 
      true si l'opération est possible. Si la led est éteinte, alors la 
      fonction ne modifie pas l'intensité lumineuse et retourne false. */
   bool DecreaseLight(){ 
      if(m_Intensity > 0){
        m_Intensity-=15;
        if(IsDebug())
          Serial << " Intensity(-) "  << "\n";
        m_IsOn = true;
        DriveLed();
        return 1;
      }else{
        if(IsDebug())
          Serial << " Min. Intensity"  << "\n";
        return 0;
      }
    }

    /* Cette fonction augmente l'intensité lumineuse de la led et retourne 
       true si l'opération est possible. Si la led est déjà au maximun, alors 
       la fonction ne modifie pas l'intensité lumineuse et retourne false. */
    bool IncreaseLight(){
      if(m_Intensity < 255){
        m_Intensity+=15;
        if(IsDebug())
          Serial << " Intensity(+) "  << "\n";
        m_IsOn = true;
        DriveLed();
        return 1;
      }else{
        if(IsDebug())
          Serial << " Max. Intensity"  << "\n";
        return 0;
      }
    }

    // Cette fonction met la diode à l'intensité maximale.
    void SwitchOn(){
      m_Intensity = 255;
      DriveLed(); 
    }

    // Cette fonction éteint la diode en mettant son intensité à 0.
    void SwitchOff(){ 
      m_Intensity = 0;
      DriveLed(); 
    } 

    /* Cette fontion est appellée afin de pouvoir soit allumer, soit 
       éteindre la diode quand le mode de clignotement est actif. */
    void Tick(){
      if(m_IsBlinking){
        m_IsOn = !m_IsOn;
        DriveLed();     
      }
    }

    // Cette fonction active et désactive le clignotement.
    void Blink(){
      m_IsBlinking = !m_IsBlinking;
    }
};
#endif
