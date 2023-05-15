/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 4 FEB 2023              	                	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the Base Addresses of the */
/*			   Register										  */
/**************************************************************/

#ifndef MCUCR_PRIV_H
#define MCUCR_PRIV_H

/*********************** Register Addresses ****************************/

#define 	MCUCR			(*(volatile u8*) 0x55)
#define		MCUCSR			(*(volatile u8*) 0x54)
#define		GICR			(*(volatile u8*) 0x5B)
#define		GIFR			(*(volatile u8*) 0x5A)  


/***************************** NULL POINTER ************************************/
#define 	NULL_PTR 			((void*) 0)


/****************** EXT INT MODES (INT0,INT1) **********************/
#define			EXT_INT_RaisingEdge					3
#define			EXT_INT_FallingEdge					2
#define			EXT_INT_OnChange					1
#define			EXT_INT_LowLevel					0

/****************** EXT INT MODES (INT2) **************************/
#define			EXT_INT_2_FallingEdge				0
#define			EXT_INT_2_RaisingEdge				1
/******************************************************************/

#define			MCUCR_ISC00						0
#define			MCUCR_ISC01						1
#define			MCUCR_ISC10						2
#define			MCUCR_ISC11						3

#define			MCUCSR_ISC2						6
/************************ FLAG INTERRUPTS REG ***************************/
#define			GIFR_INT0						6
#define			GIFR_INT1						7
#define			GIFR_INT2						5

/********************* ENABLING INTERRUPTS REG ******************************/
#define			GICR_INT0						6
#define			GICR_INT1						7
#define			GICR_INT2						5

/************************************************************************/
#define			EXT_INT_DISABLE					1
#define			EXT_INT_ENABLE					0


#endif /* GIE_PRIV_H */