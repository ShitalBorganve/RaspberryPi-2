#include "Utils.h"
#include <sstream>

string Utils::to_string(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}