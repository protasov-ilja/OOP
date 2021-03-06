// tv_task1var1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CTVSet.h"
#include "RemoteControl.h"

int main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}

