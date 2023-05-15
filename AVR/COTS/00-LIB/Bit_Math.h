/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 2 NOV 2022                              */
/* Version   : V.01                                    */
/*******************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

// SET BIT IN A REGISTER
#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO))

// CLEAR BIT IN A REGISTER
#define CLR_BIT(REG,Bit_NO)		(REG) &= ~(1<<(Bit_NO))

// Get The Bit number Bit_NO
#define GET_BIT(REG,Bit_NO)     ((REG) &= (1<<(Bit_NO)))

// Right Shift by No
#define RSHFT_REG(REG,NO)		((REG) >> NO)

// Left Shift by NO
#define LSHFT_REG(REG,NO)		((REG) << NO)

// Circular Right Shift
#define CRSHFT_REG(REG,NO)		(((REG) >> NO) | ((REG) << sizeof(REG) * 8 - NO))

// Circular Left Shift
#define CLSHFT_REG(REG,NO)      (((REG) << NO) | ((REG) >> sizeof(REG) * 8 - NO))

// Assign a Value to a Register
#define ASSIGN_REG(REG,VALUE)	(((REG) = VALUE))

// Set The Register [1s]
#define SET_REG(REG)			~((REG) &= 0)

// Clear the Register [0s]
#define CLR_REG(REG)			((REG) &= 0)

// Toggle a Bit in Register
#define TGL_BIT(REG,Bit_NO)		(REG) ^= (1<<Bit_NO)

// Toggle a Register Value
#define TGL_REG(REG)			((REG) ^= 1)

/*
	Note : High nibble is always at position [4:7]
		   Low nibble is always at position [3:0]
*/
// Set The High Nibble in a Register [Leading]
#define SET_H_NIB(REG)			((REG) |= (0xF0))

// Set The Low Nibble in a Register  [Trailing]
#define SET_L_NIB(REG)			((REG) |= (0x0F))

// Clear The High Nibble in a Register
#define CLR_H_NIB(REG)			((REG) &= (0x0F))

// Clear The Low Nibble in a Register
#define CLR_L_NIB(REG)			((REG) &= (0xF0))

// Get The High Nibble in a Register .
#define GET_H_NIB(REG)			(((REG >> 4) &= (0x0F)) << 4)

// Get The Low Nibble in a Register .
#define GET_L_NIB(REG)			(((REG << 4) &= (0xF0)) >> 4)

// Assign The High Nibble in a Register
#define ASSIGN_H_NIB(REG,VALUE)		(1 << VALUE)

// Assign the Low Nibble in a Register
#define ASSIGN_L_NIB(REG,VALUE) 	((REG) |= (REG - VALUE))

// Toggle the High Nibble in a Register
#define TGL_H_NIB(REG)				((REG) ^= (0XF0))

// Toggle the Low Nibble in a Register
#define TGL_L_NIB(REG)				((REG) ^= (0X0F))

// Swap the Nibbles in a Register
#define SWAP_NIB(REG)               CRSHFT_REG(REG,4)





#endif 		/* BIT_MATH_H */