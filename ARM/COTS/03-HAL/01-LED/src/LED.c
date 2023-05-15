#include "GPIO.h"

#include "LED.h"
/*********************** APIs Implementations ********************/
LED_tenuErrorStatus LED_enuLEDInit (void)
{
	LED_tenuErrorStatus LocalErrorStatus = LED_enuOK;

	GPIO_tsrt_PortConfig_t GPIO_Cfg;

	u8 LocalIterator;

	for (LocalIterator=0; LocalIterator < LED_enuLED_Count ; LocalIterator++)
	{
		GPIO_Cfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP_PU;
		GPIO_Cfg.GPIO_Pin = LED_tstrConfig[LocalIterator].LED_Pin;
		GPIO_Cfg.GPIO_Port = LED_tstrConfig[LocalIterator].LED_Port;
		GPIO_Cfg.GPIO_Speed = LED_tstrConfig[LocalIterator].LED_Speed;

		GPIO_enuInit(&GPIO_Cfg);
	}
	return LocalErrorStatus;
}
/**********************************************************************************/
LED_tenuErrorStatus LED_enuSetLEDValue (u8 Led, LED_tenuActiveStatus Cpy_u8LEDVal)
{
	LED_tenuErrorStatus LocalErrorStatus = LED_enuOK;

	GPIO_enuSetPinValue_(LED_tstrConfig[Led].LED_Port, LED_tstrConfig[Led].LED_Pin, Cpy_u8LEDVal ^ LED_tstrConfig[Led].LED_State);

	return LocalErrorStatus;
}
/**********************************************************************************/
