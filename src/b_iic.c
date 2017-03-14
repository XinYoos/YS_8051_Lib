#include "b_iic.h"

#define IIC_WRITE 0x00
#define IIC_READ  0x01

sbit hp_IIC_SCL = P2^0;
sbit hp_IIC_SDA = P2^1;


void bp_iicStart(void)
{
	hp_IIC_SDA = 1;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SDA = 0;
	fn_Delay5US();
}

void bp_iicStop(void)
{
	hp_IIC_SDA = 0;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SDA = 1;
}

void bp_iicAck(void)                      
{ 
	hp_IIC_SCL = 0;// 为产生脉冲准备
	hp_IIC_SDA = 0;// 产生应答信号
	fn_Delay5US();	// 延时你懂得
	hp_IIC_SCL = 1;
	fn_Delay5US();  
	hp_IIC_SCL = 0;
	fn_Delay5US();// 产生高脉冲 
	hp_IIC_SDA = 1;	// 释放总线
}

bit bp_iicJudgeACK(void)
{	
	bit m_btACK;
	unsigned char cnt_ucI = 0;
	hp_IIC_SCL = 0;
	fn_Delay5US();
	hp_IIC_SDA = 1;
	hp_IIC_SCL = 1;
	fn_Delay5US();
	while((1 == hp_IIC_SDA) && (cnt_ucI < 255))
	{
		cnt_ucI++;
		m_btACK = hp_IIC_SDA;
	}
	hp_IIC_SCL = 0;
	return m_btACK;//0有应答，1无应答
}

void bp_iicNoACK(void)
{
	hp_IIC_SDA = 1;
	hp_IIC_SCL = 0;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SCL = 0;
}

void bp_iicPushDate(unsigned char pa_ucDat)
{
	unsigned char cnt_ucI = 0;
	for ( cnt_ucI = 0; cnt_ucI < 8; cnt_ucI++)
	{
		hp_IIC_SCL = 0;
		fn_Delay5US();
		hp_IIC_SDA = (pa_ucDat & 0x80)>>7;//判断1或0，移至最低位，送出
		fn_Delay5US();
		hp_IIC_SCL = 1;
		fn_Delay5US();
		pa_ucDat = (pa_ucDat << 1); 
	}
	hp_IIC_SCL = 0;
}

unsigned char bp_iicPullDate(void)
{
	unsigned char m_ucDat = 0;
	unsigned char cnt_ucI = 0;
	hp_IIC_SDA = 1;//释放数据线
	for ( cnt_ucI = 0; cnt_ucI < 8; cnt_ucI++)
	{
		hp_IIC_SCL = 0;
		fn_Delay5US();
		hp_IIC_SCL = 1;
		fn_Delay5US();
		m_ucDat = (m_ucDat << 1);
		if (hp_IIC_SDA)
		{
			m_ucDat |= 0x01; 
		}
	}
	hp_IIC_SCL = 0;
	return (m_ucDat);
}

bit bp_iicCallDevIDAndDatAdd(unsigned char pa_ucDevID,
							unsigned char pa_ucDatAdd)
{
	bp_iicStart();
	bp_iicPushDate(pa_ucDevID);
	bp_iicJudgeACK();
	bp_iicPushDate(pa_ucDatAdd);
	bp_iicJudgeACK();
	return 1;
}

void bp_iicWrDatToDev(unsigned char pa_ucDevID,
					  unsigned char pa_ucStartAdd,
					  unsigned char pa_ucCount,
					  unsigned char *pa_Date)
{
	unsigned char cnt_ucI;
	bp_iicCallDevIDAndDatAdd(pa_ucDevID | IIC_WRITE,
							 pa_ucStartAdd);
	for ( cnt_ucI = 0; cnt_ucI < pa_ucCount; cnt_ucI++)
	{
		bp_iicPushDate(*pa_Date++);
		bp_iicJudgeACK();
	}
	bp_iicStop();

}

void bp_iicRdDatFromDev(unsigned char pa_ucDevID,
					    unsigned char pa_ucStartAdd,
					    unsigned char pa_ucCount,
					  	unsigned char *pa_Date)
{	
	unsigned char cnt_ucI = 0;
	bp_iicCallDevIDAndDatAdd(pa_ucDevID | IIC_WRITE,
							 pa_ucStartAdd);
	bp_iicStart();
	bp_iicPushDate(pa_ucDevID | IIC_READ);
	bp_iicJudgeACK();
	for ( cnt_ucI = 0; cnt_ucI < pa_ucCount; cnt_ucI++)
	{
		*pa_Date = bp_iicPullDate();
		pa_Date++;
		if (cnt_ucI != (pa_ucCount - 1))
		{
			bp_iicAck();
		}
	}
		bp_iicNoACK();
		bp_iicStop();
}