/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 16 JAN 2023                             */
/* Version   : V.02                                    */
/* Target    : AVR32								   */
/* Descrip.   : C File with the DIO Functions &		   */
/*				Checking their Saftey.				   */
/*******************************************************/
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"

#include "DIO.h"
#include "DIO_Cfg.h"
#include "DIO_Priv.h"

#define 			REG_BITS					8				// For not using Magic Numbers
/****************************************************************/
/*    DIO Init Function											*/
/*	  Input  : void												*/
/*	  Output : DIO_tenuErrorStatus to Report Errors				*/
/****************************************************************/
DIO_tenuErrorStatus DIO_enuInit (void)
{
	DIO_tenuErrorStatus Local_ErrorStatus = DIO_enuOK;      	// Assuming the current status is OK
	
	u8 Local_Iterator;
	u8 Loc_u8PortNumber = 0;
	u8 Loc_u8PinNumber  = 0;
	
	for (Local_Iterator = 0; Local_Iterator < DIO_enuNumberOfPins ; Local_Iterator++)
	{
		Loc_u8PortNumber = Local_Iterator/REG_BITS;   // PORT NUMBER
		Loc_u8PinNumber  = Local_Iterator%REG_BITS;   // PIN NUMBER
		
		/**************************** VALIDATION ***************************/
		if(Loc_u8PortNumber > DIO_enuNumberOfPorts)
		{
			Local_ErrorStatus = DIO_enuInvalidPortNum;
		}
		else if (Loc_u8PinNumber > DIO_enuNumberOfPins)
		{
			Local_ErrorStatus = DIO_enuInvalidPinNum;
		}
		/*******************************************************************/
		else if (Local_ErrorStatus == DIO_enuOK)
		{
			// Switching on the ports [A,B,C OR D]
			switch (Loc_u8PortNumber)
			{
				/****************************** PORTA ***************************************/
				case (DIO_enuPORTA):
				// Switching on the pin's Direction [INPUT OR OUTPUT]
				switch (DIO_strPinCfg[Local_Iterator].DIO_strPinDirection)
				{
					/**************************** OUTPUT **************************************/
					case (DIO_enuOUTPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputLow)
					{
						// OUTPUT PIN
						SET_BIT(DDRA, Loc_u8PinNumber);
						// MODE : LOW
						CLR_BIT(PORTA, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputHigh)
					{
						// OUTPUT PIN
						SET_BIT(DDRA, Loc_u8PinNumber);
						// MODE : LOW
						SET_BIT(PORTA, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
					
					/**************************** INPUT **************************************/
					case (DIO_enuINPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinPullUp)
					{
						// INPUT PIN
						CLR_BIT(DDRA, Loc_u8PinNumber);
						// MODE : PULL UP
						SET_BIT(PORTA, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinHighImp)
					{
						// INPUT PIN
						CLR_BIT(DDRA, Loc_u8PinNumber);
						// MODE : HIGH IMPEDANCE
						CLR_BIT(PORTA, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
				}
				
				/****************************** PORTB ***************************************/
				case (DIO_enuPORTB):
				// Switching on the pin's Direction [INPUT OR OUTPUT]
				switch (DIO_strPinCfg[Local_Iterator].DIO_strPinDirection)
				{
					/**************************** OUTPUT **************************************/
					case (DIO_enuOUTPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputLow)
					{
						// OUTPUT PIN
						SET_BIT(DDRB, Loc_u8PinNumber);
						// MODE : LOW
						CLR_BIT(PORTB, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputHigh)
					{
						// OUTPUT PIN
						SET_BIT(DDRB, Loc_u8PinNumber);
						// MODE : LOW
						SET_BIT(PORTB, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
					
					/**************************** INPUT **************************************/
					case (DIO_enuINPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinPullUp)
					{
						// INPUT PIN
						CLR_BIT(DDRB, Loc_u8PinNumber);
						// MODE : PULL UP
						SET_BIT(PORTB, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinHighImp)
					{
						// INPUT PIN
						CLR_BIT(DDRB, Loc_u8PinNumber);
						// MODE : HIGH IMPEDANCE
						CLR_BIT(PORTB, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
				}
				/****************************** PORTC ***************************************/
				case (DIO_enuPORTC):
				// Switching on the pin's Direction [INPUT OR OUTPUT]
				switch (DIO_strPinCfg[Local_Iterator].DIO_strPinDirection)
				{
					/**************************** OUTPUT **************************************/
					case (DIO_enuOUTPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputLow)
					{
						// OUTPUT PIN
						SET_BIT(DDRC, Loc_u8PinNumber);
						// MODE : LOW
						CLR_BIT(PORTC, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputHigh)
					{
						// OUTPUT PIN
						SET_BIT(DDRC, Loc_u8PinNumber);
						// MODE : LOW
						SET_BIT(PORTC, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
					
					/**************************** INPUT **************************************/
					case (DIO_enuINPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinPullUp)
					{
						// INPUT PIN
						CLR_BIT(DDRC, Loc_u8PinNumber);
						// MODE : PULL UP
						SET_BIT(PORTC, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinHighImp)
					{
						// INPUT PIN
						CLR_BIT(DDRC, Loc_u8PinNumber);
						// MODE : HIGH IMPEDANCE
						CLR_BIT(PORTC, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
				}
				
				/****************************** PORTD ***************************************/
				case (DIO_enuPORTD):
				// Switching on the Pin's Direction [INPUT OR OUTPUT]
				switch (DIO_strPinCfg[Local_Iterator].DIO_strPinDirection)
				{
					/**************************** OUTPUT **************************************/
					case (DIO_enuOUTPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputLow)
					{
						// OUTPUT PIN
						SET_BIT(DDRD, Loc_u8PinNumber);
						// MODE : LOW
						CLR_BIT(PORTD, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuOutputHigh)
					{
						// OUTPUT PIN
						SET_BIT(DDRD, Loc_u8PinNumber);
						// MODE : LOW
						SET_BIT(PORTD, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
					
					/**************************** INPUT **************************************/
					case (DIO_enuINPUT):
					if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinPullUp)
					{
						// INPUT PIN
						CLR_BIT(DDRD, Loc_u8PinNumber);
						// MODE : PULL UP
						SET_BIT(PORTD, Loc_u8PinNumber);
					}
					else if (DIO_strPinCfg[Local_Iterator].DIO_strPinMode == DIO_enuInputPinHighImp)
					{
						// INPUT PIN
						CLR_BIT(DDRD, Loc_u8PinNumber);
						// MODE : HIGH IMPEDANCE
						SET_BIT(PORTD, Loc_u8PinNumber);
					}
					else
					Local_ErrorStatus = DIO_enuInvalidValue;
					break;
				}
			}
		}
		else
		Local_ErrorStatus = DIO_enuNOK;
	}
	return Local_ErrorStatus;
}

/***************************************************************/
/*    DIO Set PIN Function									  */
/*	  Input  : Pin Number (Range from 0-31)					  */
/*	  Output : DIO_tenuErrorStatus to Report Errors			  */
/***************************************************************/
DIO_tenuErrorStatus DIO_enuSetPin (DIO_tenuPins Cpy_enuPinNumber)
{
	DIO_tenuErrorStatus Local_ErrorStatus = DIO_enuOK;      	// Assuming the current status is OK
	
	u8 Loc_u8PortNumber = Cpy_enuPinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_enuPinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > DIO_enuNumberOfPorts)
	{
		Local_ErrorStatus = DIO_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > DIO_enuNumberOfPins)
	{
		Local_ErrorStatus = DIO_enuInvalidPinNum;
	}
	/*******************************************************************/
	else if (Local_ErrorStatus == DIO_enuOK)
	{
		switch(Loc_u8PortNumber)
		{
			case DIO_enuPORTA:
			SET_BIT(PORTA, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTB:
			SET_BIT(PORTB, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTC:
			SET_BIT(PORTC, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTD:
			SET_BIT(PORTD, Loc_u8PinNumber);
			break;
		}
	}
	else
	{
		Local_ErrorStatus = DIO_enuNOK;
	}
	return Local_ErrorStatus;
}

/****************************************************************/
/*    DIO Clear Pin Function									*/
/*	  Input  : Pin Number (Range from 0-31)						*/
/*	  Output : DIO_tenuErrorStatus to Report Errors				*/
/****************************************************************/
DIO_tenuErrorStatus DIO_enuClearPin (DIO_tenuPins Cpy_enuPinNumber)
{
	DIO_tenuErrorStatus Local_ErrorStatus = DIO_enuOK;      	// Assuming the current status is OK
	
	u8 Loc_u8PortNumber = Cpy_enuPinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_enuPinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > DIO_enuNumberOfPorts)
	{
		Local_ErrorStatus = DIO_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > DIO_enuNumberOfPins)
	{
		Local_ErrorStatus = DIO_enuInvalidPinNum;
	}
	/*******************************************************************/
	else if (Local_ErrorStatus == DIO_enuOK)
	{
		switch(Loc_u8PortNumber)
		{
			case DIO_enuPORTA:
			CLR_BIT(PORTA, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTB:
			CLR_BIT(PORTB, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTC:
			CLR_BIT(PORTC, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTD:
			CLR_BIT(PORTD, Loc_u8PinNumber);
			break;
		}
	}
	else
	{
		Local_ErrorStatus = DIO_enuNOK;
	}
	return Local_ErrorStatus;
}

/************************************************************************************************/
/*    DIO Get Pin Function																		*/
/*	  Inputs : Pin Number (Range from 0-31), The Address of the Pin Value that needs to be get  */
/*	  Output : DIO_tenuErrorStatus to Report Errors												*/
/************************************************************************************************/
DIO_tenuErrorStatus DIO_enuGetPin (DIO_tenuPins Cpy_enuPinNumber, u8 *Add_u8PinValue)
{
	DIO_tenuErrorStatus Local_ErrorStatus = DIO_enuOK;      	// Assuming the current status is OK
	
	u8 Loc_u8PortNumber = Cpy_enuPinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_enuPinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > DIO_enuNumberOfPorts)
	{
		Local_ErrorStatus = DIO_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > DIO_enuNumberOfPins)
	{
		Local_ErrorStatus = DIO_enuInvalidPinNum;
	}
	else if (Add_u8PinValue == NULL)
	{
		Local_ErrorStatus = DIO_enuNULLPtr;
	}
	else if (Local_ErrorStatus == DIO_enuOK)
	{
		switch(Loc_u8PortNumber)
		{
			case DIO_enuPORTA:
			*Add_u8PinValue = GET_BIT(PINA, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTB:
			*Add_u8PinValue = GET_BIT(PINB, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTC:
			*Add_u8PinValue = GET_BIT(PINC, Loc_u8PinNumber);
			break;
			
			case DIO_enuPORTD:
			*Add_u8PinValue = GET_BIT(PIND, Loc_u8PinNumber);
			break;
		}
	}
	else
	{
		Local_ErrorStatus = DIO_enuNOK;
	}
	
	return Local_ErrorStatus;
}

/************************************************************************************************/
/*    DIO Get Port Function																		*/
/*	  Inputs : Port Number (Range from 0-3), The Address of the Port Value that needs to be get */
/*	  Output : DIO_tenuErrorStatus to Report Errors												*/
/************************************************************************************************/
DIO_tenuErrorStatus DIO_enuSetPort (DIO_tenuPort Cpy_enuPortNumber, u8 Cpy_AssignedPortVal)
{
	u8 Local_ErrorStatus = DIO_enuOK;            // Setting Status to be OK by default
	
	/**************************** VALIDATION ***************************/
	if(Cpy_enuPortNumber > DIO_enuPORTD)
	{
		Local_ErrorStatus = DIO_enuInvalidPortNum;
	}

	else if (Local_ErrorStatus == DIO_enuOK)
	{
		switch(Cpy_enuPortNumber)
		{
			case DIO_enuPORTA:
			PORTA=Cpy_AssignedPortVal;
			break;
			
			case DIO_enuPORTB:
			PORTB=Cpy_AssignedPortVal;
			break;
			
			case DIO_enuPORTC:
			PORTC=Cpy_AssignedPortVal;
			break;
			
			case DIO_enuPORTD:
			PORTD=Cpy_AssignedPortVal;
			break;
			default :
			break;
		}
	}
	
	return Local_ErrorStatus;
}

/*********************************************************************/
/***************************************************************/
/*    DIO Set PIN Value Function							  */
/*	  Input  : Pin Number (Range from 0-31)					  */
/*			   & Value (HIGH or LOW							  */
/*	  Output : DIO_tenuErrorStatus to Report Errors			  */
/***************************************************************/
/* To be used in Keypad Driver */
DIO_tenuErrorStatus DIO_enuSetPinValue (DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinMode Cpy_enuPinValue)
{
	DIO_tenuErrorStatus Local_ErrorStatus = DIO_enuOK;
	
	u8 Loc_u8PortNumber = Cpy_enuPinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_enuPinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > DIO_enuNumberOfPorts)
	{
		Local_ErrorStatus = DIO_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > DIO_enuNumberOfPins)
	{
		Local_ErrorStatus = DIO_enuInvalidPinNum;
	}
	else
	{
		switch (Loc_u8PortNumber)
		{	
			case DIO_enuPORTA:
				if (Cpy_enuPinValue == DIO_enuOutputHigh)
				{
					SET_BIT(PORTA,Loc_u8PinNumber);
				}
				else if (Cpy_enuPinValue == DIO_enuOutputLow)
				{
					CLR_BIT(PORTA,Loc_u8PinNumber);
				}
				else
				{
					Local_ErrorStatus = DIO_enuNOK;
				}
				break;
			
			case DIO_enuPORTB:
				if (Cpy_enuPinValue == DIO_enuOutputHigh)
				{
					SET_BIT(PORTB,Loc_u8PinNumber);
				}
				else if (Cpy_enuPinValue == DIO_enuOutputLow)
				{
					CLR_BIT(PORTB,Loc_u8PinNumber);
				}
				else
				{
					Local_ErrorStatus = DIO_enuNOK;
				}
				break;
			
			
			case DIO_enuPORTC:
				if (Cpy_enuPinValue == DIO_enuOutputHigh)
				{
					SET_BIT(PORTC,Loc_u8PinNumber);
				}
				else if (Cpy_enuPinValue == DIO_enuOutputLow)
				{
					CLR_BIT(PORTC,Loc_u8PinNumber);
				}
				else
				{
					Local_ErrorStatus = DIO_enuNOK;
				}
				break;
			
			case DIO_enuPORTD:
				if (Cpy_enuPinValue == DIO_enuOutputHigh)
				{
					SET_BIT(PORTD,Loc_u8PinNumber);
				}
				else if (Cpy_enuPinValue == DIO_enuOutputLow)
				{
					CLR_BIT(PORTD,Loc_u8PinNumber);
				}
				else
				{
					Local_ErrorStatus = DIO_enuNOK;
				}
				break;
				
			default:
				Local_ErrorStatus = DIO_enuInvalidPortNum;		
		}
	}
	
	return Local_ErrorStatus;
}