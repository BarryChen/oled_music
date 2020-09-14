//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018/10/01
//  最近修改   : 
//  功能描述   : 新唐N76E003单片机驱动LED灯实验

// 作    者   : HuangKai
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018/10/01
//All rights reserved
//******************************************************************************/
#include <stdio.h>
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_Define.h"

void main (void) 
{
	unsigned char i,t;
	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	InitialUART0_Timer3(115200);
	set_CLOEN;  
	
		t=' ';
  while(1)
  {
		i--;

		clr_GPIO1;												// Tiny board GPIO1 LED define in Common.h
			Timer2_Delay1ms(300);
			set_GPIO1;
			Timer2_Delay1ms(300);
			Send_Data_To_UART0(0x55);					//UART0 send ascii "U"
		
		P3M1 = 0xff;
		P3M2 = 0x00;
		P3M1 = 0x00;
		P3M2 = 0x00;
		if(P30) P10 = 1; 
		else P10 = 0;
		i += 6;
	}	  
	
}
