#ifndef LCD_H
#define LCD_H

#include "GPIO.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

const float E_PULSE = 0.00005f;
const float E_DELAY = 0.00005f;

const bool LCD_CHR = true;
const bool LCD_CMD = false;
const int LCD_LINE_1 = 0x80;
const int LCD_LINE_2 = 0xC0;

class LCD
{
	public:
		LCD(vector<std::string>, unsigned int, unsigned int);
		~LCD(void);

		void init();

		void byte(unsigned int, bool);
		void message(string, unsigned int);
	private:
		unsigned int numOfLines;
		unsigned int lineLength;
		GPIO *LCD_RS;
		GPIO *LCD_E;
		GPIO *LCD_D4;
		GPIO *LCD_D5;
		GPIO *LCD_D6;
		GPIO *LCD_D7;
};

#endif