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
#include <stdlib.h>
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_Define.h"
#include "oled.h"
#include "bmp.h"

#define PlayPause                (P03==0) && (P04==1)            //LED0,AVRCP_Play_Pause
#define V_Up                     P04==0                   //LED1,Volume_Up 
#define V_Down                   P05==0                   //LED2,Volume_Down 
#define Connected                (P03==0) && (P04==0)      //LED0  LED1,A2DP_Connected
#define Disconnected             (P04==0) && (P05==0)    //LED1  LED2,A2DP_Connected
#define RPDL                     (P03==0) && (P05==0)  //LED0  LED2,Reset Paired Device List
#define StreamingA2DP            (P30==1)               //BT_08
#define Call_Active               (P06==1)         //BT_00
#define Call_Incoming             (P01==1)         //BT_21
#define Call_Outgoing             (P07==1)        //BT01






void BT_Connected_Events_Count();
void Gpio_Key_Init();
void OLED_Gpio_Int();
void Display_BT1_ON();
void Display_BT1_OFF(void);
void Display_BT2_ON(void);
void Display_BT2_OFF(void);
void Display_Pairing_States(void);
void Display_Connected1(void);
void Display_Connected2(void);
void BT_Connected_Events_Count(void);
void Displays_BT_Icon_Contro(void);
void BT_Disconnected_Events_Count(void);
void Display_Play(void);
void Display_Pause(void);
void Displays_PlayPause_Icon_Contro(void);
void Display_Volume(void);
void Display_Volume_Value(void);
void Display_Device_Name(void);
void BT_A2DP_Volume_Events_UP(void);
void BT_A2DP_Volume_Events_Down(void);
void Display_Volume_Value_Max(void);
void Display_Volume_Value_Min(void);
void Display_Call_Outgoing(void);
void Display_Call_Incoing(void);
void Display_Call_Active(void);


/*sfr   PIF         =  0xec;
sbit  PIF0        =  PIF^0;
sbit  PIF1        =  PIF^1;
sbit  PIF2        =  PIF^2;
sbit  PIF3        =  PIF^3;
sbit  PIF4        =  PIF^4;
sbit  PIF5        =  PIF^5;
sbit  PIF6        =  PIF^6;
sbit  PIF7        =  PIF^7;
*/


uint16_t Connected_Events_Count=0;
uint16_t Connected_Events_Count_Change=0;
uint16_t PlayPause_Events_Count=0;
uint16_t PlayPause_Events_Count_Change=0;
uint16_t A2DP_Volume_Value=11;
uint16_t A2DP_Volume_Value_Change=11;
xdata unsigned char dis_data[32][16];//
unsigned char dis_rdata[16];  //
unsigned char dis_rdata[16]; 
unsigned char *YINYUE;
unsigned timer0h, timer0l,time;  
unsigned a = 0;
float Running = 0;//????

//GPIO 初始化..................................................................................

void Gpio_Key_Init()
{
	//P03_INT_LED0..............................................
	P03_Input_Mode;			
	P03_PushPull_Mode;
  Enable_BIT3_LowLevel_Trig;
	
	//P04_INT_LED1..................................................................
	P04_Input_Mode;			
	P04_PushPull_Mode;
  Enable_BIT4_LowLevel_Trig;
	
	//P05_INT_LED2.............................
	P05_Input_Mode;			
	P05_PushPull_Mode;
  Enable_BIT5_LowLevel_Trig;
	
	//P17_BT08..............................................
	/*P30_Input_Mode;
	P30_PushPull_Mode;
	Enable_BIT0_RasingEdge_Trig;*/
		
	//P01_BT21...........................................
	//P01_Input_Mode;
	//P01_OpenDrain_Mode;
	//Enable_BIT0_HighLevel_Trig;
	
	//P07_BT_01..........................
	P07_Input_Mode;
	P07_OpenDrain_Mode;
	Enable_BIT7_HighLevel_Trig;
	
	//P01_BT21
	P01_Input_Mode;
	P01_OpenDrain_Mode;
	Enable_BIT1_HighLevel_Trig;
	
	//P06_BT00....................
	/*P06_Input_Mode;
	P06_OpenDrain_Mode;
	Enable_BIT6_HighLevel_Trig;*/
	
	
	
	
	
	
	
	set_EPI;							// Enable pin interrupt
	//set_EX0;
  set_EA;								// global enable bit
}

//OLED_GPIO初始化..................................................

