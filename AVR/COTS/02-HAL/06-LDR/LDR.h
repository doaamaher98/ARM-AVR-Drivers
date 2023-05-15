#ifndef LDR_H
#define LDR_H


/* Error Status */
typedef enum
{
	LDR_enuOK=0,
	LDR_enuNOK
	}LDR_tenuErrorStatus;


/* API */
LDR_tenuErrorStatus Read_LDRValue (u8 Cpy_u8Channel, u16 *Add_u16LDRVal);

#endif
