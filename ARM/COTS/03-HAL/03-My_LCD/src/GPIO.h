#ifndef GPIO_H_
#define	GPIO_H_

/********************************* Includes ************************************/
#include "Std_Types.h"

/********************************** Defines **************************************/
#define					GPIO_CLR_MODE_MASK				0x00000003

#define					GPIO_CLR_PUPD_MASK				0x00000003

#define					GPIO_SET_CLR_MASK				0x0000FFFF
#define					GPIO_RESET_CLR_MASK				0xFFFF0000
/* =============================== MODER ======================================= */
// INPUT
#define						GPIO_MODE_INPUT_FLOATING			0b000000
#define						GPIO_MODE_INPUT_PU					0b000001
#define						GPIO_MODE_INPUT_PD					0b000010

// OUTPUT [NO SPEED INCLUDED]
#define						GPIO_MODE_OUTPUT_PP					0b001000
#define						GPIO_MODE_OUTPUT_PP_PU				0b001001
#define						GPIO_MODE_OUTPUT_PP_PD				0b001010
//#define						GPIO_MODE_OUTPUT_RES				0b001011
#define						GPIO_MODE_OUTPUT_OD					0b001100
#define						GPIO_MODE_OUTPUT_OD_PU				0b001101
#define						GPIO_MODE_OUTPUT_OD_PD				0b001111

// Alternate Function
#define						GPIO_MODE_AF_PP						0b010000
#define                     GPIO_MODE_AF_PP_PU					0b010001
#define                     GPIO_MODE_AF_PP_PD					0b010010
//#define                     GPIO_MODE_AF_RES0					0b010011
#define                     GPIO_MODE_AF_OD						0b010100
#define                     GPIO_MODE_AF_OD_PU					0b010101
#define                     GPIO_MODE_AF_OD_PD					0b010110
//#define                     GPIO_MODE_AF_RES1					0b010111

// Analog
#define                     GPIO_MODE_ANALOG_IO					0b011000
//#define                     GPIO_MODE_ANALOG_R0					0b011001
//#define                     GPIO_MODE_ANALOG_R1					0b011010

/* =============================== OTYPR ======================================= */


/* =============================== OSPEEDR ======================================= */
#define							GPIO_OUTPUT_SPEED_LOW					0b000
#define							GPIO_OUTPUT_SPEED_MEDIUM				0b001
#define							GPIO_OUTPUT_SPEED_HIGH					0b010
#define							GPIO_OUTPUT_SPEED_VERY_HIGH				0b011

#define							GPIO_NUM_OF_SPEED_MODES					4

/* =============================== PUPDR ======================================= */


/* =============================== BSRR ======================================= */


/******************************** User Defined Types ******************************/
// Error Status
typedef enum {
	GPIO_enuOK = 0,
	GPIO_enuNOK,
	GPIO_enuInvalidPort,
	GPIO_enuInvalidPin,
	GPIO_enuInvalidOutput_State,
	GPIO_enuInvalidInput_State,
	GPIO_enuInvalidAlternative_Function,
	GPIO_enuInvalidValueOption,
	GPIO_enuInvalidSpeedOption,
	GPIO_enuInvalidMode,
	GPIO_enuInvalidOutputType,
	GPIO_enuInvalidPUPD,

} GPIO_tenuErrorStatus;

// GPIO Pins
typedef enum {
	GPIO_enuPin_0 = (u16) (0x0001),
	GPIO_enuPin_1 = (u16) (0x0002),
	GPIO_enuPin_2 = (u16) (0x0004),
	GPIO_enuPin_3 = (u16) (0x0008),
	GPIO_enuPin_4 = (u16) (0x0010),
	GPIO_enuPin_5 = (u16) (0x0020),
	GPIO_enuPin_6 = (u16) (0x0040),
	GPIO_enuPin_7 = (u16) (0x0080),
	GPIO_enuPin_8 = (u16) (0x0100),
	GPIO_enuPin_9 = (u16) (0x0200),
	GPIO_enuPin_10 = (u16) (0x0400),
	GPIO_enuPin_11 = (u16) (0x0800),
	GPIO_enuPin_12 = (u16) (0x1000),
	GPIO_enuPin_13 = (u16) (0x2000),
	GPIO_enuPin_14 = (u16) (0x4000),
	GPIO_enuPin_15 = (u16) (0x8000),
	GPIO_enuNumberOfPins = 16
} GPIO_tenu_Pins;

