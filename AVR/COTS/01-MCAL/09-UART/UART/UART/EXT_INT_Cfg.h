/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 27 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations file						*/
/********************************************************/
#ifndef MCUCR_CFG_H
#define MCUCR_CFG_H

#include "EXT_INT_Priv.h"


/**************************** Configs ***********************************/
#define			EXT_INT_0_MODE			EXT_INT_RaisingEdge
#define			EXT_INT_1_MODE			EXT_INT_RaisingEdge
#define			EXT_INT_2_MODE			EXT_INT_DISABLE_

#define			EXT_INT_DISABLE_		10

/********************* ENABLE/DISABLE ***************************/
#define			EXT_INT_0				EXT_INT_0_ENABLE
#define			EXT_INT_1				EXT_INT_1_ENABLE
#define			EXT_INT_2				EXT_INT_2_ENABLE


#define			EXT_INT_0_ENABLE			0
#define			EXT_INT_1_ENABLE			1
#define			EXT_INT_2_ENABLE			2
	
/******************* MODES **********************/
/* FOR (INT0-INT1) :
-------------------
1- RAISING EDGE
2- FALLING EDGE
3- ON_CHANGE
4- LOW_LEVEL

FOR (INT2):
------------
1- RAISING EDGE
2- FALLING EDGE
*/
/****************************************************/



#endif /* MCUCR_CFG_H */