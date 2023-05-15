/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 2 FEB 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A Private file for KEYPAD Driver 		          */	 
/**************************************************************/
#ifndef KEYPAD_PRV_H
#define KEYPAD_PRV_H

/******************** Available Ports **********************/
#define				KeypadPort_A		0
#define				KeypadPort_B		1
#define				KeypadPort_C		2
#define				KeypadPort_D		3


/******************** 4x4 Keypad Pins *******************/
// Rows
#define				Keypad4x4Pin_0			0
#define				Keypad4x4Pin_1			1
#define				Keypad4x4Pin_2			2
#define				Keypad4x4Pin_3			3
// Cols
#define				Keypad4x4Pin_4			4
#define				Keypad4x4Pin_5			5
#define				Keypad4x4Pin_6			6
#define				Keypad4x4Pin_7			7

/******************** 4x3 Keypad Pins ********************/
// Rows
#define				Keypad4x3Pin_0			0
#define				Keypad4x3Pin_1			1
#define				Keypad4x3Pin_2			2
#define				Keypad4x3Pin_3			3
// Cols
#define				Keypad4x3Pin_4			4
#define				Keypad4x3Pin_5			5
#define				Keypad4x3Pin_6			6

/******************** Pressed & non-Pressed Vals *****************/
#define				KeypadKey_NotPressed		0
#define				KeypadKey_Pressed			1


#define				NULL_PTR			((void *) 0)



#endif					/* KEYPAD_PRV_H */