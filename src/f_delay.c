#include "f_delay.h"

static void fn_Delay1Ms(void)//本函数无法调用static
{
	unsigned char cnt_ucI = 2,cnt_ucJ = 199;
	do
	{
		while(--cnt_ucJ);
	}
	while(--cnt_ucI);
}

void fn_DelayMS_ui(unsigned int pa_uiValMS)
{
	unsigned int cnt_uiI;
	for ( cnt_uiI = 0; cnt_uiI < pa_uiValMS; cnt_uiI++)
	{
		fn_Delay1Ms();
	}
}

void fn_Delay5US(void)
{	

	_nop_();_nop_();_nop_();_nop_();
}