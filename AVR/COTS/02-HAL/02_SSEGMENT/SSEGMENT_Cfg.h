/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 18 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A config file For the SSEG				 	  */	 
/**************************************************************/
#ifndef _SSEG_CFG_H
#define _SSEG_CFG_H

#include "Std_Types.h"

#include "SSEGMENT.h"
#include "SSEGMENT_Prv.h"

/********************* Enum with the PORTS NO. *********************/
typedef enum
{
	SSEG_enuPORTA,
	SSEG_enuPORTB,
	SSEG_enuPORTC,
	SSEG_enuPORTD,
	SSEG_enuNumberOfPorts
}SSEG_enuPORT;

/*********************************************************************/
typedef enum {
	CommonAnode=0,
	CommonCathode
}SSEG_enuModes;

/*********************************************************************/
typedef enum {
	SSEGenu_One=0,
	SSEGenu_Two,
	SSEGenu_NumberofSEGS
}SSEG_Numbers;

/*********************************************************/
typedef struct{
	SSEG_enuPORT		    SSEGPort;	
	SSEG_enuModes			SSEGMode;
}SSEG_tstrPinCfg_t;

/*********************************************************/
//extern SSEG_tstrPinCfg_t SSEG_tstrPinCfg[SSEGenu_NumberofSEGS];
extern const u8  SSEG_LookupTable[10];
/*********************************************************************/

#endif         /* _SSEG */