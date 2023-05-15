/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 27 JAN 2023                             */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.  : Interface file that includes :		   */
/*			   1- Functions prototypes [APIs]		   */
/*			   2- Parameters definitions			   */
/*******************************************************/
#ifndef GIE_H
#define GIE_H


/********************* Enum with the Error Status *********************/
typedef enum {
	GIE_enuOK  = 0 		  ,		// To Make sure Compiler will start from zero
	GIE_enuNOK     		  
} GIE_tenuErrorStatus;

/****************************************************************/
/*      GIE Enable Function										*/
/*		Input  : Void											*/
/*		Output : GIE_tenuErrorStatus to Report Errors		   	*/
/****************************************************************/
GIE_tenuErrorStatus GIE_enuInit_EnableGIE (void);


/****************************************************************/
/*      GIE Disable Function									*/
/*		Input  : Void											*/
/*		Output : GIE_tenuErrorStatus to Report Errors		   	*/
/****************************************************************/
GIE_tenuErrorStatus GIE_enuInit_DisbaleGIE (void);

/***************************************************************/
#endif /* GIE_H */
