
#ifndef SW_H_
#define SW_H_


// Error Status
typedef enum
{
	Switch_enuOK=0,
	Switch_enuNOK

}Switch_tenu_ErrorStatus;

// Switch Pins
typedef enum
{
	Switch_enu_Switch0=0,
//	Switch_enu_Switch1  ,
//	Switch_enu_Switch2  ,
//	Switch_enu_Switch3  ,
//	Switch_enu_Switch4  ,
//	Switch_enu_Switch5  ,
//	Switch_enu_Switch6  ,
//	Switch_enu_Switch7  ,
//	Switch_enu_Switch8  ,
//	Switch_enu_Switch9  ,
//	Switch_enu_Switch10  ,
//	Switch_enu_Switch11  ,
//	Switch_enu_Switch12  ,
//    Switch_enu_Switch13  ,
//    Switch_enu_Switch14  ,
//    Switch_enu_Switch15  ,
	Switch_enu_Numbers
}Switch_tenuPins;


// Switch Ports
//typedef enum
//{
//	Switch_enuPort_A=0,
//	Switch_enuPort_B,
//	Switch_enuPort_C,
//	Switch_enuPort_D,
//    Switch_enuPort_E,
//    Switch_enuPort_H,
//}Switch_tenuPorts;

// Switch Status
typedef enum
{
	Switch_enuReleased=0,
	Switch_enuPressed
}Switch_tenuStatus;

// Switch PullUp/ PullDown
typedef enum
{
	Switch_enuPullUp=0,
	Switch_enuPullDown
}Switch_tenuPUPD;

// Switch Name
typedef enum
{
	Switch_enu_On=0,
	Switch_enu_Off,
	Switch_enu_Display,
	Switch_enu_Clear,
	Switch_enu_Move,
	Switch_enu_LED,
	Switch_enu_SSEG,
	Switch_enu_LCD,
}Switch_tenuNames;

// Switch Speed
typedef enum
{
	Switch_enu_LowSpeed=0,
	Switch_enu_MediumSpeed,
	Switch_enu_HighSpeed,
	Switch_enu_VeryHighSpeed
}Switch_tenuSpeed;

// Struct with Switch Configurations
typedef struct
{
	u8 Switch_Port;
	u16 Switch_Pin;
	Switch_tenuNames Switch_Name;
	Switch_tenuPUPD Switch_PUPD;
	Switch_tenuSpeed Switch_Speed;

}Switch_tstr_Config_t;


// Extern Array of Struct
extern const Switch_tstr_Config_t Switch_tstr_Config[Switch_enu_Numbers];


/*************************************** APIs *****************************************/
Switch_tenu_ErrorStatus Switch_enuInit(void);

Switch_tenu_ErrorStatus Switch_enuGetSwitchState (u8 Cpy_u8Port, u16 Cpy_u16Pin , u16 *Add_u8State);

void Switch_voidTask (void);

u8 Switch_u8GetSwitchState (u8 Cpy_u8SwitchID);


#endif /* SW_H_ */
