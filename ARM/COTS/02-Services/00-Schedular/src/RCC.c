/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 20 FEB 2023                             */
/* Version   : V.01                                    */
/* Target    : STM32								   */
/* Descrip.   : C File for RCC Driver ARM Cortex M4    */
/*******************************************************/
#include "RCC.h"

/* Defining a constant pointer [RCC] to start from the base address of the RCC. */
RCC_tstrRegisters_t * const volatile RCC = (RCC_tstrRegisters_t *) 0x40023800;

/*********************************** APIs ************************************/
RCC_tenuErrorStatus RCC_enuSelectSysClk(RCC_tenuSysClkSource Cpy_SysClk) {

	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	/* Local variable to hold the register data */
	u32 LocalTemp;
	/* Timeout variable for safety */
	u16 Local_u32TIMEOUT = 0;

	/* Validation */
	if (Cpy_SysClk >= RCC_enu_HSI && Cpy_SysClk < RCC_enu_NumerOfClkSources) {
		switch (Cpy_SysClk) {

		case RCC_enu_HSI:
			/* Select SW */
			/* Clear the bits */
			LocalTemp = RCC->RCC_CFGR;
			LocalTemp &= RCC_SW_MASK;
			LocalTemp |= RCC_SW_HSI;
			RCC->RCC_CFGR = LocalTemp;

			while (((((RCC->RCC_CFGR)&RCC_SWS_MASK) >> 2) != RCC_enu_HSI)
					&& Local_u32TIMEOUT < 10000) {
				Local_u32TIMEOUT++;
			}
			if (Local_u32TIMEOUT >= 10000) {
				LocalErrorStatus = RCC_enuTIMEOUT;
			}

			break;

		case RCC_enu_HSE:
			/* Select SW */
			/* Clear the bits */
			LocalTemp = RCC->RCC_CFGR;
			LocalTemp &= RCC_SW_MASK;
			LocalTemp |= RCC_SW_HSE;
			RCC->RCC_CFGR = LocalTemp;

			while (((((RCC->RCC_CFGR)&RCC_SWS_MASK) >> 2) != RCC_enu_HSE)
					&& Local_u32TIMEOUT < 10000) {
				Local_u32TIMEOUT++;
			}
			if (Local_u32TIMEOUT >= 10000) {
				LocalErrorStatus = RCC_enuTIMEOUT;
			}

			break;

		case RCC_enu_PLL:
			/* Select SW */
			/* Clear the bits */
			LocalTemp = RCC->RCC_CFGR;
			LocalTemp &= RCC_SW_MASK;
			LocalTemp |= RCC_SW_PLL;
			RCC->RCC_CFGR = LocalTemp;

			while (((((RCC->RCC_CFGR)&RCC_SWS_MASK) >> 2) != RCC_enu_PLL)
					&& Local_u32TIMEOUT < 10000) {
				Local_u32TIMEOUT++;
			}
			if (Local_u32TIMEOUT >= 10000) {
				LocalErrorStatus = RCC_enuTIMEOUT;
			}

			break;

		default:
			LocalErrorStatus = RCC_enuInvalidClockSource;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidClockSource;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuEnableSysClk(RCC_tenuSysClkSource Cpy_SysClk) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	/* Local variable to hold the register data */
	u32 LocalTemp = RCC->RCC_CR;

	/* Validation */
	if (Cpy_SysClk >= RCC_enu_HSI && Cpy_SysClk < RCC_enu_NumerOfClkSources) {
		switch (Cpy_SysClk) {

		case RCC_enu_HSI:
			LocalTemp &= RCC_HSI_CLR_MASK;
			LocalTemp |= RCC_HSI_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuHSI_Enabled;
			break;

		case RCC_enu_HSE:
			LocalTemp &= RCC_HSE_CLR_MASK;
			LocalTemp |= RCC_HSE_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuHSE_Enabled;
			break;

		case RCC_enu_PLL:
			LocalTemp &= RCC_PLL_CLR_MASK;
			LocalTemp |= RCC_PLL_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuPLL_Enabled;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidClockSource;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidClockSource;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuDisableSysClk(RCC_tenuSysClkSource Cpy_SysClk) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	/* Local variable to hold the register data */
	u32 LocalTemp = RCC->RCC_CR;

	/* Validation */
	if (Cpy_SysClk >= RCC_enu_HSI && Cpy_SysClk < RCC_enu_NumerOfClkSources) {
		switch (Cpy_SysClk) {
		case RCC_enu_HSI:
			LocalTemp &= RCC_HSI_CLR_MASK;
			LocalTemp |= RCC_HSI_OFF_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuHSI_Disabled;
			break;

		case RCC_enu_HSE:
			LocalTemp &= RCC_HSE_CLR_MASK;
			LocalTemp |= RCC_HSE_OFF_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuHSE_Disabled;
			break;

		case RCC_enu_PLL:
			LocalTemp &= RCC_PLL_CLR_MASK;
			LocalTemp |= RCC_PLL_OFF_MASK;
			RCC->RCC_CR = LocalTemp;
			LocalErrorStatus = RCC_enuPLL_Disabled;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidClockSource;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidClockSource;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuCheckClkReady(RCC_tenuSysClkSource Cpy_SysClk,
		u8 Cpy_u8ClkStatus) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	u16 LocalTIMEOUT = 0;

	/* Validation */
	if (Cpy_SysClk >= RCC_enu_HSI && Cpy_SysClk < RCC_enu_NumerOfClkSources) {
		switch (Cpy_SysClk) {
		case RCC_enu_HSI:

			/* If HSI Ready */
			if ((RCC->RCC_CR & RCC_HSI_RDY) == RCC_HSI_RDY) {
				Cpy_u8ClkStatus = RCC_enuClock_RDY;
				LocalErrorStatus = RCC_enuHSI_READY;
			}
			/* If HSI not Ready make a timeout */
			else {
				LocalErrorStatus = RCC_enuHSI_NOTRDY;
			}
			break;

		case RCC_enu_HSE:

			/* If HSE Ready */
			if ((RCC->RCC_CR & RCC_HSE_RDY) == RCC_HSE_RDY) {
				Cpy_u8ClkStatus = RCC_enuClock_RDY;
				LocalErrorStatus = RCC_enuHSE_READY;
			}
			/* If HSE not Ready */
			else {
				Cpy_u8ClkStatus = RCC_enuClock_NOTRDY;
			}
			break;

		case RCC_enu_PLL:
			/* If PLL Ready */
			if ((RCC->RCC_CR & RCC_PLL_RDY) == RCC_PLL_RDY) {
				Cpy_u8ClkStatus = RCC_enuClock_RDY;
				LocalErrorStatus = RCC_enuPLL_READY;
			}
			/* If PLL not Ready */
			else {
				Cpy_u8ClkStatus = RCC_enuClock_NOTRDY;
			}
			break;

		default:
			LocalErrorStatus = RCC_enuClock_NOTRDY;
		}
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuGetRunningClk(u32 *Cpy_AddRunningClk) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;

	u32 LocalTemp = RCC->RCC_CFGR;

	/* Clearing Mask */
	LocalTemp &= RCC_SWS_MASK;
	LocalTemp = (LocalTemp >> 2);

	if (Cpy_AddRunningClk == NULL_PTR) {
		LocalErrorStatus = RCC_enuNullPointer;
	} else {
		// HSI
		if (LocalTemp == RCC_SWS_HSI) {
			*Cpy_AddRunningClk = RCC_enu_HSI;
			// HSE
		} else if (LocalTemp == RCC_SWS_HSE) {
			*Cpy_AddRunningClk = RCC_enu_HSE;
			// PLL
		} else if (LocalTemp == RCC_SWS_PLL) {
			*Cpy_AddRunningClk = RCC_enu_PLL;
		} else {
			LocalErrorStatus = RCC_enuInvalidClockSource;
		}
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_AHB(
		RCC_tenuAHB_Prescalers Cpy_u32AHB_Prescaler) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	u32 LocalTemp = RCC->RCC_CFGR;

	/*** Validation ***/
	if (Cpy_u32AHB_Prescaler >= RCC_enuAHB_Prescaler_2
			&& Cpy_u32AHB_Prescaler < RCC_enuAHB_NumberOfPrescalers) {
		switch (Cpy_u32AHB_Prescaler) {
		case RCC_enuAHB_Prescaler_2:
			LocalTemp &= RCC_enuAHB_Prescaler2_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler2_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_4:
			LocalTemp &= RCC_enuAHB_Prescaler4_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler4_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_8:
			LocalTemp &= RCC_enuAHB_Prescaler8_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler8_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_16:
			LocalTemp &= RCC_enuAHB_Prescaler16_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler16_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_64:
			LocalTemp &= RCC_enuAHB_Prescaler64_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler64_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_128:
			LocalTemp &= RCC_enuAHB_Prescaler128_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler128_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_256:
			LocalTemp &= RCC_enuAHB_Prescaler256_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler256_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAHB_Prescaler_512:
			LocalTemp &= RCC_enuAHB_Prescaler512_MASK_CLR;
			LocalTemp |= RCC_enuAHB_Prescaler512_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAHB_Prescaler;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidAHB_Prescaler;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_APB1(
		RCC_tenuAPB1_Prescalers Cpy_u32APB1_Prescaler) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	u32 LocalTemp = RCC->RCC_CFGR;

	/*** Validation ***/
	if (Cpy_u32APB1_Prescaler >= RCC_enuAPB1_Prescaler_2
			&& Cpy_u32APB1_Prescaler < RCC_enuAPB1_NumberOfPrescalers) {
		switch (Cpy_u32APB1_Prescaler) {
		case RCC_enuAPB1_Prescaler_NotDivided:
			LocalTemp &= RCC_enuAPB1_Prescaler_NotDivided_MASK_CLR;
			LocalTemp |= RCC_enuAPB1_Prescaler_NotDivided_MASK;
			RCC->RCC_CFGR = LocalTemp;

			break;
		case RCC_enuAPB1_Prescaler_2:
			LocalTemp &= RCC_enuAPB1_Prescaler2_MASK_CLR;
			LocalTemp |= RCC_enuAPB1_Prescaler2_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB1_Prescaler_4:
			LocalTemp &= RCC_enuAPB1_Prescaler4_MASK_CLR;
			LocalTemp |= RCC_enuAPB1_Prescaler4_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB1_Prescaler_8:
			LocalTemp &= RCC_enuAPB1_Prescaler8_MASK_CLR;
			LocalTemp |= RCC_enuAPB1_Prescaler8_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB1_Prescaler_16:
			LocalTemp &= RCC_enuAPB1_Prescaler16_MASK_CLR;
			LocalTemp |= RCC_enuAPB1_Prescaler16_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB1_Prescaler;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidAPB1_Prescaler;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuControlPrescaler_APB2(
		RCC_tenuAPB2_Prescalers Cpy_u32APB2_Prescaler) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK; // OK by default
	u32 LocalTemp = RCC->RCC_CFGR;

	/*** Validation ***/
	if (Cpy_u32APB2_Prescaler >= RCC_enuAPB1_Prescaler_2
			&& Cpy_u32APB2_Prescaler < RCC_enuAPB1_NumberOfPrescalers) {
		switch (Cpy_u32APB2_Prescaler) {
		case RCC_enuAPB2_Prescaler_NotDivided:
			LocalTemp &= RCC_enuAPB2_Prescaler_NotDivided_MASK_CLR;
			LocalTemp |= RCC_enuAPB2_Prescaler_NotDivided_MASK;
			RCC->RCC_CFGR = LocalTemp;

			break;
		case RCC_enuAPB2_Prescaler_2:
			LocalTemp &= RCC_enuAPB2_Prescaler2_MASK_CLR;
			LocalTemp |= RCC_enuAPB2_Prescaler2_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB2_Prescaler_4:
			LocalTemp &= RCC_enuAPB2_Prescaler4_MASK_CLR;
			LocalTemp |= RCC_enuAPB2_Prescaler4_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB2_Prescaler_8:
			LocalTemp &= RCC_enuAPB2_Prescaler8_MASK_CLR;
			LocalTemp |= RCC_enuAPB2_Prescaler8_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		case RCC_enuAPB2_Prescaler_16:
			LocalTemp &= RCC_enuAPB2_Prescaler16_MASK_CLR;
			LocalTemp |= RCC_enuAPB2_Prescaler16_MASK;
			RCC->RCC_CFGR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB2_Prescaler;
		}
	} else {
		LocalErrorStatus = RCC_enuInvalidAPB2_Prescaler;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk(RCC_tenuSystemBus Cpy_u32PeripheralBus, RCC_tenuBuses_Peripherals Cpy_u32PeripheralName) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;
	u32 LocalTemp;
	/* Switch Buses */
	switch (Cpy_u32PeripheralBus) {

	case RCC_enuAHB1:
		LocalTemp = RCC->RCC_AHB1ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAHB1_DMA2:
			LocalTemp &= RCC_enuAHB1_DMA2_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DMA2_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_DMA1:
			LocalTemp &= RCC_enuAHB1_DMA1_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DMA1_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOH:
			LocalTemp &= RCC_enuAHB1_GPIOH_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOH_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOE:
			LocalTemp &= RCC_enuAHB1_GPIOE_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOE_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOD:
			LocalTemp &= RCC_enuAHB1_GPIOD_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOD_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOC:
			LocalTemp &= RCC_enuAHB1_GPIOC_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOC_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOB:
			LocalTemp &= RCC_enuAHB1_GPIOB_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOB_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOA:
			LocalTemp &= RCC_enuAHB1_GPIOA_EN_CLR;
			LocalTemp |= RCC_enuAHB1_GPIOA_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;
		default:
			LocalErrorStatus = RCC_enuInvalidAHB1_Peripheral;
		}

		break;

	case RCC_enuAHB2:
		LocalTemp = RCC->RCC_AHB2ENR;
		if (Cpy_u32PeripheralName == RCC_enuAHB2_OTGFS) {
			LocalTemp &= RCC_enuAHB2_OTGFS_EN_CLR;
			LocalTemp |= RCC_enuAHB2_OTGFS_EN;
			RCC->RCC_AHB2ENR = LocalTemp;
		} else {
			LocalErrorStatus = RCC_enuInvalidAHB2_Peripheral;
		}
		break;

	case RCC_enuAPB1:
		LocalTemp = RCC->RCC_APB1ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAPB1_PWR:
			LocalTemp &= RCC_enuAPB1_PWR_EN_CLR;
			LocalTemp |= RCC_enuAPB1_PWR_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C3:
			LocalTemp &= RCC_enuAPB1_I2C3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_I2C3_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C2:
			LocalTemp &= RCC_enuAPB1_I2C2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_I2C2_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C1:
			LocalTemp &= RCC_enuAPB1_I2C1_EN_CLR;
			LocalTemp |= RCC_enuAPB1_I2C1_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_USART2:
			LocalTemp &= RCC_enuAPB1_USART2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_USART2_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_SPI3:
			LocalTemp &= RCC_enuAPB1_SPI3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_SPI3_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_SPI2:
			LocalTemp &= RCC_enuAPB1_SPI2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_SPI2_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_WWDG:
			LocalTemp &= RCC_enuAPB1_WWDG_EN_CLR;
			LocalTemp |= RCC_enuAPB1_WWDG_EN;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER5:
			LocalTemp &= RCC_enuAPB1_TIMER5_EN_CLR;
			LocalTemp |= RCC_enuAPB1_TIMER5_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER4:
			LocalTemp &= RCC_enuAPB1_TIMER4_EN_CLR;
			LocalTemp |= RCC_enuAPB1_TIMER4_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER3:
			LocalTemp &= RCC_enuAPB1_TIMER3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_TIMER3_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER2:
			LocalTemp &= RCC_enuAPB1_TIMER2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_TIMER2_EN;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB1_Peripheral;
		}
		break;

	case RCC_enuAPB2:
		LocalTemp = RCC->RCC_APB2ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAPB2_TIMER11:
			LocalTemp &= RCC_enuAPB2_TIMER11_EN_CLR;
			LocalTemp |= RCC_enuAPB2_TIMER11_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER10:
			LocalTemp &= RCC_enuAPB2_TIMER10_EN_CLR;
			LocalTemp |= RCC_enuAPB2_TIMER10_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER9:
			LocalTemp &= RCC_enuAPB2_TIMER9_EN_CLR;
			LocalTemp |= RCC_enuAPB2_TIMER9_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SYSCFG:
			LocalTemp &= RCC_enuAPB2_SYSCFG_EN_CLR;
			LocalTemp |= RCC_enuAPB2_SYSCFG_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SPI4:
			LocalTemp &= RCC_enuAPB2_SPI4_EN_CLR;
			LocalTemp |= RCC_enuAPB2_SPI4_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SPI1:
			LocalTemp &= RCC_enuAPB2_SPI1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_SPI1_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SDIO:
			LocalTemp &= RCC_enuAPB2_SDIO_EN_CLR;
			LocalTemp |= RCC_enuAPB2_SDIO_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_ADC1:
			LocalTemp &= RCC_enuAPB2_ADC1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_ADC1_EN;
			RCC->RCC_AHB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_USART6:
			LocalTemp &= RCC_enuAPB2_USART6_EN_CLR;
			LocalTemp |= RCC_enuAPB2_USART6_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_USART1:
			LocalTemp &= RCC_enuAPB2_USART1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_USART1_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER1:
			LocalTemp &= RCC_enuAPB2_TIMER1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_TIMER1_EN;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB2_Peripheral;
		}
		break;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk(
		RCC_tenuSystemBus Cpy_u32PeripheralBus,
		RCC_tenuBuses_Peripherals Cpy_u32PeripheralName) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;
	u32 LocalTemp;
	/* Switch Buses */
	switch (Cpy_u32PeripheralBus) {
	case RCC_enuAHB1:
		LocalTemp = RCC->RCC_AHB1ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAHB1_DMA2:
			LocalTemp &= RCC_enuAHB1_DMA2_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_DMA1:
			LocalTemp &= RCC_enuAHB1_DMA1_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOH:
			LocalTemp &= RCC_enuAHB1_GPIOH_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOE:
			LocalTemp &= RCC_enuAHB1_GPIOE_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOD:
			LocalTemp &= RCC_enuAHB1_GPIOD_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOC:
			LocalTemp &= RCC_enuAHB1_GPIOC_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOB:
			LocalTemp &= RCC_enuAHB1_GPIOB_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAHB1_GPIOA:
			LocalTemp &= RCC_enuAHB1_GPIOA_EN_CLR;
			LocalTemp |= RCC_enuAHB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;
		default:
			LocalErrorStatus = RCC_enuInvalidAHB1_Peripheral;
		}

		break;

	case RCC_enuAHB2:
		LocalTemp = RCC->RCC_AHB2ENR;
		if (Cpy_u32PeripheralName == RCC_enuAHB2_OTGFS) {
			LocalTemp &= RCC_enuAHB2_OTGFS_EN_CLR;
			LocalTemp |= RCC_enuAHB2_DISALBE;
			RCC->RCC_AHB2ENR = LocalTemp;
		} else {
			LocalErrorStatus = RCC_enuInvalidAHB2_Peripheral;
		}
		break;

	case RCC_enuAPB1:
		LocalTemp = RCC->RCC_APB1ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAPB1_PWR:
			LocalTemp &= RCC_enuAPB1_PWR_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C3:
			LocalTemp &= RCC_enuAPB1_I2C3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C2:
			LocalTemp &= RCC_enuAPB1_I2C2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_I2C1:
			LocalTemp &= RCC_enuAPB1_I2C1_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_USART2:
			LocalTemp &= RCC_enuAPB1_USART2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_SPI3:
			LocalTemp &= RCC_enuAPB1_SPI3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_SPI2:
			LocalTemp &= RCC_enuAPB1_SPI2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_WWDG:
			LocalTemp &= RCC_enuAPB1_WWDG_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_AHB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER5:
			LocalTemp &= RCC_enuAPB1_TIMER5_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER4:
			LocalTemp &= RCC_enuAPB1_TIMER4_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER3:
			LocalTemp &= RCC_enuAPB1_TIMER3_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		case RCC_enuAPB1_TIMER2:
			LocalTemp &= RCC_enuAPB1_TIMER2_EN_CLR;
			LocalTemp |= RCC_enuAPB1_DISALBE;
			RCC->RCC_APB1ENR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB1_Peripheral;
		}
		break;

	case RCC_enuAPB2:
		LocalTemp = RCC->RCC_APB2ENR;
		switch (Cpy_u32PeripheralName) {
		case RCC_enuAPB2_TIMER11:
			LocalTemp &= RCC_enuAPB2_TIMER11_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER10:
			LocalTemp &= RCC_enuAPB2_TIMER10_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER9:
			LocalTemp &= RCC_enuAPB2_TIMER9_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SYSCFG:
			LocalTemp &= RCC_enuAPB2_SYSCFG_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SPI4:
			LocalTemp &= RCC_enuAPB2_SPI4_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SPI1:
			LocalTemp &= RCC_enuAPB2_SPI1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_SDIO:
			LocalTemp &= RCC_enuAPB2_SDIO_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_ADC1:
			LocalTemp &= RCC_enuAPB2_ADC1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_AHB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_USART6:
			LocalTemp &= RCC_enuAPB2_USART6_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_USART1:
			LocalTemp &= RCC_enuAPB2_USART1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		case RCC_enuAPB2_TIMER1:
			LocalTemp &= RCC_enuAPB2_TIMER1_EN_CLR;
			LocalTemp |= RCC_enuAPB2_DISALBE;
			RCC->RCC_APB2ENR = LocalTemp;
			break;

		default:
			LocalErrorStatus = RCC_enuInvalidAPB2_Peripheral;
		}
		break;
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigurePLL(RCC_tstrPLL_Cfg_t Cpy_tstrPLLConfig) {
	RCC_tenuErrorStatus LocalErrorStatus = RCC_enuOK;

	/* Defining Local Temp vars */
	RCC_tenuPLLClkSource LocalPLL_Src = Cpy_tstrPLLConfig.RCC_enuPLLClkSrc;
	u32 LocalPLL_M = Cpy_tstrPLLConfig.RCC_u32PLLDivFactor_M;
	u32 LocalPLL_N = Cpy_tstrPLLConfig.RCC_u32PLLMulFactor_N;
	RCC_tenuPLL_P_Prescaler LocalPLL_P = Cpy_tstrPLLConfig.RCC_u32PLL_DivFactor_P;
	RCC_tenuPLL_Q_Prescaler LocalPLL_Q = Cpy_tstrPLLConfig.RCC_enuPLLDivFactor_Q;

	/* PLLCFGR */
	u32 LocalTemp = 0;
	u32 LocalPLL = RCC->RCC_PLLCFGR;

	u32 LocalPLL_Disable = RCC->RCC_CR;

	/* WE MUST DISABLE PLL to Configure it Safely */
	LocalPLL_Disable &= RCC_PLL_CLR_MASK;
	RCC->RCC_CR = LocalPLL_Disable;

	/*********************************** Validations **************************************/
	// 1- Checking Clock Source
	if (LocalPLL_Src >= RCC_enuPLL_HSI
			&& LocalPLL_Src < RCC_enuPLLNumberOfClockSrc) {
		// 2- Checking M Config.
		if (LocalPLL_M >= 2 && LocalPLL_M < 64) {
			// 2- Checking N Config.
			if ((LocalPLL_N >= 2) && (LocalPLL_N != 433)
					&& (LocalPLL_N <= 510)) {
				// 3- Checking P Config.
				if (LocalPLL_P >= 0 && LocalPLL_P < 4) {
					// 4- Checking Q Config.
					if (LocalPLL_Q >= 2
							&& LocalPLL_Q < RCC_enuPLL_QNumberOfDivFactors) {
						/* 1- Configuring PLL Clk Src */
						LocalTemp = RCC->RCC_PLLCFGR;
						LocalTemp &= RCC_enuPLLClkSrc_CLR_Mask;
						/* Putting the Value at bit #22 */
						LocalTemp |= (LocalPLL_Src << 22);
						RCC->RCC_PLLCFGR = LocalTemp;

						/* 2- Configuring M */
						LocalTemp = RCC->RCC_PLLCFGR;
						LocalTemp &= RCC_enuPLLPrescaler_M_CLR_Mask;
						/* Putting the Value at bit #0 */
						LocalTemp |= (LocalPLL_M << 0);
						RCC->RCC_PLLCFGR = LocalTemp;

						/* 3- Configuring N */
						LocalTemp = RCC->RCC_PLLCFGR;
						LocalTemp &= RCC_enuPLLPrescaler_N_CLR_Mask;
						/* Putting the Value at bit #6 */
						LocalTemp |= (LocalPLL_N << 6);
						RCC->RCC_PLLCFGR = LocalTemp;

						/* 4- Configuring P */
						LocalTemp = RCC->RCC_PLLCFGR;
						LocalTemp &= RCC_enuPLLPrescaler_P_CLR_Mask;
						/* Putting the Value at bit #16 */
						LocalTemp |= (LocalPLL_P << 16);
						RCC->RCC_PLLCFGR = LocalTemp;

						/* 5- Configuring Q */
						LocalTemp = RCC->RCC_PLLCFGR;
						LocalTemp &= RCC_enuPLLPrescaler_Q_CLR_Mask;
						/* Putting the Value at bit #24 */
						LocalTemp |= (LocalPLL_Q << 24);
						RCC->RCC_PLLCFGR = LocalTemp;

					} else {
						LocalErrorStatus = RCC_enuInvalidPLL_Q_DivFactor;
					}

				} else {
					LocalErrorStatus = RCC_enuInvalidPLL_P_DivFactor;
				}
			} else {
				LocalErrorStatus = RCC_enuInvalidPLL_N_MulFactor;
			}

		} else {
			LocalErrorStatus = RCC_enuInvalidPLL_M_DivFactor;
		}

	} else {
		LocalErrorStatus = RCC_enuInvalidPLLClkSrc;
	}

	return LocalErrorStatus;
}
/***********************************************************************************/
