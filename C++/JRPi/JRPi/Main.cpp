#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"

using namespace std;
 
int main(void)
{
	string line = "";
	int i = 0;
	vector<string> v;
	v.push_back("7");
	v.push_back("8");
	v.push_back("25");
	v.push_back("24");
	v.push_back("23");
	v.push_back("18");
	LCD lcd(v, 16, 2);
	while(line != "exit")
	{
		getline(cin, line);
		lcd.message("Test 1", 1);
		lcd.message("Test 2", 2);
		i++;
	}

    return 0;
}