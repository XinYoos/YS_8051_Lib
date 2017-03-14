#ifndef f_DELAY_H__////
#define f_DELAY_H__////条件编译和宏定义,避免在多文件中重复编译
#include <intrins.h>
//#include "common.h"//我不需要这个
extern void fn_DelayMS_ui(unsigned int pa_ValMS);
extern void fn_Delay5US(void);
#endif////