
#include "RCC_Driv.h"
#include "LED.h"
#include "GPIO.h"


void main(void)
{
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);

	LED_tstrConfig_t Led;

	LED_enuLEDInit();

	LED_enuSetLEDValue(LED_enuLED0,LED_enuActiveHigh);
	LED_enuSetLEDValue(LED_enuLED1,LED_enuActiveHigh);
	LED_enuSetLEDValue(LED_enuLED2,LED_enuActiveHigh);
	LED_enuSetLEDValue(LED_enuLED3,LED_enuActiveHigh);


  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}


// ----------------------------------------------------------------------------
