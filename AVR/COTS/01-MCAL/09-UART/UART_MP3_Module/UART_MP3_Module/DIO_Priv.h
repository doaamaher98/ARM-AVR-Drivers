/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 16 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the Base Addresses of the */
/*			   Registers (Harvard Arch. used Addresses)		  */   	 
/**************************************************************/

#ifndef DIO_PRIV_H
#define DIO_PRIV_H

/*********************** Register Addresses ****************************/
/***************************** DDRx ************************************/
#define 	DDRA			(*(volatile u8*) 0x3A)
#define 	DDRB			(*(volatile u8*) 0x37)			
#define 	DDRC			(*(volatile u8*) 0x34)	
#define 	DDRD			(*(volatile u8*) 0x31)	

/***************************** PORTx ************************************/
#define 	PORTA			(*(volatile u8*) 0x3B)
#define 	PORTB			(*(volatile u8*) 0x38)			
#define 	PORTC			(*(volatile u8*) 0x35)	
#define 	PORTD			(*(volatile u8*) 0x32)	

/***************************** PINx ************************************/
#define 	PINA			(*(volatile u8*) 0x39)
#define 	PINB			(*(volatile u8*) 0x36)			
#define 	PINC			(*(volatile u8*) 0x33)	
#define 	PIND			(*(volatile u8*) 0x30)	


/***************************** NULL POINTER ************************************/
#define 	NULL 			((void*) 0)


#endif /* DIO_PRIV_H */