#ifndef __LCD1602_H__
#define __LCD1602_H__


#define LCD1602_Order_OFF 0x08
#define LCD1602_Order_CursorClose 0x0C



#define LCD1602_Port P0
sbit LCD1602_RS = P2^0;//0命令 1数据
sbit LCD1602_RW = P2^1;//0写  1读
sbit LCD1602_EN = P2^2;//读写使能，0允许


extern void LCD1602_init();
extern void LCD1602_Write(uchar cmd,uchar dat);
extern void LCD1602_displaySring(uchar hang, uchar lie, uchar *pstr);
extern void LCD1602_display3INT(uchar hang, uchar lie, int int_3b);
extern void LCD1602_display2UINT(uchar hang, uchar lie, uint uint_b);
extern void LCD1602_CursorSet(uchar hang, uchar lie);

#define LCD1602_CursorClose() LCD1602_Write(0,LCD1602_Order_CursorClose)		//关闭光标
#define LCD1602_Off() LCD1602_Write(0,LCD1602_Order_OFF)				//关显示	



/************LCD1602指令集及配置*****************运行时间(在250KHz下)*/
#define LCD1602_Order_Clear 0x01	//清屏 1.64us
#define LCD1602_Order_Home 0x02		//光标归位 1.64us

#define LCD1602_Order_Mode_ID 0x01	//1=数据读写操作后,AC自动增1;  0=自动减1	
#define LCD1602_Order_Mode_S 0x00	//1=数据读写操作 画面平移；  0=画面不动	  
#define LCD1602_Order_Mode (0x04|\
							(LCD1602_Order_Mode_ID<<1)|\
							LCD1602_Order_Mode_S)	//输入方式设置	40us

#define LCD1602_Order_OnOFF_D 0x01	//1=开显示，0=关显示
#define LCD1602_Order_OnOFF_C 0x00	//1=显示光标，0=不显示光标
#define LCD1602_Order_OnOFF_B 0x00	//1=光标闪烁，0=不闪烁
#define LCD1602_Order_OnOFF (0x08|\
							(LCD1602_Order_OnOFF_D<<2)|\
							(LCD1602_Order_OnOFF_C<<1)|\
							 LCD1602_Order_OnOFF_B)	//显示开关控制 40us

#define LCD1602_Order_Shift_SC 0x00	//0=光标平移一个字符位，1=画面平移
#define LCD1602_Order_Shift_RL 0x01	//1=右移，0=左移
#define LCD1602_Order_Shift (0x10|\
							(LCD1602_Order_Shift_SC<<3)|\
							(LCD1602_Order_Shift_RL<<2))	//光标、画面移动	40us

#define LCD1602_Order_Function_DL 0x00	//1=8位数据接口,0=4位
#define LCD1602_Order_Function_N  0x01	//1=两行显示,0=1行
#define LCD1602_Order_Function_F  0x01	//1=5*10点阵,0=5*7
#define LCD1602_Order_Function	(0x20|\
							(LCD1602_Order_Function_DL<<4)|\
							(LCD1602_Order_Function_N<<3)|\
							(LCD1602_Order_Function_F<<2))	//工作方式设置  40us

#define LCD1602_Order_CGRAM_Address 0	//CGRAM(Character Generator 字符产生器)地址(共6位)
#define LCD1602_Order_CGRAM (0x40|LCD1602_Order_CGRAM_Address)	//CGRAM地址设置	40us

#define LCD1602_Order_DDRAM_Address 0	//一行显示：0~0x4F;两行显示：首行:0~0x27,次行：0x40~0x67
#define LCD1602_Order_DDRAM (0x80|LCD1602_Order_DDRAM_Address)	//设置DDRAM地址 40us

#endif