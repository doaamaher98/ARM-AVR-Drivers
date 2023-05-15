/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 18 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/ 
/********************************************************/
#include "DIO.h"
#include "DIO_Cfg.h"

#include "SSEGMENT_Cfg.h"

/********************************************************/
/*
SSEG_tstrPinCfg_t SSEG_tstrPinCfg[SSEGenu_NumberofSEGS]=
{	
	{
		.SSEGPort = DIO_enuPORTA,
		.SSEGMode = CommonAnode	
	},
	
	{
		.SSEGPort = DIO_enuPORTB,
		.SSEGMode = CommonAnode
	}
};
*/
/********************************************************/
// COMMON ANODE
const u8  SSEG_LookupTable[SSEG_enuNumbersofPins] =
{
	~ZERO,
	~ONE,
	~TWO,
	~THREE,
	~FOUR,
	~FIVE,
	~SIX,
	~SEVEN,
	~EIGHT,
	~NINE
};

