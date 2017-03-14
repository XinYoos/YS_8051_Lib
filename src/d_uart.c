
#include "d_uart.h"

#ifndef hp_XTAL
#define hp_XTAL 11.0598//����Ƶ��
#endif
#ifndef hp_BAUD_RATE
#define hp_BAUD_RATE 9600//������
#endif

/**
 * [dv_InitUart ��ʼ������ͨ��]
 * @Author   YS
 * @DateTime 2017-03-07T16:05:39+0800
 */
void dv_InitUart(void)
{
	// AUXR &= 0xBF;//��ʱ��1ʱ��ΪFosc/12,��12T
	// AUXR &= 0xFE;//����1ѡ��ʱ��1Ϊ�����ʷ�����

	TMOD &= 0X0f;//��ն�ʱ��1
	TMOD |= 0X20;//���ö�ʱ��1Ϊ��ʽ2(�Զ���װģʽ)
	// TL1 = TH1 = 256 - hp_XTAL * 1000000 / 12 / 32 / hp_BAUD_RATE;//���㶨ʱ����ֵ//���ԣ�����������
	TH1 = TL1 = 0xfd;//���ò�����9600bps///
	PCON |= 0x00;//SMOD=0�����ʲ�����//

	// SCON |= 0x50;//���ڷ�ʽ1��REN=1:ʹ�ܽ���
	SCON |= 0x40;//���ڷ�ʽ1��REN=0:������
	TI = 0;
	RI = 0;

	TR1 = 1;//��ʱ��1ʹ��
	ES = 1;//�����ж�ʹ��
}

/**
 * [fn_SendChar_uc ���ַ�]
 * @Author   YS
 * @DateTime 2017-02-26T09:53:47+0800
 * @param    pa_ucDate                :���͵��ַ�
 */
void fn_SendChar_uc(unsigned char pa_ucDate)
{
    SBUF = pa_ucDate;
    while(!TI);
    TI = 0;
}
/**
 * [fn_SendString_puc ���ַ���]
 * @Author   YS
 * @DateTime 2017-02-26T09:54:29+0800
 * @param    pa_pucStr                 :���͵��ַ���
 */
void fn_SendString_puc(unsigned char *pa_pucStr)
{
    while(*pa_pucStr)
    {
        fn_SendChar_uc(*pa_pucStr++);
        // pa_pucStr++;//��ֱ��fn_SendChar_uc(*pa_pucStr++);
    }
}
/**
 * [Debug_PrintfDebug_pi ���int�ͱ�����ֵ���򴮿ڷ���]
 * @Author   YS
 * @DateTime 2017-02-28T15:38:31+0800
 * @param    pa_piPrintdVariable       :���صı���,&int
 */
void Debug_PrintfDebug_pi(int* pa_piPrintdVariable)
{
    int m_iVal;
    m_iVal = *pa_piPrintdVariable;

    fn_SendString_puc(" \n");
    fn_SendString_puc("/========Debug=========/\n");

    TI = 1;
    printf("�ɸ���:ֵΪ%d\n", m_iVal);
    while(!TI);
    TI = 0;

    fn_SendString_puc("/*=====DebugOver=====*/\n");
}
/**
 * [Debug_PrintfDebug_pi ���unChar�ͱ�����ֵ���򴮿ڷ���]
 * @Author   YS
 * @DateTime 2017-02-28T15:38:31+0800
 * @param    pa_piPrintdVariable       :���صı���,&unChar
 */
void Debug_PrintfDebug_puc(unsigned char *pa_piPrintdVariable)
{
    unsigned char m_iVal;
    m_iVal = *pa_piPrintdVariable;

    fn_SendString_puc(" \n");
    fn_SendString_puc("/========Debug=========/\n");

    TI = 1;
    printf("�ɸ���:ֵΪ%d\n", m_iVal);
    while(!TI);
    TI = 0;

    fn_SendString_puc("/*=====DebugOver=====*/\n");
}
/**
 * [fn_PrintStr_pi ִ��һ��Printf����������ʵ��int�ͱ���ֵ]
 * @Author   YS
 * @DateTime 2017-03-07T15:59:23+0800
 * @param    pa_piPrintdVariable      ��Ҫ���͵ı���ֵ,&int
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
 * [fn_PrintStr_pi ִ��һ��Printf����������ʵ��unChar�ͱ���ֵ]
 * @Author   YS
 * @DateTime 2017-03-07T15:59:23+0800
 * @param    pa_piPrintdVariable      ��Ҫ���͵ı���ֵ,&unChar
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
 * ��������
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