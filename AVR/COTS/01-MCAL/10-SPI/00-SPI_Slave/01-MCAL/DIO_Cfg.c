/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 16 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/
/********************************************************/
#include "DIO_Cfg.h"


DIO_strPinCfg_t DIO_strPinCfg [DIO_enuNumberOfPins] =
{
	/*********************************************************************/
	/*PORTA   PIN DIRECTION		PULL UP/PULL DOWN/OUTPUT LOW/OUTPUT HIGH */
	/*********************************************************************/
	/*PIN0*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN1*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN2*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN3*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},		
	/*PIN4*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},		
	/*PIN5*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},		
	/*PIN6*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},		
	/*PIN7*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},		
	/*********************************************************************/

	/*PORTB   PIN DIRECTION		PULL UP/PULL DOWN */
	/*********************************************************************/
	/*PIN8*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN9*/  {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN10*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN11*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},			// SLAVE //
	/*PIN12*/ {DIO_enuINPUT,  DIO_enuInputPinPullUp},		// PB4 :SS
	/*PIN13*/ {DIO_enuINPUT,  DIO_enuInputPinPullUp},		// PB5 :MOSI
	/*PIN14*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},			// PB6 :MISO
	/*PIN15*/ {DIO_enuINPUT,  DIO_enuInputPinPullUp},		// PB7 :SCK
	/*********************************************************************/

	/*PORTC   PIN DIRECTION		PULL UP/PULL DOWN */
	/*********************************************************************/
	/*PIN16*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN17*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN18*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN19*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN20*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN21*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN22*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN23*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*********************************************************************/

	/*PORTD   PIN DIRECTION		PULL UP/PULL DOWN */
	/*********************************************************************/
	/*PIN24*/ {DIO_enuINPUT,  DIO_enuInputPinPullUp},
	/*PIN25*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN26*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN27*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN28*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN29*/ {DIO_enuOUTPUT,  DIO_enuOutputLow},
	/*PIN30*/ {DIO_enuINPUT,  DIO_enuInputPinPullUp},
	/*PIN31*/ {DIO_enuOUTPUT,  DIO_enuOutputLow}
};
