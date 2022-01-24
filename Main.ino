
#include"UART.hpp"
#include"DimmableLed.hpp"
#include"Button.hpp"
#include"LedButton.hpp"

DimmableLed Led_1(12, "TheLed", true);
LedButton<5> Button_2(Led_1);
//Button<6> Button_1("TheButton",true);

void setup() {


  /* Jalon 1 - Phase 3
   * La diode est allumée au maximum et son intensité 
   * diminue progressivement jusqu'à ce qu'elle soit 
   * éteinte, puis elle revient au maximum.  
   * 
  Led_1.SwitchOn();
  */
  
  Serial.begin(115200);             //On met la communication serial en 115220 bit/s
  Button_2.DebugOn();               //On met sur true la valeur de IsDebug() du Button_2  
  Button_2.StartMonitorEvents();    //On active les interruptions associés au Button_2
}

void loop() {

  Led_1.Tick();                     //On appelle la méthode Tick() pour apprécier le clignotement s'il est activé
  delay(1000);

/* Jalon 1 - Phase 3 
  Led_1.DecreaseLight();
  Serial << " Intensity: " << Led_1.Get_Intensity() <<" \n";
  delay(1000);
*/
  
}
