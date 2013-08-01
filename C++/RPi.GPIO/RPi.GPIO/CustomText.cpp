#include <iostream>
#include "LCD.h"
#include "Utils.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

using namespace std;

string outputStr(string input, bool cutLineNumber)
{
	if(cutLineNumber)
	{
		return input.substr(2, input.length() - 2);
	}
	return input;
}

int zero(LCD *lcd)
{
	int i = 0;
	string str = "";
	do
	{
		getline(cin, str);
		if(str == "clear")
		{
			lcd->clear();
		}
		switch(str[0])
		{
			case '0':
				lcd->message(outputStr(str, true), 0);
				break;
			case '1':
				lcd->message(outputStr(str, true), 1);
				break;
			default:
				lcd->message(outputStr(str, false), i);
				i++;
				if(i > 1)
				{
					i = 0;
				}
		}
	}
	while(str != "exit");
	return 0;
}

int one(LCD *lcd)
{
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
	
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 50;

	vector<string> lines;
	lines.push_back("test 1");
	lines.push_back("test 2");
	lines.push_back("test 3");
	lines.push_back("test 4");
	lines.push_back("test 5");
	int next = 4;
	long double t = time(0);
	long double pt = t - 1000;
	char c = ' ';
	int i = 0;
	do
	{
		t = time(0);
		if(t - pt >= next)
		{
			if(i + 1 >= lines.size())
			{
				lcd->message(lines[0], 1);
			}
			else
			{
				lcd->message(lines[i + 1], 1);
			}
			lcd->message(lines[i], 0);
			i++;
			if(i >= lines.size())
			{
				i = 0;
			}
			pt = t;
		}

		fd_set set;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

		int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
		if(res > 0)
		{
			read(fileno(stdin), &c, 1);
		}
	}
	while(c != 'q');
	tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
	return 0;
}

int two(LCD *lcd)
{
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
	
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 50;

	char c = ' ';

	long double t = time(0);
	long double pt = t;
	long double pt1 = t - 1000;
	long double at = t;
	long double at1 = t - 1000;

	int wait = 4;
	int next = 0;
	int next2 = 0;
	
	string line1 = "1 2 3 4 5 6 7 8 9 10";
	string line2 = "AaBbCcDdEeFfGgHhIiJj 1 2 3 4 5 6 7 8 9 10";

	lcd->message(line1, 0);
	lcd->message(line2, 1);

	int prev1;
	int prev2;

	bool b = false;

	do
	{
		t = time(0);
		if(!b)
		{
			if(t - pt >= wait)
			{
				if(t - pt1 >= 1)
				{
					pt1 = t;
					if(next != prev1)
					{
						if(next + 15 >= line1.length())
						{
							if(prev1 > line1.length() + wait - 17)
							{
								lcd->message(line1, 0);
								next = 0;
								pt = t;
							}
							else
							{
								b = true;
								lcd->message(line1.substr(line1.length() - 16, line1.length() - 1), 0);
							}
						}
						else
						{
							lcd->message(line1.substr(next, next + 15), 0);
						}
						prev1 = next;
					}
					next++;
				}
			}
		}
		else
		{
			if(t - at >= wait)
			{
				if(t - at1 >= 1)
				{
					at1 = t;
					if(next2 != prev2)
					{
						if(next2 + 15 >= line2.length())
						{
							if(prev2 > line2.length() + wait - 17)
							{
								lcd->message(line2, 1);
								next2 = 0;
								at = t;
								b = false;
								prev1 = 1000;
							}
							else
							{
								lcd->message(line2.substr(line2.length() - 16, line2.length() - 1), 1);
							}
						}
						else
						{
							lcd->message(line2.substr(next2, next2 + 15), 1);
						}
						prev2 = next2;
					}
					next2++;
				}
			}
		}

		fd_set set;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

		int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
		if(res > 0)
		{
			read(fileno(stdin), &c, 1);
		}
	}
	while(c != 'q');
	tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
	return 0;
}

int three(LCD *lcd)
{
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
	
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 50;

	char c = ' ';

	long double t = time(0);
	long double pt = t;
	long double pt1 = t - 1000;
	long double at = t;
	long double at1 = t - 1000;

	int wait = 4;
	int next = 0;
	int next2 = 0;

	vector<string> lines;
	lines.push_back("(1) 1 2 3 4 5 6 7 8 9 10");
	lines.push_back("(2) AaBbCcDdEeFfGgHhIiJj 1 2 3 4 5 6 7 8 9 10");
	lines.push_back("(3) I want to be the very best, the best there ever was");
	lines.push_back("(4) To catch them is my real test, to train them is my cause");
	lines.push_back("(5) pokemon! gotta catch them all");
	
	string line1 = lines[0];
	string line2 = lines[1];

	lcd->message(line1, 0);
	lcd->message(line2, 1);

	int prev1;
	int prev2;

	bool b = false;

	int lineNum = 1;
	int prevLineNum = lineNum;

	do
	{
		t = time(0);
		if(!b)
		{
			if(t - pt >= wait)
			{
				if(t - pt1 >= 1)
				{
					pt1 = t;
					if(next != prev1)
					{
						if(next + 15 >= line1.length())
						{
							if(prev1 > line1.length() + wait - 17)
							{
								lcd->message(line1.substr(0, 15), 0);
								next = 0;
								pt = t;
							}
							else
							{
								b = true;
								lcd->message(line1.substr(line1.length() - 16, line1.length() - 1), 0);
							}
						}
						else
						{
							lcd->message(line1.substr(next, next + 15), 0);
						}
						prev1 = next;
					}
					next++;
				}
			}
		}
		else
		{
			if(t - at >= wait)
			{
				if(t - at1 >= 1)
				{
					at1 = t;
					if(next2 != prev2)
					{
						if(next2 + 15 >= line2.length())
						{
							if(prev2 > line2.length() + wait - 17)
							{
								if(lineNum + 1 >= lines.size())
								{
									line2 = lines[0];
								}
								else
								{
									line2 = lines[lineNum + 1];
								}
								line1 = lines[lineNum];
								lineNum++;
								if(lineNum >= lines.size())
								{
									lineNum = 0;
								}
								lcd->message(line1, 0);
								lcd->message(line2, 1);
								next2 = 0;
								at = t;
								b = false;
								prev1 = 1000;
								next = 1000;
							}
							else
							{
								lcd->message(line2.substr(line2.length() - 16, line2.length() - 1), 1);
							}
						}
						else
						{
							lcd->message(line2.substr(next2, next2 + 15), 1);
						}
						prev2 = next2;
					}
					next2++;
				}
			}
		}

		fd_set set;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

		int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
		if(res > 0)
		{
			read(fileno(stdin), &c, 1);
		}
	}
	while(c != 'q');
	tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
	return 0;
}
 
int main(int argc, const char* argv[])
{
	const char k = argv[1][0];
	LCD lcd(7, 8, 25, 24, 23, 18, 2, 16);
	lcd.init();
	
	switch(k)
	{
		case '0':
			zero(&lcd);
			break;
		case '1':
			one(&lcd);
			break;
		case '2':
			two(&lcd);
			break;
		case '3':
			three(&lcd);
			break;
		default:
			zero(&lcd);
	}

	lcd.~LCD();

    return 0;
}