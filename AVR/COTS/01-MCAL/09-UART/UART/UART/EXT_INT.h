/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 27 JAN 2023                             */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.  : Interface file that includes :		   */
/*			   1- Functions prototypes [APIs]		   */
/*			   2- Parameters definitions			   */
/*******************************************************/
#ifndef EXT_INT_H
#define EXT_INT_H

#include "EXT_INT_Cfg.h"

/********************* Enum with the Error Status *********************/
typedef enum {
	EXT_INT_enuOK  = 0,				// To Make sure Compiler will start from zero
	EXT_INT_enuNOK,
	EXT_INT_NullPtr,
	EXT_INT_enuInvalidINTNum     		  
} EXT_INT_tenuErrorStatus;

/********************* INIT Function ****************************/
EXT_INT_tenuErrorStatus EXT_INT_INIT (void);

/*****************************************************************************************/
/********************************* CALL BACK FUNCTION FOR ISR ****************************/
/*****************************************************************************************/
/* Takes the Interrupt Source : INT0, INT1 or INT2
   & Takes the Function pointer (pointer to a function that will be the one wanted to be in the ISR to be executed
*/

// typedef void (*EXT_INTCallback_Set)(void);
// 
// void EXT_INT0Callback_Set (EXT_INTCallback_Set CallBackFunction);
// void EXT_INT1Callback_Set (EXT_INTCallback_Set CallBackFunction);
// void EXT_INT2Callback_Set (EXT_INTCallback_Set CallBackFunction);

EXT_INT_tenuErrorStatus EXT_INT0Callback_Set (void (*ptr_int)(void));
EXT_INT_tenuErrorStatus EXT_INT1Callback_Set (void (*ptr_int)(void));
EXT_INT_tenuErrorStatus EXT_INT2Callback_Set (void (*ptr_int)(void));


/********************************* ENABLING **********************************************/
// Enable
void EXT_INT0_Enable (void);
void EXT_INT1_Enable (void);
void EXT_INT2_Enable (void);

/********************************* DISABLING **********************************************/
// Disable
void EXT_INT0_Disable (void);
void EXT_INT1_Disable (void);
void EXT_INT2_Disable (void);



#endif /* EXT_INT_H */