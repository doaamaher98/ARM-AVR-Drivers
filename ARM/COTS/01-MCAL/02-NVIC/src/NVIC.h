/****************************************************************************************/
/* Author 	: Doaa Maher																*/
/* Date   	: 13 MAR 2023																*/
/* Version 	: V01																		*/
/****************************************************************************************/
#ifndef NVIC_H
#define NVIC_H

#include "Std_Types.h"



/*************************** Defines ************************************/
// Application Interrupt & Reset Control Register
#define					SCB_AIRCR								*((volatile u32*) 0xE000ED0C)

#define					SCB_AIRCR_KEY_MASK						0x05FA0000
#define					SCB_AIRCR_KEY_CLR						0x0000FFFF


// Priority Grouping [4 MSbits]
/***************************************************************************/
#define 				NVIC_ALL_PREEMPTION  	               (0x05FA0300)
#define                 NVIC_Group_4_Sub_0						0x05FA0000
#define                 NVIC_Group_3_Sub_1						0x05FA0400
#define                 NVIC_Group_2_Sub_2						0x05FA0500
#define                 NVIC_Group_1_Sub_3						0x05FA0600
#define                 NVIC_Group_0_Sub_4						0x05FA0700
/***************************************************************************/

#define 				NVIC_STIR_Register  					0xFF

/***************************** REG MASKS *********************************/
#define					NVIC_ISPR_CLR						0xFFFFFFFE
#define					NVIC_ISPR_SET						0x00000001

#define					NVIC_ICPR_SET						0x00000001
#define					NVIC_ICPR_CLR						0xFFFFFFFE

#define					NVIC_ISER_SET							0x00000001
#define					NVIC_ISER_CLR							0xFFFFFFFE

#define					NVIC_ICER_SET							0x00000001
#define					NVIC_ICER_CLR							0xFFFFFFFE

#define					NVIC_IABR_SET							0x00000001
#define					NVIC_IABR_CLR							0xFFFFFFFE

#define					SCB_AIRCR_CLR							0x00000007
/* ====================================================================== */
#define					NVIC_IRQ_NUMBERS						240
#define					NVIC_EXT_INTERRUPTS						85

#define					NVIC_IPR_IRQS							60

#define					INTERRUPT_NOT_PENDING					0
#define					INTERRUPT_PENDING						1

#define					NULL									0
#define 				NULL_PTR								((void *)0)

/*************************** User defined types **********************************/
/********************** Void pointers to be used in APP **************************/
#define 				NVIC_ISER_                 ((void*) 0xE000E100)
#define 				NVIC_ICER_                 ((void*) 0xE000E180)
#define 				NVIC_ISPR_                 ((void*) 0xE000E200)
#define 				NVIC_ICPR_                 ((void*) 0xE000E280)
#define 				NVIC_IABR_                 ((void*) 0xE000E300)
#define 				NVIC_IPR_                  ((void*) 0xE000E400)
#define 				NVIC_STIR_                 ((void*) 0xE000EF00)

/******************************* Enums ***********************************/
// Error Status
typedef enum
{
	NVIC_enuOK=0,
	NVIC_enuNOK,
	NVIC_enuInvalidIRQ,
	NVIC_enuInvalidState,
	NVIC_enuInvalidPriority,
	NVIC_enuNullPointer,
	NVIC_enuInvalidBit,
	NVIC_enuInvalidISPR,
	NVIC_enuPending,
	NVIC_enuInvalidPriorityID,
	NVIC_enuInvalidGrpSubGrpPriority,


}NVIC_tenuErrorStatus;

/*
 * To Enable an interrupt :
 * 1- Set Pending Interrupt
 * 2- Set Interrupt Priority
 * 3- Activate Interrupt (EN)
 */

// Interrupt Pending Status
/* Notes :
 * Writing 1 to a disabled interrupt sets the state to pending.
 */
typedef enum
{
	NVIC_enuInterrptNotPending=0,
	NVIC_enuInterrptPending,
	NVIC_tenuNumberOfInterruptPendingStatus
}NVIC_tenuInterruptPendingStatus;

