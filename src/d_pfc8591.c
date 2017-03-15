
#include "d_pcf8591.h"
/**
 * [dv_pcf8591ADC 读取pcf8591ADC寄存器内的标量值]
 * @Author   YS
 * @DateTime 2017-03-15T17:11:48+0800
 * @param    pa_ucCS                  [器件片选地址]
 * @param    pa_ControlByte           [pcf8591的控制字]
 * @return                            [返回读取的标量值]
 */
unsigned char dv_pcf8591ADC(unsigned char pa_ucCS,
							unsigned char pa_ControlByte)
{
	unsigned char m_ucVoltDat;

	bp_iicRdDatFromDev(pa_ucCS,pa_ControlByte,1,&m_ucVoltDat);

	return m_ucVoltDat;
}

void dv_pcf8591DAC(unsigned char pa_ucCS,
				   unsigned char pa_ControlByte,
				   unsigned char pa_ucVoltNum)
{
	unsigned char m_ucVoltDat = pa_ucVoltNum;
	bp_iicWrDatToDev(pa_ucCS,pa_ControlByte,1,&m_ucVoltDat);
}
