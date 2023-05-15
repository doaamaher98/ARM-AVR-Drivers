/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 16 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/ 
/********************************************************/

#include "../../00-MCAL/00-DIO/DIO_Cfg.h"

#include "LED_Cfg.h"

/****************** LED Array of Configurations ****************/
LED_strCfg_t LED_strCfg [LED_enuNumberOfPins]=
{
	{DIO_enuPin0, LED_ActiveHigh},			/* LED1 */
	{DIO_enuPin1, LED_ActiveHigh},			/* LED2 */ 
	{DIO_enuPin2, LED_ActiveHigh},			/* LED3 */ 
	{DIO_enuPin3, LED_ActiveHigh},			/* LED4 */ 
	{DIO_enuPin4, LED_ActiveHigh},			/* LED5 */ 
	{DIO_enuPin5, LED_ActiveHigh},			/* LED6 */ 
	{DIO_enuPin6, LED_ActiveHigh},			/* LED7 */ 
	{DIO_enuPin7, LED_ActiveHigh}			/* LED8 */ 
};
