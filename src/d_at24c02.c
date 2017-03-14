#include "d_at24c02.h"

void dv_at24c02WriteIn(unsigned char pa_ucCS,
					   unsigned char pa_ucStartAdd,
					   unsigned char pa_ucCount,
					   unsigned char *pa_Date)
{
	bp_iicWrDatToDev(pa_ucCS,
					 pa_ucStartAdd,
					 pa_ucCount,
					 pa_Date);

	// fn_DelayMS_ui(5);
}

void dv_at24c02ReadOut(unsigned char pa_ucCS,
					   unsigned char pa_ucStartAdd,
					   unsigned char pa_ucCount,
					   unsigned char *pa_Date)
{
	bp_iicRdDatFromDev(pa_ucCS,
					   pa_ucStartAdd,
					   pa_ucCount,
					   pa_Date);
}

