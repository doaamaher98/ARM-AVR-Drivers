/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 18 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/ 
/********************************************************/
#include "PUSH_BUTTON.h"
#include "../01-MCAL/DIO.h"

PUSH_BUTTON_tstrPinCfg_t PUSH_BUTTON_strPinCfg[PUSH_BUTTON_enuNumberOfPins]=
{
	/*Pin16*/ {DIO_enuPin16 ,PUSH_BUTTON_enuPullUp},
	/*Pin17*/ {DIO_enuPin17 ,PUSH_BUTTON_enuPullUp},
	/*Pin18*/ {DIO_enuPin18 ,PUSH_BUTTON_enuPullUp},
	/*Pin19*/ {DIO_enuPin19 ,PUSH_BUTTON_enuPullUp}
};
