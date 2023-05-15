/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 20 FEB 2023                             */
/* Version   : V.01                                    */
/* Target    : STM32								   */
/* Descrip.   : Header file for Interfaces & APIS      */
/*******************************************************/
#ifndef _RCC_H
#define _RCC_H

#include "Std_Types.h"
/**************************** Defines ********************************/
/*********************************************************************/
#define 		RCC_SYSCLK_ClearMask							0xFFFFFFFC

#define			RCC_HSI_MASK						0x00000001
#define			RCC_HSI_CLR_MASK					0xFFFFFFFE

#define			RCC_LSE_MASK						0x00200000
#define			RCC_LSE_CLRMASK						0xFFDFFFFF

#define			RCC_HSE_MASK						0x00010000
#define			RCC_HSE_CLR_MASK					0xFFFEFFFF

#define 		RCC_PLL_MASK						0x01000000
#define 		RCC_PLL_CLR_MASK					0xFEFFFFFF

//////////////////////////////////////// SWS : System Clk Switch Status /////////////////////////////////////
#define				RCC_SWS_HSI							0x00000000
#define				RCC_SWS_HSI_CLR						0xFFFFFFFF

#define				RCC_SWS_HSE							0x00000004
#define				RCC_SWS_HSE_CLR						0xFFFFFFFB

#define				RCC_SWS_PLL							0x00000008
#define				RCC_SWS_PLL_CLR						0xFFFFFFF7

#define				RCC_SWS_MASK						0x0000000C

//////////////////////////////////////// SW : System Clock Switch /////////////////////////////////////////
#define				RCC_SW_HSI							0x00000000
#define				RCC_SW_HSI_CLR						0xFFFFFFFF

#define				RCC_SW_HSE							0x00000001
#define				RCC_SW_HSE_CLR						0xFFFFFFFE

#define				RCC_SW_PLL							0x00000002
#define				RCC_SW_PLL_CLR						0xFFFFFFFD

#define				RCC_SW								0x00000003
#define				RCC_SW_MASK							0xFFFFFFFC
/*******************************************************************************************/
//////////////////// PLL I2S  ///////////////////////
#define 		RCC_PLLI2S_RDY_MASK			0x00000000
#define 		RCC_PLLI2S_NOTRDY_MASK		0x01000000

#define 		RCC_PLLI2S_OFF_MASK			0x00000000
#define 		RCC_PLLI2S_ON_MASK			0x04000000

//////////////////// PLL  ///////////////////////
#define			RCC_PLL_RDY				0x02000000
#define			RCC_PLL_RDY_MASK		0xFDFFFFFF

#define			RCC_PLL_NOTRDY			0x00000000

#define			RCC_PLL_OFF_MASK			0x00000000
#define			RCC_PLL_ON_MASK				0x01000000

////////////////// CSS ///////////////////////////
#define 		RCC_CSS_OFF_MASK			0x00000000
#define			RCC_CSS_ON_MASK				0x00080000

///////////////// HSE READY //////////////////////
#define 		RCC_HSE_RDY					0x00020000
#define			RCC_HSE_RDY_MASK			0xFFFDFFFF

#define			RCC_HSE_NOTRDY			0x00000000

//////////////// HSE ON /////////////////////////
#define			RCC_HSE_ON_MASK				0x00010000
#define			RCC_HSE_OFF_MASK			0x00000000

///////////////// HSI READY //////////////////////
#define			RCC_HSI_RDY				0x00000002
#define			RCC_HSI_RDY_MASK		0xFFFFFFFD

#define			RCC_HSI_NOTRDY			0x00000000

//////////////// HSI ON //////////////////////////
#define			RCC_HSI_ON_MASK				0x00000001
#define			RCC_HSI_OFF_MASK			0x00000000

/////////////// HSI CFGR ON ////////////////////////
#define			RCC_HSI_CFGR_SET			0x00000003

/**************************************** RCC_PLLCFGR ***************************************************/
/********************************************************************************************************/
////////////////////// PLL Source ////////////////////////
#define			RCC_PLL_SRC_HSI_MASK					0x00000000
#define			RCC_PLL_SRC_HSE_MASK					0x00400000

///////////////////// PLL Division factor for Main System Clock /////////////////
#define 		RCC_PLLP2_MASK							0x00020000
#define			RCC_PLLP4_MASK							0x00040000
#define			RCC_PLLP6_MASK							0x00060000
#define			RCC_PLLP8_MASK							0x00080000

