/*
 * TIMER0_PRIV.h
 *
 * Created: 3/3/2023 4:12:41 AM
 *  Author: Doaa
 */ 
#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_

/*************************** Registers ***************************/
#define			TIMER0_OCR0						*((volatile u8*) 0x5C)
#define			TIMER0_TIMSK					*((volatile u8*) 0x59)
#define			TIMER0_TIFR						*((volatile u8*) 0x58)
#define			TIMER0_TCCR0					*((volatile u8*) 0x53)
#define			TIMER0_TCNT0					*((volatile u8*) 0x52)
#define			TIMER0_SFIOR					*((volatile u8*) 0x50)

#define			TIMER0_BUSY						0
#define			TIMER0_IDLE						1

/******************** NULL PTR *************************/
#define				NULL_PTR			((void*)0)					
#define				NULL				0

/******************** ISRs in VT ************************/
#define				ISR_TIMER0_OVF		11
#define				ISR_TIMER0_COMP		10

#define				TIMER0_OVERFLOW_VAL			255

/******************** ISR Functions [Events] ************************/
/* OV */
#define				TIMER_0_OverFlow(ISR_TIMER0_OVF)	void __vector_##ISR_TIMER0_OVF (void) __attribute__((signal));\
														void __vector_##ISR_TIMER0_OVF (void)
/* CM */
#define				TIMER_0_CompareMatch(ISR_TIMER0_COMP)	void __vector_##ISR_TIMER0_COMP (void) __attribute__((signal));\
															void __vector_##ISR_TIMER0_COMP (void)

	

#endif /* TIMER0_PRIV_H_ */