#ifndef 	LED_CFG_H
#define		LED_CFG_H


// LED Ports
typedef enum
{
	LED_enuPORTA     =  0 ,
	LED_enuPORTB     =  1 ,
	LED_enuPORTC     =  2 ,
	LED_enuPORTD     =  3 ,
	LED_enuPORTE	 =  4 ,
	LED_enuPORTH     =  5 ,
	LED_enuNumberOfPorts
}LED_tenuLEDPorts;

// LED Pins
typedef enum
{
	LED_enuPin0    = (0x00000001) ,
	LED_enuPin1    = (0x00000002) ,
	LED_enuPin2    = (0x00000004) ,
	LED_enuPin3    = (0x00000008) ,
	LED_enuPin4    = (0x00000010) ,
	LED_enuPin5    = (0x00000020) ,
	LED_enuPin6    = (0x00000040) ,
	LED_enuPin7    = (0x00000080) ,
	LED_enuPin8    = (0x00000100) ,
	LED_enuPin9    = (0x00000200) ,
	LED_enuPin10   = (0x00000400) ,
	LED_enuPin11   = (0x00000800) ,
	LED_enuPin12   = (0x00001000) ,
	LED_enuPin13   = (0x00002000) ,
	LED_enuPin14   = (0x00004000) ,
	LED_enuPin15   = (0x00008000) ,
	LED_enuNumberOfPins
}LED_tenuLEDPins;


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
//	LED_enuLED1,
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
