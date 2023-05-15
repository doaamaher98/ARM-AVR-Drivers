/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 16 FEB 2023                              	  */
/* Version   : V.02	                                    	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the Private Addresses of  */
/*			   LCD Driver									  */
/**************************************************************/
#ifndef LCD_PRV_H_
#define LCD_PRV_H_

#include "../00-LIB/Std_Types.h"

/* LCD DDRAM Visible Locations : Data Display RAM */
#define		LCD_Row1_Line_StartAdd			0x00
#define		LCD_Row1_Line_EndAdd			0x0F

#define		LCD_Row2_Line_StartAdd			0x40
#define		LCD_Row2_Line_EndAdd			0x4F



#define		LCD_DataBit7		128
#define		LCD_DataBit6		64

#define		LCD_NumberOfBlocks	8

/* LCD Function Set (8-bits) */
#define			LCD_8_BitsFunctionSet			0b00111011
/* LCD Display Control (8-bits) */
#define			LCD_8_BitsDisplayControl		0b00001100
/* Clear Display Mask (8-bits) */
#define			LCD_8_BitsClearDisplay			0b00000001
/* Returning to Start place Mask*/
#define			LCD_8_BitsStartingLoc			0b00000010
/* LCD Entry Set (8-bits) */
//#define			LCD_8_BitsEntrySet				0b00000110




/* LCD Function Set Mask (4-bits) */
#define			LCD_4_BitsFunctionSet1			0b00100000
#define			LCD_4_BitsFunctionSet2			0b00100000
#define			LCD_4_BitsFunctionSet3			0b10000000
/* LCD Display ON/OFF Control Mask (4-bits) */
#define			LCD_4_BitsDisplayControl1		0b00000000
#define			LCD_4_BitsDisplayControl2		0b11000000
/* LCD Display Clear (4-bits) */
#define			LCD_4_BitsClearDisplay1			0b00000000
#define			LCD_4_BitsClearDisplay2			0b00010000

#define			NULL_PTR			((void*)0)

#endif /* LCD_PRV_H_ */