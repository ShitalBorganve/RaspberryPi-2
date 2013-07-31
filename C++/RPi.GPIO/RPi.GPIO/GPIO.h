#ifndef GPIO_H
#define GPIO_H

#include <string>

using namespace std;

class GPIO
{
	public:
		static int output(unsigned int, bool);
		static int setup(unsigned int, string dir);
		static bool getValue(unsigned int);
		static int cleanup();
};

#endif