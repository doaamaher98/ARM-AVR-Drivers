
#include "RCC_Driv.h"
#include "GPIO.h"
#include "NVIC.h"

#include "USART_Interface.h"

#include "LED.h"

u8 TX[3] ="HIH";
u8 RX[3];

void TX_Finished(void)
{
	LED_enuSetLEDValue(LED_enuLED_Warning,LED_enuLED_ON);
}

void RX_Finished (void)
{

	LED_enuLEDToggle(LED_enuLED_Warning,LED_enuLED_ON);

	USART_enuSendAsynchZeroCpy(USART_enuUSART1, RX, 3, TX_Finished);
}

// USART CONFIGURATIONS
USART_tstrConfig_t USART_Cfg [NUMBER_OF_USART_CHANNELS] =
{
		[USART_enuUSART1] =
		{
				.USART_Enable 			= USART_enuEN,
				.USART_DataBits 		= USART_enu_8_DataBits,
				.USART_ParityType		= USART_enuOddParity,
				.USART_OverSampling     = USART_enuOverSampling_DIV_16,
				.USART_StopBits			= USART_enuStopBits_1,
				.USART_ParityControl    = USART_enuPARITY_EN,
				.USART_BaudRate			= 9600,
				.USART_Pins				=
				{
						.USART_TX =
						{
								.GPIO_Port = GPIO_enuPort_A,
								.GPIO_Pin  = GPIO_enuPin_9,
								.GPIO_Mode = GPIO_MODE_AF_PP_PU,
								.GPIO_Speed= GPIO_OUTPUT_SPEED_VERY_HIGH,
						},

						.USART_RX =
						{
								.GPIO_Port = GPIO_enuPort_A,
								.GPIO_Pin  = GPIO_enuPin_10,
								.GPIO_Mode = GPIO_MODE_AF_PP_PU,
								.GPIO_Speed= GPIO_OUTPUT_SPEED_VERY_HIGH,
						}
				}
		},
};


void main (void)
{
	RCC_enuSelectSysClk(RCC_enu_HSI);

	/* Enable GPIOA,B */
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOB);
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOC);

	/* Enable USART1 */
	RCC_enuEnablePeripheralClk(RCC_enuAPB2,RCC_enuAPB2_USART1);

	/* A0,A1 */

	USART_enuInit(USART_Cfg);

	LED_enuLEDInit();

//	Sched_enuInit();
//	Sched_enuStart();

	USART_enuSendAsynchZeroCpy(USART_enuUSART1,TX,3,TX_Finished);

	while (1)
	{
		USART_enuReceiveAsynchZeroCpy(USART_enuUSART1,RX,3,RX_Finished);
	}
}
