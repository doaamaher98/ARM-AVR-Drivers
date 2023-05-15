#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"

#include "../02-HAL/PUSH_BUTTON.h"
#include "../02-HAL/LCD.h"

u8 stick_left[8]=
{
	0b00000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b00000
};

u8 stick_right[8]=
{
	0b00000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b00000
};

u8 ball[8]=
{
	  0b00000,
	  0b00000,
	  0b01110,
	  0b01110,
	  0b00000,
	  0b00000,
	  0b00000,
	  0b00000
};

int main(void)
{
	DIO_enuInit();
	LCD_vidInit();
	
	u8 Push_Button1 = PUSH_BUTTON_enuPin16;			/* LEFT */
	u8 Push_Button2 = PUSH_BUTTON_enuPin17;			/* RIGHT */
	
	u8 State1=0;
	u8 State2=0;
	
	////////////////////////////////////
	u8 x_left=0;
	
	u8 x_right=0;
	
	u8 x_ball=0;
	u8 y_ball=8;
	////////////////////////////////////
	
	u8 Score_left=0;
	u8 Score_right=0;
	
	// 1 : Forward, 0 : Reverse
	u8 Flag= 1;   
	
	// Starting
	LCD_enuClearDisplay();
	LCD_enuGotoXY(0,6);
	LCD_enuWriteString("NEW");
	LCD_enuGotoXY(1,6);
	LCD_enuWriteString("GAME");
	Delay_MS(2000);
	
	// By default Locations
	LCD_enuWriteSpecialPattern(stick_left,		0,		x_left,		14);
	LCD_enuWriteSpecialPattern(stick_right,		1,	    x_right,	1);
	LCD_enuWriteSpecialPattern(ball,			2,		0,			8);
	
	/* Replace with your application code */
	while (1)
	{	
		LCD_enuClearDisplay();
		
		// Right Score Location		
		LCD_enuGotoXY(0,13);
		LCD_enuWriteNumber(Score_right);
		
		// Left Score Location
		LCD_enuGotoXY(0,2);
		LCD_enuWriteNumber(Score_left);
		
		
		LCD_enuWriteSpecialPattern(stick_left,		0,		x_left,		14);
		LCD_enuWriteSpecialPattern(stick_right,		1,	    x_right,	1);
		LCD_enuWriteSpecialPattern(ball,			2,		x_ball,		y_ball);
		
		// Left Stick Button
		Get_PUSH_BUTTON_State(Push_Button1,&State1);
		if (State1 == PUSH_BUTTON_enuPressed)
		{
			Delay_MS(10);
			Get_PUSH_BUTTON_State(Push_Button1,&State1);
			if (State1 == PUSH_BUTTON_enuPressed)
			{
				x_left++;
				if (x_left > 1)
				{
					x_left=0;
				}
			}
		}

		// Right Stick Button
		Get_PUSH_BUTTON_State(Push_Button2,&State2);
		if (State2 == PUSH_BUTTON_enuPressed)
		{
			Delay_MS(10);
			Get_PUSH_BUTTON_State(Push_Button2,&State2);
			if (State2 == PUSH_BUTTON_enuPressed)
			{
				x_right++;
				if (x_right > 1)
				{
					x_right=0;
				}
			}
		}
		
		// Check boundaries & increment the ball's position
		
		// 1- Moving Right
		if ((y_ball > 2) && (y_ball < 14))
		{
			// MOVING FORWARD
			if (Flag == 1)
			{
				y_ball ++;
			}
			// MOVING REVERSE
			else 
			{
				y_ball --;
			}
			
			// Toggling X
			x_ball ^= 1;
		}
		
		///////// GOING FORWARD ///////////
		else if (y_ball == 2)
		{
			if (Flag == 0)
			{
				Flag = 1;
			}
			else 
			{
				/*Do Nothing*/
			}
			// Increment y_ball
			y_ball ++;
			// Toggling X
			x_ball ^= 1;
		}
		
		///////// GOING BACK ///////////
		else if (y_ball == 14)
		{
			// If forward make it Reverse
			if (Flag == 1)
			{
				Flag =0;
			}
			
			else
			{
				/*Do Nothing*/
			}
			
			// Decrement y_ball
			y_ball --;
			// Toggling X
			x_ball ^= 1;
		}	
		
		
		/////////////// RIGHT SCORES //////////////////
		if ((y_ball == 2) && (x_ball != x_right))
		{
			Score_right++;
			// Return X & Y of ball 
			x_ball = 0;
			y_ball = 2;
		}
		
		/////////////// LEFT SCORES //////////////////
		if ((y_ball == 14) && (x_ball != x_left))
		{
			Score_left++;
			// Return X & Y of ball 
			x_ball = 0;
			y_ball = 14;
		}
		
		
		//////////////////// WINNER ////////////////////
		if (Score_right == 5)
		{
			LCD_enuClearDisplay();
			LCD_enuGotoXY(0,2);
			LCD_enuWriteString("Right is the");
			LCD_enuGotoXY(1,4);
			LCD_enuWriteString("WINNER!");
			Delay_MS(5000);
			// Reset the Score
			Score_right = 0;
		}
		
		if (Score_left == 5)
		{
			LCD_enuClearDisplay();
			LCD_enuGotoXY(0,2);
			LCD_enuWriteString("Left is the");
			LCD_enuGotoXY(1,4);
			LCD_enuWriteString("WINNER!");
			// Reset the Score
			Score_left =0;
			Delay_MS(5000);
		}
	}
	
	
}