void OLED_Gpio_Int()
{
	P00_Quasi_Mode;
	P11_Quasi_Mode;
	P12_Quasi_Mode;
	P14_Quasi_Mode;
	P13_Quasi_Mode;
}
//IO中断函数...................................................
void PinInterrupt_ISR (void) interrupt 7
{
	if(PIF == 0x08) 
	{  
		delay_ms(10);
		
		if(PlayPause)
		{
			if(PlayPause_Events_Count==0)
			{
				PlayPause_Events_Count=1;
				
			}
			
			else if(PlayPause_Events_Count==1)
			{
				PlayPause_Events_Count=0;
				Display_Play();
			}
		}
		
		
		if(Connected )     
		{
		 delay_ms(10);
		 if(Connected )
		 {
			BT_Connected_Events_Count();
		 }
		}
		
		
		if(RPDL)
		{
			delay_ms(10);
		}
		
	
		
	}
	
//.......................................................................	
	
	if(PIF == 0x10)
	{
	 if(V_Up)
	 {
		 delay_ms(50);
		 if(V_Up)
		 {
			 delay_ms(50);
			 BT_A2DP_Volume_Events_UP();
		 }
	 }
	 
	 if(Connected )
	 {
		 delay_ms(50);
		 if(Connected )
		 {
			 BT_Connected_Events_Count();
		 }
	 }
	 
	 
	 if(Disconnected)     
	 { 
		delay_ms(10);
		if(Disconnected)
		{
		 BT_Disconnected_Events_Count();
		}
	 }
  }
	
//............................................
	
	if(PIF == 0x20)
	{
	 if(V_Down)
	 {
		 delay_ms(10);
		 if(V_Down)
		 {
			 delay_ms(50);
			 BT_A2DP_Volume_Events_Down();
		 }
	 }
	 
	 if(RPDL )
	 {
		 delay_ms(10);
		 if(RPDL)
		 {
		 }
	 }
	 
	 
	 if(Disconnected)     
	 { 
		delay_ms(10);
		if(Disconnected)
		{
		 BT_Disconnected_Events_Count();
		}
	 }
  }
	
//...................................................................

  /*if(PIF == 0x00) 
	{
		Display_BT2_ON();
		if(StreamingA2DP)
		{
		  Display_BT2_ON();
			PlayPause_Events_Count=1;
		}
		
	}*/
	
//........................................	
	/*if(PIF == 0x02) 
	{
		Display_BT2_ON();
		if(StreamingA2DP)
		{
			PlayPause_Events_Count=1;
		}
		
	}*/
//............................................................................
  if(PIF == 0x80) 
	{
		if(Call_Outgoing)
		{
		  delay_ms(10);
			Display_Call_Outgoing();
		}
	}
	//.............................................
	if(PIF == 0x02)
	{
		if(Call_Incoming)
		{
			delay_ms(10);
			Display_Call_Incoing();
		}
	}
	
	//...................................................
	/*if(PIF == 0x40)
	{
		if(Call_Active)
		{
			delay_ms(10);
			Display_Call_Active();
		}
	}*/



}

//.............................................................................................


//显示屏显示.........................................................
void Display_BT1_ON(void)
{
  OLED_ShowBtImage32X32(0,0,0);
}

void Display_BT1_OFF(void)
{
  OLED_ShowBtImage32X32( 0,0,1);
}

void Display_BT2_ON(void)
{
  OLED_ShowBtImage32X32( 27,0,0);
}

void Display_BT2_OFF(void)
{
  OLED_ShowBtImage32X32( 27,0,1);
}

void Display_Play(void)
{
	OLED_ShowPpImage32X32(54,0,3);
}

void Display_Pause(void)
{
	OLED_ShowPpImage32X32(54,0,2);
}

void Display_Volume(void)
{
	OLED_ShowImage16X32(90,0,0);
}

void Display_Volume_Value(void)
{
	OLED_ShowNum(108,2,A2DP_Volume_Value,2,20);
}

void Display_Device_Name(void)
{
	OLED_ShowString(25,4,"MPOW 8888     ");
}

void Display_Volume_Value_Max(void)
{
	OLED_ShowString(108,2,"Mx");
	
}

void Display_Volume_Value_Min(void)
{
	OLED_ShowString(108,2,"Mi");
}

void Display_Call_Outgoing(void)
{
	OLED_ShowString(25,4,"Call_Outgoing");
}

void Display_Call_Incoing(void)
{
	OLED_ShowString(25,4,"Call_Incoing");
}

void Display_Call_Active(void)
{
	OLED_ShowString(25,4,"Call_Active");
}




//................................................................

void Display_Pairing_States(void)
{
  Display_BT1_ON();
  delay_ms(300);
  Display_BT1_OFF();
	delay_ms(300);
}

void Display_Connected1(void)
{
  Display_BT1_ON();
}

void Display_Connected2(void)
{
  Display_BT2_ON();
}

//........................................................................

void BT_Connected_Events_Count(void)
{
  if(Connected_Events_Count==2)
 	{
 	  Connected_Events_Count=Connected_Events_Count;
 	}

  else
  	{
  	  Connected_Events_Count=Connected_Events_Count+1;
  	}
}


//............................
void BT_A2DP_Volume_Events_UP(void)
{
	if((A2DP_Volume_Value<15)&&(!(Connected_Events_Count==0)))
	{
		A2DP_Volume_Value=A2DP_Volume_Value+1;
	}
	
  /*else if(A2DP_Volume_Value==15)
	{
	  Display_Volume_Value_Max();
	}*/
}

