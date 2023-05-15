/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 16 JAN 2023                             */
/* Version   : V.02                                    */
/* Target    : AVR32								   */
/* Descrip.   : C File with the Driver Functions	   */
/*				for Checking their Saftey.			   */
/*******************************************************/
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"

#include "GIE.h"
#include "GIE_Cfg.h"
#include "GIE_Priv.h"

/****************************************************************/
/*    GIE Init Function											*/
/*	  Input  : void												*/
/*	  Output : GIE_tenuErrorStatus to Report Errors				*/
/****************************************************************/
GIE_tenuErrorStatus GIE_enuInit_EnableGIE (void)
{	
	GIE_tenuErrorStatus LocalErrorStatus = GIE_enuOK;
	
	u8 Check_Status = GET_BIT(SREG,SREG_GIE_Pin);
	
	if (Check_Status != 1)
		// Setting the GIE at Bit #7 [GIE = 1]
		SET_BIT(SREG,SREG_GIE_Pin);
	
	else 
		return GIE_enuNOK;
		
	return LocalErrorStatus;
}
	
/****************************************************************/
/*      GIE Disable Function									*/
/*		Input  : Void											*/
/*		Output : GIE_tenuErrorStatus to Report Errors		   	*/
/****************************************************************/
GIE_tenuErrorStatus GIE_enuInit_DisbaleGIE (void)
{	
	GIE_tenuErrorStatus LocalErrorStatus = GIE_enuOK;
	
	u8 Check_Status = GET_BIT(SREG,SREG_GIE_Pin);
	
	if (Check_Status != 0)
		// Clearing the GIE at Bit #7 [GIE = 0]
		CLR_BIT(SREG,SREG_GIE_Pin);
	
	else
		return GIE_enuNOK;
	
	return LocalErrorStatus;	
}
