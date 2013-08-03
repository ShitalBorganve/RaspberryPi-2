#include <iostream>

using namespace std;

/*Compiles all of the demos*/
int main()
{
	cout << "Compiling LED_Demo" << endl;
	system("sudo g++ LED_Demo.cpp GPIO.h GPIO.cpp Utils.h Utils.cpp LCD.h LCD.cpp -o LED_Demo");
	cout << "Finished compiling LED_Demo" << endl;
	cout << "Compiling LCD_Demo" << endl;
	system("sudo g++ LCD_Demo.cpp GPIO.h GPIO.cpp Utils.h Utils.cpp LCD.h LCD.cpp -o LCD_Demo");
	cout << "Finished compiling LCD_Demo" << endl;
}