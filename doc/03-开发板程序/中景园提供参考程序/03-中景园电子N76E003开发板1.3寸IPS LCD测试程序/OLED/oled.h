//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018/10/01
//  ����޸�   : 
//  ��������   : ����N76E003��Ƭ������1.3��IPS �ӿ���ʾ��
//              ˵��: 
//              ----------------------------------------------------------------
//						��ʾ��		������
//              GND    	�ӵ�Դ��
//              VCC 	 	��3.3v��Դ
//              SCL   		��P10��SCL��
//              SDA   		��P00��SDA��
//              RES 		��P14
//              DC   		��P13
//              blk  		��P15  ���Ĭ�Ͽ��Բ��� P15�ܽ�N76E003.h��Ĭ��û�������Ҫ�û��Լ����һ��sbit P15				= P1^5;           
//              ----------------------------------------------------------------
// ��    ��   : HuangKai
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018/10/01
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
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0
//SPIͨ��ʱ����
#define OLED_SCLK_Clr() P10=0
#define OLED_SCLK_Set() P10=1
//SPIͨ��������
#define OLED_SDIN_Clr() P00=0
#define OLED_SDIN_Set() P00=1
//OLED��λ�ܽţ��͵�ƽ��λ
#define OLED_RST_Clr() P14=0
#define OLED_RST_Set() P14=1

//SPIͨ��DC�ܽ�
#define OLED_DC_Clr() P13=0
#define OLED_DC_Set() P13=1
//SPIͨ��Ƭѡ�ܽ�
#define OLED_CS_Clr()  P15=0
#define OLED_CS_Set()  P15=1

#define OLED_BLK_Clr()  P15=0
#define OLED_BLK_Set()  P15=1

extern  UINT16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

void Lcd_Init(void); 
void LCD_Clear(UINT16 Color);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_WR_DATA8(char da); //��������-8λ����
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_DrawPoint(UINT16 x,UINT16 y);//����
void LCD_DrawPoint_big(UINT16 x,UINT16 y);//��һ�����
UINT16  LCD_ReadPoint(UINT16 x,UINT16 y); //����
void Draw_Circle(UINT16 x0,UINT16 y0,UINT8 r);
void LCD_DrawLine(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2);
void LCD_DrawRectangle(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2);		   
void LCD_Fill(UINT16 xsta,UINT16 ysta,UINT16 xend,UINT16 yend,UINT16 color);
void LCD_ShowChar(UINT16 x,UINT16 y,UINT8 num,UINT8 mode);//��ʾһ���ַ�
void LCD_ShowNum(UINT16 x,UINT16 y,UINT32 num,UINT8 len);//��ʾ����
void LCD_Show2Num(UINT16 x,UINT16 y,UINT16 num,UINT8 len);//��ʾ2������
void LCD_ShowString(UINT16 x,UINT16 y,const UINT8 *p);		 //��ʾһ���ַ���,16����
 
void showhanzi(unsigned int x,unsigned int y,unsigned char index);



//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


					  		 
#endif  


