/****************************************************************************************/
/* Author 	: Doaa Maher								*/
/* Date   	: 13 MAR 2023								*/
/* Version 	: V01									*/	
/****************************************************************************************/

#include "NVIC.h"
#include "NVIC_Config.h"

/******************************* Pointers to struct with every register's base address *********************************/
// SCB Register
#define 				SCB_AIRCR   				*((volatile u32*)0xE000ED0C)

typedef struct
{
	volatile u32 ISER[8];
	volatile u32 reserved1[24];
	volatile u32 ICER[8];
	volatile u32 reserved2[24];
	volatile u32 ISPR[8];
	volatile u32 reserved3[24];
	volatile u32 ICPR[8];
	volatile u32 reserved4[24];
	volatile u32 IABR[8];
	volatile u32 reserved5[56];
	volatile u8  IPR[240];
	volatile u32 reserved6[580];
	volatile u32 STIR;
}NVIC_tstrConfig_t;

// Base Address
NVIC_tstrConfig_t * const volatile NVIC = ((NVIC_tstrConfig_t *) 0xE000E100);

																// Array of Pointer to function : Vector Table Declaration
																void (* ISR_Handler[NVIC_IRQ_NUMBERS])(void)= {NULL_PTR};


/************************************************************************************************************************/
/* Notes :-
 * -------
 * To enable an external interrupt, we must :
 * 1- Set the Enable bit in ISER
 * 2- Clear the pending flag in ICPR
 */
NVIC_tenuErrorStatus NVIC_enuEnableIRQ (u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Clear any previous Pending before Enabling the Interrupt */
		NVIC->ICPR[Cpy_InterruptNO/32] |= (1<< (Cpy_InterruptNO % 32) );
		/* Enabling the Required Interrupt */
		NVIC->ISER[Cpy_InterruptNO/32] |= (1<< (Cpy_InterruptNO % 32) );
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
/* Notes :-
 * -------
 * To Disable an external interrupt, we must :
 * 1- Set the Disable bit in ICER
 */
NVIC_tenuErrorStatus NVIC_enuDisableIRQ (u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Disabling the Required Interrupt */
		NVIC->ICER[Cpy_InterruptNO/32] |= (1<< (Cpy_InterruptNO % 32) );
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
/* Notes :
 * To set pending flag we must :
 * 1- Set Pending ISPR flag
 */
NVIC_tenuErrorStatus NVIC_enuSetPendingIRQ(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Set the Specified interrupt pending flag */
		NVIC->ISPR[Cpy_InterruptNO/32] |= (1<< (Cpy_InterruptNO % 32) );
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
/* Notes :
 * To clear pending flag we must :
 * 1- Set Pending ICPR flag
 */
NVIC_tenuErrorStatus NVIC_enuClearPendingIRQ(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Set the Specified interrupt pending flag */
		NVIC->ICPR[Cpy_InterruptNO/32] |= (1<< (Cpy_InterruptNO % 32) );
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_u32ReadPendingIRQ (u8 Cpy_InterruptNO,  u8 * Add_Value)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Getting the specified interrupt pending flag status */
		*Add_Value = (NVIC->ISPR[Cpy_InterruptNO/32] >> ( (1 >> Cpy_InterruptNO % 32) ) &1);
	}

	return LocalErrorStatus;
}
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_u32ReadActiveStatus (u8 Cpy_InterruptNO,  u8 * Add_Value)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Getting the specified interrupt Active status */
		*Add_Value = (NVIC->IABR[Cpy_InterruptNO/32] >> ( (1 >> Cpy_InterruptNO % 32) ) &1);
	}

	return LocalErrorStatus;
}
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_TriggerSWInterrupt(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	// Validating the number of interrupts
	if (Cpy_InterruptNO > NVIC_IRQ_NUMBERS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}
	else
	{
		/* Generating the wanted SW Interrupt */
		NVIC->STIR = Cpy_InterruptNO;
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_enuSetPriority(u8 Cpy_InterruptNo, u8 Cpy_u8PreemptionNO, u8 Cpy_u8SubGroupNO)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	u8 Loc_u8Register = NVIC->IPR[Cpy_InterruptNo];

	/* Checking interrupts */
	if(Cpy_InterruptNo > NVIC_IPR_IRQS)
	{
		LocalErrorStatus = NVIC_enuInvalidIRQ;
	}

	else
	{
		Loc_u8Register = (Cpy_u8SubGroupNO | (Cpy_u8PreemptionNO <<((SCB_AIRCR - NVIC_ALL_PREEMPTION)/256))) << 4;

		NVIC->IPR[Cpy_InterruptNo] = Loc_u8Register;
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_SetSysSubGroup(u32 Cpy_SubGroupBits)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	if(Cpy_SubGroupBits == NVIC_ALL_PREEMPTION  ||  Cpy_SubGroupBits == NVIC_Group_3_Sub_1  ||
			Cpy_SubGroupBits == NVIC_Group_2_Sub_2  ||  Cpy_SubGroupBits == NVIC_Group_1_Sub_3  ||
			Cpy_SubGroupBits == NVIC_Group_0_Sub_4)
	{
		SCB_AIRCR = Cpy_SubGroupBits;
	}

	else
	{
		LocalErrorStatus = NVIC_enuInvalidGrpSubGrpPriority;
	}
	return LocalErrorStatus;
}
/************************************************************************************************************************/
/************************************************************************************************************************/
NVIC_tenuErrorStatus NVIC_enuSystemReset (void)
{
	NVIC_tenuErrorStatus LocalErrorStatus = NVIC_enuOK;

	/* Reset all major components except for debugging */
	SCB_AIRCR |= SCB_AIRCR_CLR;

	return LocalErrorStatus;
}
/************************************************************************************************************************/
