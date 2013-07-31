#include "LCD.h"
#include "GPIO.h"
#include <unistd.h>

LCD::LCD(int lcd_rs, int lcd_e, int lcd_d4, int lcd_d5, int lcd_d6, int lcd_d7, int numOfLines, int lineWidth)
{
	this->LCD_RS = lcd_rs;
	this->LCD_E = lcd_e;
	this->LCD_D4 = lcd_d4;
	this->LCD_D5 = lcd_d5;
	this->LCD_D6 = lcd_d6;
	this->LCD_D7 = lcd_d7;
	this->LINE_WIDTH = lineWidth;
	this->NUM_OF_LINES = numOfLines;
}

LCD::~LCD(void)
{
	cleanup();
}

void LCD::init()
{
	GPIO::setup(LCD_RS, "out");
	GPIO::setup(LCD_E,  "out");
	GPIO::setup(LCD_D4, "out");
	GPIO::setup(LCD_D5, "out");
	GPIO::setup(LCD_D6, "out");
	GPIO::setup(LCD_D7, "out");

	byte(0x33, LCD_CMD);
	byte(0x32, LCD_CMD);
	byte(0x28, LCD_CMD);
	byte(0x0C, LCD_CMD);
	byte(0x06, LCD_CMD);
	byte(0x01, LCD_CMD);
}

void LCD::byte(int bits, bool mode)
{
	GPIO::output(LCD_RS, mode);

	bool z;
	int i;
	
	GPIO::output(LCD_D4, false);
	GPIO::output(LCD_D5, false);
	GPIO::output(LCD_D6, false);
	GPIO::output(LCD_D7, false);

	for(i=7; i>=4; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 7:
					GPIO::output(LCD_D7, true);
					break;
				case 6:
					GPIO::output(LCD_D6, true);
					break;
				case 5:
					GPIO::output(LCD_D5, true);
					break;
				case 4:
					GPIO::output(LCD_D4, true);
					break;
			}
		}
	}
	pulse();
	
	GPIO::output(LCD_D4, false);
	GPIO::output(LCD_D5, false);
	GPIO::output(LCD_D6, false);
	GPIO::output(LCD_D7, false);

	for(i=3; i>=0; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 3:
					GPIO::output(LCD_D7, true);
					break;
				case 2:
					GPIO::output(LCD_D6, true);
					break;
				case 1:
					GPIO::output(LCD_D5, true);
					break;
				case 0:
					GPIO::output(LCD_D4, true);
					break;
			}
		}
	}
	pulse();
}

void LCD::pulse()
{
	GPIO::output(LCD_E, true);
	usleep(50);
	GPIO::output(LCD_E, false);
}

void LCD::clear()
{
	byte(LCD_CLEAR, LCD_CMD);
}

void LCD::cleanup()
{
	GPIO::cleanup();
}

void LCD::message(string message, unsigned int line)
{
	switch(line)
	{
		case 0:
			byte(LCD_LINE_1, LCD_CMD);
			break;
		case 1:
			byte(LCD_LINE_2, LCD_CMD);
			break;
		default:
			byte(LCD_LINE_1, LCD_CMD);
	}
	while(message.length() < LINE_WIDTH)
	{
		message += " ";
	}
	for(unsigned int i = 0; i < LINE_WIDTH; i++)
	{
		byte(message[i], LCD_CHR);
	}
}