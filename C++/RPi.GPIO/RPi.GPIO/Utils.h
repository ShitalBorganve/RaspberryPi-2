#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

/*Color (does not work)*/
const string HEADER = "\033[95m";
/*Color*/
const string OKBLUE = "\033[94m";
/*Color*/
const string OKGREEN = "\033[32m";
/*Color*/
const string WARNING = "\033[93m";
/*Color*/
const string FAIL = "\033[31m";
/*Ends the color so it doesn't bleed into other text*/
const string ENDC = "\033[0m";
/*Color (does not work)*/
const string BOLD = "\033[1m";
/*Color*/
const string CYAN = "\33[36m";
/*Color*/

class Utils
{
	public:
		/*
		 * Converts and int to a string value
		 */
		static string to_string(int i);
};

#endif