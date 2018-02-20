// flipbyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool CheckInputNumber(const char* str, int& number);
uint8_t FlipByte(uint8_t x);

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

	// Считываем число и проверяем число ли это и принадлежит ли оно промежутку от 0 - 255
	int number;
	bool isInt = CheckInputNumber(argv[1], number);

	if (isInt)
	{
		uint8_t byte = static_cast<uint8_t>(number);
		int result = static_cast<int>(FlipByte(byte));
		fileOut << result << endl;
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
			cout << "Argument " << inputString << " is less then 0 or more than 255\n";
			return false;
		}
	}
	catch (const invalid_argument)
	{
		cout << "Argument \"" << inputString << " is not a number\n";
		return false;
	}
	catch (const out_of_range)
	{
		cout << "Argument \"" << inputString << " is not an int number\n";
		return false;
	}
	return true;
}

uint8_t FlipByte(uint8_t x)
{
	const int MAX_SHIFT = 7;
	uint8_t resultByte = 0;
	uint8_t maskBit = 1;
	int result = 0;

	for (int i = MAX_SHIFT; i >= 0; --i)
	{
		resultByte <<= 1;
		resultByte |= x & maskBit;
		//result = static_cast<int>(resultByte);
		x >>= 1;
		//cout << "result " << result << endl;
	}

	return resultByte;
}