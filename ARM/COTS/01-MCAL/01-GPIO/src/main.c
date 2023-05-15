//#include "Std_Types.h"

#include "RCC_Driv.h"
#include "GPIO.h"


void main(void)
{
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);
	GPIO_tsrt_PortConfig_t LED_Pin;

//	LED_Pin.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
//	LED_Pin.GPIO_Port = GPIO_enuPort_A;
//	LED_Pin.GPIO_Pin = GPIO_enuPin_0;
//	LED_Pin.GPIO_Speed = GPIO_OUTPUT_SPEED_HIGH;
////
//	GPIO_enuInit(&LED_Pin);
	//GPIO_SetPinValue(GPIO_enuPort_A,GPIO_enuPin_0,GPIO_enuPin_HIGH);
//	GPIO_enuSetPortValue(GPIO_enuPort_A,GPIO_enuPin_HIGH);
//	GPIO_enuSetAlternateFunctionHigh(GPIO_enuPort_A,GPIO_enuPin_1,GPIO_enu_AF_HIGH_1);
//	GPIO_enuSetAlternateFunctionLow(GPIO_enuPort_A,GPIO_enuPin_1,GPIO_enu_AF_HIGH_1);
	GPIO_enuSetMultiplePins(GPIO_enuPort_A,GPIO_enuPin_0|GPIO_enuPin_1|GPIO_enuPin_2,GPIO_enuPin_HIGH);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}