/**************************************** RCC_CLKCFG ****************************************************/
/********************************************************************************************************/
////////////////////////////// SELECT SYSTEM CLOCK [MCO2] //////////////////////////
/*
#define			RCC_MCO2_SYSCLK_MASK					0x00000000
#define			RCC_MCO2_PLLI2S_MASK					0x40000000
#define			RCC_MCO2_HSE_MASK						0x80000000
#define			RCC_MCO2_PLL_MASK						0xC0000000

///////////////////////////// MCO2 Prescaler ////////////////////////////
#define			RCC_MCO2_Prescaler2						0x20000000
#define			RCC_MCO2_Prescaler3						0x28000000
#define			RCC_MCO2_Prescaler4						0x30000000
#define			RCC_MCO2_Prescaler5						0x38000000

/////////////////////////// MCO1 Prescaler ////////////////////////////
#define			RCC_MCO1_Prescaler2						0x04000000
#define			RCC_MCO1_Prescaler3						0x05000000
#define			RCC_MCO1_Prescaler4						0x06000000
#define			RCC_MCO1_Prescaler5						0x07000000

/////////////////////////// I2S SROURCE /////////////////////////////
#define			RCC_I2S_SRC_PLLI2SMASK					0x00000000
#define			RCC_I2S_SRC_EXTCLK_MASK					0x00800000

///////////////////////////// MCO1 Clock Output 1 /////////////////////
#define			RCC_MC01_OutputCLK_HSIMASK				0x00000000
#define			RCC_MC01_OutputCLK_LSEMASK				0x00200000
#define			RCC_MC01_OutputCLK_HSEMASK				0x00400000
#define 		RCC_MC01_OutputCLK_PLLMASK				0x00600000

///////////////////////// RTC PRESCALER (HSE Division Factor for RTC Clk //////////////
#define				RCC_RTC_HSE_PrescalerMASK			0x001f0000

///////////////////////////// APB2 Prescaler ////////////////////////
#define				RCC_APB2_PrescalerNotDividedMASK		0x00000000
#define				RCC_APB2_Prescaler2_MASK				0x00008000
#define				RCC_APB2_Prescaler4_MASK				0x0000A000
#define				RCC_APB2_Prescaler8_MASK				0x0000C000
#define				RCC_APB2_Prescaler16_MASK				0x0000E000

///////////////////////// APB1 Prescaler ///////////////////////////
#define				RCC_APB1_PrescalerNotDividedMASK		0x00000000
#define				RCC_APB1_Prescaler2_MASK				0x00001000
#define				RCC_APB1_Prescaler4_MASK				0x00001400
#define				RCC_APB1_Prescaler8_MASK				0x00001800
#define				RCC_APB1_Prescaler16_MASK				0x00001C00

//////////////////////// AHB Prescaler ////////////////////////
#define 			RCC_AHB_PrescalerNotDividedMASK		0x00000000

#define				RCC_AHB_Prescaler2_MASK				0x00000080
#define				RCC_AHB_Prescaler4_MASK             0x00000090
#define				RCC_AHB_Prescaler8_MASK             0x000000A0
#define				RCC_AHB_Prescaler16_MASK            0x000000B0
#define				RCC_AHB_Prescaler64_MASK            0x000000C0
#define				RCC_AHB_Prescaler128_MASK           0x000000D0
#define				RCC_AHB_Prescaler256_MASK           0x000000E0
#define				RCC_AHB_Prescaler512_MASK           0x000000F0
*/
/**********************************************************************************************/
/*
 #define SW_MSK				0x00000003			// NOT APPLICAPLE
 #define GET_SWS_MSK			0x0000000C			// NOT APPLICAPLE
 */
#define		RCC_enuPLLPrescaler_N_CLR_Mask			0xFFFF803F
#define		RCC_enuPLLClkSrc_CLR_Mask				0xFFBFFFFF

/************************************** User Defined Types **********************************/
/************************************* Error Status Options ******************************/
typedef enum {
	RCC_enuOK = 0,
	RCC_enuNOK,
	RCC_enuNullPointer,
	RCC_enuTIMEOUT,

	RCC_enuInvalidClockSource,
	RCC_enuHSI_OFF,
	RCC_enuHSE_OFF,
	RCC_enuPLL_OFF,

	RCC_enuHSE_Enabled,
	RCC_enuHSI_Enabled,
	RCC_enuPLL_Enabled,
	RCC_enuPLLI2S_Enabled,

	RCC_enuHSE_Disabled,
	RCC_enuHSI_Disabled,
	RCC_enuPLL_Disabled,
	RCC_enuPLLI2S_Disabled,

	RCC_enuInvalidHSE_ClockSource,

	RCC_enuHSE_READY,
	RCC_enuHSE_NOTRDY,
	RCC_enuHSI_READY,
	RCC_enuHSI_NOTRDY,
	RCC_enuPLL_READY,
	RCC_enuPLL_NOTRDY,

	RCC_enuHSEInvalidStatus,
	RCC_enuHSIInvalidStatus,
	RCC_enuPLLInvalidStatus,

	RCC_enuInvalidPLL_M_DivFactor,
	RCC_enuInvalidPLL_P_DivFactor,
	RCC_enuInvalidPLL_Q_DivFactor,
	RCC_enuInvalidPLL_N_MulFactor,

	RCC_enuPLLI2S_READY,
	RCC_enuPLLI2S_NOTRDY,
	RCC_enuPLLI2SInvalidStatus,

	RCC_enuInvalidControlBus,

	RCC_enuInvalidPLLClkSrc,
	RCC_enuInvalidPLL_Q_Prescaler,
	RCC_enuInvalidPLL_P_Prescaler,

	RCC_enuPeripheralClk_Enabled,
	RCC_enuPeripheralClk_Disabled,

	RCC_enuInvalidAHB_Prescaler,
	RCC_enuInvalidAPB1_Prescaler,
	RCC_enuInvalidAPB2_Prescaler,

	RCC_enuInvalidAHB1_Peripheral,
	RCC_enuInvalidAHB2_Peripheral,
	RCC_enuInvalidAPB1_Peripheral,
	RCC_enuInvalidAPB2_Peripheral
} RCC_tenuErrorStatus;

