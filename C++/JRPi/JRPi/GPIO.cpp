#include "GPIO.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

GPIO::GPIO(void)
{
	this->io_number = "4";
}

GPIO::GPIO(string io_num)
{
	this->io_number = io_num;
}

GPIO::~GPIO(void)
{
	unExportIO();
}

int GPIO::exportIO()
{
	string exportStr = "/sys/class/gpio/export";
	ofstream exportgpio(exportStr.c_str());
    if (exportgpio < 0)
	{
        cout << " OPERATION FAILED: Unable to export GPIO"<< this->io_number <<" ."<< endl;
        return -1;
    }
 
    exportgpio << this->io_number;
    exportgpio.close();
    return 0;
}
 
int GPIO::unExportIO()
{
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio(unexport_str.c_str());
    if (unexportgpio < 0)
	{
        cout << " OPERATION FAILED: Unable to unexport GPIO" << this->io_number <<" ."<< endl;
        return -1;
    }
 
    unexportgpio << this->io_number;
    unexportgpio.close();
    return 0;
}
 
int GPIO::setDir(string dir)
{
    string setdir_str ="/sys/class/gpio/gpio" + this->io_number + "/direction";
    ofstream setdirgpio(setdir_str.c_str());
    if (setdirgpio < 0)
	{
        cout << " OPERATION FAILED: Unable to set direction of GPIO" << this->io_number <<" ."<< endl;
        return -1;
    }
 
    setdirgpio << dir;
    setdirgpio.close();
    return 0;
}
 
int GPIO::setVal(string val)
{
    string setval_str = "/sys/class/gpio/gpio" + this->io_number + "/value";
    ofstream setvalgpio(setval_str.c_str());
	if (setvalgpio < 0)
	{
		cout << " OPERATION FAILED: Unable to set the value of GPIO" << this->io_number <<" ."<< endl;
		return -1;
	}
 
    setvalgpio << val;
    setvalgpio.close();
    return 0;
}
 
int GPIO::getVal(string &val)
{
	string getval_str = "/sys/class/gpio/gpio" + this->io_number + "/value";
	ifstream getvalgpio(getval_str.c_str());
	if (getvalgpio < 0)
	{
		cout << " OPERATION FAILED: Unable to get value of GPIO" << this->io_number <<" ."<< endl;
		return -1;
	}
 
	getvalgpio >> val;
 
	getvalgpio.close();
	return 0;
}
 
string GPIO::getIO_Number()
{
	return this->io_number;
}