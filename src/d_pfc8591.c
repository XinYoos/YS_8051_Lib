
#include "d_pcf8591.h"
/**
 * [dv_pcf8591ADC 读取pcf8591ADC寄存器内的电压标量值]
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
/**
 * [dv_pcf8591DAC 向pcf8591DAC寄存器内写入指定的电压标量值]
 * @Author   YS
 * @DateTime 2017-03-15T19:57:28+0800
 * @param    pa_ucCS                  [器件片选地址]
 * @param    pa_ControlByte           [pcf8591的控制字]
 * @param    pa_ucVoltDat             [指定的电压标量值]
 */
void dv_pcf8591DAC(unsigned char pa_ucCS,
				   unsigned char pa_ControlByte,
				   unsigned char pa_ucVoltDat)
{
	unsigned char m_ucVoltDat = pa_ucVoltDat;
	bp_iicWrDatToDev(pa_ucCS,pa_ControlByte,1,&m_ucVoltDat);
}
