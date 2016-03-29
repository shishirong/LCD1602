#include<reg51.h>
#include "common.h"
#include "LCD1602.h"

void LCD1602_Delay(uint dely)
{
	for(;dely>0;dely--);
}

//读忙
uchar LCD1602_ReadBusy()
{
	uchar lcd_status;
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_EN=1;
	
#if(LCD1602_Order_Function_DL==1)	
	LCD1602_Port=0xFF;
#endif
#if(LCD1602_Order_Function_DL==0)
	LCD1602_Port|=0xF0;
#endif	
	
	LCD1602_Delay(10);
	lcd_status=LCD1602_Port;
	LCD1602_EN=0;
	
#if(LCD1602_Order_Function_DL==0)
	LCD1602_EN=1;
	LCD1602_Delay(10);
	lcd_status=(lcd_status&0xF0)|((0xF0&LCD1602_Port)>>4);
	LCD1602_EN=0;
#endif		
	return lcd_status;  
}

/*向液晶显示器写命令/数据函数
参数说明：cmd=0为写命令，cmd=1为写数据
*/
void LCD1602_Write(uchar cmd,uchar dat)
{
	while((LCD1602_ReadBusy()&0x80) == 0x80);
	LCD1602_RS=cmd;
	LCD1602_RW=0;
	LCD1602_EN=1;
#if(LCD1602_Order_Function_DL==1)	
	LCD1602_Port=dat;
#endif
	
#if(LCD1602_Order_Function_DL==0)		
	LCD1602_Port=(LCD1602_Port&0x0F)|(dat&0xF0);
	LCD1602_Delay(50);
	LCD1602_EN=0;
	

	LCD1602_EN=1;
	LCD1602_Port=(LCD1602_Port&0x0F)|(dat<<4);
#endif	
	LCD1602_Delay(50);
	LCD1602_EN=0;
}


/*显示字符串
参数说明：起始行，列，字符串
*/
void LCD1602_displaySring(uchar hang, uchar lie, uchar *pstr) 
{
    LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
    while(*pstr)
	{
        LCD1602_Write(1,*pstr++);
    }
}

/*显示一个3位的整数，包括符号位共4个字符
参数说明：起始行，列，待显示的数
*/
void LCD1602_display3INT(uchar hang, uchar lie, int int_3b) 
{
	uchar tps[]="    ";	
	uchar *pstr=&tps[0];
	if(int_3b < 0)
	{
		tps[0]='-';
		int_3b=int_3b*(-1);
	}
	else
		tps[0]='+';

	tps[1]=int_3b/100+'0';
	tps[2]=int_3b%100/10+'0';
	tps[3]=int_3b%10+'0';
	
	 LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
	while(*pstr)
	{
        LCD1602_Write(1,*pstr++);
    }
}

/*显示一个2位的无符号整数,共2位
参数说明：起始行，列，待显示的数
*/
void LCD1602_display2UINT(uchar hang, uchar lie, uint uint_b) 
{
	uchar tps[]="  ";
	uchar *pstr=&tps[0];
	
	tps[0]=uint_b/10+'0';
	tps[1]=uint_b%10+'0';
	
	LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
	while(*pstr)
	{
        LCD1602_Write(1,*pstr++);
    }
}


/*让指定位置闪烁光标
参数说明：行，列
*/
void LCD1602_CursorSet(uchar hang, uchar lie) 
{
	LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
	LCD1602_Write(0,0x0F);
}



/*初始化*/
void LCD1602_init()
{
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_EN=1;
#if(LCD1602_Order_Function_DL==1)	
	LCD1602_Port=LCD1602_Order_Function;
#endif
	
#if(LCD1602_Order_Function_DL==0)
	LCD1602_Port=(LCD1602_Port&0x0f)|(LCD1602_Order_Function&0xF0);
#endif
	LCD1602_Delay(10);
	LCD1602_EN=0;
	LCD1602_Delay(10000);
	LCD1602_Write(0,LCD1602_Order_Function);	//工作方式设置 
	LCD1602_Write(0,LCD1602_Order_OFF);		//关显示
	LCD1602_Write(0,LCD1602_Order_Clear);		//清屏
	LCD1602_Write(0,LCD1602_Order_Mode);		//输入方式设置	
	LCD1602_Write(0,LCD1602_Order_OnOFF);		//开显示
}