/*
 * LCD_ArabicNameSwitches.c
 *
 * Created: 2/18/2023 7:34:32 PM
 * Author : Doaa Maher
 */ 
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"

#include "../02-HAL/PUSH_BUTTON.h"
#include "../02-HAL/LCD.h"

u8 harf_el_dal [8] =
{
	0b00000,
	0b00000,
	0b00111,
	0b00001,
	0b00001,
	0b01111,
	0b00000,
	0b00000
};
u8 harf_el_3een2lf [8] =
{
	0b10000,
	0b10000,
	0b10111,
	0b10100,
	0b11100,
	0b00000,
	0b00000,
	0b00000
};
u8 harf_el_hamza [8] =
{
	0b00000,
	0b00000,
	0b01110,
	0b01000,
	0b11110,
	0b00000,
	0b00000,
	0b00000
};


int main(void)
{
	DIO_enuInit();
// 	PUSH_BUTTON_INIT();
	LCD_vidInit();
	
	u8 Push_Button1 = PUSH_BUTTON_enuPin16;			/* RIGHT */
	u8 Push_Button2 = PUSH_BUTTON_enuPin17;			/* LEFT */
	u8 Push_Button3 = PUSH_BUTTON_enuPin18;			/* DOWN */
	u8 Push_Button4 = PUSH_BUTTON_enuPin19;			/* UP */
	
	u8 State1=0;
	u8 State2=0;
	u8 State3=0;
	u8 State4=0;
	
	u8 x=0;
	u8 y=0;
	
	LCD_enuWriteSpecialPattern(harf_el_dal,		0,		0,	2);
	LCD_enuWriteSpecialPattern(harf_el_3een2lf,	1,	    0,	1);
	LCD_enuWriteSpecialPattern(harf_el_hamza,	2,		0,	0);
	
    /* Replace with your application code */
    while (1) 
    {
		/* LEFT & RIGHT */
		/* RIGHT */
		Get_PUSH_BUTTON_State(Push_Button1,&State1);	
		if (State1 == PUSH_BUTTON_enuPressed)
		{
			Delay_MS(10);
			Get_PUSH_BUTTON_State(Push_Button1,&State1);
			if (State1 == PUSH_BUTTON_enuPressed)
			{
				y++;
				if (y >= 13)
				{
					y=13;
				}
			}
			LCD_enuClearDisplay();
			LCD_enuWriteSpecialPattern(harf_el_dal,		0,		x,	y+2);
			LCD_enuWriteSpecialPattern(harf_el_3een2lf,	1,	    x,	y+1);
			LCD_enuWriteSpecialPattern(harf_el_hamza,	2,		x,	y);
		}
		

 		/* LEFT */
		Get_PUSH_BUTTON_State(Push_Button2,&State2);
		if (State2 == PUSH_BUTTON_enuPressed)
		{
			Delay_MS(20);
			Get_PUSH_BUTTON_State(Push_Button2,&State2);
			if (State2 == PUSH_BUTTON_enuPressed)
			{
				y--;
				if (y <= 2)
				{
					y=2;
				}
			}
			LCD_enuClearDisplay();
			LCD_enuWriteSpecialPattern(harf_el_dal,		0,		x,	y);
			LCD_enuWriteSpecialPattern(harf_el_3een2lf,	1,	    x,	y-1);
			LCD_enuWriteSpecialPattern(harf_el_hamza,	2,		x,	y-2);
		}

 	
	/* DOWN */
// 	Delay_MS(10);
	Get_PUSH_BUTTON_State(Push_Button3,&State3);
	if (State3 == PUSH_BUTTON_enuPressed)
	{
		Delay_MS(20);
		Get_PUSH_BUTTON_State(Push_Button3,&State3);
		if (State3 == PUSH_BUTTON_enuPressed)
		{
			x++;
			if (x > 1)
			{
				x=1;
			}
			LCD_enuClearDisplay();
			LCD_enuWriteSpecialPattern(harf_el_dal,		0,		x,	y+2);
			LCD_enuWriteSpecialPattern(harf_el_3een2lf,	1,	    x,	y+1);
			LCD_enuWriteSpecialPattern(harf_el_hamza,	2,		x,	y);
			
		}
		
	}

 	/* UP */
// 	Delay_MS(10);
	Get_PUSH_BUTTON_State(Push_Button4,&State4);
	if (State4 == PUSH_BUTTON_enuPressed)
	{
		Delay_MS(20);
		Get_PUSH_BUTTON_State(Push_Button4,&State4);
		if (State4 == PUSH_BUTTON_enuPressed)
		{
			x--;
			if (x > 1)
			{
				x=0;
			}
		}
		LCD_enuClearDisplay();
		LCD_enuWriteSpecialPattern(harf_el_dal,		0,		x,	y+2);
		LCD_enuWriteSpecialPattern(harf_el_3een2lf,	1,	    x,	y+1);
		LCD_enuWriteSpecialPattern(harf_el_hamza,	2,		x,	y);
	}
     }
}

