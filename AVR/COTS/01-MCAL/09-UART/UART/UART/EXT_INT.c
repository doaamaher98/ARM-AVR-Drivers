/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 1 FEB 2023                              */
/* Version   : V.02                                    */
/* Target    : AVR32								   */
/* Descrip.   : C File with the Driver Functions	   */
/*				for Checking their Saftey.			   */
/*******************************************************/
#include <avr/interrupt.h>

#include "Bit_Math.h"
#include "Std_Types.h"

#include "GIE.h"

#include "EXT_INT.h"
#include "EXT_INT_Cfg.h"
#include "EXT_INT_Priv.h"

/********** Pointer to Functions to be Assigned to ISR = Called Functions ***************/
// Assigned to pointer points to nothing
// Static : to preserve it's address
void (*INT0_fptr)(void) = NULL_PTR;
void (*INT1_fptr)(void) = NULL_PTR;
void (*INT2_fptr)(void) = NULL_PTR;
/**********************************************************************/
// EXT_INTCallback_Set INT0_CallBack;
// EXT_INTCallback_Set INT1_CallBack;
// EXT_INTCallback_Set INT2_CallBack;
/**********************************************************************/

/************************** INIT Function *******************************/
EXT_INT_tenuErrorStatus EXT_INT_INIT (void)
{
	EXT_INT_tenuErrorStatus LocalErrorStatus = EXT_INT_enuOK;	
	
	/* Configuring INT0 */
	#if EXT_INT_0_MODE == EXT_INT_LowLevel
		CLR_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
	
	#elif EXT_INT_0_MODE == EXT_INT_OnChange
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
	
	#elif EXT_INT_0_MODE == EXT_INT_FallingEdge
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
	
	#elif EXT_INT_0_MODE == EXT_INT_RaisingEdge
		SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
	
	#else
		LocalErrorStatus = EXT_INT_enuNOK;
	
	#endif
	
	/********************************** INT1 ******************************/
	/* Configuring INT1 */
	#if EXT_INT_1_MODE == EXT_INT_LowLevel
		CLR_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
	
	#elif EXT_INT_1_MODE == EXT_INT_OnChange
		SET_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
	
	#elif EXT_INT_1_MODE == EXT_INT_FallingEdge
		CLR_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
	
	#elif EXT_INT_1_MODE == EXT_INT_RaisingEdge
		SET_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
	
	#else
		LocalErrorStatus = EXT_INT_enuNOK;
	
	#endif
	
	/********************************** INT2 ******************************/
	/* Configuring INT2 */
	#if EXT_INT_2_MODE == EXT_INT_FallingEdge
		CLR_BIT(MCUCSR,MCUCSR_ISC2);
	
	#elif  EXT_INT_2_MODE == EXT_INT_RaisingEdge
		SET_BIT(MCUCSR,MCUCSR_ISC2);
	
	#else
		LocalErrorStatus = EXT_INT_enuNOK;
	
	#endif

	return LocalErrorStatus;
}

/*****************************************************************************************/
/************************** EXT_INT0_ENABLE ********************************/
void EXT_INT0_Enable (void)
{
	/********************************** INT0 ******************************/
	SET_BIT(GICR,GICR_INT0);
}


/************************** EXT_INT1_ENABLE ********************************/
void EXT_INT1_Enable (void)
{
	/********************************** INT1 ******************************/
	SET_BIT(GICR,GICR_INT1);
}

/************************** EXT_INT2_ENABLE ********************************/
void EXT_INT2_Enable (void)
{
	/********************************** INT2 ******************************/
	SET_BIT(GICR,GICR_INT2);
}

/**********************************************************************/
/**********************************************************************/

/********************************* EXT_INT0_DISABLE *****************************************/
void EXT_INT0_Disable (void)
{
	/********************************** INT0 ******************************/
	CLR_BIT(GICR,GICR_INT0);
}


/********************************* EXT_INT1_DISABLE *****************************************/
void EXT_INT1_Disable (void)
{
	/********************************** INT1 ******************************/
	CLR_BIT(GICR,GICR_INT1);
}


/********************************* EXT_INT2_DISABLE *****************************************/
void EXT_INT2_Disable (void)
{
	/********************************** INT2 ******************************/
	CLR_BIT(GICR,GICR_INT2);
}


/************************************ CallBack Function ************************************/
EXT_INT_tenuErrorStatus EXT_INT0Callback_Set (void (*ptr_int)(void))
{
	EXT_INT_tenuErrorStatus LocalErrorStatus = EXT_INT_enuOK;
	
	if (ptr_int != NULL_PTR)
	{
		INT0_fptr = ptr_int;
	}
	
	else {
		LocalErrorStatus = EXT_INT_enuNOK;
	}
	
	return LocalErrorStatus;
}

EXT_INT_tenuErrorStatus EXT_INT1Callback_Set (void (*ptr_int)(void))
{
	EXT_INT_tenuErrorStatus LocalErrorStatus = EXT_INT_enuOK;

	if (ptr_int != NULL_PTR)
	{
		INT1_fptr = ptr_int;
	}
	
	else {
		LocalErrorStatus = EXT_INT_enuNOK;
	}
	
	return LocalErrorStatus;
}

EXT_INT_tenuErrorStatus EXT_INT2Callback_Set (void (*ptr_int)(void))
{
	EXT_INT_tenuErrorStatus LocalErrorStatus = EXT_INT_enuOK;
	
	if (ptr_int != NULL_PTR)
	{
		INT2_fptr = ptr_int;
	}
	
	else 
	{
		LocalErrorStatus = EXT_INT_enuNOK;
	}
	
	return LocalErrorStatus;
}

/************************************** ISRs **************************************/
ISR(INT0_vect)
{
	INT0_fptr(); // Call it
}

ISR(INT1_vect)
{
	INT1_fptr(); // Call it
}

ISR(INT2_vect)
{	
	INT2_fptr(); // Call it
}

/**********************************************************************/

// void EXT_INT0Callback_Set (EXT_INTCallback_Set CallBackFunction)
// {
// 	INT0_CallBack = CallBackFunction;
// }
// 
// void EXT_INT1Callback_Set (EXT_INTCallback_Set CallBackFunction)
// {
// 	INT1_CallBack = CallBackFunction;
// }
// 
// void EXT_INT2Callback_Set (EXT_INTCallback_Set CallBackFunction)
// {
// 	INT2_CallBack = CallBackFunction;

/******************************* ISRs *************************************/
// 
// 
// ISR(INT0_vect)
// {
// 	
// 	INT0_CallBack();
// }
// 
// ISR(INT1_vect)
// {
// 	INT1_CallBack();
// }
// 
// ISR(INT2_vect)
// {
// 	INT2_CallBack();
// }