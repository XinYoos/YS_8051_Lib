#include "b_iic.h"

#define IIC_WRITE 0x00
#define IIC_READ  0x01
/**
 * 硬件设计决定：SCL和SDA---HP
 */
sbit hp_IIC_SCL = P2^0;
sbit hp_IIC_SDA = P2^1;

/**
 * [bp_iicStart 主机发送IIC起始信号]
 * @Author   YS
 * @DateTime 2017-03-14T15:46:14+0800
 */
void bp_iicStart(void)
{
	hp_IIC_SDA = 1;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SDA = 0;
	fn_Delay5US();
}
/**
 * [bp_iicStop 主机发送IIC终止信号]
 * @Author   YS
 * @DateTime 2017-03-14T15:46:35+0800
 */
void bp_iicStop(void)
{
	hp_IIC_SDA = 0;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SDA = 1;
}
/**
 * [bp_iicAck 主机应答]
 * @Author   YS
 * @DateTime 2017-03-14T15:47:02+0800
 */
void bp_iicAck(void)                      
{ 
	hp_IIC_SCL = 0;
	hp_IIC_SDA = 0;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();  
	hp_IIC_SCL = 0;
	fn_Delay5US();
	hp_IIC_SDA = 1;	// 释放总线
}
/**
 * [bp_iicJudgeACK 主机判断从机是否有应答]
 * @Author   YS
 * @DateTime 2017-03-14T15:47:24+0800
 * @return                            [0有应答，1无应答]
 */
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
	fn_Delay5US();
	return m_btACK;//0有应答，1无应答
}
/**
 * [bp_iicNoACK 主机不应答，使从机停止发送]
 * @Author   YS
 * @DateTime 2017-03-14T15:49:05+0800
 */
void bp_iicNoACK(void)
{
	hp_IIC_SDA = 1;
	hp_IIC_SCL = 0;
	fn_Delay5US();
	hp_IIC_SCL = 1;
	fn_Delay5US();
	hp_IIC_SCL = 0;
}
/**
 * [bp_iicPushDate 主机向总线发送8位(byte)数据]
 * @Author   YS
 * @DateTime 2017-03-14T15:49:42+0800
 * @param    pa_ucDat                 [要发送的数据]
 */
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
/**
 * [bp_iicPullDate 主机从总线读取8位(byte)数据]
 * @Author   YS
 * @DateTime 2017-03-14T15:50:57+0800
 * @return                            [读取的数据]
 */
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
/**
 * [bp_iicCallDevIDAndDatAdd 主机呼叫从机ID，并对从机寻址or写控制码]
 * @Author   YS
 * @DateTime 2017-03-14T16:00:01+0800
 * @param    pa_ucDevID               [设备ID]
 * @param    pa_ucDatAdd              [寻址地址or控制码]
 * @return                            [完毕后，返回1]
 */
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
/**
 * [bp_iicWrDatToDev 主机向从机写入指定字节量的数据]
 * @Author   YS
 * @DateTime 2017-03-14T16:03:41+0800
 * @param    pa_ucDevID               [从机ID]
 * @param    pa_ucStartAdd            [开始地址]
 * @param    pa_ucCount               [写入字节的数量]
 * @param    pa_Date                  [写入数据地址的头指针]
 */
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
/**
 * [bp_iicRdDatFromDev 主机从从机读出指定字节量的数据]
 * @Author   YS
 * @DateTime 2017-03-14T16:17:32+0800
 * @param    pa_ucDevID               [从机ID]
 * @param    pa_ucStartAdd            [开始地址]
 * @param    pa_ucCount               [读出字节的数量]
 * @param    pa_Date                  [读出数据存储地址的头指针]
 */
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