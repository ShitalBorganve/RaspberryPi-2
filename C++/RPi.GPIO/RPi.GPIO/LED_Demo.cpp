#include "GPIO.h"
#include <unistd.h>

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
			usleep(1000000);
		}
	}
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
		default:
			zero();
	}

	return 0;
}