/**************** System Clock Valid Sources ******************/
// Clock Types
typedef enum {
	RCC_enu_HSI = 0, RCC_enu_HSE, RCC_enu_PLL, RCC_enu_NumerOfClkSources
} RCC_tenuSysClkSource;

// System Bus types
typedef enum {
	RCC_enuAHB1 = 0,
	RCC_enuAHB2,
	RCC_enuAPB1,
	RCC_enuAPB2,
	RCC_enuNumberOfSystemBuses
} RCC_tenuSystemBus;

// Clk ready
typedef enum {
	RCC_enuClock_RDY = 0, RCC_enuClock_NOTRDY
} RCC_tenuClockReady;

// Clk Status
typedef enum {
	RCC_enuClock_ON = 0, RCC_enuClock_OFF
} RCC_tenuClockStatus;

/////////////////////////// PRESCALER DIVIDED MASKS [AHB,APB1,APB2] /////////////////////////
// PLL Clock Source
typedef enum {
	RCC_enuPLL_HSI = 0, RCC_enuPLL_HSE, RCC_enuPLLNumberOfClockSrc
} RCC_tenuPLLClkSource;

// PLL Prescaler : P Division Factors
typedef enum {
	RCC_enuPLL_P_DivBy2 = 0,
	RCC_enuPLL_P_DivBy4 ,
	RCC_enuPLL_P_DivBy6 ,
	RCC_enuPLL_P_DivBy8
} RCC_tenuPLL_P_Prescaler;

// PLL Prescaler : Q Division Factors
typedef enum {
	RCC_enuPLL_Q_DivBy2 = 2,
	RCC_enuPLL_Q_DivBy3,
	RCC_enuPLL_Q_DivBy4,
	RCC_enuPLL_Q_DivBy5,
	RCC_enuPLL_Q_DivBy6,
	RCC_enuPLL_Q_DivBy7,
	RCC_enuPLL_Q_DivBy8,
	RCC_enuPLL_Q_DivBy9,
	RCC_enuPLL_Q_DivBy10,
	RCC_enuPLL_Q_DivBy11,
	RCC_enuPLL_Q_DivBy12,
	RCC_enuPLL_Q_DivBy13,
	RCC_enuPLL_Q_DivBy14,
	RCC_enuPLL_Q_DivBy15,
	RCC_enuPLL_QNumberOfDivFactors
} RCC_tenuPLL_Q_Prescaler;

// AHB Prescalers
typedef enum {
	RCC_enuAHB_Prescaler_2 = 0,
	RCC_enuAHB_Prescaler_4,
	RCC_enuAHB_Prescaler_8,
	RCC_enuAHB_Prescaler_16,
	RCC_enuAHB_Prescaler_64,
	RCC_enuAHB_Prescaler_128,
	RCC_enuAHB_Prescaler_256,
	RCC_enuAHB_Prescaler_512,
	RCC_enuAHB_NumberOfPrescalers
} RCC_tenuAHB_Prescalers;

// APB1 Prescalers
typedef enum {
	RCC_enuAPB1_Prescaler_NotDivided = 0,
	RCC_enuAPB1_Prescaler_2,
	RCC_enuAPB1_Prescaler_4,
	RCC_enuAPB1_Prescaler_8,
	RCC_enuAPB1_Prescaler_16,
	RCC_enuAPB1_NumberOfPrescalers
} RCC_tenuAPB1_Prescalers;

// APB2 Prescalers
typedef enum {
	RCC_enuAPB2_Prescaler_NotDivided = 0,
	RCC_enuAPB2_Prescaler_2,
	RCC_enuAPB2_Prescaler_4,
	RCC_enuAPB2_Prescaler_8,
	RCC_enuAPB2_Prescaler_16,
	RCC_enuAPB2_NumberOfPrescalers
} RCC_tenuAPB2_Prescalers;

// AHB Prescalers MASKS
typedef enum {
	RCC_enuAHB_Prescaler2_MASK = 0x00000080,
	RCC_enuAHB_Prescaler2_MASK_CLR = 0xFFFFF7F,

	RCC_enuAHB_Prescaler4_MASK = 0x00000090,
	RCC_enuAHB_Prescaler4_MASK_CLR = 0xFFFFFF6F,

	RCC_enuAHB_Prescaler8_MASK = 0x000000A0,
	RCC_enuAHB_Prescaler8_MASK_CLR = 0xFFFFFF5A,

	RCC_enuAHB_Prescaler16_MASK = 0x000000B0,
	RCC_enuAHB_Prescaler16_MASK_CLR = 0xFFFFFF4F,

	RCC_enuAHB_Prescaler64_MASK = 0x000000C0,
	RCC_enuAHB_Prescaler64_MASK_CLR = 0xFFFFFF3F,

	RCC_enuAHB_Prescaler128_MASK = 0x000000D0,
	RCC_enuAHB_Prescaler128_MASK_CLR = 0xFFFFFF2F,

	RCC_enuAHB_Prescaler256_MASK = 0x000000E0,
	RCC_enuAHB_Prescaler256_MASK_CLR = 0xFFFFFF1F,

	RCC_enuAHB_Prescaler512_MASK = 0x000000F0,
	RCC_enuAHB_Prescaler512_MASK_CLR = 0xFFFFFF0F

} RCC_tenuAHB_PrescalersMasks;

