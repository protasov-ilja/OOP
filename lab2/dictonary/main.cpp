// dictonary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: dictonary.exe <dictonary file>\n";
		return 1;
	}

	std::ifstream fileIn(argv[1]);
	if (fileIn.is_open())
	{
	}

	return 0;
}
