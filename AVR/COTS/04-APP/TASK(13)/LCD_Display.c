#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"

#include "../02-HAL/LCD.h"

u8 boy_hands_up[8] =
{
	0b00000,
	0b01110,
	0b01110,
	0b10101,
	0b01110,
	0b00100,
	0b01010,
	0b00000
};

u8 boy_hands_down[8] =
{
	0b00000,
	0b01110,
	0b01110,
	0b00100,
	0b01110,
	0b10101,
	0b01010,
	0b00000
};



int main(void)
{
	DIO_enuInit();
	
	LCD_vidInit();
    
	LCD_enuWriteString("Asteroids ");
	LCD_enuWriteNumber(43);
	
	// Moving to second row
	LCD_enuGotoXY(1,0);
	
	LCD_enuWriteString("Doaa Maher");
	Delay_MS(500);
	
	u8 i,j;
	
	LCD_enuClearDisplay();
    while (1) 
    {
		for (i=0; i<16;i++)
		{
			for (j=0; j<2; j++)
			{
				LCD_enuWriteSpecialPattern(boy_hands_up,0,j,i);
				LCD_enuWriteSpecialPattern(boy_hands_up,0,j,i);
				
				//Delay_MS(50);
				LCD_enuWriteSpecialPattern(boy_hands_down,0,j,i);
				LCD_enuWriteSpecialPattern(boy_hands_up,0,j,i);
				
				Delay_MS(50);
			}
			
		}
    }
}