// APB1 Prescalers MASKS
typedef enum {
	RCC_enuAPB1_Prescaler_NotDivided_MASK = 0x00000000,
	RCC_enuAPB1_Prescaler_NotDivided_MASK_CLR = 0xFFFFFFFF,

	RCC_enuAPB1_Prescaler2_MASK = 0x00001000,
	RCC_enuAPB1_Prescaler2_MASK_CLR = 0xFFFFEFFF,

	RCC_enuAPB1_Prescaler4_MASK = 0x00001400,
	RCC_enuAPB1_Prescaler4_MASK_CLR = 0xFFFFEBFF,

	RCC_enuAPB1_Prescaler8_MASK = 0x00001800,
	RCC_enuAPB1_Prescaler8_MASK_CLR = 0xFFFFE7FF,

	RCC_enuAPB1_Prescaler16_MASK = 0x00001C00,
	RCC_enuAPB1_Prescaler16_MASK_CLR = 0xFFFFE3FF
} RCC_tenuAPB1_PrescalersMasks;

// APB2 Prescalers
typedef enum {
	RCC_enuAPB2_Prescaler_NotDivided_MASK = 0x00000000,
	RCC_enuAPB2_Prescaler_NotDivided_MASK_CLR = 0xFFFFFFFF,

	RCC_enuAPB2_Prescaler2_MASK = 0x00008000,
	RCC_enuAPB2_Prescaler2_MASK_CLR = 0xFFFF7FFF,

	RCC_enuAPB2_Prescaler4_MASK = 0x0000A000,
	RCC_enuAPB2_Prescaler4_MASK_CLR = 0xFFFF5FFF,

	RCC_enuAPB2_Prescaler8_MASK = 0x0000C000,
	RCC_enuAPB2_Prescaler8_MASK_CLR = 0xFFFF3FFF,

	RCC_enuAPB2_Prescaler16_MASK = 0x0000E000,
	RCC_enuAPB2_Prescaler16_MASK_CLR = 0xFFFF1FFF
} RCC_tenuAPB2_PrescalersMasks;

/////////////////////////// PLL Q DIVISON FACTOR //////////////////////
// PLL Prescaler : Q Division Factors
typedef enum {
	RCC_enuPLLPrescaler_Q_WrongConfig1 = 0x00000000,
	RCC_enuPLLPrescaler_Q_WrongConfig2 = 0x01000000,
	RCC_enuPLLPrescaler_Q_DivBy2 = 0x02000000,
	RCC_enuPLLPrescaler_Q_DivBy3 = 0x03000000,
	RCC_enuPLLPrescaler_Q_DivBy4 = 0x04000000,
	RCC_enuPLLPrescaler_Q_DivBy5 = 0x05000000,
	RCC_enuPLLPrescaler_Q_DivBy6 = 0x06000000,
	RCC_enuPLLPrescaler_Q_DivBy7 = 0x07000000,
	RCC_enuPLLPrescaler_Q_DivBy8 = 0x08000000,
	RCC_enuPLLPrescaler_Q_DivBy9 = 0x09000000,
	RCC_enuPLLPrescaler_Q_DivBy10 = 0x0A000000,
	RCC_enuPLLPrescaler_Q_DivBy11 = 0x0B000000,
	RCC_enuPLLPrescaler_Q_DivBy12 = 0x0C000000,
	RCC_enuPLLPrescaler_Q_DivBy13 = 0x0D000000,
	RCC_enuPLLPrescaler_Q_DivBy14 = 0x0E000000,
	RCC_enuPLLPrescaler_Q_DivBy15 = 0x0F000000,

	RCC_enuPLLPrescaler_Q_CLR_Mask= 0xF0FFFFFF

} RCC_tenuPLL_Q_PrescalersMask;

// Main PLL Division Factor (PLL_P)
// Only Written if PLL is disabled
typedef enum {
	RCC_enuPLLPrescaler_P_DivBy2 = 0x00000000,
	RCC_enuPLLPrescaler_P_DivBy4 = 0x00010000,
	RCC_enuPLLPrescaler_P_DivBy6 = 0x00020000,
	RCC_enuPLLPrescaler_P_DivBy8 = 0x00030000,

	RCC_enuPLLPrescaler_P_CLR_Mask=0xFFFCFFFF

} RCC_tenuPLL_P_PrescalersMask;

