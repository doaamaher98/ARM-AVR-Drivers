#include "GPIO.h"

#define			GPIO_REG_BITS			32

// GPIO Registers for each PORT
GPIO_tstr_Registers_t * const volatile GPIO[6] = {
		/*GPIOA*/{ 0x40020000 },
		/*GPIOB*/{ 0x40020400 },
		/*GPIOC*/{ 0x40020800 },
		/*GPIOD*/{ 0x40020C00 },
		/*GPIOE*/{ 0x40021000 },
		/*GPIOH*/{ 0x40021C00 } };

GPIO_tenuErrorStatus GPIO_enuInit(GPIO_tsrt_PortConfig_t *Cpy_LocalPort_Config) {
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;

	u32 LocalMode = Cpy_LocalPort_Config->GPIO_Mode;
	u32 LocalOutputSpeed = Cpy_LocalPort_Config->GPIO_Speed;
	u16 LocalPinNumber = Cpy_LocalPort_Config->GPIO_Pin;
	u8 LocalPortNumber = Cpy_LocalPort_Config->GPIO_Port;

	u32 Local_u32RegBuffer = 0;

	u16 CurrentPinNumber = 0;

	u8 LocalIterator;

	/************** Validate *****************/
	if (LocalPortNumber > GPIO_enuNumberOfPorts) {
		LocalErrorStatus = GPIO_enuInvalidPort;
	} else if (LocalPinNumber > GPIO_enuNumberOfPins) {
		LocalErrorStatus = GPIO_enuInvalidPin;
	} else if (LocalOutputSpeed > GPIO_NUM_OF_SPEED_MODES) {
		LocalErrorStatus = GPIO_enuInvalidSpeedOption;
	} else {
		for (LocalIterator = 0; LocalIterator < GPIO_enuNumberOfPins;
				LocalIterator++) {
			// Getting the HIGH Pin
			CurrentPinNumber = ((LocalPinNumber >> LocalIterator) & 1);

			// If it's the Pin == HIGH
			if (CurrentPinNumber == GPIO_enuPin_HIGH) {
				switch (LocalPortNumber) {
				case GPIO_enuPort_A:
					/* MODE REG */
					Local_u32RegBuffer = GPIO[0]->GPIO_MODER;
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode >> 3)
							<< (LocalIterator * 2));
					GPIO[0]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[0]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 2) & 1)
															<< (LocalIterator);
					GPIO[0]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[0]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 2);
					GPIO[0]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[0]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 2));
					GPIO[0]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				case GPIO_enuPort_B:
					/* MODE REG */
					/* Setting the Register value to be in Local Buffer */
					Local_u32RegBuffer = GPIO[1]->GPIO_MODER;
					/* Shifting the Clear mask of the register by local Iterator * 2 */
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode >> 3)
							<< (LocalIterator * 2));
					GPIO[1]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[1]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 2) & 1)
															<< (LocalIterator);
					GPIO[1]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[1]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 2);
					GPIO[1]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[1]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 2));
					GPIO[1]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				case GPIO_enuPort_C:
					/* MODE REG */
					/* Setting the Register value to be in Local Buffer */
					Local_u32RegBuffer = GPIO[2]->GPIO_MODER;
					/* Shifting the Clear mask of the register by local Iterator * 2 */
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode >> 3)
							<< (LocalIterator * 2));
					GPIO[2]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[2]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 2) & 1)
															<< (LocalIterator);
					GPIO[2]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[2]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 2);
					GPIO[2]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[2]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 2));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 2));
					GPIO[2]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				case GPIO_enuPort_D:
					/* MODE REG */
					/* Setting the Register value to be in Local Buffer */
					Local_u32RegBuffer = GPIO[3]->GPIO_MODER;
					/* Shifting the Clear mask of the register by local Iterator * 3 */
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 3));
					Local_u32RegBuffer |= ((LocalMode >> 3)
							<< (LocalIterator * 3));
					GPIO[3]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[3]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 3) & 1)
															<< (LocalIterator);
					GPIO[3]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[3]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 3);
					GPIO[3]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[3]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 3));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 3));
					GPIO[3]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				case GPIO_enuPort_E:
					/* MODE REG */
					/* Setting the Register value to be in Local Buffer */
					Local_u32RegBuffer = GPIO[4]->GPIO_MODER;
					/* Shifting the Clear mask of the register by local Iterator * 4 */
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 4));
					Local_u32RegBuffer |= ((LocalMode >> 4)
							<< (LocalIterator * 4));
					GPIO[4]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[4]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 4) & 1)
															<< (LocalIterator);
					GPIO[4]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[4]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 4);
					GPIO[4]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[4]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 4));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 4));
					GPIO[4]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				case GPIO_enuPort_H:
					/* MODE REG */
					/* Setting the Register value to be in Local Buffer */
					Local_u32RegBuffer = GPIO[5]->GPIO_MODER;
					/* Shifting the Clear mask of the register by local Iterator * 5 */
					Local_u32RegBuffer &= ~(GPIO_CLR_MODE_MASK
							<< (LocalIterator * 5));
					Local_u32RegBuffer |= ((LocalMode >> 5)
							<< (LocalIterator * 5));
					GPIO[5]->GPIO_MODER = Local_u32RegBuffer;

					/* OUTPUT TYPE */
					Local_u32RegBuffer = GPIO[5]->GPIO_OTYPER;
					Local_u32RegBuffer |= ((LocalMode >> 5) & 1)
															<< (LocalIterator);
					GPIO[5]->GPIO_OTYPER = Local_u32RegBuffer;

					/* OUTPUT SPEED */
					Local_u32RegBuffer = GPIO[5]->GPIO_OSPEEDR;
					Local_u32RegBuffer |= (LocalOutputSpeed)
															<< (LocalIterator * 5);
					GPIO[5]->GPIO_OSPEEDR = Local_u32RegBuffer;

					/* PUPD */
					Local_u32RegBuffer = GPIO[5]->GPIO_PUPDR;
					LocalMode &= GPIO_CLR_PUPD_MASK;
					Local_u32RegBuffer &= ~(GPIO_CLR_PUPD_MASK
							<< (LocalIterator * 5));
					Local_u32RegBuffer |= ((LocalMode) << (LocalIterator * 5));
					GPIO[5]->GPIO_PUPDR = Local_u32RegBuffer;
					break;

				default:
					LocalErrorStatus = GPIO_enuNOK;
				}
			}

		}

	}
	return LocalErrorStatus;
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPinValue_(GPIO_tenu_Ports Cpy_u8Port,
		GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenu_PinStatus Cpy_u16Value) {
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	u32 LocalTemp;

	/************ Validatios *************/
	if (Cpy_u8Port > GPIO_enuNumberOfPorts)
	{
		LocalErrorStatus = GPIO_enuInvalidPort;
	} else if (Cpy_u8Pin > GPIO_enuNumberOfPins)
	{
		LocalErrorStatus = GPIO_enuInvalidPin;
	} else
	{
		switch (Cpy_u8Port) {
		case GPIO_enuPort_A:
			/* Check SET OR RESET Vals */

			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW)
			{
				GPIO[0]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[0]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[0]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;

		case GPIO_enuPort_B:
			/* Check SET OR RESET Vals */
			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW) {
				GPIO[1]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[1]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[1]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;

		case GPIO_enuPort_C:
			/* Check SET OR RESET Vals */
			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW) {
				GPIO[2]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[2]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[2]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;

		case GPIO_enuPort_D:
			/* Check SET OR RESET Vals */
			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW) {
				GPIO[3]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[3]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[3]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;

		case GPIO_enuPort_E:
			/* Check SET OR RESET Vals */
			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW) {
				GPIO[4]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[4]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[4]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;
			break;

		case GPIO_enuPort_H:
			/* Check SET OR RESET Vals */
			// RESET
			if (Cpy_u16Value == GPIO_enuPin_LOW) {
				GPIO[5]->GPIO_BSRR &= ~(Cpy_u8Pin);
				GPIO[5]->GPIO_BSRR |= (Cpy_u8Pin << 16);
			}

			// SET
			else if (Cpy_u16Value == GPIO_enuPin_HIGH) {
				GPIO[5]->GPIO_BSRR |= Cpy_u8Pin;
			}
			break;
		default:
			LocalErrorStatus = GPIO_enuNOK;
		}
		return LocalErrorStatus;
	}
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuGetPinValue(GPIO_tenu_Ports Cpy_u8Port,GPIO_tenu_Pins Cpy_u8Pin, u8 *Cpy_Addu8Value)
{

	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;

	u32 LocalMode;

	/************ Validatios *************/
	if (Cpy_u8Port > GPIO_enuNumberOfPorts) {
		LocalErrorStatus = GPIO_enuInvalidPort;
	} else if (Cpy_u8Pin > GPIO_enuNumberOfPins) {
		LocalErrorStatus = GPIO_enuInvalidPin;
	} else {
		switch (Cpy_u8Port) {
		case GPIO_enuPort_A:
			/* Getting Value from IDR Register */
			*Cpy_Addu8Value = (GPIO[0]->GPIO_IDR >> Cpy_u8Pin) & 1;
			break;

		case GPIO_enuPort_B:
			*Cpy_Addu8Value = (GPIO[1]->GPIO_IDR >> Cpy_u8Pin) & 1;
			break;

		case GPIO_enuPort_C:
			*Cpy_Addu8Value = (GPIO[2]->GPIO_IDR >> Cpy_u8Pin) & 1;
			break;

		case GPIO_enuPort_D:
			*Cpy_Addu8Value = (GPIO[3]->GPIO_IDR >> Cpy_u8Pin) & 1;
			break;

		case GPIO_enuPort_E:
			*Cpy_Addu8Value = (GPIO[4]->GPIO_IDR >> Cpy_u8Pin) & 1;
			break;

		case GPIO_enuPort_H:
			*Cpy_Addu8Value = (GPIO[5]->GPIO_IDR >> Cpy_u8Pin) & 1;

			break;

		default:
			LocalErrorStatus = GPIO_enuNOK;
		}
	}
	return LocalErrorStatus;
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetPortValue(GPIO_tenu_Ports Cpy_u8Port,
		GPIO_tenu_PinStatus Cpy_u8Value) {
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;
	u8 LocalIterator;

	u32 LocalTemp;
	/************ Validatios *************/
	if (Cpy_u8Port > GPIO_enuNumberOfPorts) {
		LocalErrorStatus = GPIO_enuInvalidPort;
	} else {
		switch (Cpy_u8Port) {
		case GPIO_enuPort_A:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				//for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
				GPIO[0]->GPIO_BSRR &= ~(GPIO_SET_CLR_MASK);
				GPIO[0]->GPIO_BSRR |= GPIO_SET_CLR_MASK;
				//}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				//for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
				GPIO[0]->GPIO_BSRR &= ~(GPIO_RESET_CLR_MASK);
				GPIO[0]->GPIO_BSRR |= GPIO_RESET_CLR_MASK;
				//}
			}
			break;
		case GPIO_enuPort_B:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
					GPIO[1]->GPIO_BSRR |= LocalIterator;
				}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
					GPIO[1]->GPIO_BSRR |= LocalIterator;
				}
			}
			break;

		case GPIO_enuPort_C:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
					GPIO[2]->GPIO_BSRR |= LocalIterator;
				}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
					GPIO[2]->GPIO_BSRR |= LocalIterator;
				}
			}
			break;

		case GPIO_enuPort_D:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
					GPIO[3]->GPIO_BSRR |= LocalIterator;
				}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
					GPIO[3]->GPIO_BSRR |= LocalIterator;
				}
			}
			break;

		case GPIO_enuPort_E:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
					GPIO[4]->GPIO_BSRR |= LocalIterator;
				}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
					GPIO[4]->GPIO_BSRR |= LocalIterator;
				}
			}
			break;

		case GPIO_enuPort_H:
			/* Check SET OR RESET Vals */
			// SET
			if (Cpy_u8Value == GPIO_enuPin_HIGH) {
				for (LocalIterator = 0; LocalIterator < 16; LocalIterator++) {
					GPIO[5]->GPIO_BSRR |= LocalIterator;
				}
			}
			// RESET
			else if (Cpy_u8Value == GPIO_enuPin_LOW) {
				for (LocalIterator = 16; LocalIterator < 32; LocalIterator++) {
					GPIO[5]->GPIO_BSRR |= LocalIterator;
				}
			}

			break;
		default:
			LocalErrorStatus = GPIO_enuNOK;
		}
	}
	return LocalErrorStatus;
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetAlternateFunctionLow(GPIO_tenu_Ports Cpy_u8Port,
		GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenuAlternativeFunctionLow Cpy_u8AF) {

	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;

	u8 LocalIterator;
	u32 LocalAFLow;
	/************************ Validation *******************************/
	if (Cpy_u8Port >= GPIO_enuPort_A && Cpy_u8Port < GPIO_enuNumberOfPorts) {
		if (Cpy_u8Pin >= GPIO_enuPin_0 && Cpy_u8Pin < GPIO_enuNumberOfPins) {
			if (Cpy_u8AF >= GPIO_enu_AF_LOW_0
					&& Cpy_u8AF <= GPIO_enu_AF_LOW_15) {
				// Alternate Function Low Register
				for (LocalIterator = 0; LocalIterator < 8; LocalIterator++) {
					if ((Cpy_u8Pin >> LocalIterator) & 1 == GPIO_enuPin_HIGH) {
						switch (Cpy_u8Port) {
						case GPIO_enuPort_A:
							GPIO[0]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_B:
							GPIO[1]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_C:
							GPIO[2]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_D:
							GPIO[3]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_E:
							GPIO[4]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_H:
							GPIO[5]->GPIO_AFRL |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;
						}
					}
				}
			} else {
				LocalErrorStatus = GPIO_enuInvalidAlternative_Function;
			}
		} else {
			LocalErrorStatus = GPIO_enuInvalidPin;
		}
	} else {
		LocalErrorStatus = GPIO_enuInvalidPort;
	}
	return LocalErrorStatus;
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetAlternateFunctionHigh(
		GPIO_tenu_Ports Cpy_u8Port, GPIO_tenu_Pins Cpy_u8Pin,
		GPIO_tenuAlternativeFunctionHigh Cpy_u8AF) {

	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;

	u8 LocalIterator;
	u32 LocalAFHigh;
	/************************ Validation *******************************/
	if (Cpy_u8Port >= GPIO_enuPort_A && Cpy_u8Port < GPIO_enuNumberOfPorts) {
		if (Cpy_u8Pin >= GPIO_enuPin_0 && Cpy_u8Pin < GPIO_enuNumberOfPins) {
			if (Cpy_u8AF >= GPIO_enu_AF_HIGH_0
					&& Cpy_u8AF <= GPIO_enu_AF_HIGH_15) {
				// Alternate Function Low Register
				for (LocalIterator = 0; LocalIterator < 8; LocalIterator++) {
					if ((Cpy_u8Pin >> LocalIterator) & 1 == GPIO_enuPin_HIGH) {
						switch (Cpy_u8Port) {
						case GPIO_enuPort_A:
							GPIO[0]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_B:
							GPIO[1]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_C:
							GPIO[2]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_D:
							GPIO[3]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_E:
							GPIO[4]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;

						case GPIO_enuPort_H:
							GPIO[5]->GPIO_AFRH |= (Cpy_u8AF
									<< (LocalIterator * 4));
							break;
						}
					}
				}
			} else {
				LocalErrorStatus = GPIO_enuInvalidAlternative_Function;
			}
		} else {
			LocalErrorStatus = GPIO_enuInvalidPin;
		}
	} else {
		LocalErrorStatus = GPIO_enuInvalidPort;
	}
	return LocalErrorStatus;
}
/************************************************************************************/
GPIO_tenuErrorStatus GPIO_enuSetMultiplePins(GPIO_tenu_Ports Cpy_u8Port,
		GPIO_tenu_Pins Cpy_u8Pin, GPIO_tenu_PinStatus Cpy_u8Value) {
	GPIO_tenuErrorStatus LocalErrorStatus = GPIO_enuOK;

	u32 LocalBuffer = 0;

	u8 LocalIterator;
	u8 LocalIterator2;
	u16 CurrentLocation = 0;

	if (Cpy_u8Port >= GPIO_enuPort_A && Cpy_u8Port <= GPIO_enuNumberOfPorts) {
		if (Cpy_u8Pin >= GPIO_enuPin_0 && Cpy_u8Pin <= GPIO_enuNumberOfPins) {
			switch (Cpy_u8Port) {
			case GPIO_enuPort_A:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[0]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[0]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			case GPIO_enuPort_B:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[1]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[1]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			case GPIO_enuPort_C:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[2]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[2]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			case GPIO_enuPort_D:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[3]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[3]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			case GPIO_enuPort_E:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[4]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[4]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			case GPIO_enuPort_H:
				// Set
				if (Cpy_u8Value == GPIO_enuPin_HIGH) {
					GPIO[5]->GPIO_BSRR |= Cpy_u8Pin;
				}

				// RESET
				if (Cpy_u8Value == GPIO_enuPin_LOW) {
					GPIO[5]->GPIO_BSRR |= (Cpy_u8Pin + 16);
				}
				break;

			}
		} else {
			LocalErrorStatus = GPIO_enuInvalidPin;
		}
	} else {
		LocalErrorStatus = GPIO_enuInvalidPort;
	}

	return LocalErrorStatus;
}
/************************************************************************************/
