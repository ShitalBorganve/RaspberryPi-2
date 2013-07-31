#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"

using namespace std;
 
int main(void)
{
	/*GPIO* a = new GPIO("11");
	a->exportIO();
	a->setDir("out");
	string line = "";
	while(line != "exit")
	{
		//getline(cin, line);
		string val = "";
		a->getVal(val);
		a->setVal(val[0] == '1' ? "0" : "1");
		usleep(500 * 1000);
	}//*/
	vector<string> v;
	v.push_back("7");
	v.push_back("8");
	v.push_back("25");
	v.push_back("24");
	v.push_back("23");
	v.push_back("18");
	LCD lcd(v, 16, 2);
	lcd.init();
	lcd.message("abcdABCDefghEFGH", 0);
	lcd.message("1234'/><:=+LPI?[", 1);
	string line = "";
	while(line != "exit")
	{
		getline(cin, line);
	}
	lcd.clear();
	lcd.unExport();

    return 0;
}