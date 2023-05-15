#include "STD_Types.h"

#include "GPIO.h"
#include "SW.h"

static u8 Switch_State[Switch_enu_Numbers];
static u8 Counter[Switch_enu_Numbers];
static u32 Prev_State[Switch_enu_Numbers];

u32 Switch_CurrentState[Switch_enu_Numbers];

/***********************************************************************************/
/* Called every 5msec in Scheduler */
void Switch_voidTask (void)
{
	u8 LocalIterator =0;


	for (LocalIterator =0; LocalIterator< Switch_enu_Numbers; LocalIterator++)
	{
		GPIO_enuGetPinValue(Switch_tstr_Config[LocalIterator].Switch_Port,Switch_tstr_Config[LocalIterator].Switch_Pin, &Switch_CurrentState[LocalIterator]);

		if (Switch_CurrentState[LocalIterator] == Prev_State[LocalIterator])
		{
			Counter[LocalIterator] ++;
		}
		else
		{
			Counter[LocalIterator] = 0;
		}

		if (Counter[LocalIterator] == 5)
		{
			Switch_State[LocalIterator]  = Switch_CurrentState[LocalIterator]^ Switch_enuPullDown;
			Counter[LocalIterator] = 0;
		}
		Prev_State[LocalIterator] = Switch_CurrentState[LocalIterator];
	}
}
/***********************************************************************************/
Switch_tenu_ErrorStatus Switch_enuInit(void)
{
	Switch_tenu_ErrorStatus LocalErrorStatus = Switch_enuOK;

	u8 LocalIterator;
	GPIO_tsrt_PortConfig_t GPIO_Switch;

	for (LocalIterator =0; LocalIterator< Switch_enu_Numbers; LocalIterator++)
	{
		GPIO_Switch.GPIO_Port = Switch_tstr_Config[LocalIterator].Switch_Port;
		GPIO_Switch.GPIO_Pin = Switch_tstr_Config[LocalIterator].Switch_Pin;
		GPIO_Switch.GPIO_Mode = Switch_tstr_Config[LocalIterator].Switch_PUPD;
		GPIO_Switch.GPIO_Speed = Switch_tstr_Config[LocalIterator].Switch_Speed;

		GPIO_enuInit(&GPIO_Switch);
	}
	return LocalErrorStatus;
}
/***********************************************************************************/
Switch_tenu_ErrorStatus Switch_enuGetSwitchState (u8 Cpy_u8Port, u16 Cpy_u16Pin , u16 *Add_u16State)
{
	Switch_tenu_ErrorStatus LocalErrorStatus = Switch_enuOK;

	u8 LocalIterator;
	u8 LocalCounter=0;

	GPIO_enuGetPinValue(Switch_tstr_Config[Cpy_u8Port].Switch_Port,Switch_tstr_Config[Cpy_u16Pin].Switch_Pin, Add_u16State);

	return LocalErrorStatus;
}

/***********************************************************************************/
u8 Switch_u8GetSwitchState (u8 Cpy_u8SwitchID)
{
	return Switch_State[Cpy_u8SwitchID];
}
/***********************************************************************************/
