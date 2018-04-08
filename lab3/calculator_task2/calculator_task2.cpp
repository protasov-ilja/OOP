// calculator_task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <regex>
#include <string>
#include <iostream>

int main()
{
	std::string name;
	getline(std::cin, name);
	std::regex regex(R"(^([A-Za-z_])([A-Za-z0-9_]+)?)");
	std::smatch result;
	if (!std::regex_match(name, result, regex))
	{
		return 1;
	}

	if (result[1].str().empty()) {
		return 1;
	}

	std::cout << "Yes" << std::endl;
    return 0;
}

