#include "Std_Types.h"
#include "RCC.h"


void main(void)
{
	RCC_enuEnableSysClk (RCC_enu_HSE);
	RCC_enuCheckClkReady(RCC_enu_HSE, RCC_enuClock_RDY);

	RCC_enuControlPrescaler_AHB(RCC_enuAHB_Prescaler_4);
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOB);

////	RCC_enuDisableSysClk(RCC_enu_PLL);
//
//	RCC_tstrPLL_Cfg_t PLL_Config;
//
//	PLL_Config.RCC_enuPLLClkSrc = RCC_enuPLL_HSE;
//	PLL_Config.RCC_u32PLL_DivFactor_P = RCC_enuPLL_P_DivBy8;
//	PLL_Config.RCC_u32PLLDivFactor_M = RCC_enuPLLPrescaler_M_16;
//	PLL_Config.RCC_u32PLLMulFactor_N = 192;
//	PLL_Config.RCC_enuPLLDivFactor_Q=RCC_enuPLL_Q_DivBy2;
//
//	RCC_enuConfigurePLL(PLL_Config);

	RCC_enuSelectSysClk(RCC_enu_HSE);


  while (1)
    {
       // Add your code here.
    }
}

