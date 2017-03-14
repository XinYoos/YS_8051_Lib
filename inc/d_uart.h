#ifndef d_UART_H__
#define d_UART_H__
#include <reg52.h>
#include <stdio.h>
extern void dv_InitUart(void);//初始化串口通信
extern void fn_SendChar_uc(unsigned char pa_ucDate);//向串口发送出一个字符
extern void fn_SendString_puc(unsigned char *pa_pucStr);//向串口发送一个字符串
extern void Debug_PrintfDebug_pi(int* pa_piPrintdVariable);//调用printf()向串口发送要监测的值和一连串Debug用信息
extern void Debug_PrintfDebug_puc(unsigned char *pa_piPrintdVariable);
extern void fn_PrintStr_pi(int* pa_piPrintdVariable);//调用printf()向串口发送要监测的值
extern void fn_PrintStr_puc(unsigned char* pa_piPrintdVariable);
#endif