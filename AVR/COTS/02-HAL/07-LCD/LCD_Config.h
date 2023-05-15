/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 10 FEB 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the Configurations of the */
/*			   LCD Driver									  */
/**************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* LCD Data Pins (D0-D7) Modes */
#define LCD_4Bits_Data			0
#define LCD_8Bits_Data			1


/* LCD Number of Lines : (N) */
#define	LCD_1_Line				0
#define LCD_2_Line				1

/* LCD Font Type (F) */
#define LCD_Font_5x8 			0
#define LCD_Font_5x11			1

/* LCD Display Options (D) */
#define LCD_Display_ON			1
#define LCD_Display_OFF			0


/* LCD Cursor below the char or not (C) */
#define LCD_withCursor			1
#define LCD_withoutCursor		0

/* LCD Cursor Blinking or Constant (B) */
#define LCD_CursorBlinking		1
#define LCD_CursorNotBlinking	0
/********************************************************************************/


/* LCD Rows (X) */
typedef enum { 
	LCD_enuRow1=0,
	LCD_enuRow2
}LCD_tenuRows;

/* LCD Columns (Y) */
typedef enum {
	LCD_enuCol1=0,
	LCD_enuCol2,
	LCD_enuCol3,
	LCD_enuCol4,
	LCD_enuCol5,
	LCD_enuCol6,
	LCD_enuCol7,
	LCD_enuCol8,
	LCD_enuCol9,
	LCD_enuCol10,
	LCD_enuCol11,
	LCD_enuCol12,
	LCD_enuCol13,
	LCD_enuCol14,
	LCD_enuCol15
}LCD_tenuCols;

#endif /* LCD_CONFIG_H_ */