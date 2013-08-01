#ifndef LCD_H
#define LCD_H

#include <string>

using namespace std;

const bool LCD_CHR = true;
const bool LCD_CMD = false;
/*LCD memory location call first line*/
const int LCD_LINE_1 = 0x80;
/*LCD memory location call second line*/
const int LCD_LINE_2 = 0xC0;
const int LCD_SETDDRAMADDR = 0x80;
const int LCD_CLEAR = 0x01;

/*Checks to see if the bit is 0 or 1, returns boolean*/
#define CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))

class LCD
{
	public:
		/*
		 * LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, NUM_OF_LINES, LINE_WIDTH
		 */
		LCD(int, int, int, int, int, int, int, int);
		~LCD(void);

		/*
		 * Sends a byte to the LCD
		 * to send a command do byte(char, LCD_CMD)
		 * to send a character do byte(char, LCD_CHR)
		 */
		void byte(int, bool);
		/*
		 * Clears the LCD screen
		 */
		void clear();
		/*
		 * Sends a string to be displayed on the LCD
		 * Currently only works for two lines
		 */
		void message(string, unsigned int);
		/*
		 * Initializes the LCD, must call this in order for it to work
		 */
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