// PLL Division factor [M]
typedef enum {
	RCC_enuPLLPrescaler_M_WrongConfig1 = 0x00000000,
	RCC_enuPLLPrescaler_M_WrongConfig2, // 0x00000001
	RCC_enuPLLPrescaler_M_2,
	RCC_enuPLLPrescaler_M_3,
	RCC_enuPLLPrescaler_M_4,
	RCC_enuPLLPrescaler_M_5,
	RCC_enuPLLPrescaler_M_6,
	RCC_enuPLLPrescaler_M_7,
	RCC_enuPLLPrescaler_M_8,
	RCC_enuPLLPrescaler_M_9,
	RCC_enuPLLPrescaler_M_10,
	RCC_enuPLLPrescaler_M_11,
	RCC_enuPLLPrescaler_M_12,
	RCC_enuPLLPrescaler_M_13,
	RCC_enuPLLPrescaler_M_14,
	RCC_enuPLLPrescaler_M_15,
	RCC_enuPLLPrescaler_M_16,
	RCC_enuPLLPrescaler_M_17,
	RCC_enuPLLPrescaler_M_18,
	RCC_enuPLLPrescaler_M_19,
	RCC_enuPLLPrescaler_M_20,
	RCC_enuPLLPrescaler_M_21,
	RCC_enuPLLPrescaler_M_22,
	RCC_enuPLLPrescaler_M_23,
	RCC_enuPLLPrescaler_M_24,
	RCC_enuPLLPrescaler_M_25,
	RCC_enuPLLPrescaler_M_26,
	RCC_enuPLLPrescaler_M_27,
	RCC_enuPLLPrescaler_M_28,
	RCC_enuPLLPrescaler_M_29,
	RCC_enuPLLPrescaler_M_30,
	RCC_enuPLLPrescaler_M_31,
	RCC_enuPLLPrescaler_M_32,
	RCC_enuPLLPrescaler_M_33,
	RCC_enuPLLPrescaler_M_34,
	RCC_enuPLLPrescaler_M_35,
	RCC_enuPLLPrescaler_M_36,
	RCC_enuPLLPrescaler_M_37,
	RCC_enuPLLPrescaler_M_38,
	RCC_enuPLLPrescaler_M_39,
	RCC_enuPLLPrescaler_M_40,
	RCC_enuPLLPrescaler_M_41,
	RCC_enuPLLPrescaler_M_42,
	RCC_enuPLLPrescaler_M_43,
	RCC_enuPLLPrescaler_M_44,
	RCC_enuPLLPrescaler_M_45,
	RCC_enuPLLPrescaler_M_46,
	RCC_enuPLLPrescaler_M_47,
	RCC_enuPLLPrescaler_M_48,
	RCC_enuPLLPrescaler_M_49,
	RCC_enuPLLPrescaler_M_50,
	RCC_enuPLLPrescaler_M_51,
	RCC_enuPLLPrescaler_M_52,
	RCC_enuPLLPrescaler_M_53,
	RCC_enuPLLPrescaler_M_54,
	RCC_enuPLLPrescaler_M_55,
	RCC_enuPLLPrescaler_M_56,
	RCC_enuPLLPrescaler_M_57,
	RCC_enuPLLPrescaler_M_58,
	RCC_enuPLLPrescaler_M_59,
	RCC_enuPLLPrescaler_M_60,
	RCC_enuPLLPrescaler_M_61,
	RCC_enuPLLPrescaler_M_62,
	RCC_enuPLLPrescaler_M_63,

	RCC_enuPLLPrescaler_M_CLR_Mask=0xFFFFFFC0
} RCC_tenuPLL_M_PrescalersMask;


// ALL BUSES Peripherals
typedef enum {
	// AHB1
	RCC_enuAHB1_GPIOA = 0,
	RCC_enuAHB1_GPIOB,
	RCC_enuAHB1_GPIOC,
	RCC_enuAHB1_GPIOD,
	RCC_enuAHB1_GPIOE,
	RCC_enuAHB1_GPIOH=7,
	RCC_enuAHB1_CRCEN=12,
	RCC_enuAHB1_DMA1=21,
	RCC_enuAHB1_DMA2=22,

	// AHB2
	RCC_enuAHB2_OTGFS=7,

	// APB1
	RCC_enuAPB1_TIMER2=0,
	RCC_enuAPB1_TIMER3,
	RCC_enuAPB1_TIMER4,
	RCC_enuAPB1_TIMER5,
	RCC_enuAPB1_WWDG = 11,
	RCC_enuAPB1_SPI2= 14,
	RCC_enuAPB1_SPI3,
	RCC_enuAPB1_USART2 = 17,
	RCC_enuAPB1_I2C1= 21,
	RCC_enuAPB1_I2C2,
	RCC_enuAPB1_I2C3,
	RCC_enuAPB1_PWR= 28,

	// APB2
	RCC_enuAPB2_TIMER1=0,
	RCC_enuAPB2_USART1=4,
	RCC_enuAPB2_USART6,
	RCC_enuAPB2_ADC1=8,
	RCC_enuAPB2_SDIO=11,
	RCC_enuAPB2_SPI1,
	RCC_enuAPB2_SPI4,
	RCC_enuAPB2_SYSCFG,
	RCC_enuAPB2_TIMER9=16,
	RCC_enuAPB2_TIMER10,
	RCC_enuAPB2_TIMER11

} RCC_tenuBuses_Peripherals;

