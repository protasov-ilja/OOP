// calculator_task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

int main()
{
	/*std::string commandLine;
	commandLine = "vas";
	std::vector<std::string> commands;
	boost::split(commands, commandLine, boost::is_any_of(" "));*/
	std::string name = "id1 * id2";
	std::vector<std::string> operators(4);
	boost::split(operators, name, boost::is_any_of(" "));
	std::cout << name << std::endl;
	for (size_t i = 0; i < operators.size(); ++i)
	{
		std::cout << operators[i] << std::endl;
	}

	/*std::string name;
	getline(std::cin, name);
	std::regex regex(R"(^([A-Ba-b_])([A-Za-z0-9_]+)?$)");
	std::smatch result;
	if (!std::regex_match(name, result, regex))
	{
		return 1;
	}

	if (result[1].str().empty()) {
		return 1;
	}

	std::cout << "Yes" << std::endl;*/
	return 0;
}
