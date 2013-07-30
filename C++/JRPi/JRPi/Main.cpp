#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
using namespace std;
 
int main(void)
{
	GPIO *gpio24 = new GPIO("24");
	GPIO *gpio25 = new GPIO("25");

	gpio24->exportIO();
	gpio25->exportIO();

	gpio24->setDir(Out);
	gpio25->setDir(Out);

	for(unsigned int i = 0; i < 50; i++)
	{
		gpio24->setVal(One);
	}
	gpio24->~GPIO();
	gpio25->~GPIO();
	delete gpio24;
	delete gpio25;

    return 0;
}