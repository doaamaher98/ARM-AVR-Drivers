/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 5 FEB 2023                              */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.   : Private header file for Any            */
/*                Private Data/Registers  			   */
/*******************************************************/
/* Header Guard */
#ifndef ADC_PRV
#define ADC_PRV

/************************************ Defines *******************************************/
// Used Registers
#define         ADMUX                   (*(volatile u8*) 0x27)
#define         ADCSRA                  (*(volatile u8*) 0x26)

// The 2 Data Registers (ADCH) & (ADCL)
#define         ADCH                    (*(volatile u8*) 0x25)

#define         ADCL                    (*(volatile u8*) 0x24)
#define         ADCL_RESULT             (*(volatile u16*) 0x24)

#define         SFIOR                   (*(volatile u8*) 0x50)

// NULL Pointer
#define 		NULL_PTR 				((void*) 0)

// ADC INTERRUPT
#define			ADC_Interrupt			16
#define			ISR_NUMBER				ADC_Interrupt

// ADC Flags to indicate the state
#define			ADC_IDLE				0
#define			ADC_BUSY				1			
										
/************************************ Types *******************************************/
// ADMUX Register
typedef enum 
{
    ADC_enuADMUX0=0,           // Bit 0
    ADC_enuADMUX1,             // Bit 1
    ADC_enuADMUX2,             // Bit 2
    ADC_enuADMUX3,             // Bit 3
    ADC_enuADMUX4,             // Bit 4
    ADC_enuADLAR,              // Bit 5
    ADC_enuREFS0,              // Bit 6
    ADC_enuREFS1               // Bit 7
}ADC_ADMUX_tenuRegister;

// MUX(4:0) Analog Channel & Gain Selection Bits
// If these bit are changed during Conversion, the change won't happen until the conversion is done [ADIF in ADCSRA is set]
// ADC Pins & Values
typedef enum
{
    ADC_enuADCPin0=0,              // 0000 
    ADC_enuADCPin1,                // 0001
    ADC_enuADCPin2,                // 0010
    ADC_enuADCPin3,                // 0011
    ADC_enuADCPin4,                // 0100
    ADC_enuADCPin5,                // 0101
    ADC_enuADCPin6,                // 0110
    ADC_enuADCPin7,                // 0111
    ADC_enuADMUXPinNumber          // 1000
}ADC_ADMUX_SingleEndedtenuPins;

// ADCSRA : ADC Control & Status Register A
typedef enum
{
    ADC_enuADPS0=0,                // 0                
    ADC_enuADPS1,                  // 1
    ADC_enuADPS2,                  // 2
    ADC_enuADIE,                   // 3
    ADC_enuADIF,                   // 4
    ADC_enuADATE,                  // 5
    ADC_enuADSC,                   // 6
    ADC_enuADEN                    // 7
}ADC_ADCSRA_tenuRegister;


// SFIOR (Special Function Register)
typedef enum
{
    ADC_enuPSR10=0,
    ADC_enuPSR2,
    ADC_enuPUD,
    ADC_enuACME,
    ADC_enuReserved,
    ADC_enuADTS0,
    ADC_enuADTS1,
    ADC_enuADTS2
}ADC_tenuSFIORReg;


#endif /* ADC_PRV */