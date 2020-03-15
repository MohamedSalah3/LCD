/*
 * LCD.c
 *
 * Created: 15/03/2020 01:08:48 م
 *  Author: mo
 */ 
 #include "LCD.h"
 #include "softwareDelay.h"
 #include <stdlib.h>

 void LCD_EN_pulse(void)
 {
	 DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
/***********************************************************/
	 SwDelay_ms(1);
	 DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
/*************************************************************/	 
	 SwDelay_ms(1);
 }

 void LCD_config_pins(void){

	 /* set LCD pins as outputs */
	DIO_init(&Dio_configurationA);
	/* 
	 gpioPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);

	 gpioPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);

	 gpioPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);

	 gpioPinDirection(LCD_D4_PORT, LCD_D4_PIN, OUTPUT);

	 gpioPinDirection(LCD_D5_PORT, LCD_D5_PIN, OUTPUT);

	 gpioPinDirection(LCD_D6_PORT, LCD_D6_PIN, OUTPUT);

	 gpioPinDirection(LCD_D7_PORT, LCD_D7_PIN, OUTPUT); 
 */
	
}

 void LCD_send_nibble(uint8_t data){
	 uint8_t mask = 1;
	 data >>= 4;
	 if(data & mask)
	 DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	 else
	 DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

	 mask *= 2;
	 if(data & mask)
	 DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	 else
	 DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

	 mask *= 2;
	 if(data & mask)
	 DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	 else
	 DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

	 mask *= 2;
	 if(data & mask)
	 DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	 else
	 DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
 }
/***************************************************************************/
 void LCD_send_char(char data)		//Sends Char to LCD
 {
	 DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	 LCD_send_nibble(data); // Higher nibble first
	 LCD_EN_pulse();

	 LCD_send_nibble(data<<4);
	 LCD_EN_pulse();
	 SwDelay_ms(1);
 }
 /**************************************************************************/
 void LCD_send_command(uint8_t data)	//Sends Command to LCD
 {
	 DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);
	 LCD_send_nibble(data); // Higher nibble first
	 LCD_EN_pulse();

	 LCD_send_nibble(data<<4);
	 LCD_EN_pulse();
	 SwDelay_ms(1);
 }
 /******************************************************************************/
 void LCD_init(void)//Initializes LCD
 {
	 LCD_config_pins();
	 /*******************************************************************/
	 SwDelay_ms(20);
	 //	LCD_send_nibble(0x00);
	 //
	 //	gpioPinWrite(LCD_RS_PORT, LCD_RS_PIN, LOW);
	 //	gpioPinWrite(LCD_RW_PORT, LCD_RW_PIN, LOW);
	 //	gpioPinWrite(LCD_EN_PORT, LCD_EN_PIN, LOW);

	 LCD_send_command(0x33);
	 LCD_send_command(0x32);
	 LCD_send_command(Four_bit); // 4-bit
	 LCD_send_command(Cursor_on);
	 LCD_send_command(Lcd_clear);
	 /*********************************************************************/
	 SwDelay_ms(10);
	 LCD_send_command(Increment_cursor);
	 LCD_send_command(Cursor_off); // Cursor off
 }
 void LCD_clear(void)				//Clears LCD
 {
	 LCD_send_command(Lcd_clear);
 }

 void LCD_send_string(char* data)	//Outputs string to LCD
 {
	 while(*data){
		 LCD_send_char(*data++);
	 }
 }

 void LCD_goto_xy(uint8_t x, uint8_t y)	//Cursor to X Y position
 {
	 uint8_t DDRAMAddr;
	 // remap lines into proper order
	 switch(y)
	 {
		 case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		 case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		 case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		 case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		 default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	 }
	 // set data address
	 LCD_send_command(1<<LCD_DDRAM | DDRAMAddr);

 }

 /*---Modification----------------------------------------------------------------------------------------------*/

 // inline function to swap two numbers
 inline void swap(char *x, char *y) {
	 char t = *x; *x = *y; *y = t;
 }

 // function to reverse buffer[i..j]
 char* reverse(char *buffer, uint32_t i, uint32_t j)
 {
	 while (i < j)
	 swap(&buffer[i++], &buffer[j--]);

	 return buffer;
 }

 // Iterative function to implement itoa() function in C
 char* itoa_(uint32_t value, char* buffer, uint32_t base)
 {
	 // invalid input
	 if (base < 2 || base > 32)
	 return buffer;

	 // consider absolute value of number
	 int n = abs(value);

	 int i = 0;
	 while (n)
	 {
		 int r = n % base;

		 if (r >= 10)
		 buffer[i++] = 65 + (r - 10);
		 else
		 buffer[i++] = 48 + r;

		 n = n / base;
	 }

	 // if number is 0
	 if (i == 0)
	 buffer[i++] = '0';

	 // If base is 10 and value is negative, the resulting string
	 // is preceded with a minus sign (-)
	 // With any other base, value is always considered unsigned
	 if (value < 0 && base == 10)
	 buffer[i++] = '-';

	 buffer[i] = '\0'; // null terminate string

	 // reverse the string and return it
	 return reverse(buffer, 0, i - 1);
 }
