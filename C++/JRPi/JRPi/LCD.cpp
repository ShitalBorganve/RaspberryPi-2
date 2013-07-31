#include "LCD.h"
#include <iostream>
#include <unistd.h>

int millisleep(float ms)
{
	return usleep(1000 * ms);
}

int ord(char ord)
{
	return (int)ord;
}

LCD::LCD(vector<std::string> ioPorts, unsigned int lineLength, unsigned int numOfLines)
{
	if(ioPorts.size() < 6)
	{
		cout << "Error you must have 6 io ports!" << endl;
		exit(1);
	}

	this->lineLength = lineLength;
	this->numOfLines = numOfLines;

	LCD_RS = new GPIO(ioPorts[0]);
	LCD_E = new GPIO(ioPorts[1]);
	LCD_D4 = new GPIO(ioPorts[2]);
	LCD_D5 = new GPIO(ioPorts[3]);
	LCD_D6 = new GPIO(ioPorts[4]);
	LCD_D7 = new GPIO(ioPorts[5]);
}

LCD::~LCD(void)
{
}

void LCD::message(string message, unsigned int line)
{
	switch(line)
	{
		case 1:
			byte(LCD_LINE_1, LCD_CMD);
			break;
		case 2:
			byte(LCD_LINE_2, LCD_CMD);
			break;
		default:
			byte(LCD_LINE_1, LCD_CMD);
	}
	while(message.length() < lineLength)
	{
		message += " ";
	}
	for(unsigned int i = 0; i < lineLength; i++)
	{
		byte(message[i], LCD_CHR);
	}
}

void LCD::init()
{
	LCD_RS->exportIO();
	LCD_E->exportIO();
	LCD_D4->exportIO();
	LCD_D5->exportIO();
	LCD_D6->exportIO();
	LCD_D7->exportIO();
	
	LCD_RS->setDir("out");
	LCD_E->setDir("out");
	LCD_D4->setDir("out");
	LCD_D5->setDir("out");
	LCD_D6->setDir("out");
	LCD_D7->setDir("out");

	byte(0x33, LCD_CMD);
	byte(0x32, LCD_CMD);
	byte(0x28, LCD_CMD);
	byte(0x0C, LCD_CMD);
	byte(0x06, LCD_CMD);
	byte(0x01, LCD_CMD);
}

void LCD::character(char bits)
{
	LCD_RS->setVal("1");

	bool z;
	int i;

	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	for(i=7; i>=4; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 7:
					LCD_D7->setVal("1");
					break;
				case 6:
					LCD_D6->setVal("1");
					break;
				case 5:
					LCD_D5->setVal("1");
					break;
				case 4:
					LCD_D4->setVal("1");
					break;
			}
		}
	}
	pulse();
	
	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	for(i=3; i>=0; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 7:
					LCD_D7->setVal("1");
					break;
				case 6:
					LCD_D6->setVal("1");
					break;
				case 5:
					LCD_D5->setVal("1");
					break;
				case 4:
					LCD_D4->setVal("1");
					break;
			}
		}
	}
	pulse();
}

void LCD::byte(int bits, bool mode)
{
	LCD_RS->setVal(mode ? "1" : "0");

	bool z;
	int i;

	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	for(i=7; i>=4; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 7:
					LCD_D7->setVal("1");
					break;
				case 6:
					LCD_D6->setVal("1");
					break;
				case 5:
					LCD_D5->setVal("1");
					break;
				case 4:
					LCD_D4->setVal("1");
					break;
			}
		}
	}
	pulse();
	
	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	for(i=3; i>=0; i--)
	{
		z = CHECK_BIT(bits,i);
		if(z)
		{
			switch(i)
			{
				case 7:
					LCD_D7->setVal("1");
					break;
				case 6:
					LCD_D6->setVal("1");
					break;
				case 5:
					LCD_D5->setVal("1");
					break;
				case 4:
					LCD_D4->setVal("1");
					break;
			}
		}
	}
	pulse();
}

void LCD::pulse()
{
	millisleep(1);
	LCD_E->setVal("1");
	millisleep(1);
	LCD_E->setVal("0");
	millisleep(1);
}