#include "Common.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0
//SPIͨ��ʱ����
#define OLED_SCLK_Clr() P13=0
#define OLED_SCLK_Set() P13=1
//SPIͨ��������
#define OLED_SDIN_Clr() P00=0
#define OLED_SDIN_Set() P00=1
//OLED��λ�ܽţ��͵�ƽ��λ
#define OLED_RST_Clr() P20=0
#define OLED_RST_Set() P20=1

//SPIͨ��DC�ܽ�
#define OLED_DC_Clr() P14=0
#define OLED_DC_Set() P14=1
//SPIͨ��Ƭѡ�ܽ�
#define OLED_CS_Clr()  P12=0
#define OLED_CS_Set()  P12=1



//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   

void delay_ms(unsigned int ms);


 		     

//OLED�����ú���
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
void OLED_ShowBtImage32X32(UINT8 x,UINT8 y,UINT8 no);
void OLED_ShowPpImage32X32(UINT8 x,UINT8 y,UINT8 no);
void OLED_ShowImage16X32(UINT8 x,UINT8 y,UINT8 no);
void OLED_Init_picture(void);
void OLED_Clear_picture(void);
unsigned char LCD12864_Busy(void);



#endif  
	 



