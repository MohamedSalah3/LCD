/*
 * LCD.c
 *
 * Created: 15/03/2020 01:08:07 م
 *  Author: mo
 */ 
#include "LCD.h"


int main(void)
{
     LCD_init();

     while (1) {
	     LCD_clear();

	     LCD_goto_xy(0,0);
	     LCD_send_char('M');

	     SwDelay_ms(50);
     }

}