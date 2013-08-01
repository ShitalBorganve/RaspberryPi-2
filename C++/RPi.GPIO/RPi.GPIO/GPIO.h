#ifndef GPIO_H
#define GPIO_H

#include <string>

using namespace std;

class GPIO
{
	public:
		/*
		 * Sets the value of an IO pin
		 * false = off, true = on
		 */
		static int output(unsigned int, bool);
		/*
		 * Sets up the IO pin for use
		 * dir: "in" = look for value, "out" = send out value
		 */
		static int setup(unsigned int, string dir);
		/*
		 * Gets the value of an IO pin
		 * The pin must be setup for "in"
		 */
		static bool getValue(unsigned int);
		/*
		 * Cleans up the IO
		 * Doesn't completely work
		 */
		static int cleanup();
};

#endif