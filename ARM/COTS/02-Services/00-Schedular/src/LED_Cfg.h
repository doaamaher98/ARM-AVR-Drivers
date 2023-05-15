#ifndef 	LED_CFG_H
#define		LED_CFG_H



// LED Ports
//typedef enum
//{
//	LED_enuPORTA=0,
//	LED_enuPORTB,
//	LED_enuPORTC,
//	LED_enuPORTD,
//	LED_enuNumberOfPorts
//}LED_tenuLEDPorts;

// LED Pins
//typedef enum
//{
//	LED_enuPin0=0 ,
//	LED_enuPin1 ,
//	LED_enuPin2 ,
//	LED_enuPin3 ,
//	LED_enuPin4 ,
//	LED_enuPin5 ,
//	LED_enuPin6 ,
//	LED_enuPin7 ,
//	LED_enuPin8 ,
//	LED_enuPin9 ,
//	LED_enuPin10 ,
//	LED_enuPin11 ,
//	LED_enuPin12 ,
//	LED_enuPin13 ,
//	LED_enuPin14 ,
//	LED_enuPin15 ,
//	LED_enuNumberOfPins
//}LED_tenuLEDPins;


// LED Active Status
typedef enum
{
	LED_enuActiveHigh=0,
	LED_enuActiveLow,
	LED_enuNumberOfActiveStatus
}LED_tenuActiveStatus;

// LED Name
typedef enum
{
	LED_enuLED_Warning=0,
	LED_enuLED_Alarm,
	LED_enuLED_Start,
	LED_enuLED_Stop,
	LED_enuLED_Waiting,
	LED_enuLED_Ready,
	LED_enuLED_NumberOfNames
}LED_tenuLEDName;

// LED Color
typedef enum
{
	LED_enuLED_Red=0,
	LED_enuLED_Green,
	LED_enuLED_Blue,
	LED_enuLED_Yellow,
	LED_enuLED_White,
	Led_enuLED_NumberOfColors
}LED_tenuLEDColor;

// LED Config.
typedef enum
{
	LED_enuLED_OFF=0,
	LED_enuLED_ON
}LED_tenuState;


// LED Count
typedef enum
{
	LED_enuLED0=0,
	LED_enuLED1,
//	LED_enuLED2,
//	LED_enuLED3,
	//LED_enuLED5,
	//LED_enuLED6,
	//LED_enuLED7,
	//LED_enuLED8,
	//LED_enuLED9,
	//LED_enuLED10,
	//LED_enuLED11,
	//LED_enuLED12,
	//LED_enuLED13,
	//LED_enuLED14,
	//LED_enuLED15,
	LED_enuLED_Count
}LED_tenuLEDCount;



#endif
