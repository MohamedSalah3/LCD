/*
 * LCD.h
 *
 * Created: 15/03/2020 01:09:17 م
 *  Author: mo
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
#include "registers.h"
#include "DIO.h"

#define LCD_RS_PIN	0x02 	//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	0x04 	//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	0x08	//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	0x10	//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	0x20	//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	0x40	//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	0x80	//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

/* LCD Commands definition */
#define Lcd_clear           0x01
#define Return_home         0x02
#define Decrement_cursor    0x04
#define Shift_display_right 0x05
#define Increment_cursor    0x06
#define Shift_display_left  0x07
#define Shift_cursor_left   0x10
#define Shift_cursor_right  0x14
#define Four_bit            0x28
#define Eight_bit           0x38
#define Cursor_off          0x0C
#define Cursor_on           0x0E

// cursor position to DDRAM mapping
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void LCD_EN_pulse(void);
void LCD_config_pins(void); // configure LCD pins.
void LCD_send_nibble(uint8_t data); // re-maps data bits to LCD Pins.
void LCD_send_char(char data);		//forms data ready to send to LCD
void LCD_send_command(uint8_t data);	//forms command ready to send to LCD
void LCD_init(void);			//Initializes LCD
void LCD_clear(void);				//Clears LCD
void LCD_send_string(char* data);	//Outputs string to LCD
void LCD_goto_xy(uint8_t x, uint8_t y);	//Cursor to X Y position

/*---Modification--------------------------------------------------------------------------------------*/
// inline function to swap two numbers
//inline void swap(char *x, char *y);
// function to reverse buffer[i..j]
char* reverse(char *buffer, uint32_t i, uint32_t j);
// Iterative function to implement itoa() function in C
char* itoa_(uint32_t value, char* buffer, uint32_t base);



#endif /* LCD_H_ */