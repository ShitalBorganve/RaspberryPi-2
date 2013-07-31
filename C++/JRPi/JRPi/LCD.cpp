#include "LCD.h"
#if defined(WIN32)
  #include <windows.h>
#elif defined(__UNIX__)
  #include <unistd.h>
#else
#endif

int millisleep(float ms)
{
#if defined(WIN32)
  SetLastError(0);
  Sleep(ms);
  return GetLastError() ?-1 :0;
#else//#elif defined(LINUX)
  return usleep(1000 * ms);
//#else
//#error ("no milli sleep available for platform")
//  return -1;
#endif
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
	if(line > numOfLines)
	{
		cout << "Can not write to line, it does not exist!" << endl;
		exit(1);
	}
	while(message.length() < lineLength)
	{
		message += " ";
	}
	for(unsigned int i = 0; i < lineLength; i++)
	{
		char s = message[i];
		byte(ord(s), LCD_CHR);
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

	byte(0x33, LCD_CMD);
	byte(0x32, LCD_CMD);
	byte(0x28, LCD_CMD);
	byte(0x0C, LCD_CMD);
	byte(0x06, LCD_CMD);
	byte(0x01, LCD_CMD);
}

void LCD::byte(unsigned int byte, bool mode)
{
	LCD_RS->setVal("0");

	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	if(byte&0x10 == 0x10)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x20 == 0x20)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x40 == 0x40)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x80 == 0x80)
	{
		LCD_D4->setVal("1");
	}
	
	millisleep(1);
	LCD_E->setVal("1");
	millisleep(1);
	LCD_E->setVal("0");
	millisleep(1);
	
	LCD_D4->setVal("0");
	LCD_D5->setVal("0");
	LCD_D6->setVal("0");
	LCD_D7->setVal("0");

	if(byte&0x01 == 0x01)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x02 == 0x02)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x04 == 0x04)
	{
		LCD_D4->setVal("1");
	}
	if(byte&0x08 == 0x08)
	{
		LCD_D4->setVal("1");
	}
	
	millisleep(1);
	LCD_E->setVal("1");
	millisleep(1);
	LCD_E->setVal("0");
	millisleep(1);
}