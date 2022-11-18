#pragma once
#include <algorithm>
#include <string>
namespace dbf
{
	std::string toLower(const std::string& str);
	std::string toUpper(const std::string& str);
	bool compareIgnoreCase(const std::string& str1, const std::string& str2);
}