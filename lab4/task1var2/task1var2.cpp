// task1var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CShapeController.h"

int main()
{
	CShapeController shapeControl(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!shapeControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}
