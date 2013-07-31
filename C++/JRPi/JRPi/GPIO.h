#ifndef GPIO_H
#define GPIO_H

#include <string>

using namespace std;

class GPIO
{
	public:
		GPIO(void);
		GPIO(string io_num);
		~GPIO(void);

		int exportIO();
		int unExportIO();
		int setDir(string dir);
		int setVal(string val);
		int getVal(string &val);
		string getIO_Number();
	private:
		string io_number;
};

#endif