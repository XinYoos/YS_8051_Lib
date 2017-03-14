#ifndef d_AT24C02_H__
#define d_AT24C02_H__
#include "b_iic.h"
#define AT24C02CS_ID1 0xA0

extern void dv_at24c02WriteIn(unsigned char pa_ucCS,
					          unsigned char pa_ucStartAdd,
					   		  unsigned char pa_ucCount,
					   		  unsigned char *pa_Date);

extern void dv_at24c02ReadOut(unsigned char pa_ucCS,
					   		  unsigned char pa_ucStartAdd,
					   		  unsigned char pa_ucCount,
					   		  unsigned char *pa_Date);

#endif
