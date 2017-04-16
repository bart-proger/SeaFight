#include "string_utils.h"
#include <sstream>

std::vector<string> string_split(string s, char delim)
{
	std::vector<string> tokens;
	std::stringstream ss(s);
	string item;

	while (std::getline(ss, item, delim))
	{
		tokens.push_back(item);
	}

	return tokens;
}