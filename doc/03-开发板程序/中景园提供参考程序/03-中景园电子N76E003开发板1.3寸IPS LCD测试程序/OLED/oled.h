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
//******************************************************************************/
#include "Common.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define LCD_W 240
#define LCD_H 240
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

#define OLED_BLK_Clr()  P15=0
#define OLED_BLK_Set()  P15=1

extern  UINT16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void Lcd_Init(void); 
void LCD_Clear(UINT16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(char da); //发送数据-8位参数
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_DrawPoint(UINT16 x,UINT16 y);//画点
void LCD_DrawPoint_big(UINT16 x,UINT16 y);//画一个大点
UINT16  LCD_ReadPoint(UINT16 x,UINT16 y); //读点
void Draw_Circle(UINT16 x0,UINT16 y0,UINT8 r);
void LCD_DrawLine(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2);
void LCD_DrawRectangle(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2);		   
void LCD_Fill(UINT16 xsta,UINT16 ysta,UINT16 xend,UINT16 yend,UINT16 color);
void LCD_ShowChar(UINT16 x,UINT16 y,UINT8 num,UINT8 mode);//显示一个字符
void LCD_ShowNum(UINT16 x,UINT16 y,UINT32 num,UINT8 len);//显示数字
void LCD_Show2Num(UINT16 x,UINT16 y,UINT16 num,UINT8 len);//显示2个数字
void LCD_ShowString(UINT16 x,UINT16 y,const UINT8 *p);		 //显示一个字符串,16字体
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);



//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  


