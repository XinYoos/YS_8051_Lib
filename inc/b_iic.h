#ifndef b_IIC_H__
#define b_IIC_H__
#include <reg52.h>
#include "f_delay.h"
/**
 * [bp_iicStart 主机发送IIC起始信号]
 * @Author   YS
 * @DateTime 2017-03-14T15:46:14+0800
 */
extern void bp_iicStart(void);
/**
 * [bp_iicStop 主机发送IIC终止信号]
 * @Author   YS
 * @DateTime 2017-03-14T15:46:35+0800
 */
extern void bp_iicStop(void);
/**
 * [bp_iicAck 主机应答]
 * @Author   YS
 * @DateTime 2017-03-14T15:47:02+0800
 */
extern void bp_iicAck(void) ;
/**
 * [bp_iicJudgeACK 主机判断从机是否有应答]
 * @Author   YS
 * @DateTime 2017-03-14T15:47:24+0800
 * @return                            [0有应答，1无应答]
 */
extern bit bp_iicJudgeACK(void);
/**
 * [bp_iicNoACK 主机不应答，使从机停止发送]
 * @Author   YS
 * @DateTime 2017-03-14T15:49:05+0800
 */
extern void bp_iicNoACK(void);
/**
 * [bp_iicPushDate 主机向总线发送8位(byte)数据]
 * @Author   YS
 * @DateTime 2017-03-14T15:49:42+0800
 * @param    pa_ucDat                 [要发送的数据]
 */
extern void bp_iicPushDate(unsigned char pa_ucDat);
/**
 * [bp_iicPullDate 主机从总线读取8位(byte)数据]
 * @Author   YS
 * @DateTime 2017-03-14T15:50:57+0800
 * @return                            [读取的数据]
 */
extern unsigned char bp_iicPullDate(void);
/**
 * [bp_iicCallDevIDAndDatAdd 主机呼叫从机ID，并对从机寻址or写控制码]
 * @Author   YS
 * @DateTime 2017-03-14T16:00:01+0800
 * @param    pa_ucDevID               [设备ID]
 * @param    pa_ucDatAdd              [寻址地址or控制码]
 * @return                            [完毕后，返回1]
 */
extern bit bp_iicCallDevIDAndDatAdd(unsigned char pa_ucDevID,
								   unsigned char pa_ucDatAdd);
/**
 * [bp_iicWrDatToDev 主机向从机写入指定字节量的数据]
 * @Author   YS
 * @DateTime 2017-03-14T16:03:41+0800
 * @param    pa_ucDevID               [从机ID]
 * @param    pa_ucStartAdd            [开始地址]
 * @param    pa_ucCount               [写入字节的数量]
 * @param    pa_Date                  [写入数据地址的头指针]
 */
extern void bp_iicWrDatToDev(unsigned char pa_ucDevID,
					         unsigned char pa_ucStartAdd,
					  		 unsigned char pa_ucCount,
					  		 unsigned char *pa_Date);
/**
 * [bp_iicRdDatFromDev 主机从从机读出指定字节量的数据]
 * @Author   YS
 * @DateTime 2017-03-14T16:17:32+0800
 * @param    pa_ucDevID               [从机ID]
 * @param    pa_ucStartAdd            [开始地址]
 * @param    pa_ucCount               [读出字节的数量]
 * @param    pa_Date                  [读出数据存储地址的头指针]
 */
extern void bp_iicRdDatFromDev(unsigned char pa_ucDevID,
					    unsigned char pa_ucStartAdd,
					    unsigned char pa_ucCount,
					  	unsigned char *pa_Date);
#endif