//......................................................
void BT_A2DP_Volume_Events_Down(void)
{
	if((A2DP_Volume_Value>0 && A2DP_Volume_Value<=15) && (!(Connected_Events_Count==0)))
	{
		A2DP_Volume_Value=A2DP_Volume_Value-1;
  }
	
	/*else if(A2DP_Volume_Value==0)
	{
		Display_Volume_Value_Min();
	}*/
}

//...............................................
void BT_Disconnected_Events_Count(void)
{
  if(Connected_Events_Count==0)
 	{
 	  Connected_Events_Count=Connected_Events_Count;
 	}

  else
  {
		if(Connected_Events_Count==2)
		{
			Connected_Events_Count=Connected_Events_Count-1;
		}
		else if(Connected_Events_Count==1)
		{
			Connected_Events_Count=Connected_Events_Count-1;
			//Play_Count=0;
		}

  }
}

//...........................................................................

void Displays_BT_Icon_Contro(void)
{
  if(!(Connected_Events_Count_Change==Connected_Events_Count))
  {
   switch(Connected_Events_Count)
   {
		 case 0:
    {
     Display_BT1_OFF();
     Display_BT2_OFF();
		 Connected_Events_Count_Change=Connected_Events_Count;
		 break;
		}
     
    

		 case 1:
    {
     Display_BT2_OFF();
     Display_Connected1();
		 Connected_Events_Count_Change=Connected_Events_Count;
		 break;
     
    }

		 case 2:
    {
     Display_Connected1();
	   Display_Connected2();
		 Connected_Events_Count_Change=Connected_Events_Count;
		 break;
     
    }
   }
  }
  
  if(Connected_Events_Count==0)
  {
   Display_Pairing_States();
  }
}

//........................................................................
void Displays_PlayPause_Icon_Contro(void)
{
	if(!(PlayPause_Events_Count_Change==PlayPause_Events_Count))
	{
		if(PlayPause_Events_Count==0)
		{
			Display_Pause();
			PlayPause_Events_Count_Change=PlayPause_Events_Count;
		}
		
		else if(PlayPause_Events_Count==1)
		{
			Display_Play();
			PlayPause_Events_Count_Change=PlayPause_Events_Count;
		}
	}
}

//................................................
void Displays_A2DP_Volume_Value_Icon_Contro(void)
{
	if(!(A2DP_Volume_Value==A2DP_Volume_Value_Change))
	{
		Display_Volume_Value();
	}
}

unsigned int random(unsigned int xxx)
{
#define MIN 0
#define MAX 7

	unsigned int value;
	srand(xxx);
	a = rand();
	//value = rand() % (MAX + 1 - MIN)+ MIN;               //获取一个随机数(1-16)
	return value;
}


#define MAX_HIGHT 4
void OLED_Show_By_Hight()
{
	UINT8 i,j,k;
	static uint8_t pi_id=0;
	UINT8 hight[16];
	uint8_t random_num[]={
		3,0,2,3,6,8,1,3,5,3,5,6,7,2,4,5,6,1,1,2,3,4,5,6,7,3,
		1,4,3,0,2,8,3,5,5,2,4,0,3,2,1,4,5,2,4,3,1,4,2,0,1
	};
 	for(i=0; i<16; i++,pi_id++)
 	{
		if(pi_id>=sizeof(random_num)/sizeof(uint8_t))
			pi_id = 0;
		hight[i] = random_num[pi_id];
 	}

			
	for(k=0; k<16; k++)
	{
		//1、处理进来的参数
		hight[k] = hight[k] % MAX_HIGHT;
		if(hight[k]<0)
			hight[k] = 0;

		//2、先清除多余的高度
		for(i=hight[k]+1; i<MAX_HIGHT; i++)
		{
			//设置位置横坐标为第k个格子的8倍
			OLED_Set_Pos(k*8, i);
			for(j=0; j<8; j++)
			{				
				OLED_WR_Byte(0,OLED_DATA);				
			}
		}

		//3、再更新需要显示的高度
		for(i=0; i<hight[k]+1; i++)
		{
			//设置位置横坐标为第k个格子的8倍
			OLED_Set_Pos(k*8, i);
			for(j=0; j<8; j++)
			{
				//显示为小格子
				if((j+1)%8 == 0)
					OLED_WR_Byte(0,OLED_DATA);
				else
					OLED_WR_Byte(0xee,OLED_DATA);
			}
		}		
	}	
}

void OLED_Show_Line(UINT8 pos)
{
	uint8_t i;
	OLED_Set_Pos(0, pos);
	for(i=0; i<128; i++)
	{		
		OLED_WR_Byte(0x4,OLED_DATA);
	}
}


void main (void) 
{
	OLED_Gpio_Int();
	OLED_Init();//初始化OLED 	

	OLED_Show_Line(4);

	while(1)
	{
		OLED_Show_By_Hight();
		delay_ms(50);
	}
	
 	
	
}
