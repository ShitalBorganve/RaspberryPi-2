#include "GPIO.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Utils.h"
#include <algorithm>

vector<int> openIOPorts;

int GPIO::output(unsigned int ioPort, bool e)
{
	string setval_str = "/sys/class/gpio/gpio" + Utils::to_string(ioPort) + "/value";
    ofstream setvalgpio(setval_str.c_str());
	if (setvalgpio < 0)
	{
		cout << WARNING << "OPERATION FAILED: Unable to set the value of GPIO" << ioPort << "." << ENDC << endl;
		return -1;
	}
	char val = '0';
	if(e)
	{
		val = '1';
	}
    setvalgpio << val;
    setvalgpio.close();
    return 0;
}

int GPIO::setup(unsigned int ioPort, string dir)
{
	for(unsigned int i = 0; i < openIOPorts.size(); i++)
	{
		if(ioPort == openIOPorts[i])
		{
			openIOPorts.erase(std::find(openIOPorts.begin(), openIOPorts.end(), ioPort));
		}
	}
	string exportStr = "/sys/class/gpio/export";
	ofstream exportgpio(exportStr.c_str());
    if (exportgpio < 0)
	{
        cout << WARNING << "OPERATION FAILED: Unable to export GPIO"<< ioPort << "." << ENDC << endl;
        return -1;
    }
    exportgpio << ioPort;
    exportgpio.close();
	openIOPorts.push_back(ioPort);

	string setdir_str ="/sys/class/gpio/gpio" + Utils::to_string(ioPort) + "/direction";
    ofstream setdirgpio(setdir_str.c_str());
    if (setdirgpio < 0)
	{
        cout << WARNING << "OPERATION FAILED: Unable to set direction of GPIO" << ioPort << "." << ENDC << endl;
        return -1;
    }
 
    setdirgpio << dir;
    setdirgpio.close();

	return 0;
}

string getDirection(unsigned int ioPort)
{
	string dir = "out";
	string setdir_str ="/sys/class/gpio/gpio" + Utils::to_string(ioPort) + "/direction";
    ifstream setdirgpio(setdir_str.c_str());
    if (setdirgpio < 0)
	{
        cout << WARNING << "OPERATION FAILED: Unable to set direction of GPIO" << ioPort << "." << ENDC << endl;
        return dir;
    }
 
    setdirgpio >> dir;
    setdirgpio.close();
	return dir;
}

int GPIO::cleanup()
{
	bool b = false;
	for(unsigned int i = 0; i < openIOPorts.size(); i++)
	{
		if(getDirection(openIOPorts[i]) == "out")
		{
			output(openIOPorts[i], false);
		}
		string unexport_str = "/sys/class/gpio/unexport";
		ofstream unexportgpio(unexport_str.c_str());
		if (unexportgpio < 0)
		{
			b = true;
			cout << WARNING << "OPERATION FAILED: Unable to unexport GPIO" << openIOPorts[i] << "." << ENDC << endl;
		}
		else
		{
			unexportgpio.write(Utils::to_string(openIOPorts[i]).c_str(), Utils::to_string(openIOPorts[i]).length());
		}

		unexportgpio.close();
	}
	openIOPorts.clear();
	if(b)
	{
		return -1;
	}
	return 0;
}

bool GPIO::getValue(unsigned int ioPort)
{
	string val = "";
	string getval_str = "/sys/class/gpio/gpio" + Utils::to_string(ioPort) + "/value";
	ifstream getvalgpio(getval_str.c_str());
	if (getvalgpio < 0)
	{
		cout << WARNING << "OPERATION FAILED: Unable to get value of GPIO" << ioPort << "." << ENDC << endl;
		return false;
	}
 
	getvalgpio >> val;
	getvalgpio.close();
	if(val[0] == '1')
	{
		return true;
	}
	return false;
}