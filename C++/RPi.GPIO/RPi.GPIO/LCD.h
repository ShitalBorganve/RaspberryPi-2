#ifndef LCD_H
#define LCD_H

#include <string>

using namespace std;

const bool LCD_CHR = true;
const bool LCD_CMD = false;
const int LCD_LINE_1 = 0x80;
const int LCD_LINE_2 = 0xC0;
const int LCD_SETDDRAMADDR = 0x80;
const int LCD_CLEAR = 0x01;

#define CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))

class LCD
{
	public:
		LCD(int, int, int, int, int, int, int, int);
		~LCD(void);

		void byte(int, bool);
		void clear();
		void message(string, unsigned int);
		void init();

	private:
		unsigned int LCD_RS;
		unsigned int LCD_E;
		unsigned int LCD_D4;
		unsigned int LCD_D5;
		unsigned int LCD_D6;
		unsigned int LCD_D7;
		unsigned int LINE_WIDTH;
		unsigned int NUM_OF_LINES;
		void pulse();
		void cleanup();
};

#endif