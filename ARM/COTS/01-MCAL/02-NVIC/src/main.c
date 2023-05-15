#include "NVIC.h"


void main (void)
{
	__attribute__ ((section(".isr2_vector"),used));


	//	NVIC_Config.NVIC_Reg = NVIC_ISER_;
	//	NVIC_Config.NVIC_Reg_Number= NVIC_enuISER0;
	//	NVIC_Config.NVIC_Bit = NVIC_enuBit0;
	//
	//	NVIC_enuEnableIRQ(&NVIC_Config);

	/* ================================ */
	//	NVIC_Config.NVIC_Reg = NVIC_ICER_;
	//	NVIC_Config.NVIC_Reg_Number = NVIC_enuICER0;
	//	NVIC_Config.NVIC_Bit = NVIC_enuBit0;
	//
	//	NVIC_enuDisableIRQ(&NVIC_Config);

	/* ============================== */

	//	NVIC_Config.NVIC_Reg = NVIC_ISPR_;
	//	NVIC_Config.NVIC_Reg_Number = NVIC_enuISPR0;
	//	NVIC_Config.NVIC_Bit = NVIC_enuBit0;
	//
	//	NVIC_enuSetPendingIRQ(&NVIC_Config);

	/* ============================== */

	//	NVIC_Config.NVIC_Reg = NVIC_ICPR_;
	//	NVIC_Config.NVIC_Reg_Number = NVIC_enuICPR0;
	//	NVIC_Config.NVIC_Bit = NVIC_enuBit0;
	//
	//	NVIC_enuClearPendingIRQ(&NVIC_Config);

	/* ============================== */

	//	NVIC_Config.NVIC_Reg = NVIC_ISPR_;
	//	NVIC_Config.NVIC_Reg_Number = NVIC_enuISPR0;
	//	NVIC_Config.NVIC_Bit = NVIC_enuBit0;
	//
	//	u8 Status = NVIC_u32ReadPendingIRQ(&NVIC_Config);
	//	trace_printf(Status);

	/* ============================== */


//	=

	/* ============================== */

//	NVIC_enuSetPriority(NVIC_VECTOR_EXTI10,NVIC_Group_4_Sub_0);


	while (1)
	{

	}
}
