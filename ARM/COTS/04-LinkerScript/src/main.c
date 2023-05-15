#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include <stdint.h>


__attribute__ ((section(".my_section"),used))
uint32_t GlobalNotInit;					// .my_section


uint32_t GlobalInit = 100;				// .data
const uint32_t GlobalConst = 500;		// rodata



//extern print_var(const uint32_t * var);

extern unsigned int _my_section_start;


int Dodo() {
	static uint32_t  LocalNotInit;			// .stack
	static uint32_t  LocalInit = 200;		// .stack
	static const uint32_t LocalConst = 10;	// .stack

//	static int LocalStaticNotInit;							// .bss
//	static int LocalStaticInit = 300;						//	.data
//	static const int LocalStaticConstInit = 0;				// .rodata

	print_var(&GlobalConst);
	print_var(&LocalConst);

//	_my_section_start++;

	while (1)
	{
		GlobalNotInit++;
		GlobalInit++;

		_my_section_start++;

		LocalNotInit++;
		LocalInit++;

		if (GlobalInit >= GlobalConst || GlobalNotInit >= GlobalConst)
		{
			GlobalInit =0;
			GlobalNotInit =0;
		}

		if (LocalNotInit >= LocalConst || LocalInit >= LocalConst)
		{
			LocalNotInit =0;
			LocalInit =0;
		}
	}


//	LocalStaticNotInit++;
//	LocalStaticInit++;




}

