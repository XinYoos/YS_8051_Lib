#ifndef d_PCF8591_H__
#define d_PCF8591_H__
#include "b_iic.h"
#define PCF8591CS_ID1 0x92

extern unsigned char dv_pcf8591ADC(unsigned char pa_ucCS,
							unsigned char pa_ControlByte);

extern void dv_pcf8591DAC(unsigned char pa_ucCS,
				   		  unsigned char pa_ControlByte,
				  	      unsigned char pa_ucVoltNum);
#endif