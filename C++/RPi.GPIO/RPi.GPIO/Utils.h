#ifndef UTILS_H
#define UTILS_H

#include <string>

const string HEADER = "\033[95m";
const string OKBLUE = "\033[94m";
const string OKGREEN = "\033[32m";
const string WARNING = "\033[93m";
const string FAIL = "\033[31m";
const string ENDC = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\33[36m";

using namespace std;

class Utils
{
	public:
		static string to_string(int i);
};

#endif