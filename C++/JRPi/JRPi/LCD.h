#ifndef LCD_H
#define LCD_H

#include "GPIO.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

const bool LCD_CHR = true;
const bool LCD_CMD = false;
const int LCD_LINE_1 = 0x80;
const int LCD_LINE_2 = 0xC0;
const int LCD_SETDDRAMADDR = 0x80;

#define CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))

class LCD
{
	public:
		LCD(vector<std::string>, unsigned int, unsigned int);
		~LCD(void);

		void init();

		void byte(int, bool);
		void message(string, unsigned int);
		void unExport();
		void clear();
	private:
		unsigned int numOfLines;
		unsigned int lineLength;
		void pulse();
		GPIO *LCD_RS;
		GPIO *LCD_E;
		GPIO *LCD_D4;
		GPIO *LCD_D5;
		GPIO *LCD_D6;
		GPIO *LCD_D7;
};

#endif