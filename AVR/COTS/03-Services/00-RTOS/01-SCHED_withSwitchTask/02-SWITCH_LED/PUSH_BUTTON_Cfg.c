/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 18 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/ 
/********************************************************/
#include "../01-MCAL/DIO.h"
#include "PUSH_BUTTON.h"


PUSH_BUTTON_tstrPinCfg_t PUSH_BUTTON_strPinCfg[PUSH_BUTTON_enuNumberOfPins]=
{
	/*Pin8*/ {DIO_enuPin8 ,PUSH_BUTTON_enuPullUp},
	/*Pin9*/ {DIO_enuPin9 ,PUSH_BUTTON_enuPullUp},	
};
