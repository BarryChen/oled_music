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
#include "Common.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0
//SPI通信时钟线
#define OLED_SCLK_Clr() P10=0
#define OLED_SCLK_Set() P10=1
//SPI通信数据线
#define OLED_SDIN_Clr() P00=0
#define OLED_SDIN_Set() P00=1
//OLED复位管脚，低电平复位
#define OLED_RST_Clr() P14=0
#define OLED_RST_Set() P14=1

//SPI通信DC管脚
#define OLED_DC_Clr() P13=0
#define OLED_DC_Set() P13=1
//SPI通信片选管脚
#define OLED_CS_Clr()  P15=0
#define OLED_CS_Set()  P15=1



//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   

void delay_ms(unsigned int ms);


 		     

//OLED控制用函数
void OLED_WR_Byte(UINT8 dat,UINT8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(UINT8 x,UINT8 y,UINT8 t);
void OLED_Fill(UINT8 x1,UINT8 y1,UINT8 x2,UINT8 y2,UINT8 dot);
void OLED_ShowChar(UINT8 x,UINT8 y,UINT8 chr);
void OLED_ShowNum(UINT8 x,UINT8 y,UINT32 num,UINT8 len,UINT8 size2);
void OLED_ShowString(UINT8 x,UINT8 y, UINT8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(UINT8 x,UINT8 y,UINT8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



