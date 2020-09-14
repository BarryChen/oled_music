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
//  功能描述   : 新唐N76E003单片机驱动1.3寸IPS 接口显示屏
//              说明: 
//              ----------------------------------------------------------------
//						显示屏		开发板
//              GND    	接电源地
//              VCC 	 	接3.3v电源
//              SCL   		接P10（SCL）
//              SDA   		接P00（SDA）
//              RES 		接P14
//              DC   		接P13
//              blk  		接P15  这个默认可以不接 P15管脚N76E003.h中默认没有添加需要用户自己添加一下sbit P15				= P1^5;           
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
UINT8 ref=0;//刷新显示
UINT16 vx=15542,vy=11165;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
UINT16 chx=140,chy=146;//默认像素点坐标为0时的AD起始值
void xianshi()//显示信息
{   
	UINT16 lx,ly;
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	showhanzi(10,0,0);  //中
	showhanzi(45,0,1);  //景
	showhanzi(80,0,2);  //园
	showhanzi(115,0,3);  //电
	showhanzi(150,0,4);  //子
  LCD_ShowString(10,35,"1.3 IPS-SPI 240*320");
	LCD_ShowString(10,55,"LCD_W:");	LCD_ShowNum(70,55,LCD_W,3);
	LCD_ShowString(110,55,"LCD_H:");LCD_ShowNum(160,55,LCD_H,3);	
	  LCD_ShowString(10,35,"1.3 IPS-SPI 240*320");
	lx=10;ly=75;			
}



void showimage() //显示40*40图片；这里因为本单片机空间比较小；把图片显示去掉了；
{
  	int i,j,k; 

	for(k=2;k<6;k++)
	{
	   	for(j=0;j<6;j++)
		{	
			Address_set(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<1600;i++)
			 { 	
				 		
			  //	 LCD_WR_DATA8(image[i*2+1]);	 //显示40*40图片；这里因为本单片机空间比较小；把图片显示去掉了；
				// LCD_WR_DATA8(image[i*2]);			//显示40*40图片；这里因为本单片机空间比较小；把图片显示去掉了；	
			 }	
		 }
	}
	ref=0;
}
void main (void) 
{
	unsigned char i,t;
	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	InitialUART0_Timer3(115200);
	set_CLOEN;  
	 Lcd_Init();			//初始化OLED  
	
	LCD_Clear(WHITE); //清屏
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 

	xianshi(); //显示信息
  //  showimage(); //显示40*40图片
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
