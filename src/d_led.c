#include "d_led.h"

void dv_FlashLED_ucuc(unsigned char pa_ucBit1,
				 	  unsigned char pa_ucBit2)
{
	P0 = pa_ucBit1;//
	fn_DelayMS_ui(1000);
	P0 = pa_ucBit2;//
	fn_DelayMS_ui(1000);
}