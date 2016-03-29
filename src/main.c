#include <reg51.h>
#include "common.h"
#include "LCD1602.h"

void main()
{
	LCD1602_init();
	LCD1602_displaySring(1,1,"3INT:");
	LCD1602_display3INT(1,6,-123);
	LCD1602_displaySring(2,1,"2UINT:");
	LCD1602_display2UINT(2,7,12);
	LCD1602_displaySring(2,10,"4wire");
	while(1);
}