// Pin Status
typedef enum {
	GPIO_enuPin_LOW = 0, GPIO_enuPin_HIGH,
} GPIO_tenu_PinStatus;


// GPIO Ports
typedef enum {
	GPIO_enuPort_A = 0,
	GPIO_enuPort_B,
	GPIO_enuPort_C,
	GPIO_enuPort_D,
	GPIO_enuPort_E,
	GPIO_enuPort_H,
	GPIO_enuNumberOfPorts
} GPIO_tenu_Ports;

// Alternative Function [LOW]
typedef enum
{
	GPIO_enu_AF_LOW_0=0b0000,
	GPIO_enu_AF_LOW_1,
	GPIO_enu_AF_LOW_2,
	GPIO_enu_AF_LOW_3,
	GPIO_enu_AF_LOW_4,
	GPIO_enu_AF_LOW_5,
	GPIO_enu_AF_LOW_6,
	GPIO_enu_AF_LOW_7,
	GPIO_enu_AF_LOW_8,
	GPIO_enu_AF_LOW_9,
	GPIO_enu_AF_LOW_10,
	GPIO_enu_AF_LOW_11,
	GPIO_enu_AF_LOW_12,
	GPIO_enu_AF_LOW_13,
	GPIO_enu_AF_LOW_14,
	GPIO_enu_AF_LOW_15,
	GPIO_enu_NumberOfAF=16
}GPIO_tenuAlternativeFunctionLow;


// Alternative Function [HIGH]
typedef enum
{
	GPIO_enu_AF_HIGH_0=0b0000,
	GPIO_enu_AF_HIGH_1,
	GPIO_enu_AF_HIGH_2,
	GPIO_enu_AF_HIGH_3,
	GPIO_enu_AF_HIGH_4,
	GPIO_enu_AF_HIGH_5,
	GPIO_enu_AF_HIGH_6,
	GPIO_enu_AF_HIGH_7,
	GPIO_enu_AF_HIGH_8,
	GPIO_enu_AF_HIGH_9,
	GPIO_enu_AF_HIGH_10,
	GPIO_enu_AF_HIGH_11,
	GPIO_enu_AF_HIGH_12,
	GPIO_enu_AF_HIGH_13,
	GPIO_enu_AF_HIGH_14,
	GPIO_enu_AF_HIGH_15
//	GPIO_enu_NumberOfAF
}GPIO_tenuAlternativeFunctionHigh;
// GPIO Registers to be accessed with Base Addresses
typedef struct {
	volatile u32 GPIO_MODER;
	volatile u32 GPIO_OTYPER;
	volatile u32 GPIO_OSPEEDR;
	volatile u32 GPIO_PUPDR;
	volatile u32 GPIO_IDR;
	volatile u32 GPIO_ODR;
	volatile u32 GPIO_BSRR;
	volatile u32 GPIO_LCKR;
	volatile u32 GPIO_AFRL;
	volatile u32 GPIO_AFRH;
} GPIO_tstr_Registers_t;

/* ================================================================================ */
// Struct
typedef struct {
	GPIO_tenu_Ports GPIO_Port;
	GPIO_tenu_Pins GPIO_Pin;
	u32 GPIO_Mode;
	u32 GPIO_Speed;

} GPIO_tsrt_PortConfig_t;

/************************************* APIs ****************************************/
GPIO_tenuErrorStatus GPIO_enuInit(GPIO_tsrt_PortConfig_t *Cpy_LocalPort_Config);

GPIO_tenuErrorStatus GPIO_enuSetPinValue_(GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenu_PinStatus Cpy_u8Value);

GPIO_tenuErrorStatus GPIO_enuGetPinValue(GPIO_tenu_Ports Cpy_u8Port,GPIO_tenu_Pins Cpy_u8Pin, u8 *Cpy_Addu8Value) ;

GPIO_tenuErrorStatus GPIO_enuSetPortValue(GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_PinStatus Cpy_u8Value);

// Alternate Function
GPIO_tenuErrorStatus GPIO_enuSetAlternateFunctionLow(GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenuAlternativeFunctionLow Cpy_u8AF);
GPIO_tenuErrorStatus GPIO_enuSetAlternateFunctionHigh(GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenuAlternativeFunctionHigh Cpy_u8AF);

// Set Multiple Pins
GPIO_tenuErrorStatus GPIO_enuSetMultiplePins (GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenu_PinStatus Cpy_u8Value);

#endif   /* GPIO_H_ */