// Interrupt EN/DS
typedef enum
{
	NVIC_tenuInterruptDS=0,
	NVIC_tenuInterruptEN,
	NVIC_tenuNumberOfInterruptStatus
}NVIC_tenuInterruptStatus;

// Interrupt Active/Not Active State [READ ONLY]
typedef enum
{
	NVIC_enuInterruptNotActive=0,
	NVIC_enuInterruptActive,
	NVIC_enuNumberOfInterruptActiveStatus
}NVIC_tenuInterruptActiveStatus;


// Software Interrupt Triggering [SGI]
typedef enum
{
	NVIC_enuSoftwareInterrupt_DS=0,
	NVIC_enuSoftwareInterrupt_EN,
	NVIC_enuNumberOfSoftwareInterrupt_States
}NVIC_tenuSGI_Status;

/********** Register Numbers **********/
// ISER
typedef enum
{
	NVIC_enuISER0= 0xA0,
	NVIC_enuISER1= 0xA1,
	NVIC_enuISER2= 0xA2,
	NVIC_enuISER3= 0xA3,
	NVIC_enuISER4= 0xA4,
	NVIC_enuISER5= 0xA5,
	NVIC_enuISER6= 0xA6,
	NVIC_enuISER7= 0xA7,
}NVIC_tenuISER_Number;

// ICER
typedef enum
{
	NVIC_enuICER0= 0xB0,
	NVIC_enuICER1= 0xB1,
	NVIC_enuICER2= 0xB2,
	NVIC_enuICER3= 0xB3,
	NVIC_enuICER4= 0xB4,
	NVIC_enuICER5= 0xB5,
	NVIC_enuICER6= 0xB6,
	NVIC_enuICER7= 0xB7,
}NVIC_tenuICER_Number;

// ISPR
typedef enum
{
	NVIC_enuISPR0= 0xC0,
	NVIC_enuISPR1= 0xC1,
	NVIC_enuISPR2= 0xC2,
	NVIC_enuISPR3= 0xC3,
	NVIC_enuISPR4= 0xC4,
	NVIC_enuISPR5= 0xC5,
	NVIC_enuISPR6= 0xC6,
	NVIC_enuISPR7= 0xC7,
}NVIC_tenuISPR_Number;

// ICPR
typedef enum
{
	NVIC_enuICPR0= 0xD0,
	NVIC_enuICPR1= 0xD1,
	NVIC_enuICPR2= 0xD2,
	NVIC_enuICPR3= 0xD3,
	NVIC_enuICPR4= 0xD4,
	NVIC_enuICPR5= 0xD5,
	NVIC_enuICPR6= 0xD6,
	NVIC_enuICPR7= 0xD7,
}NVIC_tenuICPR_Number;

// IABR
typedef enum
{
	NVIC_enuIABR0= 0xE0,
	NVIC_enuIABR1= 0xE1,
	NVIC_enuIABR2= 0xE2,
	NVIC_enuIABR3= 0xE3,
	NVIC_enuIABR4= 0xE4,
	NVIC_enuIABR5= 0xE5,
	NVIC_enuIABR6= 0xE6,
	NVIC_enuIABR7= 0xE7,
}NVIC_tenuIABR_Number;


