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
//  功能描述   : 新唐N76E003单片机驱动0.96寸OLED SPI接口显示屏
//              说明: 
//              ----------------------------------------------------------------
//						显示屏		开发板
//              GND    	接电源地
//              VCC 	 	接3.3v电源
//              D0   		接P10（SCL）
//              D1   		接P00（SDA）
//              RES 		接P14
//              DC   		接P13
//              CS   		接P15   P15管脚N76E003.h中默认没有添加需要用户自己添加一下sbit P15				= P1^5;           
//              ----------------------------------------------------------------
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
#include "oled.h"
#include "bmp.h"

void main (void) 
{
	unsigned char i,t;
	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	InitialUART0_Timer3(115200);
	set_CLOEN;  
  				OLED_Init();			//初始化OLED  
	
		t=' ';
  while(1)
  {
		i--;
		OLED_Clear();

		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
		OLED_ShowCHinese(0,2,7);//中
		OLED_ShowCHinese(18,2,8);//景
		OLED_ShowString(34,2,"N76E003 BRD");
	//	OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 	OLED_ShowString(20,4,"2018/10/29");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		OLED_ShowChar(48,6,t);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			
		
		delay_ms(500);
			delay_ms(500);
			
				delay_ms(500);
				
					delay_ms(500);
					
						delay_ms(500);
		OLED_Clear();
		delay_ms(500);
		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(500);
		OLED_DrawBMP(0,0,128,8,BMP2);
		delay_ms(500);
		
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
