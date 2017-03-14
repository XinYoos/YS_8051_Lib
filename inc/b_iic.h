#ifndef b_IIC_H__
#define b_IIC_H__
#include <reg52.h>
#include "f_delay.h"
extern void bp_iicStart(void);//主机发送IIC起始信号
extern void bp_iicStop(void);//主机发送IIC终止信号
extern void bp_iicAck(void) ;//主机应答
extern bit bp_iicJudgeACK(void);//主机判断从机是否有应答
extern void bp_iicNoACK(void);//主机不应答使从机停止发送
extern void bp_iicPushDate(unsigned char pa_ucDat);//主机向总线发送8位数据
extern unsigned char bp_iicPullDate(void);//主机从总线读取8位数据
extern bit bp_iicCallDevIDAndDatAdd(unsigned char pa_ucDevID,
								   unsigned char pa_ucDatAdd);
extern void bp_iicWrDatToDev(unsigned char pa_ucDevID,
					         unsigned char pa_ucStartAdd,
					  		 unsigned char pa_ucCount,
					  		 unsigned char *pa_Date);

extern void bp_iicRdDatFromDev(unsigned char pa_ucDevID,
					    unsigned char pa_ucStartAdd,
					    unsigned char pa_ucCount,
					  	unsigned char *pa_Date);
#endif