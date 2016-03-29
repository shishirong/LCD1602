#ifndef __LCD1602_H__
#define __LCD1602_H__


#define LCD1602_Order_OFF 0x08
#define LCD1602_Order_CursorClose 0x0C



#define LCD1602_Port P0
sbit LCD1602_RS = P2^0;//0���� 1����
sbit LCD1602_RW = P2^1;//0д  1��
sbit LCD1602_EN = P2^2;//��дʹ�ܣ�0����


extern void LCD1602_init();
extern void LCD1602_Write(uchar cmd,uchar dat);
extern void LCD1602_displaySring(uchar hang, uchar lie, uchar *pstr);
extern void LCD1602_display3INT(uchar hang, uchar lie, int int_3b);
extern void LCD1602_display2UINT(uchar hang, uchar lie, uint uint_b);
extern void LCD1602_CursorSet(uchar hang, uchar lie);

#define LCD1602_CursorClose() LCD1602_Write(0,LCD1602_Order_CursorClose)		//�رչ��
#define LCD1602_Off() LCD1602_Write(0,LCD1602_Order_OFF)				//����ʾ	



/************LCD1602ָ�������*****************����ʱ��(��250KHz��)*/
#define LCD1602_Order_Clear 0x01	//���� 1.64us
#define LCD1602_Order_Home 0x02		//����λ 1.64us

#define LCD1602_Order_Mode_ID 0x01	//1=���ݶ�д������,AC�Զ���1;  0=�Զ���1	
#define LCD1602_Order_Mode_S 0x00	//1=���ݶ�д���� ����ƽ�ƣ�  0=���治��	  
#define LCD1602_Order_Mode (0x04|\
							(LCD1602_Order_Mode_ID<<1)|\
							LCD1602_Order_Mode_S)	//���뷽ʽ����	40us

#define LCD1602_Order_OnOFF_D 0x01	//1=����ʾ��0=����ʾ
#define LCD1602_Order_OnOFF_C 0x00	//1=��ʾ��꣬0=����ʾ���
#define LCD1602_Order_OnOFF_B 0x00	//1=�����˸��0=����˸
#define LCD1602_Order_OnOFF (0x08|\
							(LCD1602_Order_OnOFF_D<<2)|\
							(LCD1602_Order_OnOFF_C<<1)|\
							 LCD1602_Order_OnOFF_B)	//��ʾ���ؿ��� 40us

#define LCD1602_Order_Shift_SC 0x00	//0=���ƽ��һ���ַ�λ��1=����ƽ��
#define LCD1602_Order_Shift_RL 0x01	//1=���ƣ�0=����
#define LCD1602_Order_Shift (0x10|\
							(LCD1602_Order_Shift_SC<<3)|\
							(LCD1602_Order_Shift_RL<<2))	//��ꡢ�����ƶ�	40us

#define LCD1602_Order_Function_DL 0x00	//1=8λ���ݽӿ�,0=4λ
#define LCD1602_Order_Function_N  0x01	//1=������ʾ,0=1��
#define LCD1602_Order_Function_F  0x01	//1=5*10����,0=5*7
#define LCD1602_Order_Function	(0x20|\
							(LCD1602_Order_Function_DL<<4)|\
							(LCD1602_Order_Function_N<<3)|\
							(LCD1602_Order_Function_F<<2))	//������ʽ����  40us

#define LCD1602_Order_CGRAM_Address 0	//CGRAM(Character Generator �ַ�������)��ַ(��6λ)
#define LCD1602_Order_CGRAM (0x40|LCD1602_Order_CGRAM_Address)	//CGRAM��ַ����	40us

#define LCD1602_Order_DDRAM_Address 0	//һ����ʾ��0~0x4F;������ʾ������:0~0x27,���У�0x40~0x67
#define LCD1602_Order_DDRAM (0x80|LCD1602_Order_DDRAM_Address)	//����DDRAM��ַ 40us

#endif