// All buses Peripheral ENABLE Registers
typedef enum {
	RCC_enuAHB1_DISALBE = 0x00000000,
	// AHB1
	RCC_enuAHB1_DMA2_EN = 0x00400000,
	RCC_enuAHB1_DMA2_EN_CLR = 0xFFBFFFFF,

	RCC_enuAHB1_DMA1_EN = 0x00200000,
	RCC_enuAHB1_DMA1_EN_CLR = 0xFFDFFFFF,

	RCC_enuAHB1_CRC_EN = 0x00001000,
	RCC_enuAHB1_CRC_EN_CLR = 0xFFFFEFFF,

	RCC_enuAHB1_GPIOH_EN = 0x00000080,
	RCC_enuAHB1_GPIOH_EN_CLR = 0xFFFFFF7F,

	RCC_enuAHB1_GPIOE_EN = 0x00000010,
	RCC_enuAHB1_GPIOE_EN_CLR = 0xFFFFFFEF,

	RCC_enuAHB1_GPIOD_EN = 0x00000008,
	RCC_enuAHB1_GPIOD_EN_CLR = 0xFFFFFFF7,

	RCC_enuAHB1_GPIOC_EN = 0x0000004,
	RCC_enuAHB1_GPIOC_EN_CLR = 0xFFFFFFFB,

	RCC_enuAHB1_GPIOB_EN = 0x00000002,
	RCC_enuAHB1_GPIOB_EN_CLR = 0xFFFFFFFD,

	RCC_enuAHB1_GPIOA_EN = 0x00000001,
	RCC_enuAHB1_GPIOA_EN_CLR = 0xFFFFFFFE,

	// AHB2
	RCC_enuAHB2_DISALBE = 0x00000000,

	RCC_enuAHB2_OTGFS_EN = 0x00000080,
	RCC_enuAHB2_OTGFS_EN_CLR = 0xFFFFFF7F,

	// APB1
	RCC_enuAPB1_DISALBE = 0x00000000,

	RCC_enuAPB1_PWR_EN = 0x10000000,
	RCC_enuAPB1_PWR_EN_CLR = 0xEFFFFFFF,

	RCC_enuAPB1_I2C3_EN = 0x00800000,
	RCC_enuAPB1_I2C3_EN_CLR = 0xFF7FFFFF,

	RCC_enuAPB1_I2C2_EN = 0x00400000,
	RCC_enuAPB1_I2C2_EN_CLR = 0xFFBFFFFF,

	RCC_enuAPB1_I2C1_EN = 0x00200000,
	RCC_enuAPB1_I2C1_EN_CLR = 0xFFDFFFFF,

	RCC_enuAPB1_USART2_EN = 0x00020000,
	RCC_enuAPB1_USART2_EN_CLR = 0xFFFDFFFF,

	RCC_enuAPB1_SPI3_EN = 0x00008000,
	RCC_enuAPB1_SPI3_EN_CLR = 0xFFFF7FFF,

	RCC_enuAPB1_SPI2_EN = 0x00004000,
	RCC_enuAPB1_SPI2_EN_CLR = 0xFFFFBFFF,

	RCC_enuAPB1_WWDG_EN = 0x00000800,
	RCC_enuAPB1_WWDG_EN_CLR = 0xFFFFF7FF,

	RCC_enuAPB1_TIMER5_EN = 0x00000008,
	RCC_enuAPB1_TIMER5_EN_CLR = 0xFFFFFFF7,

	RCC_enuAPB1_TIMER4_EN = 0x00000004,
	RCC_enuAPB1_TIMER4_EN_CLR = 0xFFFFFFFB,

	RCC_enuAPB1_TIMER3_EN = 0x00000002,
	RCC_enuAPB1_TIMER3_EN_CLR = 0xFFFFFFFD,

	RCC_enuAPB1_TIMER2_EN = 0x00000001,
	RCC_enuAPB1_TIMER2_EN_CLR = 0xFFFFFFFE,

	// APB2
	RCC_enuAPB2_DISALBE = 0x00000000,

	RCC_enuAPB2_TIMER11_EN = 0x00040000,
	RCC_enuAPB2_TIMER11_EN_CLR = 0xFFFBFFFF,

	RCC_enuAPB2_TIMER10_EN = 0x00020000,
	RCC_enuAPB2_TIMER10_EN_CLR = 0xFFFDFFFF,

	RCC_enuAPB2_TIMER9_EN = 0x00010000,
	RCC_enuAPB2_TIMER9_EN_CLR = 0xFFFEFFFF,

	RCC_enuAPB2_SYSCFG_EN = 0x00004000,
	RCC_enuAPB2_SYSCFG_EN_CLR = 0xFFFFBFFF,

	RCC_enuAPB2_SPI4_EN = 0x00002000,
	RCC_enuAPB2_SPI4_EN_CLR = 0xFFFFDFFF,

	RCC_enuAPB2_SPI1_EN = 0x00001000,
	RCC_enuAPB2_SPI1_EN_CLR = 0xFFFFEFFF,

	RCC_enuAPB2_SDIO_EN = 0x00000800,
	RCC_enuAPB2_SDIO_EN_CLR = 0xFFFFF7FF,

	RCC_enuAPB2_ADC1_EN = 0x00000100,
	RCC_enuAPB2_ADC1_EN_CLR = 0xFFFFFEFF,

	RCC_enuAPB2_USART6_EN = 0x00000020,
	RCC_enuAPB2_USART6_EN_CLR = 0xFFFFFFDF,

	RCC_enuAPB2_USART1_EN = 0x00000010,
	RCC_enuAPB2_USART1_EN_CLR = 0xFFFFFFEF,

	RCC_enuAPB2_TIMER1_EN = 0x00000001,
	RCC_enuAPB2_TIMER1_EN_CLR = 0xFFFFFFFE
} RCC_tenuBuses_Enable_Registers;

