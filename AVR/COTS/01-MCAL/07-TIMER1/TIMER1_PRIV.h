/*
 * TIMER1_PRIV.h
 *
 * Created: 10/3/2023 4:12:41 AM
 *  Author: Doaa
 */ 
#ifndef TIMER1_PRIV_H_
#define TIMER1_PRIV_H_

/*************************** Registers ***************************/
#define			TIMER1_TCCR1A					*((volatile u8*) 0x4F)
#define			TIMER1_TCCR1B					*((volatile u8*) 0x4E)

#define			TIMER1_TCNT1H					*((volatile u8*) 0x4D)
#define			TIMER1_TCNT1L					*((volatile u16*) 0x4C)

#define			TIMER1_OCR1AH					*((volatile u8*) 0x4B)
#define			TIMER1_OCR1AL					*((volatile u16*) 0x4A)

#define			TIMER1_OCR1BH					*((volatile u8*) 0x49)
#define			TIMER1_OCR1BL					*((volatile u16*) 0x48)

#define			TIMER1_ICR1H					*((volatile u8*) 0x47)
#define			TIMER1_ICR1L					*((volatile u16*) 0x46)

#define			TIMER1_TIMSK					*((volatile u8*) 0x59)
#define			TIMER1_TIFR						*((volatile u8*) 0x58)

#define			TIMER1_BUSY						0
#define			TIMER1_IDLE						1

/******************** NULL PTR *************************/
#define				NULL_PTR			((void*)0)					
#define				NULL				0

/******************** ISRs in VT ************************/
#define				ISR_TIMER0_CAPTURE_EVENT		6
#define				ISR_TIMER0_COMP_A				7
#define				ISR_TIMER0_COMP_B				8
#define				ISR_TIMER0_OVF					9

#define				TIMER1_OVERFLOW_VAL			65536

/******************** ISR Functions [Events] ************************/
/* Capture Event */
#define				TIMER_1_CaptureEvent(ISR_TIMER0_CAPTURE_EVENT)	void __vector_##ISR_TIMER0_CAPTURE_EVENT (void) __attribute__((signal));\
																	void __vector_##ISR_TIMER0_CAPTURE_EVENT (void)
/* CM(A) */
#define				TIMER_1_CompareMatchA(ISR_TIMER0_COMP_A)		void __vector_##ISR_TIMER0_COMP_A (void) __attribute__((signal));\
																	void __vector_##ISR_TIMER0_COMP_A (void)
/* CM(B) */
#define				TIMER_1_CompareMatchB(ISR_TIMER0_COMP_B)		void __vector_##ISR_TIMER0_COMP_B (void) __attribute__((signal));\
																	void __vector_##ISR_TIMER0_COMP_B (void)
/* Overflow */
/* CM(A) */
#define				TIMER_1_CompareMatchA(ISR_TIMER0_OVF)			void __vector_##ISR_TIMER0_OVF (void) __attribute__((signal));\
																	void __vector_##ISR_TIMER0_OVF (void)
	


#endif /* TIMER1_PRIV_H_ */