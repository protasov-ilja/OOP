// task1var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CShapeController.h"
#include <fstream>

int main()
{
	std::fstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		std::cout << "faild open input.txt for reading" << std::endl;
		return 1;
	}

	CShapeController shapeControl(fileIn, std::cout);
	while (!fileIn.eof() && !fileIn.fail())
	{
		std::cout << "> ";
		if (!shapeControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}