// All buses Peripheral DISABLE Registers
typedef enum {
	// AHB1
	RCC_enuAHB1_DMA2_DS = 0xFFBFFFFF,
	RCC_enuAHB1_DMA1_DS = 0xFFDFFFFF,
	RCC_enuAHB1_CRC_DS = 0xFFFFEFFF,
	RCC_enuAHB1_GPIOH_DS = 0xFFFFFF7F,
	RCC_enuAHB1_GPIOE_DS = 0xFFFFFFEF,
	RCC_enuAHB1_GPIOD_DS = 0xFFFFFFF7,
	RCC_enuAHB1_GPIOC_DS = 0xFFFFFFFB,
	RCC_enuAHB1_GPIOB_DS = 0xFFFFFFFD,
	RCC_enuAHB1_GPIOA_DS = 0xFFFFFFFE,

	// AHB2
	RCC_enuAHB2_OTGFS_DS = 0xFFFFFF7F,

	// APB1
	RCC_enuAPB1_PWR_DS = 0xEFFFFFFF,
	RCC_enuAPB1_I2C3_DS = 0xFF7FFFFF,
	RCC_enuAPB1_I2C2_DS = 0xFFBFFFFF,
	RCC_enuAPB1_I2C1_DS = 0xFFDFFFFF,
	RCC_enuAPB1_USART2_DS = 0xFFFDFFFF,
	RCC_enuAPB1_SPI3_DS = 0xFFFF7FFF,
	RCC_enuAPB1_SPI2_DS = 0xFFFFBFFF,
	RCC_enuAPB1_WWDG_DS = 0xFFFFF7FF,
	RCC_enuAPB1_TIMER5_DS = 0xFFFFFFF7,
	RCC_enuAPB1_TIMER4_DS = 0xFFFFFFFB,
	RCC_enuAPB1_TIMER3_DS = 0xFFFFFFFD,
	RCC_enuAPB1_TIMER2_DS = 0xFFFFFFFE,

	// APB2
	RCC_enuAPB2_TIMER11_DS = 0xFFFBFFFF,
	RCC_enuAPB2_TIMER10_DS = 0xFFFDFFFF,
	RCC_enuAPB2_TIMER9_DS = 0xFFFEFFFF,
	RCC_enuAPB2_SYSCFG_DS = 0xFFFFBFFF,
	RCC_enuAPB2_SPI4_DS = 0xFFFFDFFF,
	RCC_enuAPB2_SPI1_DS = 0xFFFFEFFF,
	RCC_enuAPB2_SDIO_DS = 0xFFFFF7FF,
	RCC_enuAPB2_ADC1_DS = 0xFFFFFEFF,
	RCC_enuAPB2_USART6_DS = 0xFFFFFFDF,
	RCC_enuAPB2_USART1_DS = 0xFFFFFFEF,
	RCC_enuAPB2_TIMER1_DS = 0xFFFFFFFE,
} RCC_tenuBuses_Disable_Registers;

/*
// Buses Enable Registers [LOW POWER]
typedef enum
{
	// AHB1 [LOW POWER]
		RCC_enuAHB1LPENR_DMA2LP_EN=,
		RCC_enuAHB1LPENR_DMA1LP_EN=,
		RCC_enuAHB1LPENR_SRAM1LP_EN=,
		RCC_enuAHB1LPENR_FLITFLPEN_EN=,
		RCC_enuAHB1LPENR_CRCLP_EN=,
		RCC_enuAHB1LPENR_GPIOHLP_EN=,
		RCC_enuAHB1LPENR_GPIOELP_EN=,
		RCC_enuAHB1LPENR_GPIODLP_EN=,
		RCC_enuAHB1LPENR_GPIOCLP_EN=,
		RCC_enuAHB1LPENR_GPIOBLP_EN=,
		RCC_enuAHB1LPENR_GPIOALP_EN=,

		// AHB2 [LOW POWER]
		RCC_enuAHB2_OTGFSLP_EN=,


		// APB1 [LOW POWER]
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_I2C3LP_EN=,
		RCC_enuAPB1_I2C2LP_EN=,
		RCC_enuAPB1__EN=,
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_PWRLP_EN=,
		RCC_enuAPB1_PWRLP_EN=,
}RCC_tenuBuses_Enable_Register_LP;

// Buses Reset Peripherals
typedef enum
{
	// APB2 Peripheral RESET
		RCC_enuAPB2_TIMER11RST=,
		RCC_enuAPB2_TIMER10RST=,
		RCC_enuAPB2_TIMER9RST=,
		RCC_enuAPB2_TIMER11RST=,
		RCC_enuAPB2_SYSCFGRST=,
		RCC_enuAPB2_SPI4RST=,
		RCC_enuAPB2_SPI1RST=,
		RCC_enuAPB2_SDIORST=,
		RCC_enuAPB2_ADC1RST=,
		RCC_enuAPB2_USART6RST=,
		RCC_enuAPB2_USART1RST=,
		RCC_enuAPB2_TIMER1RST=,
}RCC_tenuBuses_Reset_Registers;
*/

