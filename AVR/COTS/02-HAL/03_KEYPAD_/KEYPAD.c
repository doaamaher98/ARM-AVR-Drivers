
#include "Std_Types.h"
#include "Bit_Math.h"

#include "Delay.h"
#include "DIO.h"

#include "KEYPAD_Cfg.h"
#include "KEYPAD.h"
#include "KEYPAD_Prv.h"

/*void HAL_KEYPAD_INIT (void)	{}*/
	
	
KEYPAD_tenuErrorStatus HAL_GET_KEYPAD_KEY (u8 * Cpy_Addu8PinValue)
{
	KEYPAD_tenuErrorStatus LocalErrorStatus = KEYPAD_enuOK;
	
	u8 Iterator_r,Iterator_c;
	u8 Status ;
	
	/*********************** VALIDATON *****************************/
	if (Cpy_Addu8PinValue == NULL_PTR)
	{
		LocalErrorStatus = KEYPAD_enuNullPtr;
	}
	else
	{		
		for (Iterator_r=0; Iterator_r < Keypad_enuNumberOfRows ; Iterator_r ++)
		{
			// Assuming Each row to be LOW, to check the cols value
			DIO_enuSetPinValue(Keypad_tstrRowsConfig[Iterator_r].strRow_Pin, DIO_enuOutputLow);
			
			for (Iterator_c=0; Iterator_c < Keypad_enuNumberOfCols; Iterator_c++)
			{
				Delay_MS(50);
				
				DIO_enuGetPin(Keypad_tstrColsConfig[Iterator_c].strCol_Pin, &Status);
				if (Status == Keypad_tstrColsConfig[Iterator_c].strCol_Mode)
				{
					*Cpy_Addu8PinValue = Keypad_Pin_Vals[Iterator_r][Iterator_c];
				}
				else
				{
					LocalErrorStatus = KEYPAD_enuNOK;
				}
			}
			// Returning the Row pin to HIGH
			DIO_enuSetPinValue(Keypad_tstrRowsConfig[Iterator_r].strRow_Pin, DIO_enuOutputHigh);
		}
		
	}
	
	return LocalErrorStatus;
}