/************* Registers bits **************/
typedef enum
{
	NVIC_enuBit0 = 0x00000001,
	NVIC_enuBit1 = 0x00000002,
	NVIC_enuBit2 = 0x00000004,
	NVIC_enuBit3 = 0x00000008,
	NVIC_enuBit4 = 0x00000010,
	NVIC_enuBit5 = 0x00000020,
	NVIC_enuBit6 = 0x00000040,
	NVIC_enuBit7 = 0x00000080,
	NVIC_enuBit8 = 0x00000100,
	NVIC_enuBit9 = 0x00000200,
	NVIC_enuBit10 = 0x00000400,
	NVIC_enuBit11 = 0x00000800,
	NVIC_enuBit12 = 0x00001000,
	NVIC_enuBit13 = 0x00002000,
	NVIC_enuBit14 = 0x00004000,
	NVIC_enuBit15 = 0x00008000,
	NVIC_enuBit16 = 0x00010000,
	NVIC_enuBit17 = 0x00020000,
	NVIC_enuBit18 = 0x00040000,
	NVIC_enuBit19 = 0x00080000,
	NVIC_enuBit20 = 0x00100000,
	NVIC_enuBit21 = 0x00200000,
	NVIC_enuBit22 = 0x00400000,
	NVIC_enuBit23 = 0x00800000,
	NVIC_enuBit24 = 0x01000000,
	NVIC_enuBit25 = 0x02000000,
	NVIC_enuBit26 = 0x04000000,
	NVIC_enuBit27 = 0x08000000,
	NVIC_enuBit28 = 0x10000000,
	NVIC_enuBit29 = 0x20000000,
	NVIC_enuBit30 = 0x40000000,
	NVIC_enuBit31 = 0x80000000,
	NVIC_enuNumberOfBits = 32
}NVIC_tenu_Bits;

/*
 * SCB Register : System Control Block
 * We use the Register AIRCR that provides grouping control
 * To write to this register, you must write 0x5FA to the Vectkey field, otherwise the uP will ignore the write
 */

/* Groups & Subgroups */
typedef enum
{
	NVIC_enuGroup_4_Sub_0=0,
	NVIC_enuGroup_3_Sub_1,
	NVIC_enuGroup_2_Sub_2,
	NVIC_enuGroup_1_Sub_3,
	NVIC_enuGroup_0_Sub_4,
	NVIC_enuNumberOfGroup_Sub_Options
}NVIC_tenu_Groups_SubGroups;

/******************************* Structures ***********************************/

/***************************** APIs **************************************/
/************************************************************************/
/* Function : Enables an External Interrupt or Exception(HW)
 * Inputs   : Interrupt number [0->240]
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuEnableIRQ (u8 Cpy_InterruptNO);
/************************************************************************/

/* Function : Disables an Interrupt or Exception(HW)
 * Inputs   : Interrupt number [0->240]
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuDisableIRQ(u8 Cpy_InterruptNO);
/************************************************************************/

/* Function : Sets Pending Status of Interrupt or of Exception
 * Inputs   : Interrupt number [0->240]
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuSetPendingIRQ(u8 Cpy_InterruptNO);
/************************************************************************/

/* Function : Clears Pending Status of Interrupt or of Exception
 * Inputs   : Interrupt number [0->240]
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuClearPendingIRQ(u8 Cpy_InterruptNO);
/************************************************************************/

/* Function : Reading Pending status from Interrupt or Exception (returns 1 if it's set & 0 if it's cleared)
 * Inputs   : Interrupt number [0->240] and Value (ptr)
 * Return   : Status of Pending Register
 */
NVIC_tenuErrorStatus NVIC_u32ReadPendingIRQ (u8 Cpy_InterruptNO, u8 * Add_Value);
/************************************************************************/
/* Function : Reading the Active status if high or low
 * Inputs   : Interrupt number [0->240] and Value (ptr)
 * Return   : Status of Active Register
 */
NVIC_tenuErrorStatus NVIC_u32ReadActiveStatus (u8 Cpy_InterruptNO, u8 * Add_Value);
/************************************************************************/
/* Function : Sets the Priority of an Interrupt or Exception with Configurable Priority level to 1
 * Inputs   :
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuSetPriority(u8 Cpy_InterruptNo, u8 Cpy_u8PreemptionNO, u8 Cpy_u8SubGroupNO);
/************************************************************************/

/* Function : Reading the Priority of an Interrupt or Exception with Configurable Priority level; returns current priority level
 * Inputs   : void
 * Return   : Priority number of IRQ
 */
