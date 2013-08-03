#include "GPIO.h"
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * DEMO
 * Blinks a LED 5 times
 */
int zero()
{
	GPIO::setup(11, "out");
	bool val = true;
	for(int i = 0; i < 10; i++)
	{
		GPIO::output(11, val);
		val = !val;
		if(i < 9)
		{
			usleep(500000);
		}
	}
	return 0;
}

/*
 * DEMO
 * Turn on and off LED using a (on) and s (off)
 * q to exit
 */
int one()
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
	GPIO::setup(11, "out");
	do
	{
		if(c == 'a')
		{
			if(!GPIO::getValue(11))
			{
				GPIO::output(11, true);
			}
		}
		if(c == 's')
		{
			if(GPIO::getValue(11))
			{
				GPIO::output(11, false);
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

	switch(k)
	{
		/*Blinks a LED 5 times*/
		case '0':
			zero();
			break;
		/*Turn on and off LED using a (on) and s (off)*/
		case '1':
			one();
			break;
		default:
			zero();
	}
	GPIO::cleanup();

	return 0;
}