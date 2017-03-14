
#include "d_uart.h"

#ifndef hp_XTAL
#define hp_XTAL 11.0598//晶振频率
#endif
#ifndef hp_BAUD_RATE
#define hp_BAUD_RATE 9600//波特率
#endif

/**
 * [dv_InitUart 初始化串口通信]
 * @Author   YS
 * @DateTime 2017-03-07T16:05:39+0800
 */
void dv_InitUart(void)
{
	// AUXR &= 0xBF;//定时器1时钟为Fosc/12,即12T
	// AUXR &= 0xFE;//串口1选择定时器1为波特率发生器

	TMOD &= 0X0f;//清空定时器1
	TMOD |= 0X20;//配置定时器1为方式2(自动重装模式)
	// TL1 = TH1 = 256 - hp_XTAL * 1000000 / 12 / 32 / hp_BAUD_RATE;//计算定时器初值//不对，调试有乱码
	TH1 = TL1 = 0xfd;//设置波特率9600bps///
	PCON |= 0x00;//SMOD=0波特率不翻倍//

	// SCON |= 0x50;//串口方式1，REN=1:使能接收
	SCON |= 0x40;//串口方式1，REN=0:不接收
	TI = 0;
	RI = 0;

	TR1 = 1;//定时器1使能
	ES = 1;//串口中断使能
}

/**
 * [fn_SendChar_uc 发字符]
 * @Author   YS
 * @DateTime 2017-02-26T09:53:47+0800
 * @param    pa_ucDate                :发送的字符
 */
void fn_SendChar_uc(unsigned char pa_ucDate)
{
    SBUF = pa_ucDate;
    while(!TI);
    TI = 0;
}
/**
 * [fn_SendString_puc 发字符串]
 * @Author   YS
 * @DateTime 2017-02-26T09:54:29+0800
 * @param    pa_pucStr                 :发送的字符串
 */
void fn_SendString_puc(unsigned char *pa_pucStr)
{
    while(*pa_pucStr)
    {
        fn_SendChar_uc(*pa_pucStr++);
        // pa_pucStr++;//或直接fn_SendChar_uc(*pa_pucStr++);
    }
}
/**
 * [Debug_PrintfDebug_pi 监控int型变量的值并向串口发送]
 * @Author   YS
 * @DateTime 2017-02-28T15:38:31+0800
 * @param    pa_piPrintdVariable       :需监控的变量,&int
 */
void Debug_PrintfDebug_pi(int* pa_piPrintdVariable)
{
    int m_iVal;
    m_iVal = *pa_piPrintdVariable;

    fn_SendString_puc(" \n");
    fn_SendString_puc("/========Debug=========/\n");

    TI = 1;
    printf("可改名:值为%d\n", m_iVal);
    while(!TI);
    TI = 0;

    fn_SendString_puc("/*=====DebugOver=====*/\n");
}
/**
 * [Debug_PrintfDebug_pi 监控unChar型变量的值并向串口发送]
 * @Author   YS
 * @DateTime 2017-02-28T15:38:31+0800
 * @param    pa_piPrintdVariable       :需监控的变量,&unChar
 */
void Debug_PrintfDebug_puc(unsigned char *pa_piPrintdVariable)
{
    unsigned char m_iVal;
    m_iVal = *pa_piPrintdVariable;

    fn_SendString_puc(" \n");
    fn_SendString_puc("/========Debug=========/\n");

    TI = 1;
    printf("可改名:值为%d\n", m_iVal);
    while(!TI);
    TI = 0;

    fn_SendString_puc("/*=====DebugOver=====*/\n");
}
/**
 * [fn_PrintStr_pi 执行一次Printf函数，发送实参int型变量值]
 * @Author   YS
 * @DateTime 2017-03-07T15:59:23+0800
 * @param    pa_piPrintdVariable      ：要发送的变量值,&int
 */
void fn_PrintStr_pi(int* pa_piPrintdVariable)
{
	int m_iVal;
    m_iVal = *pa_piPrintdVariable;

	TI = 1;
	printf("%d\n", m_iVal);
	while(!TI);
	TI = 0;
}
/**
 * [fn_PrintStr_pi 执行一次Printf函数，发送实参unChar型变量值]
 * @Author   YS
 * @DateTime 2017-03-07T15:59:23+0800
 * @param    pa_piPrintdVariable      ：要发送的变量值,&unChar
 */
void fn_PrintStr_puc(unsigned char* pa_piPrintdVariable)
{
	unsigned char m_iVal;
    m_iVal = *pa_piPrintdVariable;

	TI = 1;
	printf("%d\n", m_iVal);
	while(!TI);
	TI = 0;
}
/**
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * 测试用例
 */
/**
#include <reg52.h>
#include "d_uart.h"
#include "f_delay.h"

 void main(void)
{
	int m_iNumber = 222;

	EA = 1;
	dv_InitUart();

	while(1)
	{
		Debug_PrintfDebug_pi(&m_iNumber);
		fn_DelayMS_ui(1000);
		fn_PrintStr_pi(&m_iNumber);
		fn_DelayMS_ui(1000);
	}
}
*/