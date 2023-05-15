/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 27 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the Base Addresses of the */
/*			   Register										  */
/**************************************************************/

#ifndef GIE_PRIV_H
#define GIE_PRIV_H

/*********************** Register Addresses ****************************/
#define 	SREG			(*(volatile u8*) 0x5F)


/***************************** NULL POINTER ************************************/
#define 	NULL 			((void*) 0)




#endif /* GIE_PRIV_H */