/********************************* REGISTERS ********************************/
typedef struct {
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 RCC_Reserved1;
	u16 RCC_Reserved2;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 RCC_Reserved3;
	u16 RCC_Reserved4;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 RCC_Reserved5;
	u16 RCC_Reserved6;
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 RCC_Reserved7;
	u16 RCC_Reserved8;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 RCC_Reserved9;
	u16 RCC_Reserved10;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 RCC_Reserved11;
	u16 RCC_Reserved12;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 RCC_Reserved13;
	u16 RCC_Reserved14;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 RCC_Reserved15;
	u32 RCC_DCKCFGR;
} RCC_tstrRegisters_t;

// PLL CONFIGURATION STRUCT
// CONFIGURE PLL BEFORE ENABLING IT!
typedef struct {
	RCC_tenuPLLClkSource RCC_enuPLLClkSrc;
	u32 RCC_u32PLLDivFactor_M;
	u32 RCC_u32PLLMulFactor_N;
	RCC_tenuPLL_P_Prescaler RCC_u32PLL_DivFactor_P;
	RCC_tenuPLL_Q_Prescaler RCC_enuPLLDivFactor_Q;
} RCC_tstrPLL_Cfg_t;

/*************************************** APIS ***********************************************/
/********************************************************************************************/
/********************************************************************************************/
/* Inputs        : System Clock choice from the options										*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_HSI															*/
/*				   2- RCC_enu_HSE															*/
/*				   3- RCC_enu_PLL															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Selecting the System's Clock Source                                      */
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuSelectSysClk(RCC_tenuSysClkSource Cpy_SysClk);

/********************************************************************************************/
/* Inputs        : System Clock to be Enabled												*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_HSI															*/
/*				   2- RCC_enu_HSE															*/
/*				   3- RCC_enu_PLL															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Enabling the Chosen Clk                                      			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnableSysClk(RCC_tenuSysClkSource Cpy_SysClk);
/********************************************************************************************/
/* Inputs        : System Clock to be Disabled												*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_HSI															*/
/*				   2- RCC_enu_HSE															*/
/*				   3- RCC_enu_PLL															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Disabling the Chosen Clk                                      			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisableSysClk(RCC_tenuSysClkSource Cpy_SysClk);
/********************************************************************************************/
/* Inputs        : System Clock Source														*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_HSI															*/
/*				   2- RCC_enu_HSE															*/
/*				   3- RCC_enu_PLL															*/
/* 				   & Address to check the Status if RDY or NOT_RDY 							*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : CHECKING THE CLK IF READY OR NOT                               			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuCheckClkReady(RCC_tenuSysClkSource Cpy_SysClk,u8 Cpy_u8ClkStatus);

/********************************************************************************************/
/* Inputs        : & Address to Check the Running Clk of the System							*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : GETTING THE CURRENT RUNNING CLOCK                               			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuGetRunningClk(u32 *Cpy_AddRunningClk);

///////////////////////////////////// PRESCALER ///////////////////////////////////////////////
/********************************************************************************************/
/* Inputs        : AHB BUS PRESCALER OPTION													*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_AHB_Prescaler_xx												*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : SETTING THE AHB BUS PRESCALER                               				*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_AHB(RCC_tenuAHB_Prescalers Cpy_u32AHB_Prescaler);
/********************************************************************************************/
/* Inputs        : APB1 BUS PRESCALER OPTION												*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_APB1_Prescaler_xx												*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : SETTING THE APB1 BUS PRESCALER                               			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_APB1(RCC_tenuAPB1_Prescalers Cpy_u32APB1_Prescaler);
/********************************************************************************************/
/* Inputs        : APB2 BUS PRESCALER OPTION												*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_APB2_Prescaler_xx												*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : SETTING THE APB2 BUS PRESCALER                               			*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_APB2(RCC_tenuAPB2_Prescalers Cpy_u32APB2_Prescaler);
/********************************************************************************************/
/********************************************************************************************/
/* Inputs        : 1- Peripheral Bus														*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_ABB1															*/
/* 				   2- RCC_enu_AHB2															*/
/* 				   3- RCC_enu_APB1															*/
/* 				   4- RCC_enu_APB2 															*/
/* 				   2- Peripheral Name														*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Enabling Peripheral's Clk                               					*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk(RCC_tenuSystemBus Cpy_u32PeripheralBus,RCC_tenuBuses_Peripherals Cpy_u32PeripheralName);
/********************************************************************************************/
/* Inputs        : 1- Peripheral Bus														*/
/* 				   Options :-																*/
/* 				   ----------																*/
/* 				   1- RCC_enu_ABB1															*/
/* 				   2- RCC_enu_AHB2															*/
/* 				   3- RCC_enu_APB1															*/
/* 				   4- RCC_enu_APB2 															*/
/* 				   2- Peripheral Name														*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Disabling Peripheral's Clk                               				*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk(RCC_tenuSystemBus Cpy_u32PeripheralBus,RCC_tenuBuses_Peripherals Cpy_u32PeripheralName);

/********************************************************************************************/
/* Inputs        : RCC_tstrPLL_Cfg_t														*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Configuring the PLL :													*/
/* 					1- RCC_tenuSourceClock													*/
/* 					2- RCC_u16MultiplyFactor_N												*/
/* 					3- RCC_u16MultiplyFactor_M												*/
/* 					4- RCC_enuPLL_P															*/
/* 					5- RCC_enuPLL_Q															*/
/********************************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigurePLL(RCC_tstrPLL_Cfg_t Cpy_tstrPLLConfig);




#endif		/* RCC_H */
