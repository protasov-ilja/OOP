// flipbyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool CheckInputNumber(const char* str, int& number);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: flipbyte.exe <input byte>\n";
		return 1;
	}

	string outputName = "output.txt";
	ofstream fileOut(outputName);
	if (!fileOut.is_open())
	{
		cout << "Failed to open " << outputName << " for writing\n";
		return 1;
	}

	// Считываем число и проверяем число ли это и принадлежит ли оно промежутку от 0 - 255s
	int number;
	bool isInt = CheckInputNumber(argv[1], number);

	if (isInt)
	{
		// переводим его в байтовый формат
		uint8_t byte = static_cast<int>(number);
		// меняем местами 1 и последний биты в числе
	}

	return 0;
}

bool CheckInputNumber(const char* inputString, int& number)
{
	try
	{
		number = stoi(inputString);
		if ((number < 0) || (number > 255))
		{
			cout << "Argument " << inputString << " is less then 0 or more than 255\n.";
			return false;
		}
	}
	catch (const invalid_argument)
	{
		cout << "Argument \"" << inputString << " is not a number.\n";
		return false;
	}
	catch (const out_of_range)
	{
		cout << "Argument \"" << inputString << " is not an int number.\n";
		return false;
	}
	return true;
}