u32 NVIC_u32ReadPriority(u8 Cpy_InterruptNO,u8 Cpy_u8PriorityID, u8 * Add_Value);
/************************************************************************/
/* Function : Resets the System
 * Inputs   : void
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuSystemReset (void);
/************************************************************************/
/* Function : Sets the priority grouping
 * Inputs   :
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_enuSetPriorityGrouping(u32 Cpy_SubGroupBits);
/************************************************************************/
/* Function : Trigger the Interrupt
 * Inputs   :
 * Return   : Error Status to ensure function safety
 */
NVIC_tenuErrorStatus NVIC_TriggerSWInterrupt(u8 Cpy_InterruptNO);

/************************************************************************/

/*				EXTERNAL INTERRUPTS PRIORITES 					*/
#define                 NVIC_VECTOR_WWDG					0
#define                 NVIC_VECTOR_EXTI16					1
#define                 NVIC_VECTOR_EXTI21					2
#define                 NVIC_VECTOR_EXTI22					3
#define                 NVIC_VECTOR_FLASH					4
#define                 NVIC_VECTOR_RCC						5
#define                 NVIC_VECTOR_EXTI10					6
#define                 NVIC_VECTOR_EXTI11					7
#define                 NVIC_VECTOR_EXTI12					8
#define                 NVIC_VECTOR_EXTI13					9
#define                 NVIC_VECTOR_EXTI14					10
#define                 NVIC_VECTOR_DMA1_S0					11
#define                 NVIC_VECTOR_DMA1_S1					12
#define                 NVIC_VECTOR_DMA1_S2					13
#define                 NVIC_VECTOR_DMA1_S3					14
#define                 NVIC_VECTOR_DMA1_S4					15
#define                 NVIC_VECTOR_DMA1_S5					16
#define                 NVIC_VECTOR_DMA1_S6					17
#define                 NVIC_VECTOR_ADC						18
#define                 NVIC_VECTOR_EXTI9					23
#define                 NVIC_VECTOR_TIM1_TIM9				24
#define                 NVIC_VECTOR_TIM1_TIM10				25
#define                 NVIC_VECTOR_TIM1_TIM11				26
#define                 NVIC_VECTOR_TIM1_CC					27
#define                 NVIC_VECTOR_TIM2					28
#define                 NVIC_VECTOR_TIM3					29
#define                 NVIC_VECTOR_TIM4					30
#define                 NVIC_VECTOR_I2C1_EV					31
#define                 NVIC_VECTOR_I2C1_ER					32
#define                 NVIC_VECTOR_I2C2_EV					33
#define                 NVIC_VECTOR_I2C2_ER					34
#define                 NVIC_VECTOR_SPI1                    35
#define                 NVIC_VECTOR_SPI2                    36
#define                 NVIC_VECTOR_USART1                  37
#define                 NVIC_VECTOR_USART2                  38
#define                 NVIC_VECTOR_EXTI15					40
#define                 NVIC_VECTOR_EXTI17                  41
#define                 NVIC_VECTOR_EXTI18                  42
#define                 NVIC_VECTOR_DMA1_S7                 47
#define                 NVIC_VECTOR_SDIO					49
#define                 NVIC_VECTOR_TIM5					50
#define                 NVIC_VECTOR_SPI3					51
#define                 NVIC_VECTOR_DMA2_S0					56
#define                 NVIC_VECTOR_DMA2_S1                 57
#define                 NVIC_VECTOR_DMA2_S2                 58
#define                 NVIC_VECTOR_DMA2_S3                 59
#define                 NVIC_VECTOR_DMA2_S4                 60
#define                 NVIC_VECTOR_OTG                     67
#define                 NVIC_VECTOR_DMA2_S5                 68
#define                 NVIC_VECTOR_DMA2_S6					69
#define                 NVIC_VECTOR_DMA2_S7                 70
#define                 NVIC_VECTOR_USART6                  71
#define                 NVIC_VECTOR_I2C3_EV                 72
#define                 NVIC_VECTOR_I2C3_ER                 73
#define                 NVIC_VECTOR_FPU                     81
#define                 NVIC_VECTOR_SPI4                    84


#endif
