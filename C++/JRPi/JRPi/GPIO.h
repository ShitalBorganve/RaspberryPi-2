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
		int setDir(IO_Dir dir);
		int setVal(IO_Val val);
		int getVal(IO_Val &val);
		string getIO_Number();
	private:
		string io_number;
		static string Dir(IO_Dir dir)
		{
			if(dir == In)
			{
				return "in";
			}
			else
			{
				return "out";
			}
		}

		static string Val(IO_Val val)
		{
			if(val == One)
			{
				return "1";
			}
			else
			{
				return "0";
			}
		}
};

enum IO_Dir
{
	In, Out
};

enum IO_Val
{
	One, Zero
};

#endif