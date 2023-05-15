/*
 * STK_Private.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Doaa
 */

#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_


/****************************** Defines **********************************/
#define				STK_CTRL					*((volatile u32 *) 0xE000E010) // Systick control & enable register
#define				STK_LOAD					*((volatile u32 *) 0xE000E014) // Systick reload value register
#define				STK_VAL						*((volatile u32 *) 0xE000E018) // Systick current value register
#define				STK_CALIB					*((volatile u32 *) 0xE000E01C) // Systick calibration value register



#endif /* STK_PRIVATE_H_ */
