/*
 * LCD_Cfg.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Doaa Maher
 */

#include "LCD_Interface.h"

LCD_tstrPinConfiguration_t LCD_Array [LCD_enuNumberOfLCDs]=
{
		[LCD_enuAdvertisement] =
		{
				/* Mode : 8-Bit */
				.LCD_tstr_OperatingMode_t.LCD_Mode = LCD_enu_8Bits_Mode,

				/* 								Control Pins :  						*/
				/* ==================================================================== */
				/* ========================== 1- RS ================================== */
				.LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Port  = GPIO_enuPort_B,
				.LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Pin   = GPIO_enuPin_0,
				.LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
				.LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Speed = GPIO_OUTPUT_SPEED_HIGH,

				/* ========================== 2- RW ================================== */
				.LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Port  = GPIO_enuPort_B,
				.LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Pin   = GPIO_enuPin_1,
				.LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
				.LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Speed = GPIO_OUTPUT_SPEED_HIGH,

				/* ========================== 3- E ================================== */
				.LCD_tstrLCD_Pins_t.LCD_E.GPIO_Port  = GPIO_enuPort_B,
				.LCD_tstrLCD_Pins_t.LCD_E.GPIO_Pin   = GPIO_enuPin_2,
				.LCD_tstrLCD_Pins_t.LCD_E.GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
				.LCD_tstrLCD_Pins_t.LCD_E.GPIO_Speed = GPIO_OUTPUT_SPEED_HIGH,

				/*							 Data Pins 								*/
				/* ==================================================================== */
				// 1-D0
				.LCD_tstrLCD_Pins_t.LCD_Data[0] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_0,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 2- D1
				.LCD_tstrLCD_Pins_t.LCD_Data[1] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_1,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 3- D2
				.LCD_tstrLCD_Pins_t.LCD_Data[2] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_2,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 4- D3
				.LCD_tstrLCD_Pins_t.LCD_Data[3] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_3,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 5- D4
				.LCD_tstrLCD_Pins_t.LCD_Data[4] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_4,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 6- D5
				.LCD_tstrLCD_Pins_t.LCD_Data[5] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_5,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 7- D6
				.LCD_tstrLCD_Pins_t.LCD_Data[6] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_6,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},

				// 8- D7
				.LCD_tstrLCD_Pins_t.LCD_Data[7] =
				{
						.GPIO_Port 		= GPIO_enuPort_A,
						.GPIO_Pin		= GPIO_enuPin_7,
						.GPIO_Mode		= GPIO_MODE_OUTPUT_PP,
						.GPIO_Speed		= GPIO_OUTPUT_SPEED_HIGH,
				},
		}
};


