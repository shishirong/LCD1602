#include<reg51.h>
#include "common.h"
#include "LCD1602.h"

void LCD1602_Delay(uint dely)
{
	for(;dely>0;dely--);
}

//��æ
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

/*��Һ����ʾ��д����/���ݺ���
����˵����cmd=0Ϊд���cmd=1Ϊд����
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


/*��ʾ�ַ���
����˵������ʼ�У��У��ַ���
*/
void LCD1602_displaySring(uchar hang, uchar lie, uchar *pstr) 
{
    LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
    while(*pstr)
	{
        LCD1602_Write(1,*pstr++);
    }
}

/*��ʾһ��3λ����������������λ��4���ַ�
����˵������ʼ�У��У�����ʾ����
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

/*��ʾһ��2λ���޷�������,��2λ
����˵������ʼ�У��У�����ʾ����
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


/*��ָ��λ����˸���
����˵�����У���
*/
void LCD1602_CursorSet(uchar hang, uchar lie) 
{
	LCD1602_Write(0,0x80+(0x40 * (hang - 1)) + (lie - 1));
	LCD1602_Write(0,0x0F);
}



/*��ʼ��*/
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
	LCD1602_Write(0,LCD1602_Order_Function);	//������ʽ���� 
	LCD1602_Write(0,LCD1602_Order_OFF);		//����ʾ
	LCD1602_Write(0,LCD1602_Order_Clear);		//����
	LCD1602_Write(0,LCD1602_Order_Mode);		//���뷽ʽ����	
	LCD1602_Write(0,LCD1602_Order_OnOFF);		//����ʾ
}